/*
 * Copyright MindstormsBlock 2021
 * 
 * This is the Thrust programming language official compiler source
 */
#include "app.h"

#include "parser.h"

#include "preprocessor.h"

MAINRET MAIN(ARGC* argc, ARGV** argv) {

	[[unlikely]]
	if ((intp)argc < 1) {
		sout << "Not enough arguments; filepath missing" << std::endl;
		return (intp)ThrustCompiler::Status::ERROR_NO_FILEPATH;
	}

	const charp* filePath = argv[1];

	ThrustCompiler::Status status = ThrustCompiler::tokenize(filePath);

	if (status != ThrustCompiler::Status::OK) {
		return (intp)status;
	}

	/*if ((int)argc > 1) {
		const char* filePath = argv[1];

		std::wstring fileContents;
		std::wstring fileLine;

		std::wifstream inputFile("test.txt");

		while (inputFile.good()) {
			std::getline(inputFile, fileLine);
			fileContents.append(fileLine);
			fileContents.append(L"\r\n");
		}
		
		Status pre = preprocess(fileContents);

		return 0;
	}
	else {
		std::cout << "Not enough arguments" << std::endl;

		return -1;
	}*/

	return (intp)ThrustCompiler::Status::OK;
}