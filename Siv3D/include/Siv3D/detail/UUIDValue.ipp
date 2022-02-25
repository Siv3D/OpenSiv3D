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
	inline constexpr UUIDValue::UUIDValue(const std::array<value_type, 16>& uuid) noexcept
		: m_data{ uuid } {}

	template <class Iterator>
	inline UUIDValue::UUIDValue(Iterator first, Iterator last)
	{
		if (std::distance(first, last) == 16)
		{
			std::copy(first, last, std::begin(m_data));
		}
	}

	inline constexpr bool UUIDValue::isNil() const noexcept
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

	inline constexpr const std::array<UUIDValue::value_type, 16>& UUIDValue::getData() const noexcept
	{
		return m_data;
	}

	inline void UUIDValue::swap(UUIDValue& other)
	{
		m_data.swap(other.m_data);
	}

	inline size_t UUIDValue::hash() const noexcept
	{
		return Hash::FNV1a(m_data);
	}
}

template <>
void std::swap(s3d::UUIDValue& a, s3d::UUIDValue& b) noexcept
{
	a.swap(b);
}
