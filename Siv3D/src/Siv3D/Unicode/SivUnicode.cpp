//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include "../../ThirdParty/miniutf/miniutf.hpp"

namespace s3d::detail
{
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

# include <Siv3D/Windows.hpp>

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
