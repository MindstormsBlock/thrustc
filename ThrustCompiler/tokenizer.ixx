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

using ThrustCompiler::Token;

using TokenPairVector = std::vector<std::pair<Token, String>>;

#pragma endregion

namespace ThrustCompiler {

	export TokenPairVector tokenPairVector;

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
	/// <param name="fileStream">File stream to read from</param>
	/// <returns>An optional containing the token string if a read was succesful, otherwise is empty</returns>
	static std::optional<String> getTokenString(IFStream& fileStream) noexcept;

	/// <summary>
	/// Generates a (token, token string) pair in the tokenValuePair parameter
	/// </summary>
	/// 
	/// <param name="fileStream">File stream to read from</param>
	/// <param name="tokenValuePair">Pair to insetr values to</param>
	/// <returns>A status code</returns>
	static Status getTokenValuePair(IFStream& fileStream, std::pair<Token, String>& tokenValuePair) noexcept;

	/// <summary>
	/// Pushes back a (token, token string) pair into tokenPairVector
	/// </summary>
	/// 
	/// <param name="fileStream">File stream to read from</param>
	/// <returns>A status code</returns>
	static Status pushBackTokenPair(IFStream& fileStream) noexcept;

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
			IFStream fileStream(filePath);
			fileStream.exceptions(IFStream::failbit | IFStream::badbit);

			while (fileStream.good()) {
				Status status = pushBackTokenPair(fileStream);

				if (status != Status::OK) {
					return status;
				}
			}
		}
		catch (std::exception e) {
			sout << strVal("Error while tokenizing: ") << e.what() << std::endl;
			return Status::ERROR_BAD_FILE;
		}

		return Status::OK;
	}

	static Status pushBackTokenPair(IFStream& fileStream) noexcept {
		std::pair<Token, String> tokenValuePair;

		Status status = getTokenValuePair(fileStream, tokenValuePair);
		if (status != Status::OK) {
			return status;
		}

		tokenPairVector.push_back(std::move(tokenValuePair));

		return Status::OK;
	}

	static Status getTokenValuePair(IFStream& fileStream, std::pair<Token, String>& tokenValuePair) noexcept {
		std::optional<String> optionalTokenString = getTokenString(fileStream);
		if (!optionalTokenString.has_value()) {
			return Status::ERROR_BAD_FILE;
		}

		String tokenString = optionalTokenString.value();
		String tokenStringCopy = tokenString;

		Token token = getToken(std::move(tokenString));

		if (token == Token::TNONE) {
			sout << strVal("Invalid token while parsing: ") << tokenStringCopy << std::endl;
			return Status::ERROR_TOKENIZER;
		}

		tokenValuePair = std::make_pair(token, std::move(tokenStringCopy));

		return Status::OK;
	}

	static std::optional<String> getTokenString(IFStream& fileStream) noexcept {
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