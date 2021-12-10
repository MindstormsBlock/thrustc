/*
 * Hold values for returning from functions
 * DO NOT USE REGULAR NUMBERS
 */

export module Status;

namespace ThrustCompiler {

	export enum class Status {
		OK = 0, ERROR_NO_FILEPATH, ERROR_TOKENIZER, ERROR_PREPROCESSOR
	};
}