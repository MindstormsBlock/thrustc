/*
 * Copyright MindstormsBlock 2021
 * 
 * This is the Thrust programming language official compiler source
 */

#include "app.h"

import Status;
import parser;

MAINRET MAIN(ARGC* argc, ARGV** argv) {

	[[unlikely]]
	if ((intp)argc < 1) {
		serr << strVal("Not enough arguments; filepath missing") << std::endl;
		return (intp)ThrustCompiler::Status::ERROR_NO_FILEPATH;
	}

	const charp* filePath = argv[1];

	ThrustCompiler::Status status = ThrustCompiler::tokenize(filePath);

	if (status != ThrustCompiler::Status::OK) {
		return (intp)status;
	}

	return (intp)ThrustCompiler::Status::OK;
}