#include "id.hxx"
#include <sstream>

unsigned nextid = 0;

std::string prefix = "ls_";

std::string id::get(std::string type) {
	std::ostringstream id;
	id << prefix << type << "_" << ++nextid;
	return id.str();
}

bool id::test(std::string id) {
	if (id.substr(0,prefix.length()) == prefix) return true;
	return false;
}
