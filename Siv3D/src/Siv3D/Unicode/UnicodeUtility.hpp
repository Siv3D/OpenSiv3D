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

# pragma once
# include <Siv3D/StringView.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// UTF-8
		//

		[[nodiscard]]
		size_t UTF8_Length(std::u16string_view s) noexcept;

		[[nodiscard]]
		size_t UTF8_Length(char32 codePoint) noexcept;

		[[nodiscard]]
		size_t UTF8_Length(StringView s) noexcept;

		void UTF8_Encode(char8** s, char32 codePoint) noexcept;


		//
		// UTF-16
		//
		[[nodiscard]]
		size_t UTF16_Length(std::string_view s) noexcept;

		[[nodiscard]]
		size_t UTF16_Length(char32 codePoint) noexcept;

		[[nodiscard]]
		size_t UTF16_Length(StringView s) noexcept;

		template <class Char16, std::enable_if_t<sizeof(Char16) == sizeof(char16_t)>* = nullptr>
		void UTF16_Encode(Char16** s, char32 codePoint) noexcept
		{
			if (codePoint < 0x10000)
			{
				*(*s)++ = static_cast<Char16>(codePoint);
			}
			else if (codePoint < 0x110000)
			{
				// [Siv3D ToDo] 不正なビット列をはじく
				*(*s)++ = static_cast<Char16>(((codePoint - 0x10000) >> 10) + 0xD800);
				*(*s)++ = static_cast<Char16>((codePoint & 0x3FF) + 0xDC00);
			}
			else
			{
				// REPLACEMENT CHARACTER (0xFFFD)
				*(*s)++ = static_cast<Char16>(0xFFFD);
			}
		}

		//
		// UTF-32
		//
		[[nodiscard]]
		size_t UTF32_Length(std::string_view s) noexcept;

		[[nodiscard]]
		size_t UTF32_Length(std::u16string_view s) noexcept;
	}
}
