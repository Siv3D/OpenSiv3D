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

# include <Siv3D/FontAsset.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Asset/IAsset.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Font FromAsset(const IAsset* asset)
		{
			if (const FontAssetData* assetData = dynamic_cast<const FontAssetData*>(asset))
			{
				return assetData->font;
			}

			return{};
		}

		[[nodiscard]]
		static bool CheckFileExists(const FilePathView path)
		{
			if (not FileSystem::Exists(path))
			{
				LOG_FAIL(U"❌ FontAsset::Register(): Font file `" + path + U"` not found");
				return false;
			}

			return true;
		}
	}

	FontAsset::FontAsset(const AssetNameView name)
		: Font{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::Font, name)) } {}

	bool FontAsset::Register(const AssetNameView name, const int32 fontSize, const FilePathView path, const FontStyle style)
	{
		return Register(name, FontMethod::Bitmap, fontSize, path, 0, style);
	}

	bool FontAsset::Register(const AssetNameView name, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
	{
		return Register(name, FontMethod::Bitmap, fontSize, path, faceIndex, style);
	}

	bool FontAsset::Register(const AssetNameView name, const int32 fontSize, const Typeface typeface, const FontStyle style)
	{
		return Register(name, FontMethod::Bitmap, fontSize, typeface, style);
	}

	bool FontAsset::Register(const AssetNameView name, const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const FontStyle style)
	{
		return Register(name, fontMethod, fontSize, path, 0, style);
	}

	bool FontAsset::Register(const AssetNameView name, const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<FontAssetData> data = std::make_unique<FontAssetData>(fontMethod, fontSize, path, faceIndex, style);
	
		return Register(name, std::move(data));
	}

	bool FontAsset::Register(const AssetNameView name, const FontMethod fontMethod, const int32 fontSize, const Typeface typeface, const FontStyle style)
	{
		std::unique_ptr<FontAssetData> data = std::make_unique<FontAssetData>(fontMethod, fontSize, typeface, style);

		return Register(name, std::move(data));
	}

	bool FontAsset::Register(const AssetNameView name, std::unique_ptr<FontAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::Font, name, std::move(data));
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const FilePathView path, const FontStyle style)
	{
		return Register(nameAndTags, FontMethod::Bitmap, fontSize, path, 0, style);
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
	{
		return Register(nameAndTags, FontMethod::Bitmap, fontSize, path, faceIndex, style);
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const int32 fontSize, const Typeface typeface, const FontStyle style)
	{
		return Register(nameAndTags, FontMethod::Bitmap, fontSize, typeface, style);
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const FontStyle style)
	{
		return Register(nameAndTags, fontMethod, fontSize, path, 0, style);
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<FontAssetData> data = std::make_unique<FontAssetData>(fontMethod, fontSize, path, faceIndex, style, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool FontAsset::Register(const AssetNameAndTags& nameAndTags, const FontMethod fontMethod, const int32 fontSize, const Typeface typeface, const FontStyle style)
	{
		std::unique_ptr<FontAssetData> data = std::make_unique<FontAssetData>(fontMethod, fontSize, typeface, style, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool FontAsset::IsRegistered(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isRegistered(AssetType::Font, name);
	}

	bool FontAsset::Load(const AssetNameView name, const StringView preloadText)
	{
		return SIV3D_ENGINE(Asset)->load(AssetType::Font, name, preloadText);
	}

	void FontAsset::LoadAsync(const AssetNameView name, const StringView preloadText)
	{
		SIV3D_ENGINE(Asset)->loadAsync(AssetType::Font, name, preloadText);
	}

	void FontAsset::Wait(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->wait(AssetType::Font, name);
	}

	bool FontAsset::IsReady(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isReady(AssetType::Font, name);
	}

	void FontAsset::Release(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->release(AssetType::Font, name);
	}

	void FontAsset::ReleaseAll()
	{
		SIV3D_ENGINE(Asset)->releaseAll(AssetType::Font);
	}

	void FontAsset::Unregister(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->unregister(AssetType::Font, name);
	}

	void FontAsset::UnregisterAll()
	{
		SIV3D_ENGINE(Asset)->unregisterAll(AssetType::Font);
	}

	HashTable<AssetName, AssetInfo> FontAsset::Enumerate()
	{
		return SIV3D_ENGINE(Asset)->enumerate(AssetType::Font);
	}
}
