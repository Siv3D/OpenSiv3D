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

# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/UnicodeConverter.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView BytesUnits[9] =
		{
			U"B"_sv,
			U"KiB"_sv,
			U"MiB"_sv,
			U"GiB"_sv,
			U"TiB"_sv,
			U"PiB"_sv,
			U"EiB"_sv,
			U"ZiB"_sv,
			U"YiB"_sv
		};

		static constexpr char8 HexTable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		String ThousandsSeparateInt(String&& value, const StringView separator)
		{
			String result = std::move(value);

			const size_t endIndex = result.starts_with(U'-') ? 1 : 0;

			size_t count = 0;

			for (size_t i = result.size(); i != endIndex; --i)
			{
				if (++count == 4)
				{
					result.insert(i, separator);
					count = 1;
				}
			}

			return result;
		}

		String ThousandsSeparateFloat(String&& value, const StringView separator)
		{
			String result = std::move(value);

			const size_t zeroPos = result.lastIndexOf(U'.');
			const size_t startIndex = (zeroPos == String::npos) ? result.size() : zeroPos;
			const size_t endIndex = result.starts_with(U'-') ? 1 : 0;

			size_t count = 0;

			for (size_t i = startIndex; i != endIndex; --i)
			{
				if (++count == 4)
				{
					result.insert(i, separator);
					count = 1;
				}
			}

			return result;
		}
	}

	String FormatDataSize(const int64 bytes)
	{
		double s = static_cast<double>(bytes);

		for (uint32 i = 0; i < 9; ++i)
		{
			if (s < 10.0)
			{
				return (ToString(s, 2) + detail::BytesUnits[i]);
			}
			else if (s < 100.0)
			{
				return (ToString(s, 1) + detail::BytesUnits[i]);
			}
			else if (s < 1024.0)
			{
				return (ToString(s, 0) + detail::BytesUnits[i]);
			}

			s /= 1024.0;
		}

		return{};
	}

	String PercentEncode(const StringView s)
	{
		String result;

		UTF32toUTF8_Converter coverter{};

		for (auto codePoint : s)
		{
			const size_t size = coverter.put(codePoint);

			for (size_t i = 0; i < size; ++i)
			{
				const char8 ch = coverter.get()[i];

				if (IsAlnum(ch) || (ch == '-') || (ch == '_') || (ch == '.') || (ch == '~'))
				{
					result.push_back(ch);
				}
				else
				{
					const char8 chars[3] = { '%', detail::HexTable[(ch >> 4) & 0xF], detail::HexTable[ch & 0xF] };
					result.append(std::begin(chars), std::end(chars));
				}
			}
		}

		return result;
	}
}
