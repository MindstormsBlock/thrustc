/*
 * Holds values for returning from functions
 * DO NOT USE REGULAR NUMBERS
 */

#include "app.h"

export module Status;

namespace ThrustCompiler {


	/// <summary>
	/// Enum class for status codes
	/// 
	/// ALWAYS check against error codes (for example by <code>if (status != Status::OK) return status;</code>, where status contains a status code)
	/// </summary>
	export enum class Status {
		OK = 0, ERROR_NO_FILEPATH, ERROR_BAD_FILE, ERROR_TOKENIZER, ERROR_PREPROCESSOR
	};

	/// <summary>
	/// Cast a Status code to intp
	/// </summary>
	export intp operator!(Status status) {
		return (intp)status;
	}
}