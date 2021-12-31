#include "type.h"

//#include <ctype.h>
//#include <cwctype>
#include <locale>

export module string;

import Setup;

namespace ThrustCompiler {

	export bool isAlpha(const charp& value) {
		return std::isalpha(value, setup.UTF8Locale);
	}
}