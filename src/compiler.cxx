// lascra compiler implementation
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "compiler.hxx"
#include "error.hxx"

#include "declare.hxx"
#include "define.hxx"
#include "when.hxx"

#include "procedure.hxx"

void compile(bparser::node& sprite, bparser::node& code) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i].value == "#") continue;
		if (code[i].value == "declare") {
			try {
				declare(sprite, code[i]);
			}
			catch (std::exception& e) {
				throw error(i, "declare", e);
			}
		}
		else if (code[i].value == "define") {
			try {
				define(sprite, code[i]);
			}
			catch (std::exception& e) {
				throw error(i, "define", e);
			}
		}
		else if (code[i].value == "when") {
			try {
				when(sprite, code[i]);
			}
			catch (std::exception& e) {
				throw error(i, "when", e);
			}
		}
		else if (code[i].value == "procedure") {
			try {
				procedure(sprite, code[i]);
			}
			catch (std::exception& e) {
				throw error(i, "procedure", e);
			}
		}
		else {
			throw error(i, code[i].value, "Unknown Keyword");
		}
	}
}
