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

# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "Texture.hpp"
# include "TextureAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class TextureAsset : public Texture
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit TextureAsset(AssetNameView name);

		static bool Register(AssetNameView name, FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		static bool Register(AssetNameView name, const Icon& icon, int32 size, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, std::unique_ptr<TextureAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Icon& icon, int32 size, TextureDesc desc = TextureDesc::Unmipped);


		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		static bool Load(AssetNameView name);

		static void LoadAsync(AssetNameView name);

		static void Wait(AssetNameView name);

		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		static void Release(AssetNameView name);

		static void ReleaseAll();

		static void Unregister(AssetNameView name);

		static void UnregisterAll();

		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
