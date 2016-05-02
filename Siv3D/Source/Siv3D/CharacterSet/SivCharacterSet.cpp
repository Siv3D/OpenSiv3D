//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/CharacterSet.hpp"
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

inline uint32_t decode(uint32_t* state, uint32_t* codep, uint32_t byte)
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
		static std::string FromString(const StringView str, uint32 code)
		{
			const int length = ::WideCharToMultiByte(
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
				static_cast<int>(str.length()),
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

		static String ToString(const std::string& str, uint32 code)
		{
			const int length = ::MultiByteToWideChar(
				code,
				0,
				str.data(),
				static_cast<int>(str.length() + 1),
				nullptr,
				0
			);

			String output(length ? length - 1 : 0, '\0');

			if (length != ::MultiByteToWideChar(
				code,
				0,
				str.data(),
				static_cast<int>(str.length() + 1),
				&output[0],
				length
			))
			{
				output.clear();
			}

			return output;
		}
	}
}

# elif defined (SIV3D_TARGET_OSX)


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
	}

	String Widen(const std::string& str)
	{
		if (str.empty())
		{
			return String();
		}

		# if defined (SIV3D_TARGET_WINDOWS)
			
			return detail::ToString(str, CP_ACP);
		
		# elif defined (SIV3D_TARGET_OSX)

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

		# endif
	}

	std::string NarrowAscii(StringView asciiStr)
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

	//std::string Narrow(StringView str)
	//{
	//	# if defined (SIV3D_TARGET_WINDOWS)

	//		return FromString(str, CP_THREAD_ACP);

	//	# elif defined (SIV3D_TARGET_OSX)

	//	# endif
	//}
}
