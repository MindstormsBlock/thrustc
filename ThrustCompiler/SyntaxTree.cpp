#include "SyntaxTree.h"

namespace ThrustCompiler {

	ExpressionST::~ExpressionST() {}

	NumberST::NumberST(float64 value) : value(value) {}

	VariableST::VariableST(const String16& name) : name(name) {}

	BinaryExpressionST::BinaryExpressionST(char16 op, ExpressionST* LHS, ExpressionST* RHS) : op(op), LHS(LHS), RHS(RHS) {
		LHS = nullptr;
		RHS = nullptr;
	}

	BinaryExpressionST::~BinaryExpressionST() {
		delete LHS;
		delete RHS;
	}

	CallExpresionST::CallExpresionST(const String16& callee, std::vector<ExpressionST*>&& argumentList)
		: callee(callee), argumentList(std::move(argumentList)) {}

	CallExpresionST::~CallExpresionST() {
		for (sizep i = 0; i < argumentList.size(); i++) {
			delete argumentList[i];
		}
	}

	FunctionPrototypeST::FunctionPrototypeST(const String16& name, std::vector<String16>&& argumentNames)
		: name(name), argumentNames(std::move(argumentNames)) {}

	const String16& FunctionPrototypeST::getName() {
		return name;
	}

	FunctionST::FunctionST(FunctionPrototypeST* prototype, ExpressionST* body)
		: prototype(std::move(prototype)), body(std::move(body)) {
		prototype = nullptr;
		body = nullptr;
	}

	FunctionST::~FunctionST() {
		delete prototype;
		delete body;
	}
}