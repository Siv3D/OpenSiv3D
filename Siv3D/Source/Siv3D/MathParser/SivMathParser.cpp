//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MathParser.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include "CMathParser.hpp"

namespace s3d
{
	MathParser::MathParser()
		: pImpl(std::make_shared<CMathParser>())
	{

	}

	MathParser::MathParser(const String& expression)
		: MathParser()
	{
		setExpression(expression);
	}

	const String& MathParser::getErrorMessage() const
	{
		return pImpl->getErrorMessage();
	}

	void MathParser::setExpression(const String& expression)
	{
		pImpl->setExpression(expression);
	}

	bool MathParser::setConstant(const String& name, const double value)
	{
		return pImpl->setConstant(name, value);
	}

	bool MathParser::setVaribale(const String& name, double* value)
	{
		return pImpl->setVaribale(name, value);
	}

	bool MathParser::setFunction(const String& name, Fty0 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty1 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty2 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty3 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty4 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty5 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty6 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty7 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty8 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty9 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setFunction(const String& name, Fty10 f)
	{
		return pImpl->setFunction(name, f);
	}

	bool MathParser::setPrefixOperator(const String& name, Fty1 f)
	{
		return pImpl->setPrefixOperator(name, f);
	}

	bool MathParser::setPostfixOperator(const String& name, Fty1 f)
	{
		return pImpl->setPostfixOperator(name, f);
	}

	void MathParser::removeVariable(const String& name)
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

	Optional<const std::map<std::wstring, double*>&> MathParser::getUsedVariables() const
	{
		return pImpl->getUsedVariables();
	}

	Optional<const std::map<std::wstring, double*>&> MathParser::getVariables() const
	{
		return pImpl->getVariables();
	}

	Optional<const std::map<std::wstring, double>&> MathParser::getConstants() const
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

		pImpl->eval(&xy.x, 2);

		return xy;
	}

	Vec3 MathParser::evalVec3() const
	{
		Vec3 xyz;

		pImpl->eval(&xyz.x, 3);

		return xyz;
	}

	Vec4 MathParser::evalVec4() const
	{
		Vec4 xyzw;

		pImpl->eval(&xyzw.x, 4);

		return xyzw;
	}

	ColorF MathParser::evalColorF() const
	{
		ColorF rgba;

		pImpl->eval(&rgba.r, 4);

		return rgba;
	}

	HSV MathParser::evalHSV() const
	{
		HSV hsva;

		pImpl->eval(&hsva.h, 4);

		return hsva;
	}
}
