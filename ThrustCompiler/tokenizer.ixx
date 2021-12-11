/*
 * Module file for tokenizer
 * 
 */

#include "app.h"

export module tokenizer;

import Token;
import Value;

//Container types
#pragma region containerTypes

using TokenMap = std::map<const ThrustCompiler::Token, ThrustCompiler::Value>;

#pragma endregion

namespace ThrustCompiler {

	export TokenMap tokenMap;

	/// <summary>
	/// Generates a (token, value) pair for an input string, for examle '+' generates (<code>Token::OPERATOR, Value::PLUS</code>) - NYI
	/// </summary>
	/// 
	/// <param name="tokenString"></param>
	/// <returns>The (token, value) pair</returns>
	static Token getToken(const String& tokenString);

	/// <summary>
	/// Tokenizes an entire file, pushes a (token, value) pair into <code>tokenList</code>
	/// </summary>
	/// 
	/// <param name="filePath">Filepath to the file</param>
	/// <returns>A status code</returns>
	export Status tokenize(const charp* filePath) noexcept {
		try {
			IFStream fileStream(filePath);
			fileStream.exceptions(IFStream::failbit | IFStream::badbit);

			while (fileStream.good()) {
				String tokenString;
				fileStream >> tokenString;

				Value v(strVal("nice 69"));

				tokenMap.emplace(getToken(std::move(tokenString)), v);
			}
		}
		catch (std::exception e) {
			sout << "Error while tokenizing: " << e.what() << std::endl;
			return Status::ERROR_TOKENIZER;
		}
		catch (...) {
			sout << "Unknown error while tokenizing" << std::endl;
			return Status::ERROR_TOKENIZER;
		}

		return Status::OK;
	}

	static Token getToken(const String& tokenString) {
		charp tokenChar = tokenString[0];

		if (tokenString == strVal("var")) {
			return Token::TVAR;
		}
		else if (tokenString == strVal("print")) {
			return Token::TPRINT;
		}
		else if (tokenString == strVal("=")) {
			return Token::TASSIGN;
		}
		else if (std::isalpha(tokenChar) || tokenChar == charVal('_')) {
			return Token::TIDENTIFIER;
		}
		else if (std::isdigit(tokenChar)) {
			return Token::TF64VAL;
		}
		else {
			throw std::exception("invalid token");
		}
	}
}