//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Formatter.hpp>
# include <Siv3D/IntFormatter.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const bool value)
	{
		formatData.string.append(value ? U"true"_sv : U"false"_sv);
	}

	void Formatter(FormatData& formatData, const int8 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	void Formatter(FormatData& formatData, const uint8 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	void Formatter(FormatData& formatData, const int16 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	void Formatter(FormatData& formatData, const uint16 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
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

	void Formatter(FormatData& formatData, const long value)
	{
		if constexpr (sizeof(long) == sizeof(int32))
		{
			Formatter(formatData, static_cast<int32>(value));
		}
		else
		{
			Formatter(formatData, static_cast<long long>(value));
		}
	}

	void Formatter(FormatData& formatData, const unsigned long value)
	{
		if constexpr (sizeof(unsigned long) == sizeof(uint32))
		{
			Formatter(formatData, static_cast<uint32>(value));
		}
		else
		{
			Formatter(formatData, static_cast<unsigned long long>(value));
		}
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

	void Formatter(FormatData& formatData, const float value)
	{
		Formatter(formatData, static_cast<double>(value));
	}

	void Formatter(FormatData& formatData, const long double value)
	{
		Formatter(formatData, static_cast<double>(value));
	}

	void Formatter(FormatData& formatData, const char ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char8_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char16_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const wchar_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char32_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(U"null"_sv);
	}

	void Formatter(FormatData& formatData, const void* value)
	{
		const String hex = ToHex(reinterpret_cast<std::uintptr_t>(value));
		constexpr size_t HexRepresentationLength = (sizeof(void*) * 2);

		formatData.string.reserve(formatData.string.size() + HexRepresentationLength);
		formatData.string.append((HexRepresentationLength - hex.size()), U'0');
		formatData.string.append(hex);
	}

	void Formatter(FormatData& formatData, const char32_t* s)
	{
		formatData.string.append(s);
	}

	void Formatter(FormatData& formatData, const std::u32string& s)
	{
		formatData.string.append(s);
	}

# if __cpp_lib_three_way_comparison

	void Formatter(FormatData& formatData, const std::strong_ordering value)
	{
		if (std::is_lt(value))
		{
			formatData.string.append(U"LT"_sv);
		}
		else if (std::is_gt(value))
		{
			formatData.string.append(U"GT"_sv);
		}
		else
		{
			formatData.string.append(U"EQ"_sv);
		}
	}

	void Formatter(FormatData& formatData, const std::weak_ordering value)
	{
		if (std::is_lt(value))
		{
			formatData.string.append(U"LT"_sv);
		}
		else if (std::is_gt(value))
		{
			formatData.string.append(U"GT"_sv);
		}
		else
		{
			formatData.string.append(U"EQ"_sv);
		}
	}

	void Formatter(FormatData& formatData, const std::partial_ordering value)
	{
		if (std::is_lt(value))
		{
			formatData.string.append(U"LT"_sv);
		}
		else if (std::is_gt(value))
		{
			formatData.string.append(U"GT"_sv);
		}
		else if (std::is_eq(value))
		{
			formatData.string.append(U"EQ"_sv);
		}
		else
		{
			formatData.string.append(U"UN"_sv);
		}
	}

# endif
}
