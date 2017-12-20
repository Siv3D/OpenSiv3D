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

# include "../Siv3DEngine.hpp"
# include "IAsset.hpp"
# include <Siv3D/Asset.hpp>

namespace s3d
{
	namespace detail
	{
		static Texture FromAsset(const IAsset* asset)
		{
			if (const TextureAssetData* textureAssetData = dynamic_cast<const TextureAssetData*>(asset))
			{
				return textureAssetData->texture;
			}

			return Texture();
		}
	}

	TextureAssetData::TextureAssetData(
		const FilePath& _path,
		TextureDesc _desc,
		const AssetParameter& _parameter,
		std::function<bool(TextureAssetData&)> _onPreload,
		std::function<bool(TextureAssetData&)> _onUpdate,
		std::function<bool(TextureAssetData&)> _onRelease)
		: IAsset(_parameter)
		, path(_path)
		, desc(_desc)
		, onPreload(_onPreload)
		, onUpdate(_onUpdate)
		, onRelease(_onRelease)
	{

	}

	TextureAsset::TextureAsset(const AssetName& name)
		: Texture(detail::FromAsset(Siv3DEngine::GetAsset()->getAsset(AssetType::Texture, name)))
	{

	}

	bool TextureAsset::Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, path, TextureDesc::Unmipped, parameter);
	}

	bool TextureAsset::Register(const AssetName& name, const FilePath& path, TextureDesc desc, const AssetParameter& parameter)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Texture, name, std::make_unique<TextureAssetData>(path, desc, parameter));
	}

	bool TextureAsset::Register(const AssetName& name, const TextureAssetData& data)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Texture, name, std::make_unique<TextureAssetData>(data));
	}

	bool TextureAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isRegistered(AssetType::Texture, name);
	}

	bool TextureAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->preload(AssetType::Texture, name);
	}

	void TextureAsset::Release(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->release(AssetType::Texture, name);
	}

	void TextureAsset::ReleaseAll()
	{
		Siv3DEngine::GetAsset()->releaseAll(AssetType::Texture);
	}

	void TextureAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->unregister(AssetType::Texture, name);
	}

	void TextureAsset::UnregisterAll()
	{
		Siv3DEngine::GetAsset()->unregisterAll(AssetType::Texture);
	}

	bool TextureAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isReady(AssetType::Texture, name);
	}
}
