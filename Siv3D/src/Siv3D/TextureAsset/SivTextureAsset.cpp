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

	//bool TextureAsset::Register(const AssetName& name, const int32 fontSize, const FilePathView path, const TextureStyle style)
	//{
	//	return Register(name, TextureMethod::Bitmap, fontSize, path, 0, style);
	//}

	//bool TextureAsset::Register(const AssetName& name, const int32 fontSize, const FilePathView path, const size_t faceIndex, const TextureStyle style)
	//{
	//	return Register(name, TextureMethod::Bitmap, fontSize, path, faceIndex, style);
	//}

	//bool TextureAsset::Register(const AssetName& name, const int32 fontSize, const Typeface typeface, const TextureStyle style)
	//{
	//	return Register(name, TextureMethod::Bitmap, fontSize, typeface, style);
	//}

	//bool TextureAsset::Register(const AssetName& name, const TextureMethod fontMethod, const int32 fontSize, const FilePathView path, const TextureStyle style)
	//{
	//	return Register(name, fontMethod, fontSize, path, 0, style);
	//}

	//bool TextureAsset::Register(const AssetName& name, const TextureMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const TextureStyle style)
	//{
	//	std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(fontMethod, fontSize, path, faceIndex, style);
	//
	//	return Register(name, std::move(data));
	//}

	//bool TextureAsset::Register(const AssetName& name, const TextureMethod fontMethod, const int32 fontSize, const Typeface typeface, const TextureStyle style)
	//{
	//	std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(fontMethod, fontSize, typeface, style);

	//	return Register(name, std::move(data));
	//}

	bool TextureAsset::Register(const AssetName& name, std::unique_ptr<TextureAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::Texture, name, std::move(data));
	}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const FilePathView path, const TextureStyle style)
	//{
	//	return Register(nameAndTags, TextureMethod::Bitmap, fontSize, path, 0, style);
	//}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const FilePathView path, const size_t faceIndex, const TextureStyle style)
	//{
	//	return Register(nameAndTags, TextureMethod::Bitmap, fontSize, path, faceIndex, style);
	//}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const Typeface typeface, const TextureStyle style)
	//{
	//	return Register(nameAndTags, TextureMethod::Bitmap, fontSize, typeface, style);
	//}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const TextureMethod fontMethod, const int32 fontSize, const FilePathView path, const TextureStyle style)
	//{
	//	return Register(nameAndTags, fontMethod, fontSize, path, 0, style);
	//}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const TextureMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const TextureStyle style)
	//{
	//	std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(fontMethod, fontSize, path, faceIndex, style, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool TextureAsset::Register(const AssetNameAndTags& nameAndTags, const TextureMethod fontMethod, const int32 fontSize, const Typeface typeface, const TextureStyle style)
	//{
	//	std::unique_ptr<TextureAssetData> data = std::make_unique<TextureAssetData>(fontMethod, fontSize, typeface, style, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

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
