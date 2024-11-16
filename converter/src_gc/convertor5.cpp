#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <filesystem>

struct NinjaRule {
    std::string name;
    std::string command;
    std::string deps;
    std::string depfile;
    std::map<std::string, std::string> variables;
};

struct NinjaBuild {
    std::vector<std::string> outputs;
    std::vector<std::string> implicit_outputs;
    std::string rule;
    std::vector<std::string> inputs;
    std::vector<std::string> implicit_inputs;
    std::vector<std::string> order_only_inputs;
    std::map<std::string, std::string> variables;
};

struct NinjaPool {
    std::string name;
    int depth;
    std::string description;
};

class ZlibNinjaConverter {
private:
    std::map<std::string, NinjaRule> rules;
    std::vector<NinjaBuild> builds;
    std::vector<NinjaPool> pools;
    bool debug = true;

    void debugPrint(const std::string& message) {
        if (debug) {
            std::cout << "[DEBUG] " << message << std::endl;
        }
    }

    bool readBuildFile(const std::string& build_path) {
        std::ifstream file(build_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open build file: " << build_path << std::endl;
            return false;
        }

        std::string line;
        NinjaBuild* current_build = nullptr;
        int build_count = 0;

        while (std::getline(file, line)) {
            line = trimString(line);
            if (line.empty() || line[0] == '#') continue;

            if (line.substr(0, 5) == "pool ") {
                parsePool(line);
            }

            else if (line.substr(0, 6) == "build ") {
                build_count++;
                debugPrint("Processing build statement #" + std::to_string(build_count));
                
                auto build = parseBuildStatement(line);
                if (!build.outputs.empty()) {
                    builds.push_back(build);
                    current_build = &builds.back();
                }
            }
           else if (line[0] == ' ' && current_build != nullptr) {
                // Check if this line specifies a pool
                if (line.find("pool = ") != std::string::npos) {
                    std::string pool_name = trimString(line.substr(line.find("=") + 1));
                    debugPrint("Build uses pool: " + pool_name);
                }
                parseVariable(line, *current_build);
            }
        }

       // If no pools were found in ninja file, create default pools
        if (pools.empty()) {
            pools.push_back({"pool1", 1, "Default pool 1"});
            pools.push_back({"pool2", 1, "Default pool 2"});
            pools.push_back({"pool3", 1, "Default pool 3"});
        }

        debugPrint("Total build statements processed: " + std::to_string(build_count));
        debugPrint("Total pools found: " + std::to_string(pools.size()));
        return true;
    }

    void parsePool(const std::string& line) {
        std::regex pool_regex(R"(pool\s+(\w+))");
        std::smatch matches;
        if (std::regex_search(line, matches, pool_regex)) {
            NinjaPool pool;
            pool.name = matches[1];
            pool.depth = 1; // Default depth
            pools.push_back(pool);
            debugPrint("Found pool: " + pool.name);
        }
    }

    std::string trimString(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    NinjaBuild parseBuildStatement(const std::string& line) {
        NinjaBuild build;
        
        // Remove "build " prefix
        std::string content = line.substr(6);
        
        // Split into outputs and rule/inputs parts
        size_t colon_pos = content.find(':');
        if (colon_pos == std::string::npos) return build;
        
        // Parse outputs
        std::string outputs_str = content.substr(0, colon_pos);
        std::istringstream outputs_stream(outputs_str);
        std::string output;
        while (outputs_stream >> output) {
            if (output != "||") {
                build.outputs.push_back(output);
            }
        }
        
        // Parse rule and inputs
        std::string rule_inputs = content.substr(colon_pos + 1);
        std::istringstream rule_inputs_stream(trimString(rule_inputs));
        
        // First token is the rule
        rule_inputs_stream >> build.rule;
        
        // Rest are inputs
        std::string input;
        bool implicit = false;
        bool order_only = false;
        
        while (rule_inputs_stream >> input) {
            if (input == "|") {
                implicit = true;
                continue;
            }
            if (input == "||") {
                order_only = true;
                continue;
            }
            
            if (order_only) {
                build.order_only_inputs.push_back(input);
            } else if (implicit) {
                build.implicit_inputs.push_back(input);
            } else {
                build.inputs.push_back(input);
            }
        }
        
        return build;
    }

    void parseVariable(const std::string& line, NinjaBuild& build) {
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) return;
        
        std::string name = trimString(line.substr(0, eq_pos));
        std::string value = trimString(line.substr(eq_pos + 1));
        build.variables[name] = value;
    }

    std::string getRuleType(const std::string& ninja_rule) {
        if (ninja_rule == "phony") return "phony";
        if (ninja_rule.find("C_COMPILER") != std::string::npos) return "compile";
        if (ninja_rule.find("SHARED_LIBRARY_LINKER") != std::string::npos) return "link_shared";
        if (ninja_rule.find("STATIC_LIBRARY_LINKER") != std::string::npos) return "link_static";
        if (ninja_rule.find("EXECUTABLE_LINKER") != std::string::npos) return "link";
        if (ninja_rule.find("CUSTOM_COMMAND") != std::string::npos) return "custome_cmd";
        if (ninja_rule.find("RERUN_CMAKE") != std::string::npos) return "rerun_cmake";
        if (ninja_rule.find("CLEAN") != std::string::npos) return "clean";
        if (ninja_rule.find("HELP") != std::string::npos) return "help";
        return ninja_rule;
    }


    bool writeManifestFile(const std::string& output_path) {
        std::ofstream out(output_path);
        if (!out.is_open()) {
            std::cerr << "Failed to open output file: " << output_path << std::endl;
            return false;
        }

        // Write header
        out << "#include \"manifest.h\"\n\nmanifest() {\n";

        // Write compiler rules
        out << "\trule(\n\t\tcompile,\n";
        out << "\t\tbind(command, {\"clang\", \"-c\", \"in\"_v, \"-o\", \"out\"_v, \"-MD\", \"-MF\", \"depfile\"_v}),\n";
        out << "\t\tbind(depfile, {\"out\"_v, \".d\"}),\n";
        out << "\t\tbind(deps, {\"gcc\"})\n";
        out << "\t);\n\n";

        // Write shared library rule
        out << "\trule(\n\t\tlink_shared,\n";
        out << "\t\tbind(command, {\"g++\", \"-shared\", \"in\"_v, \"-o\", \"out\"_v})\n";
        out << "\t);\n\n";

        // Write link_exe rule
        out << "\trule(\n\t\tlink,\n";
        out << "\t\tbind(command, {\"g++\", \"in\"_v, \"-o\", \"out\"_v})\n";
        out << "\t);\n\n";

        // Write static library rule
        out << "\trule(\n\t\tlink_static,\n";
        out << "\t\tbind(command, {\"llvm-lib\", \"in\"_v, \"-out:out\"_v})\n";
        out << "\t);\n\n";

        // Write phony rule
        out << "\trule(\n\t\tphony,\n";
        out << "\t\tbind(command, {\"echo\", \"phony target\"})\n";
        out << "\t);\n\n";

        // Write build statements

        int build_counter = 1;
        std::vector<std::string> valid_rules = {"compile", "link", "link_shared", "link_static", "phony"};
        
        for (const auto& build : builds) {
            std::string rule_type = getRuleType(build.rule);
            
            // Check if rule_type is in the list of valid rules
            if (std::find(valid_rules.begin(), valid_rules.end(), rule_type) == valid_rules.end()) {
                continue;  // Skip this build statement if rule type is not in our list
            }
            
            out << "\tauto build" << build_counter << " = build(\n";
            out << "\t\tlist(";
            
            // Outputs
            for (size_t i = 0; i < build.outputs.size(); ++i) {
                if (i > 0) out << ", ";
                out << "str(\"" << build.outputs[i] << "\")";
            }
            
            out << "),\n\t\tlist(";
            
            // Implicit outputs
            for (size_t i = 0; i < build.implicit_outputs.size(); ++i) {
                if (i > 0) out << ", ";
                out << "str(\"" << build.implicit_outputs[i] << "\")";
            }
            
            out << "),\n\t\t" << rule_type << ",\n\t\tlist(";
            
            // Inputs
            for (size_t i = 0; i < build.inputs.size(); ++i) {
                if (i > 0) out << ", ";
                out << "str(\"" << build.inputs[i] << "\")";
            }
            
            out << "),\n\t\tlist(";
            
            // Implicit inputs
            for (size_t i = 0; i < build.implicit_inputs.size(); ++i) {
                if (i > 0) out << ", ";
                out << "str(\"" << build.implicit_inputs[i] << "\")";
            }
            
            out << "),\n\t\tlist(";
            
            // Order-only inputs
            for (size_t i = 0; i < build.order_only_inputs.size(); ++i) {
                if (i > 0) out << ", ";
                out << "str(\"" << build.order_only_inputs[i] << "\")";
            }
            
            out << "),\n";
            
            // Variables
            out << "\t\t{\n";
            bool first = true;
            for (const auto& [key, value] : build.variables) {
                if (!first) out << ",\n";
                out << "\t\t\tbind(" << key << ", {\"" << value << "\"})";
                first = false;
            }
            out << "\n\t\t}\n\t);\n\n";
            
            build_counter++; // Only increment counter for valid rule types
            debugPrint("Generated build statement for rule type: " + rule_type);
        }

            for (const auto& pool : pools) {
            out << "\tnew_pool(" << pool.name << ", " << pool.depth << "); // " 
                << pool.description << "\n";
        }
        out << "\n";

        // Write default targets
        out << "\tdefault(str(\"zlib.dll\"), str(\"zlibstatic.lib\"));\n\n";

        // Write ShadowDash return with all pools
        out << "\tShadowDash({";
        for (int i = 1; i < build_counter; i++) {
            if (i > 1) out << ", ";
            out << "build" << i;
        }
        out << "}, {";
        
        // Add all pools to ShadowDash
        for (size_t i = 0; i < pools.size(); ++i) {
            if (i > 0) out << ", ";
            out << pools[i].name;
        }
        out << "}, default_target);\n}\n\n";
    

        // // Write pools
        // out << "\tnew_pool(pool1, 1);\n";
        // out << "\tnew_pool(pool2, 1);\n";
        // out << "\tnew_pool(pool3, 1);\n\n";

        // // Write default targets
        // out << "\tdefault(str(\"zlib.dll\"), str(\"zlibstatic.lib\"));\n\n";

        // // Write ShadowDash return - include all three pools
        // out << "\tShadowDash({";
        // for (int i = 1; i < build_counter; i++) {
        //     if (i > 1) out << ", ";
        //     out << "build" << i;
        // }
        // out << "}, {pool1, pool2, pool3}, default_target);\n}\n\n";


        // Write main function
        out << "int main() {\n";
        out << "    manifest();\n";
        out << "    return 0;\n";
        out << "}\n";

        debugPrint("Finished writing manifest file");
        return true;
    }

public:
    bool convertFile(const std::string& build_path, const std::string& output_path) {
        debugPrint("Starting conversion...");
        
        if (!readBuildFile(build_path)) {
            std::cerr << "Failed to read build file" << std::endl;
            return false;
        }
        
        debugPrint("Successfully read build file with " + std::to_string(builds.size()) + " build statements");
        
        if (!writeManifestFile(output_path)) {
            std::cerr << "Failed to write manifest file" << std::endl;
            return false;
        }
        
        debugPrint("Conversion completed successfully");
        return true;
    }
};

int main() {
    const std::string build_path = "../testing/build.ninja";
    const std::string output_path = "../testing/manifest_result.cc";
    
    // Create testing directory if it doesn't exist
    std::filesystem::create_directories("../testing");
    
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Build path: " << std::filesystem::absolute(build_path) << std::endl;
    std::cout << "Output path: " << std::filesystem::absolute(output_path) << std::endl;
    
    ZlibNinjaConverter converter;
    if (!converter.convertFile(build_path, output_path)) {
        std::cerr << "Conversion failed!" << std::endl;
        return 1;
    }
    
    std::cout << "Conversion completed successfully!" << std::endl;
    return 0;
}