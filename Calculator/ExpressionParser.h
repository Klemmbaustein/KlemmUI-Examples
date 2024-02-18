#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace ExpressionParser
{
	typedef double NumberType;

	enum class ExpressionOperation
	{
		Add,
		Subtract,
		Multiply,
		Divide,
		Pow,
		None
	};

	extern std::unordered_map<std::string, ExpressionOperation> Operators;
	
	struct ExpressionNode
	{
		std::string Value;
		ExpressionOperation Operation = ExpressionOperation::None;

		std::vector<ExpressionNode> Children;

		NumberType Evaluate() const;

		std::string ToString() const;
	};

	ExpressionNode Parse(const std::string& Expression);
}
