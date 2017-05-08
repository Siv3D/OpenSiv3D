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

# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	Array<String> String::split(const value_type ch) const
	{
		if (m_string.empty())
		{
			return{};
		}

		Array<String> result(1);

		const value_type* pSrc = m_string.data();
		const value_type* const pSrcEnd = pSrc + m_string.length();
		String* currentLine = &result.back();

		while (pSrc != pSrcEnd)
		{
			if (*pSrc == ch)
			{
				result.emplace_back();
				currentLine = &result.back();
			}
			else
			{
				currentLine->push_back(*pSrc);
			}

			++pSrc;
		}

		return result;
	}

	Array<String> String::split_lines() const
	{
		if (m_string.empty())
		{
			return{};
		}

		Array<String> result(1);

		const value_type* pSrc = m_string.data();
		const value_type* const pSrcEnd = pSrc + m_string.length();
		String* currentLine = &result.back();

		while (pSrc != pSrcEnd)
		{
			if (*pSrc == value_type('\n'))
			{
				result.emplace_back();
				currentLine = &result.back();
			}
			else if (*pSrc != value_type('\r'))
			{
				currentLine->push_back(*pSrc);
			}

			++pSrc;
		}

		return result;
	}
}
