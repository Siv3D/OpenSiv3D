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

# include <Siv3D/FontAssetData.hpp>

namespace s3d
{
	FontAssetData::FontAssetData() {}

	FontAssetData::FontAssetData(const FontMethod _fontMethod, const int32 _fontSize, const FilePathView _path, const size_t _faceIndex, const FontStyle _style, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, fontMethod{ _fontMethod }
		, fontSize{ _fontSize }
		, path{ _path }
		, faceIndex{ _faceIndex }
		, style{ _style } {}

	FontAssetData::FontAssetData(const FontMethod _fontMethod, const int32 _fontSize, const Typeface _typeface, const FontStyle _style, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, fontMethod{ _fontMethod }
		, fontSize{ _fontSize }
		, typeface{ _typeface }
		, style{ _style } {}

	bool FontAssetData::load(const String& hint)
	{
		if (isUninitialized())
		{
			if (onLoad(*this, hint))
			{
				setState(AssetState::Loaded);
				return true;
			}
			else
			{
				setState(AssetState::Failed);
				return false;
			}
		}

		if (isAsyncLoading())
		{
			wait();
		}

		return isLoaded();
	}

	void FontAssetData::loadAsync(const String& hint)
	{
		if (isUninitialized())
		{
			setState(AssetState::AsyncLoading);

			m_task = Async([this, hint = hint]()
				{
					setState(onLoad(*this, hint) ? AssetState::Loaded : AssetState::Failed);
				});
		}
	}

	void FontAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void FontAssetData::release()
	{
		if (isUninitialized())
		{
			return;
		}

		if (isAsyncLoading())
		{
			wait();
		}

		onRelease(*this);

		setState(AssetState::Uninitialized);
	}

	bool FontAssetData::DefaultLoad(FontAssetData& asset, const String& hint)
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

		if (not asset.font)
		{
			return false;
		}

		asset.font.preload(hint);

		return true;
	}

	void FontAssetData::DefaultRelease(FontAssetData& asset)
	{
		asset.font.release();
	}
}
