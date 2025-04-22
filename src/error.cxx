// lascra error system

#include "error.hxx"
#include <sstream>
#include <iostream>

std::runtime_error error(std::string error) {
	std::cout << "Error: " << error << std::endl;
	return std::runtime_error(error);
}

std::runtime_error error(int num, std::exception& previous) {
	std::ostringstream err;
	err << num << previous.what();
	return std::runtime_error(err.str());
}
std::runtime_error error(std::string tag, std::exception& previous) {
	std::cout << "- " << tag << std::endl;
	std::ostringstream err;
	err << "[" << tag << "]:" << previous.what();
	return std::runtime_error(err.str());
}
std::runtime_error error(int num, std::string tag, std::string error) {
	std::cout << "Error: " << error << std::endl;
	std::cout << "- " << tag << std::endl;
	std::ostringstream err;
	err << num << "[" << tag << "]:" << error;
	return std::runtime_error(err.str());
}

std::runtime_error error(int num, std::string tag, std::exception& previous) {
	std::cout << "- " << tag << std::endl;
	std::ostringstream err;
	err << num << "[" << tag << "]:" << previous.what();
	return std::runtime_error(err.str());
}
