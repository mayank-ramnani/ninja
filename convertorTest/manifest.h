#pragma once

#include <string>
#include <unordered_map>
#include <vector>

// Forward declare the shadowdash namespace where rule and build2 are implemented
namespace shadowdash {


// Declare global functions for the manifest, such as let or bind
void let(const std::string& variable, const std::string& value);

std::pair<std::string, std::string> bind(const std::string& key, const std::string& value);

}  // namespace shadowdash
