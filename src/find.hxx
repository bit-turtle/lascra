// variable, list, broadcast id finding

#include <string>
#include <bparser/node.hxx>

std::string find_variable(bparser::node& sprite, std::string name);
std::string find_list(bparser::node& sprite, std::string name);
std::string find_broadcast(bparser::node& sprite, std::string name);
