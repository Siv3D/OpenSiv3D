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

# include <Siv3D/TextureAssetData.hpp>

namespace s3d
{
	TextureAssetData::TextureAssetData() {}

	//TextureAssetData::TextureAssetData(const TextureMethod _fontMethod, const int32 _fontSize, const FilePathView _path, const size_t _faceIndex, const TextureStyle _style, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, fontMethod{ _fontMethod }
	//	, fontSize{ _fontSize }
	//	, path{ _path }
	//	, faceIndex{ _faceIndex }
	//	, style{ _style } {}

	//TextureAssetData::TextureAssetData(const TextureMethod _fontMethod, const int32 _fontSize, const Typeface _typeface, const TextureStyle _style, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, fontMethod{ _fontMethod }
	//	, fontSize{ _fontSize }
	//	, typeface{ _typeface }
	//	, style{ _style } {}

	bool TextureAssetData::load(const String& hint)
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

	void TextureAssetData::loadAsync(const String& hint)
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

	void TextureAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void TextureAssetData::release()
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

	bool TextureAssetData::DefaultLoad(TextureAssetData& asset, const String&)
	{
		if (asset.texture)
		{
			return true;
		}

		// [Siv3D ToDo]
		{



		}

		if (not asset.texture)
		{
			return false;
		}

		return true;
	}

	void TextureAssetData::DefaultRelease(TextureAssetData& asset)
	{
		asset.texture.release();
	}
}
