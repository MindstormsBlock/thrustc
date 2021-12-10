#include "preprocessor.h"

#include <iostream>
#include <regex>
#include <cwctype>
#include <queue>
#include <vector>

namespace ThrustCompiler {

	static std::queue<Command> commands;
	static std::vector<std::string> definitions;

	Status preprocess(std::wstring& fileContents) {
		std::wregex reg(L"(#@[A-Za-z]+)");
		std::wsregex_iterator current(fileContents.begin(), fileContents.end(), reg);
		std::wsregex_iterator last;
		while (current != last) {
			std::wsmatch match = *current;
			std::wstring matchStr = match.str();

			std::transform(matchStr.begin(), matchStr.end(), matchStr.begin(), std::towlower);
			if (matchStr == L"#@copy") {
				commands.push(std::move(Command::COPY));
			}
			else if (matchStr == L"#@define") {
				commands.push(std::move(Command::DEF));
			}
			else {
				std::wcout << L"Invalid preprocessor statement: " << matchStr << std::endl;
			}

			current++;
		}

		while (!commands.empty()) {
			Command command = commands.front();
			std::wstring output;

			switch (command) {
			case Command::COPY:
				output = L"copying";
				break;
			case Command::DEF:
				output = L"defined";
				break;
			default:
				output = L"Error while handling command stack";
			}
			std::wcout << output << std::endl;

			commands.pop();
		}

		return Status::OK;
	}
}