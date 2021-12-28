#include "app.h"

export module Setup;

import Status;

namespace ThrustCompiler {

	export struct Setup {
		const charp* filePath;
		const std::locale UTF8Locale;

		Setup() : UTF8Locale(std::locale(".utf8")) {}
	};

	export Setup setup;
}