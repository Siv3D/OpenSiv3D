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

# include <Siv3D/UnicodeConverter.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Unicode/UnicodeUtility.hpp>
# include <ThirdParty/miniutf/miniutf.hpp>

namespace s3d
{
	bool UTF8toUTF32_Converter::put(const char8 code) noexcept
	{
		m_buffer[m_count++] = code;

		const auto result = detail::utf8_decode_check(m_buffer, m_count);

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

	bool UTF16toUTF32_Converter::put(const char16 code) noexcept
	{
		if (m_hasHighSurrogate)
		{
			m_hasHighSurrogate = false;

			if (Unicode::IsHighSurrogate(code))
			{
				// error
				m_result = 0xFFFD;
			}
			else if (Unicode::IsLowSurrogate(code))
			{
				// ok
				m_result = ((((m_buffer - 0xD800) << 10) | (code - 0xDC00)) + 0x10000);
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
			if (Unicode::IsHighSurrogate(code))
			{
				// ok
				m_buffer = code;

				m_hasHighSurrogate = true;

				return false;
			}
			else if (Unicode::IsLowSurrogate(code))
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

	size_t UTF32toUTF8_Converter::put(const char32 code) noexcept
	{
		char8* pBuffer = m_buffer.data();

		detail::UTF8_Encode(&pBuffer, code);

		return (pBuffer - m_buffer.data());
	}

	size_t UTF32toUTF16_Converter::put(const char32 code) noexcept
	{
		char16* pBuffer = m_buffer.data();

		detail::UTF16_Encode(&pBuffer, code);

		return (pBuffer - m_buffer.data());
	}
}
