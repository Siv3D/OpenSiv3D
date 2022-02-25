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
	template <class AssetType>
	inline AssetHandle<AssetType>::AssetHandle()
		: m_handle{ std::make_shared<AssetIDWrapperType>() } {}

	template <class AssetType>
	inline AssetHandle<AssetType>::AssetHandle(std::shared_ptr<AssetIDWrapperType>&& id)
		: m_handle{ std::move(id) } {}

	template <class AssetType>
	inline typename AssetHandle<AssetType>::IDType AssetHandle<AssetType>::id() const noexcept
	{
		return m_handle->id();
	}

	template <class AssetType>
	inline bool AssetHandle<AssetType>::isEmpty() const noexcept
	{
		return m_handle->id().isNull();
	}

	template <class AssetType>
	inline AssetHandle<AssetType>::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	template <class AssetType>
	inline bool AssetHandle<AssetType>::operator ==(const AssetHandle& other) const noexcept
	{
		return (m_handle->id() == other.m_handle->id());
	}

	template <class AssetType>
	inline bool AssetHandle<AssetType>::operator !=(const AssetHandle& other) const noexcept
	{
		return (m_handle->id() != other.m_handle->id());
	}

	template <class AssetType>
	inline void AssetHandle<AssetType>::release()
	{
		m_handle = std::make_shared<AssetIDWrapperType>();
	}
}
