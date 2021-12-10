#pragma once

#include "app.h"

#include "Token.h"
#include "SyntaxTree.h"

namespace ThrustCompiler {

	//extern TokenMap tokenMap;

	Status tokenize(const charp* filePath) noexcept;
}