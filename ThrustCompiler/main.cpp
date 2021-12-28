/*
 * Copyright MindstormsBlock 2021
 * 
 * This is the Thrust programming language official compiler source
 */

#include "app.h"

#include <io.h>
#include <fcntl.h>

import Status;
import Setup;

import tokenizer;
import parser;


namespace ThrustCompiler {

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
		for (auto& [k, v] : tokenPairVector) {
			sout << k << strVal(", ") << v << std::endl;
		}
	}

	void outputFile() {
		OFStream fileStream(strVal("tests\\test.out"));
		fileStream.imbue(setup.UTF8Locale);

		try {
			fileStream.exceptions(OFStream::failbit | OFStream::badbit);

			for (auto& [k, v] : tokenPairVector) {
				fileStream << k << strVal(", ") << v << "\r\n";
			}
		}
		catch (std::exception e) {
			sout << e.what() << std::endl;
		}
	}
}

using ThrustCompiler::Status;
using ThrustCompiler::parseArgs;
using ThrustCompiler::tokenize;
using ThrustCompiler::setup;
using ThrustCompiler::printTokenMap;
using ThrustCompiler::outputFile;

MAINRET MAIN(ARGC* argc, ARGV** argv) {

	std::setlocale(LC_ALL, setup.UTF8Locale.name().c_str());
	//sout.imbue(setup.UTF8Locale); // - redundant

	Status status = parseArgs((intp*)argc, argv);

	if (status != Status::OK) {
		return !status;
	}

	status = tokenize(setup.filePath);

	if (status != Status::OK) {
		return !status;
	}

	printTokenMap();
	//outputFile();

	return !Status::OK;
}