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

# pragma once
# include <Siv3D/Asset.hpp>

namespace s3d
{
	class IAsset::IAssetDetail
	{
	public:

		IAssetDetail();

		explicit IAssetDetail(const Array<String>& tags);

		~IAssetDetail();

		[[nodiscard]]
		AssetState getState() const;

		void setState(AssetState state);

		[[nodiscard]]
		const Array<AssetTag>& getTags() const;

	private:

		Array<String> m_tags;

		std::atomic<AssetState> m_state = AssetState::Uninitialized;
	};
}
