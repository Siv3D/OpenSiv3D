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

# include <memory.h>
# include <Siv3D/Format.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Byte.hpp>

namespace s3d
{
	namespace detail
	{
		void AppendInt(wchar** const p, const long value)
		{
			bool negative;
			unsigned long val;

			if (value < 0)
			{
				negative = true;
				val = -value;
			}
			else
			{
				negative = false;
				val = value;
			}

			wchar buffer[12];
			wchar* pos = &buffer[11];
			*pos = S3DCHAR('\0');

			do
			{
				*(--pos) = S3DCHAR('0') + static_cast<wchar>(val % 10);

				val = val / 10;

			} while (val != 0);

			if (negative)
			{
				*(--pos) = S3DCHAR('-');
			}

			const size_t length = &buffer[11] - pos;

			::memcpy(*p, pos, length * sizeof(wchar));

			*p += length;
		}
	}

	void Formatter(FormatData& formatData, const int32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const uint32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const long long value)
	{
		const detail::FormatInt buffer(static_cast<int64>(value));
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const unsigned long long value)
	{
		const detail::FormatInt buffer(static_cast<uint64>(value));
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const double value)
	{
		wchar buf[384];
		const size_t len = detail::FormatFloat(buf, value, formatData.decimalPlace.value, false);
		formatData.string.append(buf, len);
	}

	void Formatter(FormatData& formatData, const void* value)
	{
	# if (SIV3D_PLATFORM_PTR_SIZE == 4)

		formatData.string.append(ToHex(reinterpret_cast<uint32>(value)).lpad(8, L'0'));

	# elif (SIV3D_PLATFORM_PTR_SIZE == 8)

		formatData.string.append(ToHex(reinterpret_cast<uint64>(value)).lpad(16, L'0'));

	# endif
	}

	void Formatter(FormatData& formatData, const char16_t ch)
	{
		formatData.string.push_back(static_cast<wchar>(ch));
	}
	
	void Formatter(FormatData& formatData, const char32_t ch)
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		const auto c = CharacterSet::GetUTF16CodePoint(ch);
		
		if (!c[1])
		{
			formatData.string.push_back(static_cast<wchar>(c[0]));
		}
		else
		{
			formatData.string.push_back(static_cast<wchar>(c[0]));
		
			formatData.string.push_back(static_cast<wchar>(c[1]));
		}
		
	# else
		
		formatData.string.push_back(ch);
		
	# endif
	}
	
	void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(S3DSTR("null"), 4);
	}

	void Formatter(FormatData& formatData, const bool value)
	{
		if (value)
		{
			formatData.string.append(S3DSTR("true"), 4);
		}
		else
		{
			formatData.string.append(S3DSTR("false"), 5);
		}
	}
	
	std::ostream& operator <<(std::ostream& os, const ByteArrayView& value)
	{
		return os << Format(value);
	}
	
	std::wostream& operator <<(std::wostream& os, const ByteArrayView& value)
	{
		return os << Format(value);
	}
}
