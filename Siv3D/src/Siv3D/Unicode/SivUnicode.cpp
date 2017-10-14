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
# include "Siv3D/String.hpp"
# include "Siv3D/Unicode.hpp"


# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d::detail
{

}

# endif


namespace s3d
{
	namespace Unicode
	{
		String WidenAscii(const std::string_view asciiText)
		{
			return String(asciiText.begin(), asciiText.end());
		}

		//String Widen(const std::string_view text)
		//{

		//}

		//std::string NarrowAscii(StringView asciiString);

		//std::string Narrow(StringView text);

		//String FromUTF8(std::string_view text);

		//String FromUTF16(std::u16string_view text);

		//String FromUTF32(std::u32string_view text);

		//std::string ToUTF8(StringView text);

		//std::u16string ToUTF16(StringView text);

		//std::u32string ToUTF32(StringView text);

		//std::u16string UTF8ToUTF16(std::string_view text);

		//std::u32string UTF8ToUTF32(std::string_view text);

		//std::string UTF16ToUTF8(std::u16string_view text);

		//std::u32string UTF16ToUTF32(std::u16string_view text);

		//std::string UTF32ToUTF8(std::u32string_view text);

		//std::u16string UTF32ToUTF16(std::u32string_view text);

		//size_t CountCodePoints(StringView str);
	}
}
