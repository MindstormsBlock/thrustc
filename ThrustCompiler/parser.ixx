#include "app.h"

export module parser;

import Token;
import Status;

import tokenizer;

import SyntaxTree;

namespace ThrustCompiler {

	String identifier = strVal("");
	float64 value = 0.0;

	static ptr<ExpressionST> parseNumberExpression() noexcept;

	export Status parse() noexcept {
		sizep size = tokenPairVector.size();

		for (sizep i = 0; i < size; i++) {

		}

		return Status::OK;
	}

	static ptr<ExpressionST> parseNumberExpression() noexcept {
		ptr<NumberST> numberExpression = std::make_unique<NumberST>(value);
		return numberExpression;
	}

	static ptr<ExpressionST> parseParenthesesExpression() noexcept {
		return nullptr; // TODO
	}
}