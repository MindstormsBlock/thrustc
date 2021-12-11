#include "app.h"

export module parser;

import Token;
import tokenizer;
import SyntaxTree;

namespace ThrustCompiler {

	String identifier = strVal("");
	float64 value = 0.0;

	ptr<NumberST> parseNumberExpression() {
		ptr<NumberST> numberExpression = std::make_unique<NumberST>(value);
		return numberExpression;
	}
}