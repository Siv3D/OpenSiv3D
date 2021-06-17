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

# include <Siv3D/FontAssetData.hpp>

namespace s3d
{
	FontAssetData::FontAssetData() {}

	FontAssetData::FontAssetData(const FontMethod _fontMethod, const int32 _fontSize, const FilePathView _path, const size_t _faceIndex, const FontStyle _style)
		: fontMethod{ _fontMethod }
		, fontSize{ _fontSize }
		, path{ _path }
		, faceIndex{ _faceIndex }
		, style{ _style } {}

	FontAssetData::FontAssetData(const FontMethod _fontMethod, const int32 _fontSize, const Typeface _typeface, const FontStyle _style)
		: fontMethod{ _fontMethod }
		, fontSize{ _fontSize }
		, typeface{ _typeface }
		, style{ _style } {}

	bool FontAssetData::load()
	{
		if (isUninitialized())
		{
			if (onLoad(*this))
			{
				setState(AssetState::Loaded);
			}
			else
			{
				setState(AssetState::Failed);
			}
		}

		return isLoaded();
	}

	void FontAssetData::release()
	{
		if (isUninitialized())
		{
			return;
		}

		onRelease(*this);

		setState(AssetState::Uninitialized);
	}

	bool FontAssetData::DefaultLoad(FontAssetData& asset)
	{
		if (asset.font)
		{
			return true;
		}

		if (asset.path)
		{
			asset.font = Font{ asset.fontMethod, asset.fontSize, asset.path, asset.faceIndex, asset.style };
		}
		else
		{
			asset.font = Font{ asset.fontMethod, asset.fontSize, asset.typeface, asset.style };
		}

		return static_cast<bool>(asset.font);
	}

	void FontAssetData::DefaultRelease(FontAssetData& asset)
	{
		asset.font.release();
	}
}
