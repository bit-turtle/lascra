// lascra "macro" keyword

// Creates a macro parameter that can be used as a parameter

#include <bparser/node.hxx>
#include <string>

void end_macro();
void clear_macros();
void define_macro(bparser::node& params);
bparser::node& macro(bparser::node& code);
bparser::node& macro_parameter(std::string key);
