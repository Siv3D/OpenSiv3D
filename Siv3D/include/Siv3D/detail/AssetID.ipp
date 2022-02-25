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
	template <class AssetTag>
	inline constexpr AssetID<AssetTag>::AssetID(const value_type id) noexcept
		: m_value{ id } {}

# ifndef __cpp_impl_three_way_comparison

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator ==(const AssetID& other) const noexcept
	{
		return (m_value == other.m_value);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator !=(const AssetID& other) const noexcept
	{
		return (m_value != other.m_value);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator <(const AssetID& other) const noexcept
	{
		return (m_value < other.m_value);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator <=(const AssetID& other) const noexcept
	{
		return (m_value <= other.m_value);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator >(const AssetID& other) const noexcept
	{
		return (m_value > other.m_value);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::operator >=(const AssetID& other) const noexcept
	{
		return (m_value >= other.m_value);
	}

# endif

	template <class AssetTag>
	inline constexpr typename AssetID<AssetTag>::value_type AssetID<AssetTag>::value() const noexcept
	{
		return m_value;
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::isNull() const noexcept
	{
		return (m_value == NullID);
	}

	template <class AssetTag>
	inline constexpr bool AssetID<AssetTag>::isInvalid() const noexcept
	{
		return (m_value == InvalidID);
	}

	template <class AssetTag>
	inline constexpr AssetID<AssetTag> AssetID<AssetTag>::NullAsset() noexcept
	{
		return AssetID{ NullID };
	}

	template <class AssetTag>
	inline constexpr AssetID<AssetTag> AssetID<AssetTag>::InvalidValue() noexcept
	{
		return AssetID{ InvalidID };
	}
}
