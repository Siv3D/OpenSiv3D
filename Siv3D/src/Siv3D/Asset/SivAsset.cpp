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

# include <Siv3D/Asset.hpp>
# include "IAssetDetail.hpp"

namespace s3d
{
	IAsset::IAsset()
		: pImpl{ std::make_shared<IAssetDetail>() } {}

	IAsset::IAsset(LoadOption loadOption, const Array<String>& tags)
		: pImpl{ std::make_shared<IAssetDetail>(loadOption, tags) } {}

	IAsset::~IAsset() {}

	AssetState IAsset::getState() const
	{
		return pImpl->getState();
	}

	bool IAsset::isUninitialized() const
	{
		const AssetState state = pImpl->getState();

		return (state == AssetState::Uninitialized);
	}

	bool IAsset::isFinished() const
	{
		const AssetState state = pImpl->getState();

		return ((state == AssetState::Loaded)
			|| (state == AssetState::Failed));
	}

	bool IAsset::isLoaded() const
	{
		const AssetState state = pImpl->getState();

		return (state == AssetState::Loaded);
	}

	void IAsset::setState(const AssetState state)
	{
		pImpl->setState(state);
	}
}
