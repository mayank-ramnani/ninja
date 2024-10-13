#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

namespace shadowdash {

// Structure to store a Ninja rule
class Rule {
public:
    string name;
    string command;

    Rule(const string& name, const string& command)
        : name(name), command(command) {}
};

// Structure to store a build instruction
class Build {
public:
    string output;
    vector<string> inputs;
    string ruleName;
    unordered_map<string, string> bindings;

    Build(const string& output, const vector<string>& inputs, const string& ruleName, const unordered_map<string, string>& bindings = {})
        : output(output), inputs(inputs), ruleName(ruleName), bindings(bindings) {}
};

// NinjaConverter class to store parsed rules and builds
class NinjaConverter {
public:
    vector<Rule> rules;
    vector<Build> builds;

    // Add a rule
    void addRule(const string& name, const string& command) {
        rules.emplace_back(name, command);
    }

    // Add a build
    void addBuild(const string& output, const vector<string>& inputs, const string& ruleName, const unordered_map<string, string>& bindings = {}) {
        builds.emplace_back(output, inputs, ruleName, bindings);
    }

    // Generate the build.ninja.cc file
    void generateBuildNinjaCC(const string& filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Error creating build.ninja.cc file" << endl;
            return;
        }

        // Generate the C++ file with system() calls
        outFile << "#include <iostream>" << endl;
        outFile << "#include <cstdlib>" << endl;  // for system()
        outFile << "using namespace std;" << endl;
        outFile << "int main() {" << endl;

        // Write the build steps
        for (const auto& build : builds) {
            const auto& rule = getRuleByName(build.ruleName);

            // Replace placeholders ($in, $out) in the command
            string command = rule.command;
            size_t inPos = command.find("$in");
            if (inPos != string::npos) {
                string inputFiles;
                for (const auto& input : build.inputs) {
                    inputFiles += input + " ";
                }
                command.replace(inPos, 3, inputFiles);
            }

            size_t outPos = command.find("$out");
            if (outPos != string::npos) {
                command.replace(outPos, 4, build.output);
            }

            // Handle bindings (e.g., flags)
            for (const auto& binding : build.bindings) {
                size_t bindingPos = command.find(binding.first);
                if (bindingPos != string::npos) {
                    command.replace(bindingPos, binding.first.length(), binding.second);
                }
            }

            // Write the system command to the output file
            outFile << "    cout << \"Running: " << command << "\" << endl;" << endl;
            outFile << "    system(\"" << command << "\");" << endl;
        }

        outFile << "    return 0;" << endl;
        outFile << "}" << endl;

        outFile.close();
        cout << "Generated " << filename << " successfully." << endl;
    }

private:
    // Find a rule by its name
    const Rule& getRuleByName(const string& name) const {
        for (const auto& rule : rules) {
            if (rule.name == name) {
                return rule;
            }
        }
        throw runtime_error("Rule not found: " + name);
    }
};

// Global converter object
extern NinjaConverter converter;

// Define the `rule` type in the manifest
void rule(const string& name, const string& command) {
    converter.addRule(name, command);
}

// Define the `build2` function in the manifest
void build2(const vector<string>& outputs, const vector<string>& inputs, const string& ruleName, const unordered_map<string, string>& bindings = {}) {
    for (const auto& output : outputs) {
        converter.addBuild(output, inputs, ruleName, bindings);
    }
}

// Declare global converter object
NinjaConverter converter;

}  // namespace shadowdash
