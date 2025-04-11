// lascra block creation

#include <string>
#include <bparser/node.hxx>

bparser::node& block(std::string id, std::string opcode, bool topLevel = true, bool shadow = false);

void next(bparser::node& block, std::string id);

void parent(bparser::node& block, std::string id);
