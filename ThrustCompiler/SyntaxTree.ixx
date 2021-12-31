#include "app.h"

#include <vector>

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
		VariableST(const String& name) : name(name) {}

	private:
		String name;
	};

	export class BinaryExpressionST : public ExpressionST {
	public:
		BinaryExpressionST(charp op, ptr<ExpressionST> LHS, ExpressionST* RHS) : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

	private:
		charp op;

		ptr<ExpressionST> LHS;
		ptr<ExpressionST> RHS;
	};

	export class CallExpressionST : public ExpressionST {
	public:
		CallExpressionST(const String& callee, std::vector<ptr<ExpressionST>>&& argumentList)
			: callee(callee), argumentList(std::move(argumentList)) {}

	private:
		String callee;
		std::vector<ptr<ExpressionST>> argumentList;
	};

	export class FunctionPrototypeST {
	public:
		FunctionPrototypeST(const String& name, std::vector<String>&& argumentNames)
			: name(name), argumentNames(std::move(argumentNames)) {}

		const String& getName() {
			return name;
		}
	private:
		String name;
		std::vector<String> argumentNames;
	};

	export class FunctionST {
	public:
		FunctionST(ptr<FunctionPrototypeST> prototype, ptr<ExpressionST> body) : prototype(std::move(prototype)), body(std::move(body)) {}

	private:
		ptr<FunctionPrototypeST> prototype;
		ptr<ExpressionST> body;
	};
}