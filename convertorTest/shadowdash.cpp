#include "manifest.h"
#include "build2.h"
#include <iostream>
#include <cstdlib> // For system() function

using namespace shadowdash;

void manifest() {
    rule("compile", "g++ -O3 -c $in -o $out");
    rule("link", "g++ $in -o $out");

    // Define build steps
    build2({"hello.o"}, {"hello.cc"}, "compile", {{"flags", "-O2"}});
    build2({"hello"}, {"hello.o"}, "link");
}

int main() {
    std::cout << "Program started." << std::endl;

    // Call the manifest function
    manifest();

    // Generate the build.ninja.cc file from the parsed manifest
    converter.generateBuildNinjaCC("build.ninja.cc");

    std::cout << "Program finished successfully." << std::endl;
    return 0;
}
