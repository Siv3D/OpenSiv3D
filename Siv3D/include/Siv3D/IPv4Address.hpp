//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	struct IPv4Address
	{
		uint8 asUint8[4] = { 0, 0, 0, 0 };

		IPv4Address() = default;

		constexpr IPv4Address(uint8 a, uint8 b, uint8 c, uint8 d) noexcept;

		explicit IPv4Address(StringView ipv4);

		constexpr bool isLoopback() const noexcept;

		constexpr bool isPrivate() const noexcept;

		[[nodiscard]]
		String str() const;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		static constexpr IPv4Address Loopback() noexcept;
	};
}

# include "detail/IPv4Address.ipp"
