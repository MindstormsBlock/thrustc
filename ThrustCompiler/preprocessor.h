#pragma once

#include "app.h"

#include <string>

namespace ThrustCompiler {

	enum class Command {
		COPY = 0, IF, ELSE, ELIF, ENDIF, DEF
	};

	Status preprocess(std::wstring& fileContents);
}