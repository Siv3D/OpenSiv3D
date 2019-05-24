//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "HashTable.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	class MathParser
	{
	private:

		class MathParserDetail;

		std::shared_ptr<MathParserDetail> pImpl;

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

		[[nodiscard]] String getErrorMessage() const;

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

		[[nodiscard]] String getExpression() const;

		[[nodiscard]] HashTable<String, double*> getUsedVariables() const;

		[[nodiscard]] HashTable<String, double*> getVariables() const;

		[[nodiscard]] HashTable<String, double> getConstants() const;

		// function, variable, constant
		// "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		[[nodiscard]] String validNameCharacters() const;

		// prefix
		// "/+-*^?<>=#!$%&|~'_"
		[[nodiscard]] String validPrefixCharacters() const;

		// postfix
		// "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*^/?<>=#!$%&|~'_"
		[[nodiscard]] String validPostfixCharacters() const;

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

	[[nodiscard]] double Eval(const String& expression);

	[[nodiscard]] Optional<double> EvalOpt(const String& expression);
}
