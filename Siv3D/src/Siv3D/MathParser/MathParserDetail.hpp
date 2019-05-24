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
# include <Siv3D/MathParser.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4310)
# include <muparser/muParser.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	class MathParser::MathParserDetail
	{
	private:

		mu::Parser m_parser;

		mutable std::wstring m_errorMessage;

	public:

		MathParserDetail();

		~MathParserDetail();

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

		HashTable<String, double*> getUsedVariables() const;

		HashTable<String, double*> getVariables() const;

		HashTable<String, double> getConstants() const;

		String validNameCharacters() const;

		String validPrefixCharacters() const;

		String validPostfixCharacters() const;

		Optional<double> evalOpt() const;

		Array<double> evalArray() const;

		void eval(double* dst, size_t count) const;
	};
}
