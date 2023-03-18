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

# include <Siv3D/MD5Value.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr std::array<char, 2> MD5ToHex(const uint8 value) noexcept
		{
			constexpr char s[16] =
			{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};

			return{ {
				s[static_cast<uint8>(value) >> 4],
				s[static_cast<uint8>(value) & 0xF] } };
		}
	}

	std::string MD5Value::asStdString() const
	{
		std::string result(32, '\0');

		for (size_t i = 0; i < 16; ++i)
		{
			std::array<char, 2> hexs = detail::MD5ToHex(value[i]);
			result[i * 2] = hexs[0];
			result[i * 2 + 1] = hexs[1];
		}

		return result;
	}

	String MD5Value::asString() const
	{
		String result(32, U'\0');

		for (size_t i = 0; i < 16; ++i)
		{
			std::array<char, 2> hexs = detail::MD5ToHex(value[i]);
			result[i * 2] = hexs[0];
			result[i * 2 + 1] = hexs[1];
		}

		return result;
	}

	void Formatter(FormatData& formatData, const MD5Value& value)
	{
		formatData.string.append(value.asString());
	}
}
