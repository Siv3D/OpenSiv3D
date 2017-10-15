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

# include <array>
# include <iostream>
# include "Siv3D/Byte.hpp"

namespace s3d
{
	namespace detail
	{
		template <class CharType>
		[[nodiscard]] constexpr std::array<CharType, 2> ToHex(const Byte value)
		{
			constexpr char s[16] =
			{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};

			return{{
				static_cast<CharType>(s[static_cast<uint8>(value) >> 4]),
				static_cast<CharType>(s[static_cast<uint8>(value) & 0xF]) }};
		}
	}

	COStream& operator <<(COStream& os, const Byte& value)
	{
		const auto hex = detail::ToHex<char>(value);

		return os.write(hex.data(), 2);
	}

	WOStream& operator <<(WOStream& os, const Byte& value)
	{
		const auto hex = detail::ToHex<wchar_t>(value);

		return os.write(hex.data(), 2);
	}

	C32OStream& operator <<(C32OStream& os, const Byte& value)
	{
		const auto hex = detail::ToHex<char32>(value);

		return os.write(hex.data(), 2);
	}
}
