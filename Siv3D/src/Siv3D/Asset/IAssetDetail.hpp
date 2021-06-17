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
# include <Siv3D/Asset.hpp>

namespace s3d
{
	class IAsset::IAssetDetail
	{
	public:

		IAssetDetail();

		IAssetDetail(LoadOption loadOption, const Array<String>& tags);

		~IAssetDetail();

		[[nodiscard]]
		AssetState getState() const;

		void setState(AssetState state);

	private:

		LoadOption m_loadOption = LoadOption::Default;

		Array<String> m_tags;

		AssetState m_state = AssetState::Uninitialized;
	};
}
