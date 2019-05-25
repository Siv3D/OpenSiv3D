//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextureAsset.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3DEngine.hpp>
# include <Asset/IAsset.hpp>

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

	const String& TextureAssetData::Name()
	{
		static const String name = U"Texture";

		return name;
	}

	bool TextureAssetData::DefaultPreload(TextureAssetData& asset)
	{
		if (asset.texture)
		{
			return true;
		}

		asset.texture = Texture(asset.path, asset.desc);

		return !asset.texture.isEmpty();
	}

	bool TextureAssetData::DefaultUpdate(TextureAssetData&)
	{
		return true;
	}

	bool TextureAssetData::DefaultRelease(TextureAssetData& asset)
	{
		asset.texture.release();

		return true;
	}

	TextureAssetData::TextureAssetData()
		: IAsset()
		, onPreload(DefaultPreload)
		, onUpdate(DefaultUpdate)
		, onRelease(DefaultRelease)
	{

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

	bool TextureAssetData::preload()
	{
		if (uninitialized())
		{
			setState(onPreload(*this) ? State::LoadSucceeded : State::LoadFailed);
		}

		return loadSucceeded();
	}

	void TextureAssetData::preloadAsync()
	{
		if (uninitialized())
		{
			launchLoading([this]() { return onPreload(*this); });

			setState(State::PreloadingAsync);
		}
	}

	bool TextureAssetData::update()
	{
		if (!isPreloaded())
		{
			return false;
		}

		return onUpdate(*this);
	}

	bool TextureAssetData::release()
	{
		if (uninitialized())
		{
			return true;
		}

		const bool result = onRelease(*this);

		setState(State::Uninitialized);

		return result;
	}

	TextureAsset::TextureAsset(const AssetName& name)
		: Texture(detail::FromAsset(Siv3DEngine::Get<ISiv3DAsset>()->getAsset(AssetType::Texture, name)))
	{

	}

	TextureAsset::TextureAsset(const AssetName& name, const Texture& dummy)
		: Texture(IsReady(name) ? detail::FromAsset(Siv3DEngine::Get<ISiv3DAsset>()->getAsset(AssetType::Texture, name)) : dummy)
	{

	}

	bool TextureAsset::Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, path, TextureDesc::Unmipped, parameter);
	}

	bool TextureAsset::Register(const AssetName& name, const FilePath& path, TextureDesc desc, const AssetParameter& parameter)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Texture, name, std::make_unique<TextureAssetData>(path, desc, parameter));
	}

	bool TextureAsset::Register(const AssetName& name, const Icon& icon, const AssetParameter& parameter)
	{
		return Register(name, icon, TextureDesc::Mipped, parameter);
	}

	bool TextureAsset::Register(const AssetName& name, const Icon& icon, const TextureDesc desc, const AssetParameter& parameter)
	{
		return Register(name, TextureAssetData(FilePath(), desc, parameter,
			[=](TextureAssetData & a) { a.texture = Texture(icon, a.desc); return !!a.texture; },
			TextureAssetData::DefaultUpdate,
			TextureAssetData::DefaultRelease
		));
	}

	bool TextureAsset::Register(const AssetName& name, const Emoji& emoji, const AssetParameter& parameter)
	{
		return Register(name, emoji, TextureDesc::Mipped, parameter);
	}

	bool TextureAsset::Register(const AssetName& name, const Emoji& emoji, const TextureDesc desc, const AssetParameter& parameter)
	{
		return Register(name, TextureAssetData(FilePath(), desc, parameter,
			[=](TextureAssetData & a) { a.texture = Texture(emoji, a.desc); return !!a.texture; },
			TextureAssetData::DefaultUpdate,
			TextureAssetData::DefaultRelease
		));
	}

	bool TextureAsset::Register(const AssetName& name, const TextureAssetData& data)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Texture, name, std::make_unique<TextureAssetData>(data));
	}

	bool TextureAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isRegistered(AssetType::Texture, name);
	}

	bool TextureAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->preload(AssetType::Texture, name);
	}

	void TextureAsset::Release(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->release(AssetType::Texture, name);
	}

	void TextureAsset::ReleaseAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->releaseAll(AssetType::Texture);
	}

	void TextureAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregister(AssetType::Texture, name);
	}

	void TextureAsset::UnregisterAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregisterAll(AssetType::Texture);
	}

	bool TextureAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isReady(AssetType::Texture, name);
	}
}
