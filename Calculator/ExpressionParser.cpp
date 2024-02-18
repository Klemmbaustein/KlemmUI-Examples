#include "ExpressionParser.h"
#include <iostream>
#include <limits>

std::unordered_map<std::string, ExpressionParser::ExpressionOperation> ExpressionParser::Operators = 
{
	{ "+", ExpressionOperation::Add },
	{ "-", ExpressionOperation::Subtract },
	{ "*", ExpressionOperation::Multiply },
	{ "/", ExpressionOperation::Divide },
	{ "^", ExpressionOperation::Pow}
};

const static ExpressionParser::NumberType NaN = std::numeric_limits<ExpressionParser::NumberType>::quiet_NaN();

ExpressionParser::NumberType ExpressionParser::ExpressionNode::Evaluate() const
{
	NumberType Val = NaN;

	if (Operation == ExpressionOperation::None)
	{
		if (Children.size())
		{
			return Children[0].Evaluate();
		}
		if (Value.empty())
		{
			return 0;
		}
		return std::stod(Value);
	}

	for (const ExpressionNode& Node : Children)
	{
		if (std::isnan(Val))
		{
			Val = Node.Evaluate();
			continue;
		}
		switch (Operation)
		{
		case ExpressionOperation::Add:
			Val += Node.Evaluate();
			break;
		case ExpressionOperation::Subtract:
			Val -= Node.Evaluate();
			break;
		case ExpressionOperation::Multiply:
			Val *= Node.Evaluate();
			break;
		case ExpressionOperation::Divide:
			Val /= Node.Evaluate();
			break;
		case ExpressionOperation::Pow:
			Val = pow(Val, Node.Evaluate());
			break;
		default:
			break;
		}
	}

	return Val;
}

std::string ExpressionParser::ExpressionNode::ToString() const
{
	std::string Str;
	if (Operation != ExpressionOperation::None)
	{
		Str = " (";
	}
	else
	{
		Str.append(" ");
	}
	for (const std::pair op : Operators)
	{
		if (op.second == Operation)
		{
			Str.append(op.first);
			break;
		}
	}

	Str.append(Value);

	for (const ExpressionNode& Node : Children)
	{
		Str.append(Node.ToString());
	}

	if (Operation != ExpressionOperation::None)
	{
		Str.append(") ");
	}

	return Str;
}

ExpressionParser::ExpressionNode ExpressionParser::Parse(const std::string& Expression)
{
	ExpressionNode Root;
	ExpressionNode* Current = &Root;

	for (size_t i = 0; i < Expression.size(); i++)
	{
		const char c = Expression[i];

		if (c < 0 || c > 128)
		{
			return ExpressionNode();
		}

		if (std::isdigit(c) || (c == '-' && i + 1 < Expression.size() && std::isdigit(Expression[i + 1])))
		{
			std::string ValueString = { c };
			while (Expression.size() > i && (std::isdigit(Expression[i + 1]) || Expression[i + 1] == '.'))
			{
				ValueString.push_back(Expression[++i]);
			}
			ExpressionNode New;
			New.Value = ValueString;
			New.Operation = ExpressionOperation::None;
			Current->Children.push_back(New);
			continue;
		}

		if (Operators.contains({ c }))
		{
			if (Current->Operation != ExpressionOperation::None)
			{
				ExpressionNode New;

				if (Current->Children.empty())
				{
				}
				else
				{
					New.Children.push_back(*Current);
					Current->Value.clear();
					Current->Children.clear();
				}
				New.Operation = Operators[{ c }];
				*Current = New;

				continue;
			}

			Root.Operation = Operators[{ c }];
			continue;
		}

		switch (c)
		{
		case ' ':
		case '\t':
			break;
		default:
			break;
		}
	}

	return Root;
}
