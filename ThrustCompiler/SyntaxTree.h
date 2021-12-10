#pragma once

#include "app.h"

namespace ThrustCompiler {

	class ExpressionST {
	public:
		virtual ~ExpressionST();
	};

	class NumberST : public ExpressionST {
	public:
		NumberST(float64 value);
		NumberST() = delete;

	private:
		float64 value;
	};

	class VariableST : public ExpressionST {
	public:
		VariableST(const String16& name);
		VariableST() = delete;

	private:
		String16 name;
	};

	class BinaryExpressionST : public ExpressionST {
	public:
		BinaryExpressionST(char16 op, ExpressionST* LHS, ExpressionST* RHS);
		BinaryExpressionST() = delete;

		~BinaryExpressionST();

	private:
		char16 op;

		ExpressionST* LHS;
		ExpressionST* RHS;
	};

	class CallExpresionST : public ExpressionST {
	public:
		CallExpresionST(const String16& callee, std::vector<ExpressionST*>&& argumentList);

		~CallExpresionST();

	private:
		String16 callee;
		std::vector<ExpressionST*> argumentList;
	};

	class FunctionPrototypeST {
	public:
		FunctionPrototypeST(const String16& name, std::vector<String16>&& argumentNames);

		const String16& getName();
	private:
		String16 name;
		std::vector<String16> argumentNames;
	};

	class FunctionST {
	public:
		FunctionST(FunctionPrototypeST* prototype, ExpressionST* body);

		~FunctionST();

	private:
		FunctionPrototypeST* prototype;
		ExpressionST* body;
	};
}