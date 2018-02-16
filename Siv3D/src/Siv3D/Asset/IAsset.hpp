//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	enum class AssetType
	{
		Audio,

		Texture,

		Font,
	};

	class ISiv3DAsset
	{
	public:

		static ISiv3DAsset* Create();

		virtual ~ISiv3DAsset() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual bool registerAsset(AssetType assetType, const String& name, std::unique_ptr<IAsset>&& asset) = 0;

		virtual IAsset* getAsset(AssetType assetType, const String& name) = 0;

		virtual bool isRegistered(AssetType assetType, const String& name) const = 0;

		virtual bool preload(AssetType assetType, const String& name) = 0;

		virtual void release(AssetType assetType, const String& name) = 0;

		virtual void releaseAll(AssetType assetType) = 0;

		virtual void unregister(AssetType assetType, const String& name) = 0;

		virtual void unregisterAll(AssetType assetType) = 0;

		virtual bool isReady(AssetType assetType, const String& name) const = 0;
	};
}
