#pragma once

#include "type.h"

namespace ThrustCompiler {

	enum class Status {
		OK = 0, ERROR_NO_FILEPATH, ERROR_TOKENIZER, ERROR_PREPROCESSOR
	};
}