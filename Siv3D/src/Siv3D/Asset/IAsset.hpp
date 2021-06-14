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
# include <Siv3D/Common.hpp>
# include <Siv3D/Asset.hpp>

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

		virtual bool registerAsset(AssetType assetType, const AssetName& name, std::unique_ptr<IAsset>&& asset) = 0;

		virtual IAsset* getAsset(AssetType assetType, AssetNameView name) = 0;

		virtual bool isRegistered(AssetType assetType, AssetNameView name) const = 0;
	};
}
