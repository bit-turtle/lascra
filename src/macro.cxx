// lascra macro

#include "macro.hxx"

#include "id.hxx"
#include "block.hxx"
#include "error.hxx"
#include "find.hxx"

#include "code.hxx"
#include "parameter.hxx"

#include <bparser/node.hxx>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <iostream>

struct macro_def {
	std::vector<std::string> params;
	bparser::node* macro;
};
std::map<std::string, macro_def> macros;

struct param_def {
	macro_def* macro;
	std::vector<bparser::node*> params;
};
std::stack<param_def> params;

void end_macro() {
	if (params.empty())
		throw error("No active macros");
	params.pop();
}

void clear_macros() {
	macros.clear();
	while (!params.empty())
		params.pop();
}

void define_macro(bparser::node& code) {
	if (code.size() != 2)
		throw error("Expected exactly two arguments");
	macro_def& macro = macros[code[0].value];
	macro.macro = &code[1];
	for (int p = 0; p < code[0].size(); p++) {
		macro.params.push_back(code[0][p].value);
	}
}

bparser::node& macro(bparser::node& code) {
	if (code.size() == 0)
		throw error("Expected at least one parameter");
	if (code[0].size() != 0)
		throw error("Macro name should be a string");
	if (macros.find(code[0].value) == macros.end())
		throw error("Macro not found");
	macro_def& macro = macros[code[0].value];
	if (!params.empty()) {
		std::stack<param_def> paramcopy = params;
		while (!paramcopy.empty()) {
			if (paramcopy.top().macro == &macro)
				throw error("Cyclic macro detected (Compiling would really never finish...)");
			paramcopy.pop();
		}
	}
	if (code.size()-1 > macro.params.size())
		throw error("Incorrect number of parameters");
	params.push({&macro, {}});
	for (int p = 1; p <= macro.params.size(); p++) {
		params.top().params.push_back(&code[p]);
	}
	return *macro.macro;
}

bparser::node& macro_parameter(std::string key) {
	if (params.size() == 0)
		throw error("Not in a macro");
	int index = -1;
	while (++index < params.top().macro->params.size())
		if (params.top().macro->params[index] == key)
			break;
	if (index >= params.top().macro->params.size())  {
		std::ostringstream err;
		err << "Macro parameter does not exist: " << key << " (Expected: ";
		for (std::string& p : params.top().macro->params)
			err << p << " ";
		err << ")"; 
		throw error(err.str());
	}
	return *params.top().params.at(index);
}
