// lascra error system

#include "error.hxx"
#include <sstream>

std::runtime_error error(std::string error) {
	return std::runtime_error(error);
}

std::runtime_error error(std::string error, std::exception& previous) {
	std::ostringstream err;
	err << error << previous.what();
	return std::runtime_error(err.str());
}
std::runtime_error error(int num, std::string tag, std::string error) {
	std::ostringstream err;
	err << num << "[" << tag << "]:" << error;
	return std::runtime_error(err.str());
}

std::runtime_error error(int num, std::string tag, std::exception& previous) {
	std::ostringstream err;
	err << num << "[" << tag << "]:" << previous.what();
	return std::runtime_error(err.str());
}
