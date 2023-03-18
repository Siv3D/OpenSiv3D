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

# include <array>
# include <Siv3D/Byte.hpp>
# include <Siv3D/ParseInt.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
		template <class CharType>
		[[nodiscard]]
		constexpr std::array<CharType, 2> ToHex(const Byte value) noexcept
		{
			constexpr char s[16] =
			{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
			};

			return{ {
				static_cast<CharType>(s[static_cast<uint8>(value) >> 4]),
				static_cast<CharType>(s[static_cast<uint8>(value) & 0xF]) } };
		}
	}

	void Formatter(FormatData& formatData, const Byte& value)
	{
		const auto hex = detail::ToHex<char32>(value);

		formatData.string.append(hex.begin(), hex.end());
	}

	std::ostream& operator <<(std::ostream& output, const Byte& value)
	{
		const auto hex = detail::ToHex<char>(value);

		return output.write(hex.data(), 2);
	}

	std::wostream& operator <<(std::wostream& output, const Byte& value)
	{
		const auto hex = detail::ToHex<wchar_t>(value);

		return output.write(hex.data(), 2);
	}

	std::istream& operator >>(std::istream& input, Byte& value)
	{
		std::string in;

		input >> in;

		value = Byte{ ParseInt<uint8>(Unicode::FromUTF8(in), Arg::radix = 16) };

		return input;
	}

	std::wistream& operator >>(std::wistream& input, Byte& value)
	{
		std::wstring in;

		input >> in;

		value = Byte{ ParseInt<uint8>(Unicode::FromWstring(in), Arg::radix = 16) };

		return input;
	}
}
