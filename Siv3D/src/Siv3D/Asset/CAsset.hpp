//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <unordered_map>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Asset.hpp>
# include "IAsset.hpp"

namespace s3d
{
	class CAsset : public ISiv3DAsset
	{
	private:

		std::array<HashTable<String, std::unique_ptr<IAsset>>, 1> m_assetLists;
	
	public:

		CAsset();

		~CAsset() override;

		bool init() override;

		void update() override;

		bool registerAsset(AssetType assetType, const String& name, std::unique_ptr<IAsset>&& asset) override;

		IAsset* getAsset(AssetType assetType, const String& name) override;

		bool isRegistered(AssetType assetType, const String& name) const override;

		bool preload(AssetType assetType, const String& name) override;

		void release(AssetType assetType, const String& name) override;

		void releaseAll(AssetType assetType) override;

		void unregister(AssetType assetType, const String& name) override;

		void unregisterAll(AssetType assetType) override;

		bool isReady(AssetType assetType, const String& name) const override;
	};
}
