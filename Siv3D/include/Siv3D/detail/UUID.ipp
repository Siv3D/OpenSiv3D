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

namespace s3d
{
	inline constexpr UUID::UUID(const std::array<value_type, 16>& uuid) noexcept
		: m_data{ uuid } {}

	template <class Iterator>
	inline UUID::UUID(Iterator first, Iterator last)
	{
		if (std::distance(first, last) == 16)
		{
			std::copy(first, last, std::begin(m_data));
		}
	}

	inline constexpr bool UUID::isNil() const noexcept
	{
		for (auto& value : m_data)
		{
			if (value != 0)
			{
				return false;
			}
		}

		return true;
	}

	inline constexpr const std::array<UUID::value_type, 16>& UUID::getData() const noexcept
	{
		return m_data;
	}

	inline void UUID::swap(UUID& other)
	{
		m_data.swap(other.m_data);
	}

	inline size_t UUID::hash() const noexcept
	{
		return Hash::FNV1a(m_data);
	}
}

template <>
void std::swap(s3d::UUID& a, s3d::UUID& b) noexcept
{
	a.swap(b);
}
