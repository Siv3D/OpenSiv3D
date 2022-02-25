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
	inline AssetIDWrapper<AssetTag>::AssetIDWrapper(const IDType id) noexcept
		: m_id{ id } {}

	template <class AssetTag>
	inline constexpr typename AssetIDWrapper<AssetTag>::IDType AssetIDWrapper<AssetTag>::id() const noexcept
	{
		return m_id;
	}
}
