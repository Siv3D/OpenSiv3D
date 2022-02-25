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
	inline constexpr Input::Input(const InputDeviceType deviceType, const uint8 code, const uint8 playerIndex) noexcept
		: m_deviceType{ deviceType }
		, m_code{ code }
		, m_playerIndex{ playerIndex } {}

	inline constexpr InputDeviceType Input::deviceType() const noexcept
	{
		return m_deviceType;
	}

	inline constexpr uint8 Input::code() const noexcept
	{
		return m_code;
	}

	inline constexpr uint8 Input::playerIndex() const noexcept
	{
		return m_playerIndex;
	}

	inline constexpr uint32 Input::asUint32() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<uint32>(*this);
	# else
		return (uint32(m_playerIndex) << 16) | (uint32(m_code) << 8) | (uint32(m_deviceType));
	# endif
	}

	inline constexpr InputCombination Input::operator +(const Input other) const noexcept
	{
		return{ *this, other };
	}
}
