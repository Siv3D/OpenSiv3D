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
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "Number.hpp"

namespace s3d
{
	template <class AssetTag>
	class AssetID
	{
	public:

		using value_type = size_t;

		static constexpr value_type NullID = 0;

		static constexpr value_type InvalidID = Largest<value_type>;

		SIV3D_NODISCARD_CXX20
		AssetID() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr AssetID(value_type id) noexcept;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		constexpr auto operator <=>(const AssetID&) const = default;

	# else

		[[nodiscard]]
		constexpr bool operator ==(const AssetID& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator !=(const AssetID& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator <(const AssetID& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator <=(const AssetID& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator >(const AssetID& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator >=(const AssetID& other) const noexcept;

	# endif

		[[nodiscard]]
		constexpr value_type value() const noexcept;

		[[nodiscard]]
		constexpr bool isNull() const noexcept;

		[[nodiscard]]
		constexpr bool isInvalid() const noexcept;

		[[nodiscard]]
		static constexpr AssetID NullAsset() noexcept;

		[[nodiscard]]
		static constexpr AssetID InvalidValue() noexcept;

	private:

		value_type m_value = NullID;
	};
}

template <class AssetTag>
struct std::hash<s3d::AssetID<AssetTag>>
{
	[[nodiscard]]
	size_t operator()(const s3d::AssetID<AssetTag>& value) const noexcept
	{
		return std::hash<typename s3d::AssetID<AssetTag>::value_type>{}(value.value());
	}
};

# include "detail/AssetID.ipp"
