// lascra checknum

#include "checknum.hxx"
#include <sstream>

// Make sure it is a valid number
bool checknum(std::string& num) {
	std::istringstream nstr(num);
	bool decimal = false;
	bool first = true;
	char c;
	while (nstr.get(c)) {
		switch (c) {
			case '-':
				if (!first) return false;
				first = true;
			case '.':
				if (decimal) return false;
				decimal = true;
				first = false;
				break;
			case '0':
				if (first) return false;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				first = false;
				break;
			default:
				return false;
		}
	}
	return true;
}
