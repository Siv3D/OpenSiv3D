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

# include <Siv3D/Format.hpp>
# include <Siv3D/IntFormat.hpp>
# include <Siv3D/FloatFormat.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	namespace detail
	{
		void AppendInt(char32** const p, const long value)
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

			char32 buffer[12];
			char32* pos = &buffer[11];
			*pos = U'\0';

			do
			{
				*(--pos) = U'0' + static_cast<char32>(val % 10);

				val = val / 10;

			} while (val != 0);

			if (negative)
			{
				*(--pos) = U'-';
			}

			const size_t length = &buffer[11] - pos;

			::memcpy(*p, pos, length * sizeof(char32));

			*p += length;
		}
	}

	void Formatter(FormatData& formatData, const int32 value)
	{
		const detail::IntFormatter buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const uint32 value)
	{
		const detail::IntFormatter buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const long long value)
	{
		const detail::IntFormatter buffer(static_cast<int64>(value));
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const unsigned long long value)
	{
		const detail::IntFormatter buffer(static_cast<uint64>(value));
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	void Formatter(FormatData& formatData, const double value)
	{
		char32 buf[384];
		const size_t len = detail::FormatFloat(buf, value, formatData.decimalPlace.value, false);
		formatData.string.append(buf, len);
	}

	void Formatter(FormatData& formatData, const void* value)
	{
	# if (SIV3D_PLATFORM_PTR_SIZE == 4)

		formatData.string.append(ToHex(reinterpret_cast<uint32>(value)).lpad(8, U'0'));

	# elif (SIV3D_PLATFORM_PTR_SIZE == 8)

		formatData.string.append(ToHex(reinterpret_cast<uint64>(value)).lpad(16, U'0'));

	# endif
	}

	void Formatter(FormatData& formatData, const char16_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}
	
	void Formatter(FormatData& formatData, const char32_t ch)
	{
		formatData.string.push_back(ch);
	}
	
	void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(U"null", 4);
	}

	void Formatter(FormatData& formatData, const bool value)
	{
		if (value)
		{
			formatData.string.append(U"true", 4);
		}
		else
		{
			formatData.string.append(U"false", 5);
		}
	}

	void Formatter(FormatData& formatData, __m128 value)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		Formatter(formatData, Vec4(value.m128_f32[0], value.m128_f32[1], value.m128_f32[2], value.m128_f32[3]));

	# else

		Formatter(formatData, Vec4(value[0], value[1], value[2], value[3]));
	
	# endif	
	}
}
