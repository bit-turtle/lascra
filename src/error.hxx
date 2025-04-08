// lascra error system

#include <stdexcept>
#include <string>

std::runtime_error error(std::string error);
std::runtime_error error(int num, std::string tag, std::string error);
// Merge errors
std::runtime_error error(int num, std::exception& previous);
std::runtime_error error(std::string error, std::exception& previous);
std::runtime_error error(int num, std::string tag, std::exception& previous);
