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
# include <Siv3D/MathParser.hpp>
# include "../../ThirdParty/muparser/muParser.h"

namespace s3d
{
	class MathParser::CMathParser
	{
	private:

		mu::Parser m_parser;

		mutable std::wstring m_errorMessage;

	public:

		CMathParser();

		~CMathParser();

		String getErrorMessage() const;

		void setExpression(const String& expression);

		bool setConstant(const String& name, double value);

		bool setVaribale(const String& name, double* value);

		template <class Fty>
		bool setFunction(const String& name, Fty f)
		{
			m_errorMessage.clear();

			try
			{
				m_parser.DefineFun(name.toWstr(), f);

				return true;
			}
			catch (mu::Parser::exception_type& e)
			{
				m_errorMessage = e.GetMsg();

				return false;
			}
		}

		bool setPrefixOperator(const String& name, Fty1 f);

		bool setPostfixOperator(const String& name, Fty1 f);

		void removeVariable(const String& name);

		void clear();

		String getExpression() const;

		Optional<const std::map<std::wstring, double*>&> getUsedVariables() const;

		Optional<const std::map<std::wstring, double*>&> getVariables() const;

		Optional<const std::map<std::wstring, double>&> getConstants() const;

		String validNameCharacters() const;

		String validPrefixCharacters() const;

		String validPostfixCharacters() const;

		Optional<double> evalOpt() const;

		Array<double> evalArray() const;

		void eval(double* dst, size_t count) const;
	};
}
