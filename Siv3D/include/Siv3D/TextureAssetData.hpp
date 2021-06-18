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
# include "Common.hpp"
# include "Asset.hpp"
# include "Texture.hpp"
# include "Emoji.hpp"
# include "Icon.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct TextureAssetData : IAsset
	{
		FilePath path;

		FilePath secondaryPath;

		Color rgbColor = Color{ 255 };

		TextureDesc desc = TextureDesc::Mipped;

		Emoji emoji;

		Icon icon;

		int32 iconSize = 0;

		Texture texture;

		std::function<bool(TextureAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(TextureAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		TextureAssetData();

		//SIV3D_NODISCARD_CXX20
		//TextureAssetData(TextureMethod _fontMethod, int32 _fontSize, FilePathView _path, size_t _faceIndex, TextureStyle _style, const Array<AssetTag>& tags = {});

		//SIV3D_NODISCARD_CXX20
		//TextureAssetData(TextureMethod _fontMethod, int32 _fontSize, Typeface _typeface, TextureStyle _tyle, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(TextureAssetData& asset, const String& hint);

		static void DefaultRelease(TextureAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
