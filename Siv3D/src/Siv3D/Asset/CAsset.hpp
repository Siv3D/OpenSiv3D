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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/String.hpp>
# include "IAsset.hpp"

namespace s3d
{
	class CAsset final : public ISiv3DAsset
	{
	public:

		CAsset();

		~CAsset() override;

		void update() override;

		bool registerAsset(AssetType assetType, AssetNameView name, std::unique_ptr<IAsset>&& asset) override;

		IAsset* getAsset(AssetType assetType, AssetNameView name) override;

		bool isRegistered(AssetType assetType, AssetNameView name) const override;

		bool load(AssetType assetType, AssetNameView name, StringView hint) override;

		void loadAsync(AssetType assetType, AssetNameView name, StringView hint) override;

		void wait(AssetType assetType, AssetNameView name) override;

		bool isReady(AssetType assetType, AssetNameView name) override;

		void release(AssetType assetType, AssetNameView name) override;

		void releaseAll(AssetType assetType) override;

		void unregister(AssetType assetType, AssetNameView name) override;

		void unregisterAll(AssetType assetType) override;

		HashTable<AssetName, AssetInfo> enumerate(AssetType assetType) override;

	private:

		std::array<HashTable<String, std::unique_ptr<IAsset>>, 5> m_assetLists;
	};
}
