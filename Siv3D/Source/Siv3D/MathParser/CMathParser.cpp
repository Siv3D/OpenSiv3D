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

# include "CMathParser.hpp"

namespace s3d
{
	MathParser::CMathParser::CMathParser()
	{

	}

	MathParser::CMathParser::~CMathParser()
	{

	}

	const String& MathParser::CMathParser::getErrorMessage() const
	{
		return m_errorMessage;
	}

	void MathParser::CMathParser::setExpression(const String& expression)
	{
		m_errorMessage.clear();

		m_parser.SetExpr(expression.str());
	}

	bool MathParser::CMathParser::setConstant(const String& name, const double value)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineConst(name.str(), value);

			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return false;
		}
	}

	bool MathParser::CMathParser::setVaribale(const String& name, double* value)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineVar(name.str(), value);

			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return false;
		}
	}

	bool MathParser::CMathParser::setPrefixOperator(const String& name, Fty1 f)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefineInfixOprt(name.str(), f);

			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return false;
		}
	}

	bool MathParser::CMathParser::setPostfixOperator(const String& name, Fty1 f)
	{
		m_errorMessage.clear();

		try
		{
			m_parser.DefinePostfixOprt(name.str(), f);

			return true;
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return false;
		}
	}

	void MathParser::CMathParser::removeVariable(const String& name)
	{
		m_errorMessage.clear();

		m_parser.RemoveVar(name.str());
	}

	void MathParser::CMathParser::clear()
	{
		m_errorMessage.clear();

		m_parser.SetExpr(L"");

		m_parser.ClearConst();

		m_parser.ClearVar();

		m_parser.ClearFun();

		m_parser.ClearInfixOprt();

		m_parser.ClearPostfixOprt();

		m_parser.ClearOprt();
	}

	String MathParser::CMathParser::getExpression() const
	{
		return m_parser.GetExpr();
	}

	Optional<const std::map<std::wstring, double*>&> MathParser::CMathParser::getUsedVariables() const
	{
		m_errorMessage.clear();

		try
		{
			return m_parser.GetUsedVar();
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return none;
		}
	}

	Optional<const std::map<std::wstring, double*>&> MathParser::CMathParser::getVariables() const
	{
		m_errorMessage.clear();

		try
		{
			return m_parser.GetVar();
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return none;
		}
	}

	Optional<const std::map<std::wstring, double>&> MathParser::CMathParser::getConstants() const
	{
		m_errorMessage.clear();

		try
		{
			return m_parser.GetConst();
		}
		catch (mu::Parser::exception_type& e)
		{
			m_errorMessage = e.GetMsg();

			return none;
		}
	}

	String MathParser::CMathParser::validNameCharacters() const
	{
		return m_parser.ValidNameChars();
	}

	String MathParser::CMathParser::validPrefixCharacters() const
	{
		return m_parser.ValidInfixOprtChars();
	}

	String MathParser::CMathParser::validPostfixCharacters() const
	{
		return m_parser.ValidOprtChars();
	}

	Optional<double> MathParser::CMathParser::evalOpt() const
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

	Array<double> MathParser::CMathParser::evalArray() const
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

	void MathParser::CMathParser::eval(double* dst, const size_t count) const
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
