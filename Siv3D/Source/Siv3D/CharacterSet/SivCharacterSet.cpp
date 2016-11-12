//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/String.hpp>
# include <Siv3D/Optional.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr char hexTable[2][16] =
		{
			{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
			{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
		};

		using Char8 = char;
		using String8 = std::string;

		static size_t UTF8Length(const char32_t codePoint)
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

		static void UTF8Encode(Char8** s, const char32_t codePoint)
		{
			if (codePoint < 0x80)
			{
				*(*s)++ = static_cast<Char8>(codePoint);
			}
			else if (codePoint < 0x800)
			{
				*(*s)++ = static_cast<Char8>((codePoint >> 6)   | 0xC0);
				*(*s)++ = static_cast<Char8>((codePoint & 0x3F) | 0x80);
			}
			else if (codePoint < 0x10000)
			{
				*(*s)++ = static_cast<Char8>((codePoint >> 12)         | 0xE0);
				*(*s)++ = static_cast<Char8>(((codePoint >> 6) & 0x3F) | 0x80);
				*(*s)++ = static_cast<Char8>((codePoint & 0x3F)        | 0x80);
			}
			else if (codePoint < 0x110000)
			{
				*(*s)++ = static_cast<char>((codePoint >> 18)          | 0xF0);
				*(*s)++ = static_cast<char>(((codePoint >> 12) & 0x3F) | 0x80);
				*(*s)++ = static_cast<char>(((codePoint >> 6) & 0x3F)  | 0x80);
				*(*s)++ = static_cast<char>((codePoint & 0x3F)         | 0x80);
			}
			else
			{
				*(*s)++ = static_cast<uint8>(0xEF);
				*(*s)++ = static_cast<uint8>(0xBF);
				*(*s)++ = static_cast<uint8>(0xBD);
			}
		}

		static size_t UTF16Length(const char32_t codePoint)
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

		template <class Char16>
		static void UTF16Encode(Char16** s, const char32_t codePoint)
		{
			if (codePoint < 0x10000)
			{
				*(*s)++ = static_cast<Char16>(codePoint);
			}
			else if (codePoint < 0x110000)
			{
				*(*s)++ = static_cast<Char16>(((codePoint - 0x10000) >> 10) + 0xD800);
				*(*s)++ = static_cast<Char16>((codePoint & 0x3FF)           + 0xDC00);
			}
			else
			{
				*(*s)++ = static_cast<Char16>(0xFFFD);
			}
		}

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

		static offset_pt utf8_decode_check(const Char8* s, const size_t length)
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

		static char32_t utf8_decode(const Char8* s, const size_t length, int32& offset)
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

		inline bool is_high_surrogate(const char16_t c) { return (c >= 0xD800) && (c < 0xDC00); }

		inline bool is_low_surrogate(const char16_t c) { return (c >= 0xDC00) && (c < 0xE000); }

		template <class Char16>
		static offset_pt utf16_decode_check(const Char16* const s, const size_t length)
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

		template <class Char16>
		static char32_t utf16_decode(const Char16* s, const size_t length, int32& offset)
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

		static size_t UTF8ToUTF16_Length(const Char8* const begin, const Char8* const end)
		{
			size_t length = 0;

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				length += UTF16Length(utf8_decode(it, end - it, offset));

				it += offset;			
			}

			return length;
		}

		template <class Char32>
		static size_t UTF8ToUTF32_Length(const Char8* const begin, const Char8* const end)
		{
			size_t length = 0;

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				utf8_decode(it, end - it, offset);

				length += 1;

				it += offset;
			}

			return length;
		}

		template <class Char16>
		static size_t UTF16ToUTF8_Length(const Char16* const begin, const Char16* const end)
		{
			size_t length = 0;

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				length += UTF8Length(utf16_decode(it, end - it, offset));

				it += offset;
			}

			return length;
		}

		template <class Char16>
		static size_t UTF16ToUTF32_Length(const Char16* const begin, const Char16* const end)
		{
			size_t length = 0;

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				utf16_decode(it, end - it, offset);

				length += 1;

				it += offset;
			}

			return length;
		}

		template <class Char32>
		static size_t UTF32ToUTF8_Length(const Char32* const begin, const Char32* const end)
		{
			size_t length = 0;

			for (auto it = begin; it != end; ++it)
			{
				length += UTF8Length(*it);
			}

			return length;
		}

		template <class Char32>
		static size_t UTF32ToUTF16_Length(const Char32* const begin, const Char32* const end)
		{
			size_t length = 0;

			for (auto it = begin; it != end; ++it)
			{
				length += UTF16Length(*it);
			}

			return length;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-8 -> UTF-16
		//
		////////////////////////////////////////////////////////////////

		template <class String16>
		static String16 UTF8ToUTF16(const Char8* begin, const Char8* const end)
		{
			using Char16 = typename String16::value_type;
			String16 result(UTF8ToUTF16_Length(begin, end), '0');
			Char16* dst = &result[0];

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				UTF16Encode(&dst, utf8_decode(it, end - it, offset));

				it += offset;
			}

			return result;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-8 -> UTF-32
		//
		////////////////////////////////////////////////////////////////

		template <class String32>
		static String32 UTF8ToUTF32(const Char8* begin, const Char8* const end)
		{
			using Char32 = typename String32::value_type;
			String32 result(UTF8ToUTF32_Length<char32_t>(begin, end), '0');
			Char32* dst = &result[0];

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				*dst++ = utf8_decode(it, end - it, offset);

				it += offset;
			}

			return result;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-16 -> UTF-8
		//
		////////////////////////////////////////////////////////////////

		template <class Char16>
		static String8 UTF16ToUTF8(const Char16* begin, const Char16* const end)
		{
			String8 result(UTF16ToUTF8_Length(begin, end), '0');
			Char8* dst = &result[0];

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				UTF8Encode(&dst, utf16_decode(it, end - it, offset));

				it += offset;
			}

			return result;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-16 -> UTF-32
		//
		////////////////////////////////////////////////////////////////

		template <class Char16, class String32>
		static String32 UTF16ToUTF32(const Char16* begin, const Char16* const end)
		{
			using Char32 = typename String32::value_type;
			String32 result(UTF16ToUTF32_Length(begin, end), '0');
			Char32* dst = &result[0];

			auto it = begin;

			while (it != end)
			{
				int32 offset;

				*dst++ = utf16_decode(it, end - it, offset);

				it += offset;
			}

			return result;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-32 -> UTF-8
		//
		////////////////////////////////////////////////////////////////

		template <class Char32>
		static String8 UTF32ToUTF8(const Char32* begin, const Char32* const end)
		{
			String8 result(UTF32ToUTF8_Length(begin, end), '0');
			Char8* dst = &result[0];

			for (auto it = begin; it != end; ++it)
			{
				UTF8Encode(&dst, *it);
			}

			return result;
		}

		////////////////////////////////////////////////////////////////
		//
		//		UTF-32 -> UTF-16
		//
		////////////////////////////////////////////////////////////////

		template <class Char32, class String16>
		static String16 UTF32ToUTF16(const Char32* begin, const Char32* const end)
		{
			using Char16 = typename String16::value_type;
			String16 result(UTF32ToUTF16_Length(begin, end), '0');
			Char16* dst = &result[0];

			for (auto it = begin; it != end; ++it)
			{
				UTF16Encode(&dst, *it);
			}

			return result;
		}
	}
}

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d
{
	namespace detail
	{
		static std::string FromString(const StringView str, const uint32 code)
		{
			if (str.empty())
			{
				return std::string();
			}

			const int32 length = ::WideCharToMultiByte(
				code,
				0,
				str.begin(),
				static_cast<int>(str.length()),
				nullptr,
				0,
				nullptr,
				nullptr
			);

			std::string result(length, '\0');

			if (length != ::WideCharToMultiByte(
				code,
				0,
				str.begin(),
				static_cast<int32>(str.length()),
				&result[0],
				length,
				nullptr,
				nullptr
			))
			{
				result.clear();
			}

			return result;
		}

		static String ToString(const CStringView str, const uint32 code)
		{
			if (str.empty())
			{
				return String();
			}

			const int32 length = ::MultiByteToWideChar(
				code,
				0,
				str.begin(),
				static_cast<int32>(str.length()),
				nullptr,
				0
			);

			if (length == 0)
			{
				return String();
			}

			String result(length, L'\0');

			if (length != ::MultiByteToWideChar(
				code,
				0,
				str.begin(),
				static_cast<int32>(str.length()),
				&result[0],
				length
			))
			{
				result.clear();
			}

			return result;
		}
	}
}

# endif

namespace s3d
{
	namespace CharacterSet
	{
		String WidenAscii(const CStringView asciiStr)
		{
			const char* const begin = asciiStr.begin();
			const char* const end = asciiStr.end();

			String result(asciiStr.length(), L'\0');
			wchar* dst = &result[0];

			for (auto it = begin; it != end; ++it)
			{
				*dst++ = *it;
			}

			return result;
		}

		String Widen(const CStringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)
			
			return detail::ToString(str, CP_ACP);
		
		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF8ToUTF32<String>(str.begin(), str.end());

		# endif
		}

		std::string NarrowAscii(const StringView asciiStr)
		{
			const wchar* const begin = asciiStr.begin();
			const wchar* const end = asciiStr.end();

			std::string result(asciiStr.length(), L'\0');
			char* dst = &result[0];

			for (auto it = begin; it != end; ++it)
			{
				*dst++ = static_cast<char>(*it);
			}

			return result;
		}

		std::string Narrow(const StringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::FromString(str, CP_THREAD_ACP);

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF32ToUTF8<wchar>(str.begin(), str.end());

		# endif
		}

		String FromUTF8(const UTF8StringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::UTF8ToUTF16<String>(str.begin(), str.end());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF8ToUTF32<String>(str.begin(), str.end());

		# endif
		}
		
		String FromUTF16(const std::u16string& str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return String(str.begin(), str.end());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF16ToUTF32<char16_t, String>(str.data(), str.data() + str.length());

		# endif
		}

		String FromUTF32(const std::u32string& str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::UTF32ToUTF16<char32_t, String>(str.data(), str.data() + str.length());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return String(str.data(), str.data() + str.length());

		# endif
		}

		std::string ToUTF8(const StringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::UTF16ToUTF8<wchar>(str.begin(), str.end());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF32ToUTF8<wchar>(str.begin(), str.end());

		# endif
		}

		std::u16string ToUTF16(const StringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return std::u16string(str.begin(), str.end());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return detail::UTF32ToUTF16<wchar, std::u16string>(str.begin(), str.end());

		# endif
		}

		std::u32string ToUTF32(const StringView str)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return detail::UTF16ToUTF32<wchar, std::u32string>(str.begin(), str.end());

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			return std::u32string(str.begin(), str.end());

		# endif
		}

		std::u16string UTF8ToUTF16(UTF8StringView str)
		{
			return detail::UTF8ToUTF16<std::u16string>(str.begin(), str.end());
		}

		std::u32string UTF8ToUTF32(UTF8StringView str)
		{
			return detail::UTF8ToUTF32<std::u32string>(str.begin(), str.end());
		}

		std::string UTF16ToUTF8(const std::u16string& str)
		{
			return detail::UTF16ToUTF8<char16_t>(str.data(), str.data() + str.length());
		}

		std::u32string UTF16ToUTF32(const std::u16string& str)
		{
			return detail::UTF16ToUTF32<char16_t, std::u32string>(str.data(), str.data() + str.length());
		}

		std::string UTF32ToUTF8(const std::u32string& str)
		{
			return detail::UTF32ToUTF8<char32_t>(str.data(), str.data() + str.length());
		}

		std::u16string UTF32ToUTF16(const std::u32string& str)
		{
			return detail::UTF32ToUTF16<char32_t, std::u16string>(str.data(), str.data() + str.length());
		}

		String PercentEncode(const StringView str, const Arg::upperCase_<bool> upperCase)
		{
			const std::string utf8 = ToUTF8(str);

			size_t length = 0;

			for (const uint8 ch : utf8)
			{
				if (IsAlnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~')
				{
					++length;
				}
				else
				{
					length += 3;
				}
			}

			const char* const table = detail::hexTable[*upperCase];

			String result(length, L'\0');
			wchar* dst = &result[0];

			for (const uint8 ch : utf8)
			{
				if (IsAlnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~')
				{
					*dst++ = static_cast<wchar>(ch);
				}
				else
				{
					*dst++ = L'%';

					*dst++ = table[ch >> 4];

					*dst++ = table[ch & 0x0F];
				}
			}

			return result;
		}
	}
}
