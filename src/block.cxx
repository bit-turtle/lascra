// lascra blocks

#include "block.hxx"

bparser::node& block(std::string id, std::string opcode, bool shadow) {
	bparser::node& block = *(new bparser::node(id));
	block.emplace("opcode").emplace(opcode);
	block.emplace("next").emplace("null");
	block.emplace("parent").emplace("null");
	block.emplace("inputs");
	block.emplace("fields");
	block.emplace("shadow").emplace(shadow ? "true" : "false");
	block.emplace("topLevel").emplace("true");
	return block;
}

void next(bparser::node& block, std::string id) {
	block.find("next")[0].value = id;
}

void parent(bparser::node& block, std::string id) {
	block.find("parent")[0].value = id;
	block.find("topLevel")[0].value = "false";
}
