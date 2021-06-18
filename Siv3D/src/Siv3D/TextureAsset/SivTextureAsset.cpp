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

# include <Siv3D/TextureAsset.hpp>
# include <Siv3D/Asset/IAsset.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Texture FromAsset(const IAsset* asset)
		{
			if (const TextureAssetData* assetData = dynamic_cast<const TextureAssetData*>(asset))
			{
				return assetData->texture;
			}

			return{};
		}
	}

	TextureAsset::TextureAsset(const AssetNameView name)
		: Texture{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::Texture, name)) } {}

	bool TextureAsset::Register(const AssetName& name, const FilePathView path, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(path, desc);

		return Register(name, std::move(data));
	}

	bool TextureAsset::Register(const AssetName& name, const FilePathView rgb, const FilePathView alpha, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(rgb, alpha, desc);

		return Register(name, std::move(data));
	}

	bool TextureAsset::Register(const AssetName& name, const Color& rgb, const FilePathView alpha, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(rgb, alpha, desc);

		return Register(name, std::move(data));
	}

	bool TextureAsset::Register(const AssetName& name, const Emoji& emoji, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(emoji, desc);

		return Register(name, std::move(data));
	}

	bool TextureAsset::Register(const AssetName& name, const Icon& icon, const int32 size, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(icon, size, desc);

		return Register(name, std::move(data));
	}

	bool TextureAsset::Register(const AssetName& name, std::unique_ptr<TextureAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::Texture, name, std::move(data));
	}

	bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView path, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(path, desc, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView rgb, const FilePathView alpha, TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(rgb, alpha, desc, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const Color& rgb, const FilePathView alpha, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(rgb, alpha, desc, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const Emoji& emoji, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(emoji, desc, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const Icon& icon, const int32 size, const TextureDesc desc)
	{
		std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(icon, size, desc, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool TextureAsset::IsRegistered(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isRegistered(AssetType::Texture, name);
	}

	bool TextureAsset::Load(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->load(AssetType::Texture, name, {});
	}

	void TextureAsset::LoadAsync(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->loadAsync(AssetType::Texture, name, {});
	}

	void TextureAsset::Wait(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->wait(AssetType::Texture, name);
	}

	bool TextureAsset::IsReady(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isReady(AssetType::Texture, name);
	}

	void TextureAsset::Release(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->release(AssetType::Texture, name);
	}

	void TextureAsset::ReleaseAll()
	{
		SIV3D_ENGINE(Asset)->releaseAll(AssetType::Texture);
	}

	void TextureAsset::Unregister(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->unregister(AssetType::Texture, name);
	}

	void TextureAsset::UnregisterAll()
	{
		SIV3D_ENGINE(Asset)->unregisterAll(AssetType::Texture);
	}

	HashTable<AssetName, AssetInfo> TextureAsset::Enumerate()
	{
		return SIV3D_ENGINE(Asset)->enumerate(AssetType::Texture);
	}
}
