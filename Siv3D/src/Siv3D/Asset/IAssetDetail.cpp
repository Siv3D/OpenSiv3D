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

# include "IAssetDetail.hpp"

namespace s3d
{
	IAsset::IAssetDetail::IAssetDetail() {}

	IAsset::IAssetDetail::IAssetDetail(const LoadOption loadOption, const Array<String>& tags)
		: m_loadOption{ loadOption }
		, m_tags{ tags } {}

	IAsset::IAssetDetail::~IAssetDetail() {}

	AssetState IAsset::IAssetDetail::getState() const
	{
		return m_state;
	}

	void IAsset::IAssetDetail::setState(const AssetState state)
	{
		m_state = state;
	}
}
