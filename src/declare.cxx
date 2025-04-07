#include "declare.hxx"
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "checknum.hxx"
#include "error.hxx"

void declaration(bparser::node& sprite, bparser::node& code) {
	// Delare sprite name
	if (code.value == "name") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		sprite.find("name")[0].value = code[0].value;
	}
	else if (code.value == "x") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("x")[0].value = code[0].value;
	}
	else if (code.value == "y") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("y")[0].value = code[0].value;
	}
	else if (code.value == "size") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("size")[0].value = code[0].value;
	}
	else if (code.value == "direction") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("direction")[0].value = code[0].value;
	}
	else if (code.value == "volume") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("volume")[0].value = code[0].value;
	}
	else if (code.value == "visible") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "true" && code[0].value != "false") {
			throw error("Invalid value (Expected \"true\" or \"false\")");
		}
		sprite.find("visible")[0].value = code[0].value;
	}
	else if (code.value == "draggable") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "true" && code[0].value != "false") {
			throw error("Invalid value (Expected \"true\" or \"false\")");
		}
		sprite.find("draggable")[0].value = code[0].value;
	}
	else if (code.value == "rotationStyle") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "all around" && code[0].value != "left-right" && code[0].value != "don't rotate") {
			throw error("Invalid value (Expected \"all around\", \"left-right\", or \"don't rotate\")");
		}
		sprite.find("rotationStyle")[0].value = code[0].value;
	}
	else {
		throw error("Unknown declaration");
	}
}

void declare(bparser::node& sprite, bparser::node& code) {
	for (int i = 0; i < code.size(); i++) {
		try {
			declaration(sprite, code[i]);
		}
		catch (std::exception e) {
			throw error(i, code[i].value, e);
		}
	}
}

