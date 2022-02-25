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

# pragma once

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		constexpr uint8 MakeByte(const uint32 c0, const uint32 c1) noexcept
		{
			const uint32 n0 = ((c0 & 0xF) + ((c0 & 0x40) >> 6) * 9);
			const uint32 n1 = ((c1 & 0xF) + ((c1 & 0x40) >> 6) * 9);
			return static_cast<uint8>(n0 * 16 + n1);
		}
	}

	inline constexpr MD5Value::MD5Value() noexcept
		: value{ { 0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e } } {}

	inline constexpr MD5Value::MD5Value(const std::array<uint8, 16>& md5) noexcept
		: value{ md5 } {}

	inline constexpr MD5Value::MD5Value(const std::string_view md5)
		: value{}
	{
		if (md5.length() != 32)
		{
			throw Error{ U"MD5Value: Invalid MD5 string" };
		}

		for (const char c : md5)
		{
			if ((not InRange(c, '0', '9'))
				&& (not InRange(c, 'a', 'f'))
				&& (not InRange(c, 'A', 'F')))
			{
				throw Error{ U"MD5Value: Invalid MD5 string" };
			}
		}

		for (size_t i = 0; i < 16; ++i)
		{
			value[i] = detail::MakeByte(md5[i * 2], md5[i * 2 + 1]);
		}
	}

	inline constexpr MD5Value::MD5Value(const StringView md5)
		: value{}
	{
		if (md5.length() != 32)
		{
			throw Error{ U"MD5Value: Invalid MD5 string" };
		}

		for (const char32 c : md5)
		{
			if ((not InRange(c, U'0', U'9'))
				&& (not InRange(c, U'a', U'f'))
				&& (not InRange(c, U'A', U'F')))
			{
				throw Error{ U"MD5Value: Invalid MD5 string" };
			}
		}

		for (size_t i = 0; i < 16; ++i)
		{
			value[i] = detail::MakeByte(md5[i * 2], md5[i * 2 + 1]);
		}
	}

	inline size_t MD5Value::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
