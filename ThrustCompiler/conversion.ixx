#include "type.h"

//#include <ctype.h>
//#include <cwctype>
#include <locale>
export module conversion;

import Setup;

namespace ThrustCompiler {

	export bool isAlpha(const charp value) {
		return std::isalpha(value, setup.UTF8Locale);
	}

#ifdef _WIN32

	export bool isAlpha(const charp* value) {
		return std::iswalpha(*value);
	}

	export bool isAlpha(charp* value) {
		return std::iswalpha(*value);
	}

	export bool isAlpha(const charp& value) {
		return std::iswalpha((uint16)value);
	}

	export bool isAlpha(charp& value) {
		return std::iswalpha((uint16)value);
	}

	export bool isAlpha(const charp* value) {
		return std::isalpha((uint8)value);
	}

	export bool isAlpha(charp* value) {
		return std::isalpha((uint8)value);
	}

	export bool isAlpha(const charp& value) {
		return std::isalpha((uint8)value);
	}

	export bool isAlpha(charp& value) {
		return std::isalpha((uint8)value);
	}

#endif
}