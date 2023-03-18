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

# include "UnicodeUtility.hpp"
# include <ThirdParty/miniutf/miniutf.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// UTF-8
		//

		size_t UTF8_Length(const std::u16string_view s) noexcept
		{
			size_t length = 0;

			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				length += UTF8_Length(utf16_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return length;
		}

		size_t UTF8_Length(const char32 codePoint) noexcept
		{
			if (codePoint < 0x80) // 0x00 - 0x7F
			{
				return 1;
			}
			else if (codePoint < 0x800) // 0x80 - 0x07FF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				return 2;
			}
			else if (codePoint < 0x10000) // 0x0800 - 0xFFFF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				return 3;
			}
			else if (codePoint < 0x110000) // 0x010000 - 0x10FFFF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				return 4;
			}
			else // Invalid code point
			{
				return 3; // REPLACEMENT CHARACTER (0xEF 0xBF 0xBD)
			}
		}

		size_t UTF8_Length(const StringView s) noexcept
		{
			size_t result = 0;

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();

			while (pSrc != pSrcEnd)
			{
				result += UTF8_Length(*pSrc++);
			}

			return result;
		}

		void UTF8_Encode(char8** s, const char32 codePoint) noexcept
		{
			if (codePoint < 0x80) // 0x00 - 0x7F
			{
				*(*s)++ = static_cast<char8>(codePoint);
			}
			else if (codePoint < 0x800) // 0x80 - 0x07FF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				*(*s)++ = (0xC0 | static_cast<char8>(codePoint >> 6));
				*(*s)++ = (0x80 | static_cast<char8>(codePoint & 0x3F));
			}
			else if (codePoint < 0x10000) // 0x0800 - 0xFFFF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				*(*s)++ = (0xE0 | static_cast<char8>(codePoint >> 12));
				*(*s)++ = (0x80 | static_cast<char8>((codePoint >> 6) & 0x3F));
				*(*s)++ = (0x80 | static_cast<char8>(codePoint & 0x3F));
			}
			else if (codePoint < 0x110000) // 0x010000 - 0x10FFFF
			{
				// [Siv3D ToDo] 不正なコードポイントをはじく
				*(*s)++ = (0xF0 | static_cast<char8>(codePoint >> 18));
				*(*s)++ = (0x80 | static_cast<char8>((codePoint >> 12) & 0x3F));
				*(*s)++ = (0x80 | static_cast<char8>((codePoint >> 6) & 0x3F));
				*(*s)++ = (0x80 | static_cast<char8>(codePoint & 0x3F));
			}
			else // Invalid code point
			{
				// REPLACEMENT CHARACTER (0xEF 0xBF 0xBD)
				*(*s)++ = static_cast<char8>(uint8(0xEF));
				*(*s)++ = static_cast<char8>(uint8(0xBF));
				*(*s)++ = static_cast<char8>(uint8(0xBD));
			}
		}

		//
		// UTF-16
		//

		size_t UTF16_Length(const std::string_view s) noexcept
		{
			size_t length = 0;

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();

			while (pSrc != pSrcEnd)
			{
				int32 offset = 0;

				length += UTF16_Length(detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return length;
		}

		size_t UTF16_Length(const char32 codePoint) noexcept
		{
			if (codePoint < 0x10000) // 0x00 - 0xFFFF
			{
				return 1;
			}
			else if (codePoint < 0x110000) // 0x010000 - 0x10FFFF
			{
				// [Siv3D ToDo] 不正なビット列をはじく
				return 2;
			}
			else
			{
				return 1; // REPLACEMENT CHARACTER (0xFFFD)
			}
		}

		size_t UTF16_Length(const StringView s) noexcept
		{
			size_t result = 0;

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();

			while (pSrc != pSrcEnd)
			{
				result += UTF16_Length(*pSrc++);
			}

			return result;
		}

		size_t UTF32_Length(const std::string_view s) noexcept
		{
			size_t length = 0;

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				utf8_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;

				++length;
			}

			return length;
		}

		size_t UTF32_Length(const std::u16string_view s) noexcept
		{
			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();

			size_t length = 0;

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;

				++length;
			}

			return length;
		}
	}
}
