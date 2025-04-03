#include "id.hxx"
#include <sstream>

unsigned nextid = 0;
std::string id::get(std::string type) {
	std::ostringstream id;
	id << type << ++nextid;
	return id.str();
}
