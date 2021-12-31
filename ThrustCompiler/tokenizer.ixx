/*
 * Module file for tokenizer
 * 
 */

#include "app.h"

#include <vector>

#include <optional>

export module tokenizer;

import Token;
import Status;
import Setup;

import string;

//Container types
#pragma region containerTypes

using ThrustCompiler::Token;

using TokenPair = std::pair<Token, String>;

using TokenPairVector = std::vector<TokenPair>;

#pragma endregion

namespace ThrustCompiler {

	/// <summary>
	/// Vector containing (token, token string) pairs
	/// </summary>
	export TokenPairVector tokenPairVector;

	/// <summary>
	/// Filestream functions use to read from source files
	/// </summary>
	static IFStream fileStream;

	/// <summary>
	/// Generates a token for the token string, for example '+' generates <code>Token::TOPERATOR</code>
	/// </summary>
	/// 
	/// <param name="tokenString">The token string to generate a token for</param>
	/// <returns>The token from the string</returns>
	static Token getToken(const String& tokenString) noexcept;

	/// <summary>
	/// Gets 1 token string from a file stream
	/// </summary>
	/// 
	/// <returns>An optional containing the token string if a read was succesful, otherwise is empty</returns>
	static const std::optional<String> getTokenString() noexcept;

	/// <summary>
	/// Pushes 1 character
	/// </summary>
	/// <param name="tokenString"></param>
	/// <param name="token"></param>
	/// <returns></returns>
	static void pushBackMarkedCharTokenPair(const String& tokenString, const Token token) noexcept;

	/// <summary>
	/// Generates a (token, token string) pair and emplaces it back into tokenPairVector
	/// </summary>
	/// 
	/// <returns>A status code</returns>
	static Status pushBackTokenPair() noexcept;

	/// <summary>
	/// Tokenizes an entire file
	/// 
	/// After execution, tokenPairVector vector contains (token, token string) pairs
	/// </summary>
	/// 
	/// <param name="filePath">File path to the file</param>
	/// <returns>A status code</returns>
	export Status tokenize(const charp* filePath) noexcept {
		try {
			Status status;

			fileStream = IFStream(filePath);
			fileStream.imbue(setup.UTF8Locale);
			fileStream.exceptions(IFStream::failbit | IFStream::badbit);

			while (fileStream.good()) {
				status = pushBackTokenPair();

				if (status != Status::OK) {
					return status;
				}
			}

			return status;
		}
		catch (std::exception e) {
			sout << strVal("Error while tokenizing: ") << e.what() << std::endl;
			return Status::ERROR_BAD_FILE;
		}
	}

	static Status pushBackTokenPair() noexcept {
		const std::optional<String>& optionalTokenString = getTokenString();
		if (!optionalTokenString.has_value()) {
			return Status::ERROR_BAD_FILE;
		}

		String tokenString = optionalTokenString.value();
		
		if (tokenString[0] == charVal('(')) {
			tokenString.erase(0, 1);
			const String value(1, charVal('('));
			pushBackMarkedCharTokenPair(std::move(value), Token::TLPAREN);
		}

		const sizep lastI = tokenString.size() - 1;
		if (tokenString[lastI] == charVal(')')) {
			tokenString.erase(lastI);
			const String value(1, charVal(')'));
			pushBackMarkedCharTokenPair(std::move(value), Token::TRPAREN);
		}
		else if (tokenString[lastI] == charVal(',')) {
			tokenString.erase(lastI);
			const String value(1, charVal(','));
			pushBackMarkedCharTokenPair(std::move(value), Token::TCOMMA);
		}

		const String tokenStringCopy = tokenString;

		const Token token = getToken(std::move(tokenString));

		if (token == Token::TNONE) {
			sout << strVal("Invalid token while parsing: ") << tokenStringCopy << std::endl;
			return Status::ERROR_TOKENIZER;
		}

		tokenPairVector.emplace_back(token, std::move(tokenStringCopy));

		return Status::OK;
	}

	static void pushBackMarkedCharTokenPair(const String& tokenString, const Token token) noexcept {
		tokenPairVector.emplace_back(token, std::move(tokenString));
	}

	static const std::optional<String> getTokenString() noexcept {
		try {
			String tokenString;
			fileStream >> tokenString;

			return std::optional(tokenString);
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
		const charp& tokenChar = tokenString[0];

		if (tokenString == strVal("var")) {
			return Token::TVAR;
		}
		else if (tokenString == strVal("print")) {
			return Token::TPRINT;
		}
		else if (tokenString == strVal("=")) {
			return Token::TASSIGN;
		}
		else if (isAlpha(tokenChar) || tokenChar == charVal('_')) {
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