//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Unicode.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	namespace Unicode
	{
		String Widen(const std::string_view s)
		{
			return FromUTF8(s);
		}
	
		String FromWstring(const std::wstring_view s)
		{
			return String(s.begin(), s.end());
		}
	
		std::string Narrow(const StringView s)
		{
			return ToUTF8(s);
		}

		std::wstring ToWstring(const StringView s)
		{
			return std::wstring(s.begin(), s.end());
		}
	}
}
