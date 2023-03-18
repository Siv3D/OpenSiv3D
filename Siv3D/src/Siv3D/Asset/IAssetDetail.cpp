//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "IAssetDetail.hpp"

namespace s3d
{
	IAsset::IAssetDetail::IAssetDetail() {}

	IAsset::IAssetDetail::IAssetDetail(const Array<String>& tags)
		: m_tags{ tags } {}

	IAsset::IAssetDetail::~IAssetDetail() {}

	AssetState IAsset::IAssetDetail::getState() const
	{
		return m_state;
	}

	void IAsset::IAssetDetail::setState(const AssetState state)
	{
		m_state = state;
	}

	const Array<AssetTag>& IAsset::IAssetDetail::getTags() const
	{
		return m_tags;
	}
}
