// declaration of id system
// Purpose:
// 1. Generate unique ids
// 2. Detect if a id was generated by lascra or if it was generated by scratch

#include <string>

namespace id {
	// Get an ID string
	std::string get(std::string type);
	// Test if an ID was generated by lascra
	bool test(std::string id);
}
