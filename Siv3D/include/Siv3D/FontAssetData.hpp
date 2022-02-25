//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "Font.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct FontAssetData : IAsset
	{
		FontMethod fontMethod = FontMethod::Bitmap;
		
		int32 fontSize = 0;
		
		FilePath path;
		
		size_t faceIndex = 0;
		
		Typeface typeface = Typeface::Regular;

		FontStyle style = FontStyle::Default;

		Font font;

		std::function<bool(FontAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(FontAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		FontAssetData();

		SIV3D_NODISCARD_CXX20
		FontAssetData(FontMethod _fontMethod, int32 _fontSize, FilePathView _path, size_t _faceIndex, FontStyle _style, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		FontAssetData(FontMethod _fontMethod, int32 _fontSize, Typeface _typeface, FontStyle _style, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(FontAssetData& asset, const String& hint);

		static void DefaultRelease(FontAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
