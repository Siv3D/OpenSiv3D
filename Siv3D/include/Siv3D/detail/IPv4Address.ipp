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
	inline constexpr IPv4Address::IPv4Address(const value_type a, const value_type b, const value_type c, const value_type d) noexcept
		: m_data{ { a, b, c, d } } {}

	inline IPv4Address::IPv4Address(const value_type(&ipv4)[4]) noexcept
		: m_data{ { ipv4[0], ipv4[1], ipv4[2], ipv4[3] } } {}

	inline constexpr IPv4Address::IPv4Address(const std::array<value_type, 4>& ipv4) noexcept
		: m_data{ ipv4 } {}

	inline constexpr bool IPv4Address::isLoopback() const noexcept
	{
		return (m_data[0] == 127);
	}

	inline constexpr const std::array<IPv4Address::value_type, 4>& IPv4Address::getData() const noexcept
	{
		return m_data;
	}

	inline void IPv4Address::swap(IPv4Address& other)
	{
		m_data.swap(other.m_data);
	}

	inline size_t IPv4Address::hash() const noexcept
	{
		return Hash::FNV1a(m_data);
	}

	inline constexpr IPv4Address IPv4Address::Localhost() noexcept
	{
		return{ 127, 0, 0, 1 };
	}
}

template <>
void std::swap(s3d::IPv4Address& a, s3d::IPv4Address& b) noexcept
{
	a.swap(b);
}
