//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "String.hpp"
# include "HashTable.hpp"
# include "Optional.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"

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

		SIV3D_NODISCARD_CXX20
		MathParser();

		SIV3D_NODISCARD_CXX20
		explicit MathParser(StringView expression);

		[[nodiscard]]
		String getErrorMessage() const;

		void setExpression(StringView expression);

		bool setConstant(StringView name, double value);

		bool setVaribale(StringView name, double* value);

		bool setFunction(StringView name, Fty0 f);

		bool setFunction(StringView name, Fty1 f);

		bool setFunction(StringView name, Fty2 f);

		bool setFunction(StringView name, Fty3 f);

		bool setFunction(StringView name, Fty4 f);

		bool setFunction(StringView name, Fty5 f);

		bool setFunction(StringView name, Fty6 f);

		bool setFunction(StringView name, Fty7 f);

		bool setFunction(StringView name, Fty8 f);

		bool setFunction(StringView name, Fty9 f);

		bool setFunction(StringView name, Fty10 f);

		bool setPrefixOperator(StringView name, Fty1 f);

		bool setPostfixOperator(StringView name, Fty1 f);

		void removeVariable(StringView name);

		void clear();

		[[nodiscard]]
		String getExpression() const;

		[[nodiscard]]
		HashTable<String, double*> getUsedVariables() const;

		[[nodiscard]]
		HashTable<String, double*> getVariables() const;

		[[nodiscard]]
		HashTable<String, double> getConstants() const;

		// function, variable, constant
		// "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		[[nodiscard]]
		String validNameCharacters() const;

		// prefix
		// "/+-*^?<>=#!$%&|~'_"
		[[nodiscard]]
		String validPrefixCharacters() const;

		// postfix
		// "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*^/?<>=#!$%&|~'_"
		[[nodiscard]]
		String validPostfixCharacters() const;

		[[nodiscard]]
		Optional<double> evalOpt() const;

		[[nodiscard]]
		double evalOr(double defaultValue = Math::NaN) const;

		[[nodiscard]]
		double eval() const;

		[[nodiscard]]
		Array<double> evalArray() const;

		[[nodiscard]]
		Vec2 evalVec2() const;

		[[nodiscard]]
		Vec3 evalVec3() const;

		[[nodiscard]]
		Vec4 evalVec4() const;

		[[nodiscard]]
		ColorF evalColorF() const;

		[[nodiscard]]
		HSV evalHSV() const;
	};

	[[nodiscard]]
	double Eval(StringView expression);

	[[nodiscard]]
	Optional<double> EvalOpt(StringView expression);
}
