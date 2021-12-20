/*
 * Copyright MindstormsBlock 2021
 * 
 * This is the Thrust programming language official compiler source
 */

#include "app.h"

import Status;
import tokenizer;
import parser;

namespace ThrustCompiler {
	struct Setup {
		const charp* filePath;
	} setup;

	Status parseArgs(intp* argc, charp** argv) {

		[[unlikely]]
		if ((intp)argc < 2) {
			serr << strVal("Not enough arguments; filepath missing") << std::endl;
			return Status::ERROR_NO_FILEPATH;
		}

		setup.filePath = argv[1];
		
		return Status::OK;
	}

	void printTokenMap() {
		for (auto& [k, v] : tokenMap) {
			sout << k << strVal(", ") << v << std::endl;
		}
	}
}

using ThrustCompiler::Status;
using ThrustCompiler::parseArgs;
using ThrustCompiler::tokenize;
using ThrustCompiler::setup;
using ThrustCompiler::printTokenMap;

MAINRET MAIN(ARGC* argc, ARGV** argv) {

	Status status = parseArgs((intp*)argc, argv);

	if (status != Status::OK) {
		return (intp)status;
	}

	status = tokenize(setup.filePath);

	if (status != Status::OK) {
		return (intp)status;
	}

	printTokenMap();

	return (intp)Status::OK;
}