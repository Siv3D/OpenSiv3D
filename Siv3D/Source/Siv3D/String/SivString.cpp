//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/String.hpp"

namespace s3d
{
	size_t String::count(const StringView& str) const
	{
		size_t count = 0;

		for (auto it = begin();; ++it, ++count)
		{
			it = std::search(it, end(), str.begin(), str.end());

			if (it == end())
			{
				return count;
			}
		}
	}

	bool String::ends_with(const StringView& str) const
	{
		return (length() >= str.length()) && std::equal(str.begin(), str.end(), end() - str.length());
	}

	String String::expand_tabs(const size_t tabSize) const
	{
		const size_t new_size = length() + (count(L'\t') * tabSize);

		String result(new_size, L'\0');

		wchar* dst = &result[0];

		for (const auto v : m_string)
		{
			if (v == L'\t')
			{
				for (size_t i = 0; i < tabSize; ++i)
				{
					*dst++ = L' ';
				}
			}
			else
			{
				*dst++ = v;
			}
		}

		return result;
	}

	String String::layout(const size_t width) const
	{
		String result;
		result.reserve(length());

		size_t count = 0;

		for (const auto v : m_string)
		{
			if (v == L'\n')
			{
				result.push_back(L'\n');
				count = 0;
			}
			else if (v == L'\r')
			{
				continue;
			}
			else
			{
				if (width <= count)
				{
					result.push_back(L'\n');
					count = 0;
				}

				result.push_back(v);
				++count;
			}
		}

		return result;
	}

	//std::string String::narrow() const
	//{
	//	return CharacterSet::Narrow(*this);
	//}


}
