﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Number.hpp"

namespace s3d
{
	template <class Type>
	class AssetIDWrapper
	{
	public:

		using ValueType = uint32;

		inline static const ValueType NullAssetID = 0;

		inline static const  ValueType InvalidID = Largest<ValueType>();

	private:

		ValueType m_value = NullAssetID;

	public:

		constexpr AssetIDWrapper() = default;

		explicit constexpr AssetIDWrapper(ValueType id) noexcept
			: m_value(id) {}

		constexpr ValueType value() const noexcept
		{
			return m_value;
		}

		constexpr bool isNullAsset() const noexcept
		{
			return m_value == NullAssetID;
		}

		constexpr bool operator ==(const AssetIDWrapper& other) const noexcept
		{
			return m_value == other.m_value;
		}

		constexpr bool operator !=(const AssetIDWrapper& other) const noexcept
		{
			return m_value != other.m_value;
		}

		static constexpr AssetIDWrapper NullAsset() noexcept
		{
			return AssetIDWrapper(NullAssetID);
		}

		static constexpr AssetIDWrapper InvalidValue() noexcept
		{
			return AssetIDWrapper(InvalidID);
		}
	};

	template <class Type>
	class AssetHandle
	{
	private:

		AssetIDWrapper<Type> m_id;

	public:

		using IDWrapperType = AssetIDWrapper<Type>;

		constexpr AssetHandle() = default;

		constexpr AssetHandle(IDWrapperType id) noexcept
			: m_id(id) {}

		~AssetHandle();

		constexpr IDWrapperType id() const noexcept
		{
			return m_id;
		}
	};
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <class Type>
	struct hash<s3d::AssetIDWrapper<Type>>
	{
		[[nodiscard]] size_t operator()(const s3d::AssetIDWrapper<Type>& value) const noexcept
		{
			return hash<typename s3d::AssetIDWrapper<Type>::ValueType>()(value.value());
		}
	};
}
