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

# include "Siv3D/String.hpp"
# include "Siv3D/Unicode.hpp"

namespace s3d::detail
{
	/* Copyright (c) 2013 Dropbox, Inc.
	*
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	*
	* The above copyright notice and this permission notice shall be included in
	* all copies or substantial portions of the Software.
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	* THE SOFTWARE.
	*/
	//////////////////////////////////////////////////////////////////////////////
	//
	struct offset_pt
	{
		int32 offset;
			
		char32_t codePoint;
	};

	static constexpr const offset_pt invalid_pt = { -1, 0 };

	static offset_pt utf8_decode_check(const char8* s, const size_t length)
	{
		uint32_t b0, b1, b2, b3;

		b0 = static_cast<uint8>(s[0]);

		if (b0 < 0x80)
		{
			// 1-byte character
			return{ 1, b0 };
		}
		else if (b0 < 0xC0)
		{
			// Unexpected continuation byte
			return invalid_pt;
		}
		else if (b0 < 0xE0)
		{
			if (length < 2)
			{
				return invalid_pt;
			}

			// 2-byte character
			if (((b1 = s[1]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			const char32_t pt = (b0 & 0x1F) << 6 | (b1 & 0x3F);
				
			if (pt < 0x80)
			{
				return invalid_pt;
			}

			return{ 2, pt };
		}
		else if (b0 < 0xF0)
		{
			if (length < 3)
			{
				return invalid_pt;
			}

			// 3-byte character
			if (((b1 = s[1]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			if (((b2 = s[2]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			const char32_t pt = (b0 & 0x0F) << 12 | (b1 & 0x3F) << 6 | (b2 & 0x3F);

			if (pt < 0x800)
			{
				return invalid_pt;
			}

			return{ 3, pt };
		}
		else if (b0 < 0xF8)
		{
			if (length < 3)
			{
				return invalid_pt;
			}

			// 4-byte character
			if (((b1 = s[1]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			if (((b2 = s[2]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			if (((b3 = s[3]) & 0xC0) != 0x80)
			{
				return invalid_pt;
			}

			const char32_t pt = (b0 & 0x0F) << 18 | (b1 & 0x3F) << 12 | (b2 & 0x3F) << 6 | (b3 & 0x3F);
				
			if (pt < 0x10000 || pt >= 0x110000)
			{
				return invalid_pt;
			}

			return{ 4, pt };
		}
		else
		{
			// Codepoint out of range
			return invalid_pt;
		}
	}

	static char32_t utf8_decode(const char8* s, const size_t length, int32& offset)
	{
		const offset_pt res = utf8_decode_check(s, length);

		if (res.offset < 0)
		{
			offset = 1;

			return 0xFFFD;
		}
		else
		{
			offset = res.offset;

			return res.codePoint;
		}
	}

	inline constexpr bool is_high_surrogate(const char16_t c) { return (c >= 0xD800) && (c < 0xDC00); }

	inline constexpr bool is_low_surrogate(const char16_t c) { return (c >= 0xDC00) && (c < 0xE000); }

	static offset_pt utf16_decode_check(const char16* const s, const size_t length)
	{
		if (is_high_surrogate(s[0]) && length >= 2 && is_low_surrogate(s[1]))
		{
			// High surrogate followed by low surrogate
			const char32_t pt = (((s[0] - 0xD800) << 10) | (s[1] - 0xDC00)) + 0x10000;
			
			return{ 2, pt };
		}
		else if (is_high_surrogate(s[0]) || is_low_surrogate(s[0]))
		{
			// High surrogate *not* followed by low surrogate, or unpaired low surrogate
			return invalid_pt;
		}
		else
		{
			return{ 1, s[0] };
		}
	}

	static char32 utf16_decode(const char16* s, const size_t length, int32& offset)
	{
		const offset_pt res = utf16_decode_check(s, length);

		if (res.offset < 0)
		{
			offset = 1;

			return 0xFFFD;
		}
		else
		{
			offset = res.offset;

			return res.codePoint;
		}
	}
	//
	//////////////////////////////////////////////////////////////////////////////

	[[nodiscard]] static constexpr size_t UTF8Length(const char32_t codePoint) noexcept
	{
		if (codePoint < 0x80)
		{
			return 1;
		}
		else if (codePoint < 0x800)
		{
			return 2;
		}
		else if (codePoint < 0x10000)
		{
			return 3;
		}
		else if (codePoint < 0x110000)
		{
			return 4;
		}
		else
		{
			return 3; // U+FFFD
		}
	}

	[[nodiscard]] static constexpr size_t UTF8Length(const StringView view) noexcept
	{
		size_t length = 0;

		const char32* pSrc = view.data();
		const char32* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			length += UTF8Length(*pSrc++);
		}

		return length;
	}

	[[nodiscard]] static size_t UTF8Length(const std::u16string_view view) noexcept
	{
		size_t length = 0;

		const char16* pSrc = view.data();
		const char16* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset;

			length += UTF8Length(utf16_decode(pSrc, pSrcEnd - pSrc, offset));

			pSrc += offset;
		}

		return length;
	}

	static void UTF8Encode(char8** s, const char32_t codePoint) noexcept
	{
		if (codePoint < 0x80)
		{
			*(*s)++ = static_cast<char8>(codePoint);
		}
		else if (codePoint < 0x800)
		{
			*(*s)++ = static_cast<char8>((codePoint >> 6) | 0xC0);
			*(*s)++ = static_cast<char8>((codePoint & 0x3F) | 0x80);
		}
		else if (codePoint < 0x10000)
		{
			*(*s)++ = static_cast<char8>((codePoint >> 12) | 0xE0);
			*(*s)++ = static_cast<char8>(((codePoint >> 6) & 0x3F) | 0x80);
			*(*s)++ = static_cast<char8>((codePoint & 0x3F) | 0x80);
		}
		else if (codePoint < 0x110000)
		{
			*(*s)++ = static_cast<char8>((codePoint >> 18) | 0xF0);
			*(*s)++ = static_cast<char8>(((codePoint >> 12) & 0x3F) | 0x80);
			*(*s)++ = static_cast<char8>(((codePoint >> 6) & 0x3F) | 0x80);
			*(*s)++ = static_cast<char8>((codePoint & 0x3F) | 0x80);
		}
		else
		{
			*(*s)++ = static_cast<uint8>(0xEF);
			*(*s)++ = static_cast<uint8>(0xBF);
			*(*s)++ = static_cast<uint8>(0xBD);
		}
	}

	[[nodiscard]] static constexpr size_t UTF16Length(const char32_t codePoint) noexcept
	{
		if (codePoint < 0x10000)
		{
			return 1;
		}
		else if (codePoint < 0x110000)
		{
			return 2;
		}
		else
		{
			return 1; // 0xFFFD
		}
	}

	[[nodiscard]] static constexpr size_t UTF16Length(const StringView view) noexcept
	{
		size_t length = 0;

		const char32* pSrc = view.data();
		const char32* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			length += UTF16Length(*pSrc++);
		}

		return length;
	}

	[[nodiscard]] static constexpr size_t UTF16Length(const std::string_view view) noexcept
	{
		size_t length = 0;

		const char8* pSrc = view.data();
		const char8* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset = 0;

			length += UTF16Length(detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset));

			pSrc += offset;
		}

		return length;
	}

	static void UTF16Encode(char16** s, const char32_t codePoint) noexcept
	{
		if (codePoint < 0x10000)
		{
			*(*s)++ = static_cast<char16>(codePoint);
		}
		else if (codePoint < 0x110000)
		{
			*(*s)++ = static_cast<char16>(((codePoint - 0x10000) >> 10) + 0xD800);
			*(*s)++ = static_cast<char16>((codePoint & 0x3FF) + 0xDC00);
		}
		else
		{
			*(*s)++ = static_cast<char16>(0xFFFD);
		}
	}

	[[nodiscard]] static size_t UTF32Length(const std::string_view view) noexcept
	{
		size_t length = 0;

		const char8* pSrc = view.data();
		const char8* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset;

			utf8_decode(pSrc, pSrcEnd - pSrc, offset);

			pSrc += offset;

			++length;
		}

		return length;
	}

	[[nodiscard]] static size_t UTF32Length(const std::u16string_view view)
	{
		size_t length = 0;

		const char16* pSrc = view.data();
		const char16* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset;

			utf16_decode(pSrc, pSrcEnd - pSrc, offset);

			pSrc += offset;

			++length;
		}

		return length;
	}

# if defined(SIV3D_TARGET_WINDOWS)

	[[nodiscard]] static size_t UTF32Length(const std::wstring_view view)
	{
		size_t length = 0;

		const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(view.data()));
		const char16* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset;

			utf16_decode(pSrc, pSrcEnd - pSrc, offset);

			pSrc += offset;

			++length;
		}

		return length;
	}

# endif

}


# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d::detail
{
	[[nodiscard]] static std::string FromString(const std::u16string_view view, const uint32 code)
	{
		if (view.empty())
		{
			return std::string();
		}

		const int32 length = ::WideCharToMultiByte(code, 0,
			static_cast<const wchar_t*>(static_cast<const void*>(view.data())),
			static_cast<int>(view.length()), nullptr, 0, nullptr, nullptr);

		std::string result(length, '\0');

		if (length != ::WideCharToMultiByte(code, 0,
			static_cast<const wchar_t*>(static_cast<const void*>(view.data())),
			static_cast<int>(view.length()), &result[0], length, nullptr, nullptr))
		{
			result.clear();
		}

		return result;
	}

	[[nodiscard]] static std::u16string ToString(const std::string_view view, const uint32 code)
	{
		if (view.empty())
		{
			return std::u16string();
		}

		const int32 length = ::MultiByteToWideChar(code, 0, view.data(), static_cast<int32>(view.length()),
			nullptr, 0);

		if (length == 0)
		{
			return std::u16string();
		}

		std::u16string result(length, u'\0');

		if (length != ::MultiByteToWideChar(code, 0, view.data(), static_cast<int32>(view.length()),		
			static_cast<wchar_t*>(static_cast<void*>(&result[0])), length))
		{
			result.clear();
		}

		return result;
	}
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

		String Widen(const std::string_view view)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return FromUTF16(detail::ToString(view, CP_ACP));

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return FromUTF8(view);

		# endif
		}

		std::string NarrowAscii(const StringView asciiText)
		{
			std::string result(asciiText.length(), '\0');
		
			const char32* pSrc = asciiText.begin();
			const char32* const pSrcEnd = asciiText.end();
			char* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				*pDst++ = static_cast<char>(*pSrc++);
			}

			return result;
		}

		std::string Narrow(const StringView view)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::FromString(ToUTF16(view), CP_THREAD_ACP);

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return ToUTF8(view);

		# endif
		}

		std::wstring ToWString(const StringView view)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			std::wstring result(detail::UTF16Length(view), u'0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char16* pDst = static_cast<char16*>(static_cast<void*>(&result[0]));

			while (pSrc != pSrcEnd)
			{
				detail::UTF16Encode(&pDst, *pSrc++);
			}

			return result;

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return std::wstring(view.begin(), view.end());

		# endif
		}

		String FromWString(const std::wstring_view view)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			String result(detail::UTF32Length(view), '0');

			const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(view.data()));
			const char16* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return String(view.begin(), view.end());

		# endif
		}

		String FromUTF8(const std::string_view view)
		{
			String result(detail::UTF32Length(view), '0');

			const char8* pSrc = view.data();
			const char8* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		String FromUTF16(const std::u16string_view view)
		{
			String result(detail::UTF32Length(view), '0');

			const char16* pSrc = view.data();
			const char16* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		String FromUTF32(const std::u32string_view view)
		{
			return String(view.begin(), view.end());
		}

		std::string ToUTF8(const StringView view)
		{
			std::string result(detail::UTF8Length(view), '0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF8Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u16string ToUTF16(const StringView view)
		{
			std::u16string result(detail::UTF16Length(view), u'0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u32string ToUTF32(const StringView view)
		{
			return std::u32string(view.begin(), view.end());
		}

		std::u16string UTF8ToUTF16(const std::string_view view)
		{
			std::u16string result(detail::UTF16Length(view), '0');

			const char8* pSrc = view.data();
			const char8* const pSrcEnd = pSrc + view.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				detail::UTF16Encode(&pDst, detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return result;
		}

		std::u32string UTF8ToUTF32(const std::string_view view)
		{
			std::u32string result(detail::UTF32Length(view), '0');
			
			const char8* pSrc = view.data();
			const char8* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		std::string UTF16ToUTF8(const std::u16string_view view)
		{
			std::string result(detail::UTF8Length(view), '0');
			
			const char16* pSrc = view.data();
			const char16* const pSrcEnd = pSrc + view.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				detail::UTF8Encode(&pDst, detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset));

				pSrc += offset;
			}

			return result;
		}

		std::u32string UTF16ToUTF32(const std::u16string_view view)
		{
			std::u32string result(detail::UTF32Length(view), '0');
			
			const char16* pSrc = view.data();
			const char16* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}

		std::string UTF32ToUTF8(const std::u32string_view view)
		{
			std::string result(detail::UTF8Length(view), '0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF8Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u16string UTF32ToUTF16(const std::u32string_view view)
		{
			std::u16string result(detail::UTF16Length(view), u'0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16Encode(&pDst, *pSrc++);
			}

			return result;
		}

		size_t CountCodePoints(const std::string_view view) noexcept
		{
			size_t length = 0;

			const char* pSrc = view.data();
			const char* const pSrcEnd = pSrc + view.size();

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;

				++length;
			}

			return length;
		}

		size_t CountCodePoints(const std::u16string_view view) noexcept
		{
			return detail::UTF32Length(view);
		}

		size_t CountCodePoints(const StringView view) noexcept
		{
			return view.size();
		}

		bool Translator_UTF8toUTF32::put(const char8 code) noexcept
		{
			m_buffer[m_count++] = code;

			const auto result = detail::utf8_decode_check(m_buffer.data(), m_count);

			if (result.offset != -1)
			{
				m_result = result.codePoint;

				m_count = 0;

				return true;
			}

			if (m_count >= 4)
			{
				m_result = 0xFFFD;

				m_count = 0;

				return true;
			}

			return false;
		}

		bool Translator_UTF16toUTF32::put(const char16 code) noexcept
		{
			if (m_hasHighSurrogate)
			{
				m_hasHighSurrogate = false;

				if (IsHighSurrogate(code))
				{
					// error
					m_result = 0xFFFD;
				}
				else if (IsLowSurrogate(code))
				{
					// ok
					m_result = (((m_buffer - 0xD800) << 10) | (code - 0xDC00)) + 0x10000;
				}
				else
				{
					// error
					m_result = 0xFFFD;
				}

				return true;
			}
			else
			{
				if (IsHighSurrogate(code))
				{
					// ok
					m_buffer = code;

					m_hasHighSurrogate = true;

					return false;
				}
				else if (IsLowSurrogate(code))
				{
					// error
					m_result = 0xFFFD;
				}
				else
				{
					// ok
					m_result = code;
				}

				return true;
			}
		}

		size_t Translator_UTF32toUTF8::put(const char32 code) noexcept
		{
			char8* pBuffer = m_buffer.data();

			detail::UTF8Encode(&pBuffer, code);

			return pBuffer - m_buffer.data();
		}

		size_t Translator_UTF32toUTF16::put(const char32 code) noexcept
		{
			char16* pBuffer = m_buffer.data();

			detail::UTF16Encode(&pBuffer, code);

			return pBuffer - m_buffer.data();
		}
	}
}
