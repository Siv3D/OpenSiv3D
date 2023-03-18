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
# include <Siv3D/Common.hpp>

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

		char32 codePoint;
	};

	inline constexpr const offset_pt invalid_pt = { -1, 0 };

	inline offset_pt utf8_decode_check(const char8* s, const size_t length)
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

			const char32 pt = (b0 & 0x1F) << 6 | (b1 & 0x3F);

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

			const char32 pt = (b0 & 0x0F) << 12 | (b1 & 0x3F) << 6 | (b2 & 0x3F);

			if (pt < 0x800)
			{
				return invalid_pt;
			}

			return{ 3, pt };
		}
		else if (b0 < 0xF8)
		{
			if (length < 4)
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

			const char32 pt = (b0 & 0x0F) << 18 | (b1 & 0x3F) << 12 | (b2 & 0x3F) << 6 | (b3 & 0x3F);

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

	inline char32 utf8_decode(const char8* s, const size_t length, int32& offset)
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

	inline constexpr bool is_high_surrogate(const char16 c) { return (c >= 0xD800) && (c < 0xDC00); }

	inline constexpr bool is_low_surrogate(const char16 c) { return (c >= 0xDC00) && (c < 0xE000); }

	inline offset_pt utf16_decode_check(const char16* const s, const size_t length)
	{
		if (is_high_surrogate(s[0]) && length >= 2 && is_low_surrogate(s[1]))
		{
			// High surrogate followed by low surrogate
			const char32 pt = (((s[0] - 0xD800) << 10) | (s[1] - 0xDC00)) + 0x10000;

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

	inline char32 utf16_decode(const char16* s, const size_t length, int32& offset)
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
}