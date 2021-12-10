#include "parser.h"

namespace ThrustCompiler {

	//TokenMap tokenList;
	
	/*std::wostream operator<<(std::wostream wos, TokenStringList tsl) {

	}*/

	std::vector<Token> tokenList;

	static Token getToken(String tokenString) {
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

	Status tokenize(const charp* filePath) noexcept {
#if _DEBUG
		if (filePath == nullptr) {
			return Status::ERROR_NO_FILEPATH;
		}
#endif
		Token token = Token::TNONE;
		String identifier = strVal("");
		float64 value = 0.0;
		bool acceptingVal = false;

		try {
			IFStream fileStream(filePath);
			fileStream.exceptions(IFStream::failbit | IFStream::badbit);

			while (fileStream.good()) {
				String tokenString;
				fileStream >> tokenString;

				tokenList.push_back(std::move(getToken(tokenString)));

				//std::wcout << tokenString << std::endl;
				//tokenList.push_back(std::move(tokenString));
			}

			/*for (sizep i = 0; i < tokenList.size(); i++) {
				std::wcout << tokenList[i] << ", ";
			}
			std::wcout << std::endl;*/
		}
		catch (std::exception e) {
			sout << "Error while tokenizing: " << e.what() << std::endl;
			return Status::ERROR_TOKENIZER;
		}
		catch (...) {
			sout << "Error while tokenizing" << std::endl;
			return Status::ERROR_TOKENIZER;
		}

		return Status::OK;
	}
}