// lascra code

#include "code.hxx"
#include "error.hxx"
#include "block.hxx"
#include "id.hxx"
#include "parameter.hxx"

std::string say(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("say");
	bparser::node& say = block(id, "looks_say", false);
	say.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "MESSAGE";
	sprite.find("blocks").push(&say);
	return id;
}

std::string code(bparser::node& sprite, bparser::node& code) {
	std::string id;
	try {
		if (code.value == "say") return say(sprite, code);
		else throw error("Unknown command");
	}
	catch (std::exception e) {
		throw error(code.value, e);
	}
}
