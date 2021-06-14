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

	bool IAsset::isFinished() const
	{
		const State state = pImpl->getState();

		return ((state == State::Loaded)
			|| (state == State::Failed));
	}

	bool IAsset::isUninitialized() const
	{
		const State state = pImpl->getState();

		return (state == State::Uninitialized);
	}

	bool IAsset::isLoaded() const
	{
		const State state = pImpl->getState();

		return (state == State::Loaded);
	}

	void IAsset::setState(const State state)
	{
		pImpl->setState(state);
	}
}
