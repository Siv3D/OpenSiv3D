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

# include <Siv3D/Asset.hpp>
# include "IAssetDetail.hpp"

namespace s3d
{
	IAsset::IAsset()
		: pImpl{ std::make_shared<IAssetDetail>() } {}

	IAsset::IAsset(const Array<String>& tags)
		: pImpl{ std::make_shared<IAssetDetail>(tags) } {}

	IAsset::~IAsset() {}

	AssetState IAsset::getState() const
	{
		return pImpl->getState();
	}

	const Array<AssetTag>& IAsset::getTags() const
	{
		return pImpl->getTags();
	}

	bool IAsset::isAsyncLoading() const
	{
		return (pImpl->getState() == AssetState::AsyncLoading);
	}

	bool IAsset::isFinished() const
	{
		const AssetState state = pImpl->getState();

		return ((state == AssetState::Loaded)
			|| (state == AssetState::Failed));
	}

	bool IAsset::isUninitialized() const
	{
		return (pImpl->getState() == AssetState::Uninitialized);
	}

	bool IAsset::isLoaded() const
	{
		return (pImpl->getState() == AssetState::Loaded);
	}

	void IAsset::setState(const AssetState state)
	{
		pImpl->setState(state);
	}
}
