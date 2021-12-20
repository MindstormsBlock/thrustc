/*
 * Module file for tokenizer
 * 
 */

#include "app.h"

#include <optional>

export module tokenizer;

import Token;
import Status;
import Value;

//Container types
#pragma region containerTypes

using TokenMap = std::map<const ThrustCompiler::Token, ThrustCompiler::Value>;

#pragma endregion

namespace ThrustCompiler {

	export TokenMap tokenMap;

	/// <summary>
	/// Generates a token for the token string, for examle '+' generates <code>Token::OPERATOR</code>
	/// </summary>
	/// 
	/// <param name="tokenString">The token string to generate a token for</param>
	/// <returns>The (token, value) pair</returns>
	static Token getToken(const String& tokenString) noexcept;

	/// <summary>
	/// Gets a token string from a file stream
	/// </summary>
	/// 
	/// <param name="fileStream">File stream to read from</param>
	/// <returns>An optional containing the token string if a read was succesful, otherwise is empty</returns>
	static std::optional<String> readFile(IFStream& fileStream) noexcept;

	/// <summary>
	/// Tokenizes an entire file, pushes a (token, value) pair into <code>tokenMap</code>
	/// </summary>
	/// 
	/// <param name="filePath">File Path to the file</param>
	/// <returns>A status code</returns>
	export Status tokenize(const charp* filePath) noexcept {
		IFStream fileStream(filePath);
		fileStream.exceptions(IFStream::failbit | IFStream::badbit);

		std::optional<String> opt = readFile(fileStream);
		String tokenString = opt.value();

		if (!opt.has_value()) {
			return Status::ERROR_BAD_FILE;
		}

		Value v(strVal("nice 69"));

		Token token = getToken(std::move(tokenString));

		if (token == Token::TNONE) {
			sout << strVal("Invalid token while parsing: ") << std::endl;
			return Status::ERROR_TOKENIZER;
		}

		tokenMap.emplace(token, v);

		return Status::OK;
	}

	static std::optional<String> readFile(IFStream& fileStream) noexcept {
		try {
			while (fileStream.good()) {
				String tokenString;
				fileStream >> tokenString;

				return std::optional(tokenString);
			}
		}
		catch (std::exception e) {
			sout << strVal("Error while tokenizing: ") << e.what() << std::endl;
			return std::nullopt;
		}
		catch (...) {
			sout << strVal("Unknown error while tokenizing") << std::endl;
			return std::nullopt;
		}
	}

	static Token getToken(const String& tokenString) noexcept {
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
			return Token::TNONE;
		}
	}
}