// lascra compiler implementation
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "compiler.hxx"

#include "declare.hxx"

void compile(bparser::node& sprite, bparser::node& code) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i].value == "declare") {
			try {
				declare(sprite, code[i]);
			}
			catch (std::exception e) {
				std::ostringstream error;
				error << i << "[declare]:" << e.what();
				throw std::runtime_error(error.str());
			}
		}
		else {
			std::ostringstream error;
			error << " node " << i << ": " << "Unknown keyword \"" << code[i].value << "\"";
			throw std::runtime_error(error.str());
		}
	}
}
