// lascra parameter system

/* Scratch Enums:
 * - Format: [number, params...]
 * - Numbers:
 *   - 3: Block ID // [3, "blockID_8923042", [10, "Default value"] ]
 *   - 4: Number // [1,[4, -620.33]]
 *   - 5: Positive number // [1,[5, 50.23]]
 *   - 6: Positive integer // [1,[6, 50]]
 *   - 7: Integer // [1,[7, -50]]
 *   - 8: Angle // [1,[8, 90]]
 *   - 9: Color // [1,[9, "#ffeedd"]]
 *   - 10: String // [1,[10, "Hello!"]]
 *   - 11: Broadcast // [11, "broadcastName", "broadcastID_89024"]
 *   - 12: Variable // [12, "VariableName", "VariableID_24890"]
 *   - 13: List // [13, "ListName", "ListID_2348902"]
*/

#include <bparser/node.hxx>
#include <string>

// Parameter function, returns a scratch enum
bparser::node& parameter_string(bparser::node& sprite, bparser::node& code, std::string parentid);
bparser::node& parameter_number(bparser::node& sprite, bparser::node& code, std::string parentid, bool posint = false);
