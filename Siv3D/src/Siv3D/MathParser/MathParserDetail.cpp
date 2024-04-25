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

# include "MathParserDetail.hpp"
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	MathParser::MathParserDetail::MathParserDetail()
	{

	}

	MathParser::MathParserDetail::~MathParserDetail()
	{

	}

	String MathParser::MathParserDetail::getErrorMessage() const
	{
		return Unicode::FromWstring(m_errorMessage);
	}

	void MathParser::MathParserDetail::setExpression(const StringView expression)
	{
		m_errorMessage.clear();

		m_parser.SetExpr(expression.toWstr());
	}

	bool MathParser::MathParserDetail::setConstant(const StringView name, const double value)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineConst(name.toWstr(), value);
			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return false;
		}
	}

	bool MathParser::MathParserDetail::setVariable(const StringView name, double* value)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineVar(name.toWstr(), value);
			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return false;
		}
	}

	bool MathParser::MathParserDetail::setPrefixOperator(const StringView name, Fty1 f)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineInfixOprt(name.toWstr(), f);
			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return false;
		}
	}

	bool MathParser::MathParserDetail::setPostfixOperator(const StringView name, Fty1 f)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefinePostfixOprt(name.toWstr(), f);
			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return false;
		}
	}

	void MathParser::MathParserDetail::removeVariable(const StringView name)
	{
		m_errorMessage.clear();

		m_parser.RemoveVar(name.toWstr());
	}

	void MathParser::MathParserDetail::clear()
	{
		m_errorMessage.clear();

		m_parser.SetExpr(mu::string_type{});
		m_parser.ClearConst();
		m_parser.ClearVar();
		m_parser.ClearFun();
		m_parser.ClearInfixOprt();
		m_parser.ClearPostfixOprt();
		m_parser.ClearOprt();
	}

	String MathParser::MathParserDetail::getExpression() const
	{
		return Unicode::FromWstring(m_parser.GetExpr());
	}

	HashTable<String, double*> MathParser::MathParserDetail::getUsedVariables() const
	{
		m_errorMessage.clear();

		try
		{
			HashTable<String, double*> result;

			for (const auto& pair : m_parser.GetUsedVar())
			{
				result.emplace(Unicode::FromWstring(pair.first), pair.second);
			}

			return result;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return{};
		}
	}

	HashTable<String, double*> MathParser::MathParserDetail::getVariables() const
	{
		m_errorMessage.clear();

		try
		{
			HashTable<String, double*> result;

			for (const auto& pair : m_parser.GetVar())
			{
				result.emplace(Unicode::FromWstring(pair.first), pair.second);
			}

			return result;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return{};
		}
	}

	HashTable<String, double> MathParser::MathParserDetail::getConstants() const
	{
		m_errorMessage.clear();

		try
		{
			HashTable<String, double> result;

			for (const auto& pair : m_parser.GetConst())
			{
				result.emplace(Unicode::FromWstring(pair.first), pair.second);
			}

			return result;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return{};
		}
	}

	String MathParser::MathParserDetail::validNameCharacters() const
	{
		return Unicode::FromWstring(m_parser.ValidNameChars());
	}

	String MathParser::MathParserDetail::validPrefixCharacters() const
	{
		return Unicode::FromWstring(m_parser.ValidInfixOprtChars());
	}

	String MathParser::MathParserDetail::validPostfixCharacters() const
	{
		return Unicode::FromWstring(m_parser.ValidOprtChars());
	}

	Optional<double> MathParser::MathParserDetail::evalOpt() const
	{
		m_errorMessage.clear();

		try
		{
			return m_parser.Eval();
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
			return none;
		}
	}

	Array<double> MathParser::MathParserDetail::evalArray() const
	{
		m_errorMessage.clear();

		Array<double> result;

		try
		{
			int32 num_results;
			const double* v = m_parser.Eval(num_results);
			result.assign(v, v + num_results);
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();
		}

		return result;
	}

	void MathParser::MathParserDetail::eval(double* dst, const size_t count) const
	{
		m_errorMessage.clear();

		try
		{
			int32 num_results;

			const double* v = m_parser.Eval(num_results);

			size_t i = 0;

			for (; i < static_cast<size_t>(num_results); ++i)
			{
				dst[i] = v[i];
			}

			for (; i < count; ++i)
			{
				dst[i] = Math::NaN;
			}
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			for (size_t i = 0; i < count; ++i)
			{
				dst[i] = Math::NaN;
			}
		}
	}
}
