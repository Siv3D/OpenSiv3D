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

# include <ThirdParty/miniutf/miniutf.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include "UnicodeUtility.hpp"

namespace s3d
{
	namespace Unicode
	{
		String WidenAscii(const std::string_view asciiText)
		{
			return String(asciiText.begin(), asciiText.end());
		}

		String FromUTF8(const std::string_view s)
		{
			String result(detail::UTF32_Length(s), '0');

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;
				*pDst++ = detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);
				pSrc += offset;
			}

			return result;
		}

		String FromUTF16(const std::u16string_view s)
		{
			String result(detail::UTF32_Length(s), '0');

			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;
				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);
				pSrc += offset;
			}

			return result;
		}

		String FromUTF32(const std::u32string_view s)
		{
			return String{ s };
		}

		std::string NarrowAscii(const StringView asciiText)
		{
			std::string result(asciiText.length(), '\0');

			const char32* pSrc = asciiText.data();
			const char32* const pSrcEnd = pSrc + asciiText.size();
			char* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				*pDst++ = static_cast<char>(*pSrc++);
			}

			return result;
		}

		std::string ToUTF8(const StringView s)
		{
			std::string result(detail::UTF8_Length(s), '0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF8_Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u16string ToUTF16(const StringView s)
		{
			std::u16string result(detail::UTF16_Length(s), u'0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16_Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u32string ToUTF32(const StringView s)
		{
			return std::u32string(s.begin(), s.end());
		}

		std::u16string UTF8ToUTF16(const std::string_view s)
		{
			std::u16string result(detail::UTF16_Length(s), '0');

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				detail::UTF16_Encode(&pDst, detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return result;
		}

		std::u32string UTF8ToUTF32(const std::string_view s)
		{
			std::u32string result(detail::UTF32_Length(s), '0');

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		std::string UTF16ToUTF8(const std::u16string_view s)
		{
			std::string result(detail::UTF8_Length(s), '0');

			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				detail::UTF8_Encode(&pDst, detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return result;
		}

		std::u32string UTF16ToUTF32(const std::u16string_view s)
		{
			std::u32string result(detail::UTF32_Length(s), '0');

			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		std::string UTF32ToUTF8(const std::u32string_view s)
		{
			std::string result(detail::UTF8_Length(s), '0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF8_Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u16string UTF32ToUTF16(const std::u32string_view s)
		{
			std::u16string result(detail::UTF16_Length(s), u'0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16_Encode(&pDst, *pSrc++);
			}

			return result;
		}
	}
}
