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

# pragma once
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	union IPv4
	{
		uint32 asUint = 0;

		uint8 asUint8[4];

		IPv4() = default;

		explicit IPv4(uint32 value) noexcept
			: asUint(value) {}

		constexpr IPv4(uint8 b1, uint8 b2, uint8 b3, uint8 b4) noexcept
			: asUint8{ b1,b2,b3,b4 } {}

		explicit IPv4(const String& ipv4);

		[[nodiscard]] static constexpr IPv4 localhost() noexcept
		{
			return{ 127,0,0,1 };
		}

		String toStr() const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	inline void Formatter(FormatData& formatData, const IPv4& value)
	{
		formatData.string.append(value.toStr());
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const IPv4& value)
	{
		return output << value.toStr();
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, IPv4& value)
	{
		CharType unused;
		uint32 b1 = 0, b2 = 0, b3 = 0, b4 = 0;
		input >> b1 >> unused >> b2 >> unused >> b3 >> unused >> b4;
		value.asUint8[0] = static_cast<uint8>(b1);
		value.asUint8[1] = static_cast<uint8>(b2);
		value.asUint8[2] = static_cast<uint8>(b3);
		value.asUint8[3] = static_cast<uint8>(b4);

		return input;
	}
}
