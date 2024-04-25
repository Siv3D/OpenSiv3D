//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MathParser.hpp>
# include "MathParserDetail.hpp"

namespace s3d
{
	MathParser::MathParser()
		: pImpl{ std::make_shared<MathParserDetail>() }
	{

	}

	MathParser::MathParser(const StringView expression)
		: MathParser{}
	{
		if (not expression)
		{
			return;
		}

		setExpression(expression);
	}

	String MathParser::getErrorMessage() const
	{
		return pImpl->getErrorMessage();
	}

	void MathParser::setExpression(const StringView expression)
	{
		pImpl->setExpression(expression);
	}

	bool MathParser::setConstant(const StringView name, const double value)
	{
		return pImpl->setConstant(name, value);
	}

	bool MathParser::setVariable(const StringView name, double* value)
	{
		return pImpl->setVariable(name, value);
	}

	bool MathParser::setFunction(const StringView name, Fty0 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty1 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty2 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty3 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty4 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty5 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty6 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty7 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty8 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty9 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const StringView name, Fty10 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setPrefixOperator(const StringView name, Fty1 f)
	{
		return pImpl->setPrefixOperator(name, f);
	}

	bool MathParser::setPostfixOperator(const StringView name, Fty1 f)
	{
		return pImpl->setPostfixOperator(name, f);
	}

	void MathParser::removeVariable(const StringView name)
	{
		pImpl->removeVariable(name);
	}

	void MathParser::clear()
	{
		pImpl->clear();
	}

	String MathParser::getExpression() const
	{
		return pImpl->getExpression();
	}

	HashTable<String, double*> MathParser::getUsedVariables() const
	{
		return pImpl->getUsedVariables();
	}

	HashTable<String, double*> MathParser::getVariables() const
	{
		return pImpl->getVariables();
	}

	HashTable<String, double> MathParser::getConstants() const
	{
		return pImpl->getConstants();
	}

	String MathParser::validNameCharacters() const
	{
		return pImpl->validNameCharacters();
	}

	String MathParser::validPrefixCharacters() const
	{
		return pImpl->validPrefixCharacters();
	}

	String MathParser::validPostfixCharacters() const
	{
		return pImpl->validPostfixCharacters();
	}

	Optional<double> MathParser::evalOpt() const
	{
		return pImpl->evalOpt();
	}

	double MathParser::evalOr(const double defaultValue) const
	{
		return evalOpt().value_or(defaultValue);
	}

	double MathParser::eval() const
	{
		return evalOr(Math::NaN);
	}

	Array<double> MathParser::evalArray() const
	{
		return pImpl->evalArray();
	}

	Vec2 MathParser::evalVec2() const
	{
		Vec2 xy;

		pImpl->eval(xy.getPointer(), 2);

		return xy;
	}

	Vec3 MathParser::evalVec3() const
	{
		Vec3 xyz;

		pImpl->eval(xyz.getPointer(), 3);

		return xyz;
	}

	Vec4 MathParser::evalVec4() const
	{
		Vec4 xyzw;

		pImpl->eval(xyzw.getPointer(), 4);

		return xyzw;
	}

	ColorF MathParser::evalColorF() const
	{
		ColorF rgba;

		pImpl->eval(rgba.getPointer(), 4);

		return rgba;
	}

	HSV MathParser::evalHSV() const
	{
		HSV hsva;

		pImpl->eval(&hsva.h, 4);

		return hsva;
	}

	double Eval(const StringView expression)
	{
		if (not expression)
		{
			return Math::NaN;
		}

		return MathParser{ expression }.eval();
	}

	Optional<double> EvalOpt(const StringView expression)
	{
		if (not expression)
		{
			return none;
		}

		return MathParser{ expression }.evalOpt();
	}
}
