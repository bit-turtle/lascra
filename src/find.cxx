// lascra find

#include "find.hxx"
#include "error.hxx"

std::string find_variable(bparser::node& sprite, std::string name) {
	bparser::node& variables = sprite.find("variables");
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i][0].value == name) return variables[i].value;
	}
	throw error("Variable does not exist");
}

std::string find_list(bparser::node& sprite, std::string name) {
	bparser::node& lists = sprite.find("lists");
	for (int i = 0; i < lists.size(); i++) {
		if (lists[i][0].value == name) return lists[i].value;
	}
	throw error("List does not exist");
}

std::string find_broadcast(bparser::node& sprite, std::string name) {
	bparser::node& broadcasts = sprite.find("broadcasts");
	for (int i = 0; i < broadcasts.size(); i++) {
		if (broadcasts[i][0].value == name) return broadcasts[i].value;
	}
	throw error("Broadcast does not exist");
}
