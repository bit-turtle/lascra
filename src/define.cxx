// lascra define

#include "define.hxx"
#include <sstream>
#include <stdexcept>

#include "id.hxx"
#include "error.hxx"

void variable(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1 && code.size() != 2) {
		throw error("Wrong number of parameters (Expected 1 or 2)");
	}
	bparser::node* var = new bparser::node(id::get(code[0].value));
	var->emplace(code[0].value).string = true;
	if (code.size() == 2) {

		var->emplace(code[1].value);
	}
	else {
		var->emplace("0");
	}
  // Global Flag
  if (code.value == "global_variable") var->emplace("global");
	// Add variable
	sprite.find("variables").push(var);
}

void list(bparser::node& sprite, bparser::node& code) {
	if (code.size() < 1) {
		throw error("Wrong number of parameters (Expected at least 1)");
	}
	bparser::node* list = new bparser::node(id::get(code[0].value));
	list->emplace(code[0].value).string = true;
	bparser::node* arr = new bparser::node("");
	for (int i = 1; i < code.size(); i++) {
		arr->emplace(code[i].value);
	}
  // Global Flag
  if (code.value == "global_list") list->emplace("global");
	// Add list
	if (arr->size() == 1) list->emplace("").push(arr);
	else list->push(arr);
	sprite.find("lists").push(list);
}
void broadcast(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) {
		throw error("Wrong number of parameters (Expected 1)");
	}
	sprite.find("broadcasts").emplace(id::get(code[0].value)).emplace(code[0].value);
}

void define(bparser::node& sprite, bparser::node& code) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i].value == "#") continue;
    try {
      if (code[i].value == "variable" || code[i].value == "global_variable")
        variable(sprite, code[i]);
      else if (code[i].value == "list" || code[i].value == "global_list")
        list(sprite,code[i]);
      else if (code[i].value == "broadcast")
        broadcast(sprite,code[i]);
      else throw error("Invalid type");
    }
    catch (std::exception& e) { throw error(i, code[i].value, e); }
	}
}
