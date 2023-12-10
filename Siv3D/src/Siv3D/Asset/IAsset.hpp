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
# include <Siv3D/Common.hpp>
# include <Siv3D/Asset.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	enum class AssetType
	{
		Audio,

		Texture,

		Font,

		VertexShader,

		PixelShader,
	};

	class SIV3D_NOVTABLE ISiv3DAsset
	{
	public:

		static ISiv3DAsset* Create();

		virtual ~ISiv3DAsset() = default;

		virtual void update() = 0;

		virtual bool registerAsset(AssetType assetType, AssetNameView name, std::unique_ptr<IAsset>&& asset) = 0;

		virtual IAsset* getAsset(AssetType assetType, AssetNameView name) = 0;

		virtual bool isRegistered(AssetType assetType, AssetNameView name) const = 0;

		virtual bool load(AssetType assetType, AssetNameView name, StringView hint) = 0;

		virtual void loadAsync(AssetType assetType, AssetNameView name, StringView hint) = 0;

		virtual void wait(AssetType assetType, AssetNameView name) = 0;

		virtual bool isReady(AssetType assetType, AssetNameView name) = 0;

		virtual void release(AssetType assetType, AssetNameView name) = 0;

		virtual void releaseAll(AssetType assetType) = 0;

		virtual void unregister(AssetType assetType, AssetNameView name) = 0;

		virtual void unregisterAll(AssetType assetType) = 0;

		virtual HashTable<AssetName, AssetInfo> enumerate(AssetType assetType) = 0;
	};
}
