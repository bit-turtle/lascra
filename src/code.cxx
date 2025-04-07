// lascra code

#include "code.hxx"
#include "error.hxx"
#include "block.hxx"
#include "id.hxx"

std::string say(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("say");
	bparser::node& say = block(id, "looks_say", false);
	bparser::node& message = say.find("inputs").emplace("MESSAGE");
	message.emplace("1");
	bparser::node& inner = message.emplace("");
	inner.emplace("10");
	inner.emplace(code[0].value);
	sprite.find("blocks").push(&say);
	return id;
}

std::string code(bparser::node& sprite, bparser::node& code) {
	std::string id;
	if (code.value == "say") return say(sprite, code);
	throw error("Unknown command");
}
