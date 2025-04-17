// lascra checknum

#include "checknum.hxx"
#include <sstream>

// Make sure it is a valid number
bool checknum(std::string& num, bool positive, bool integer) {
	std::istringstream nstr(num);
	bool decimal = false;
	bool first = true;
	bool zerofirst = false;
	char c;
	while (nstr.get(c)) {
		switch (c) {
			case '-':
				if (positive) return false;
				if (!first) return false;
				first = true;
				break;
			case '.':
				if (integer) return false;
				if (decimal) return false;
				decimal = true;
				first = false;
				zerofirst = false;
				break;
			case '0':
				if (zerofirst) return false;
				if (first) zerofirst = true;
				first = false;
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (zerofirst) return false;
				first = false;
				break;
			default:
				return false;
		}
	}
	return true;
}
