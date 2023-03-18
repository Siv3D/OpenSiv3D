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

# include <Siv3D/TextureAssetData.hpp>

namespace s3d
{
	TextureAssetData::TextureAssetData() {}

	TextureAssetData::TextureAssetData(const FilePathView _path, const TextureDesc _desc, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, desc{ _desc } {}

	TextureAssetData::TextureAssetData(const FilePathView rgb, const FilePathView alpha, const TextureDesc _desc, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ rgb }
		, secondaryPath{ alpha }
		, desc{ _desc } {}

	TextureAssetData::TextureAssetData(const Color& rgb, const FilePathView alpha, TextureDesc _desc, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, secondaryPath{ alpha }
		, rgbColor{ rgb }
		, desc{ _desc } {}

	TextureAssetData::TextureAssetData(const Emoji& _emoji, const TextureDesc _desc, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, desc{ _desc }
		, emoji{ _emoji }{}

	TextureAssetData::TextureAssetData(const Icon& _icon, const int32 _size, const TextureDesc _desc, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, desc{ _desc }
		, icon{ _icon }
		, iconSize{ _size }{}

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

		if (asset.path)
		{
			if (asset.secondaryPath)
			{
				asset.texture = Texture{ asset.path, asset.secondaryPath, asset.desc };
			}
			else
			{
				asset.texture = Texture{ asset.path, asset.desc };
			}
		}
		else if (asset.secondaryPath)
		{
			asset.texture = Texture{ asset.rgbColor, asset.secondaryPath };
		}
		else if (asset.emoji.codePoints)
		{
			asset.texture = Texture{ asset.emoji, asset.desc };
		}
		else if (asset.icon.code)
		{
			asset.texture = Texture{ asset.icon, asset.iconSize, asset.desc };
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
