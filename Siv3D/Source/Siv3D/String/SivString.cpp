//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/String.hpp"
# include "../../../Include/Siv3D/Array.hpp"

namespace s3d
{
	Array<String, std::allocator<String>> String::split(const wchar ch) const
	{
		Array<String, std::allocator<String>> result(m_string.empty() ? 0 : 1);

		for (const auto v : m_string)
		{
			if (v == ch)
			{
				result.emplace_back();
			}
			else
			{
				result.back().push_back(v);
			}
		}

		return result;
	}

	Array<String, std::allocator<String>> String::split_lines() const
	{
		Array<String, std::allocator<String>> result(m_string.empty() ? 0 : 1);

		for (const auto v : m_string)
		{
			if (v == L'\n')
			{
				result.emplace_back();
			}
			else if(v != L'\r')
			{
				result.back().push_back(v);
			}
		}

		return result;
	}
}
