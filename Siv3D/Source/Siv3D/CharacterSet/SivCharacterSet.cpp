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
# include "../../../Include/Siv3D/Optional.hpp"

//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

static constexpr uint8_t utf8d[] =
{
	// The first part of the table maps bytes to character classes that
	// to reduce the size of the transition table and create bitmasks.
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

	// The second part is a transition table that maps a combination
	// of a state of the automaton and a character class to a state.
	0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
	12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
	12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
	12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
	12,36,12,12,12,12,12,12,12,12,12,12,
};

inline uint32_t decode(uint32_t* state, uint32_t* codep, const uint32_t byte)
{
	uint32_t type = utf8d[byte];

	*codep = (*state != UTF8_ACCEPT) ?
		(byte & 0x3fu) | (*codep << 6) :
		(0xff >> type) & (byte);

	*state = utf8d[256 + *state + type];
	return *state;
}
//
//////////////////////////////////////////////////////////////////////////////

namespace s3d
{
	namespace detail
	{
		static constexpr char hexTable[2][16] =
		{
			{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
			{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
		};

		inline Optional<size_t> CountCodePoints(const char* s)
		{
			size_t count = 0;
			uint32_t state = 0;
			uint32_t codepoint;

			for (; *s; ++s)
			{
				if (!decode(&state, &codepoint, *s))
				{
					++count;
				}
			}

			return state == UTF8_ACCEPT ? Optional<size_t>(count) : none;
		}

		inline constexpr bool IsUTF16Surrogate(const char16_t ch)
		{
			return static_cast<uint32>(ch - 0xD800u) < 2048u;
		}

		inline constexpr bool IsUTF16HighSurrogate(const char16_t ch)
		{
			return (ch & 0xFFffFC00) == 0xD800;
		}

		inline constexpr bool IsUTF16LowSurrogate(const char16_t ch)
		{
			return (ch & 0xFFffFC00) == 0xDC00;
		}

		inline constexpr char32_t SurrogateToUTF32(const char16_t high, const char16_t low)
		{
			return (high << 10) + low - 0x035Fdc00;
		}

		inline Optional<size_t> CountCodePoints(const char16_t* begin, const char16_t* end)
		{
			size_t count = 0;

			while (begin != end)
			{
				const char16_t ch = *begin++;

				if (!IsUTF16Surrogate(ch))
				{
					++count;
				}
				else if (IsUTF16HighSurrogate(ch) && begin < end && IsUTF16LowSurrogate(*begin))
				{
					++count;
					++begin;
				}
				else
				{
					return none;
				}
			}

			return count;
		}
	}
}

# if defined (SIV3D_TARGET_WINDOWS)

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
				str.data(),
				static_cast<int>(str.length()),
				nullptr,
				0,
				nullptr,
				nullptr
			);

			std::string output(length, '\0');

			if (length != ::WideCharToMultiByte(
				code,
				0,
				str.data(),
				static_cast<int32>(str.length()),
				&output[0],
				length,
				nullptr,
				nullptr
			))
			{
				output.clear();
			}

			return output;
		}

		static String ToString(const std::string& str, const uint32 code)
		{
			if (str.empty())
			{
				return String();
			}

			const int32 length = ::MultiByteToWideChar(
				code,
				0,
				str.data(),
				static_cast<int32>(str.length() + 1),
				nullptr,
				0
			);

			String output(length ? length - 1 : 0, '\0');

			if (length != ::MultiByteToWideChar(
				code,
				0,
				str.data(),
				static_cast<int32>(str.length() + 1),
				&output[0],
				length
			))
			{
				output.clear();
			}

			return output;
		}

		String UTF32ToString(const std::u32string& str)
		{
			String result;

			result.reserve(str.length());

			for (const auto& ch : str)
			{
				if (ch <= 0xFFff)
				{
					result.push_back(static_cast<char16_t>(ch));
				}
				else
				{
					result.push_back(static_cast<char16_t>(0xD7c0 + (ch >> 10)));
					result.push_back(static_cast<char16_t>(0xDC00 + (ch & 0x03ff)));
				}
			}

			return result;
		}

		inline Optional<size_t> CountCodePoints(const wchar* begin, const wchar* end)
		{
			size_t count = 0;

			while (begin != end)
			{
				const char16_t ch = *begin++;

				if (!IsUTF16Surrogate(ch))
				{
					++count;
				}
				else if (IsUTF16HighSurrogate(ch) && begin < end && IsUTF16LowSurrogate(*begin))
				{
					++count;
					*begin++;
				}
				else
				{
					return none;
				}
			}

			return count;
		}
		
		std::u32string StringToUTF32(const StringView str)
		{
			if (str.empty())
			{
				return std::u32string();
			}

			const wchar* begin = &str[0];
			const wchar* end = begin + str.length();

			if (const auto length = detail::CountCodePoints(begin, end))
			{
				std::u32string result(length.value(), L'\0');

				while (begin != end)
				{
					const auto ch = *begin++;

					if (!IsUTF16Surrogate(ch))
					{
						result.push_back(ch);
					}
					else
					{
						result.push_back(SurrogateToUTF32(ch, *begin++));
					}
				}

				return result;
			}
			else
			{
				return std::u32string();
			}
		}
	}
}

# elif defined (SIV3D_TARGET_OSX)

# include <codecvt>

namespace s3d
{
	namespace detail
	{
		String UTF8ToString(const std::string& str)
		{
			if (str.empty())
			{
				return String();
			}

			if (const auto length = detail::CountCodePoints(str.c_str()))
			{
				String result(length.value(), L'\0');
				uint32 codepoint;
				uint32 state = 0;
				const char* src = &str[0];
				wchar* dst = &result[0];

				while (*src)
				{
					if (!decode(&state, &codepoint, *(src++)))
					{
						*(dst++) = static_cast<wchar>(codepoint);
					}
				}

				return result;
			}
			else
			{
				return String();
			}
		}

		std::string StringToUTF8(const StringView str)
		{
			return std::wstring_convert<std::codecvt_utf8<wchar>>().to_bytes(str.begin(), str.end());
		}

		String UTF16ToString(const std::u16string& str)
		{
			if (str.empty())
			{
				return String();
			}

			const char16_t* begin = &str[0];
			const char16_t* end = begin + str.length();

			if (const auto length = detail::CountCodePoints(begin, end))
			{
				String result(length.value(), L'\0');

				while (begin != end)
				{
					const auto ch = *begin++;

					if (!IsUTF16Surrogate(ch))
					{
						result.push_back(ch);
					}
					else
					{
						result.push_back(SurrogateToUTF32(ch, *begin++));
					}
				}

				return result;
			}
			else
			{
				return String();
			}
		}

		std::u16string StringToUTF16(const StringView str)
		{
			std::u16string result;

			result.reserve(str.length());

			for (const auto& ch : str)
			{
				if (ch <= 0xFFff)
				{
					result.push_back(static_cast<char16_t>(ch));
				}
				else
				{
					result.push_back(static_cast<char16_t>(0xD7c0 + (ch >> 10)));
					result.push_back(static_cast<char16_t>(0xDC00 + (ch & 0x03ff)));
				}
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
		String WidenAscii(const std::string& asciiStr)
		{
			const size_t length = asciiStr.length();

			String result(length, L'\0');

			wchar* dst = &result[0];

			const char* src = asciiStr.data();

			for (size_t i = 0; i < length; ++i)
			{
				*(dst++) = *(src++);
			}

			return result;
		}

		String Widen(const std::string& str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)
			
				return detail::ToString(str, CP_ACP);
		
			# elif defined (SIV3D_TARGET_OSX)

				return detail::UTF8ToString(str);

			# endif
		}

		std::string NarrowAscii(const StringView asciiStr)
		{
			const size_t length = asciiStr.length();

			std::string result(length, L'\0');

			char* dst = &result[0];

			const wchar* src = asciiStr.data();

			while (*src)
			{
				*(dst++) = static_cast<char>(*(src++));
			}

			return result;
		}

		std::string Narrow(const StringView str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return detail::FromString(str, CP_THREAD_ACP);

			# elif defined (SIV3D_TARGET_OSX)

				return detail::StringToUTF8(str);

			# endif
		}

		String FromUTF8(const std::string& str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return detail::ToString(str, CP_UTF8);

			# elif defined (SIV3D_TARGET_OSX)

				return detail::UTF8ToString(str);

			# endif
		}

		std::string ToUTF8(const StringView str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return detail::FromString(str, CP_UTF8);

			# elif defined (SIV3D_TARGET_OSX)

				return detail::StringToUTF8(str);

			# endif
		}

		String FromUTF16(const std::u16string& str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return String(str.begin(), str.end());

			# elif defined (SIV3D_TARGET_OSX)

				return detail::UTF16ToString(str);

			# endif
		}

		std::u16string ToUTF16(const StringView str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return std::u16string(str.begin(), str.end());

			# elif defined (SIV3D_TARGET_OSX)

				return detail::StringToUTF16(str);

			# endif
		}

		String FromUTF32(const std::u32string& str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return detail::UTF32ToString(str);

			# elif defined (SIV3D_TARGET_OSX)

				return String(str.begin(), str.end());

			# endif
		}

		std::u32string ToUTF32(const StringView str)
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return detail::StringToUTF32(str);

			# elif defined (SIV3D_TARGET_OSX)

				return std::u32string(str.begin(), str.end());

			# endif
		}

		String PercentEncode(const StringView str, const bool upperCase)
		{
			const char* table = detail::hexTable[upperCase];

			String result;

			for (const uint8 ch : ToUTF8(str))
			{
				if (IsAlnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~')
				{
					result.push_back(static_cast<wchar>(ch));
				}
				else
				{
					result.push_back(L'%');

					result.push_back(table[ch >> 4]);

					result.push_back(table[ch & 0x0F]);
				}
			}

			return result;
		}
	}
}
