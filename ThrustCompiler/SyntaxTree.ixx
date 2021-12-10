#include "app.h"

export module SyntaxTree;

namespace ThrustCompiler {

	export class ExpressionST {
	public:
		virtual ~ExpressionST() {}
	};

	export class NumberST : public ExpressionST {
	public:
		NumberST(float64 value) : value(value) {}

	private:
		float64 value;
	};

	export class VariableST : public ExpressionST {
	public:
		VariableST(const String16& name) : name(name) {}

	private:
		String16 name;
	};

	export class BinaryExpressionST : public ExpressionST {
	public:
		BinaryExpressionST(char16 op, ptr<ExpressionST> LHS, ExpressionST* RHS) : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

	private:
		char16 op;

		ptr<ExpressionST> LHS;
		ptr<ExpressionST> RHS;
	};

	export class CallExpressionST : public ExpressionST {
	public:
		CallExpressionST(const String16& callee, std::vector<ptr<ExpressionST>>&& argumentList)
			: callee(callee), argumentList(std::move(argumentList)) {}

	private:
		String16 callee;
		std::vector<ptr<ExpressionST>> argumentList;
	};

	export class FunctionPrototypeST {
	public:
		FunctionPrototypeST(const String16& name, std::vector<String16>&& argumentNames)
			: name(name), argumentNames(std::move(argumentNames)) {}

		const String16& getName() {
			return name;
		}
	private:
		String16 name;
		std::vector<String16> argumentNames;
	};

	export class FunctionST {
	public:
		FunctionST(ptr<FunctionPrototypeST> prototype, ptr<ExpressionST> body) : prototype(std::move(prototype)), body(std::move(body)) {}

	private:
		ptr<FunctionPrototypeST> prototype;
		ptr<ExpressionST> body;
	};
}