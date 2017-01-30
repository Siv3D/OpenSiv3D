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

# pragma once
# include <memory>
# include <map>
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	class MathParser
	{
	private:

		class CMathParser;

		std::shared_ptr<CMathParser> pImpl;

		using Fty0	= double(*)();
		using Fty1	= double(*)(double);
		using Fty2	= double(*)(double, double);
		using Fty3	= double(*)(double, double, double);
		using Fty4	= double(*)(double, double, double, double);
		using Fty5	= double(*)(double, double, double, double, double);
		using Fty6	= double(*)(double, double, double, double, double, double);
		using Fty7	= double(*)(double, double, double, double, double, double, double);
		using Fty8	= double(*)(double, double, double, double, double, double, double, double);
		using Fty9	= double(*)(double, double, double, double, double, double, double, double, double);
		using Fty10	= double(*)(double, double, double, double, double, double, double, double, double, double);

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MathParser();

		explicit MathParser(const String& expression);

		const String& getErrorMessage() const;

		void setExpression(const String& expression);

		bool setConstant(const String& name, double value);

		bool setVaribale(const String& name, double* value);

		bool setFunction(const String& name, Fty0 f);

		bool setFunction(const String& name, Fty1 f);

		bool setFunction(const String& name, Fty2 f);

		bool setFunction(const String& name, Fty3 f);

		bool setFunction(const String& name, Fty4 f);

		bool setFunction(const String& name, Fty5 f);

		bool setFunction(const String& name, Fty6 f);

		bool setFunction(const String& name, Fty7 f);

		bool setFunction(const String& name, Fty8 f);

		bool setFunction(const String& name, Fty9 f);

		bool setFunction(const String& name, Fty10 f);

		bool setPrefixOperator(const String& name, Fty1 f);

		bool setPostfixOperator(const String& name, Fty1 f);

		void removeVariable(const String& name);

		void clear();

		String getExpression() const;

		Optional<const std::map<std::wstring, double*>&> getUsedVariables() const;

		Optional<const std::map<std::wstring, double*>&> getVariables() const;

		Optional<const std::map<std::wstring, double>&> getConstants() const;

		// function, variable, constant
		// "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		String validNameCharacters() const;

		// prefix
		// "/+-*^?<>=#!$%&|~'_"
		String validPrefixCharacters() const;

		// postfix
		// "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*^/?<>=#!$%&|~'_"
		String validPostfixCharacters() const;

		Optional<double> evalOpt() const;

		double evalOr(double defaultValue = Math::NaN) const;

		double eval() const;

		Array<double> evalArray() const;

		Vec2 evalVec2() const;

		Vec3 evalVec3() const;

		Vec4 evalVec4() const;

		ColorF evalColorF() const;

		HSV evalHSV() const;
	};

	inline double Eval(const String& expression)
	{
		return MathParser(expression).eval();
	}

	inline Optional<double> EvalOpt(const String& expression)
	{
		return MathParser(expression).evalOpt();
	}
}
