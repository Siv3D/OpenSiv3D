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

# pragma once
# include "Fwd.hpp"
# include "Asset.hpp"
# include "Texture.hpp"

namespace s3d
{
	/// <summary>
	/// Texture アセットデータ
	/// </summary>
	struct TextureAssetData : IAsset
	{
		FilePath path;

		TextureDesc desc = TextureDesc::Unmipped;

		Texture texture;

		std::function<bool(TextureAssetData&)> onPreload;

		std::function<bool(TextureAssetData&)> onUpdate;

		std::function<bool(TextureAssetData&)> onRelease;

		static const String& Name();

		static bool DefaultPreload(TextureAssetData& asset);

		static bool DefaultUpdate(TextureAssetData&);

		static bool DefaultRelease(TextureAssetData& asset);

		TextureAssetData();

		explicit TextureAssetData(
			const FilePath& _path,
			TextureDesc _desc = TextureDesc::Unmipped,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(TextureAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(TextureAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(TextureAssetData&)> _onRelease = DefaultRelease);

		bool preload() override;

		void preloadAsync() override;

		bool update() override;

		bool release() override;
	};

	/// <summary>
	/// Texture アセット
	/// </summary>
	class TextureAsset : public Texture
	{
	public:

		TextureAsset(const AssetName& name);

		TextureAsset(const AssetName& name, const Texture& dummy);

		static bool Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const FilePath& path, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Icon& icon, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Icon& icon, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Emoji& emoji, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Emoji& emoji, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const TextureAssetData& data);

		[[nodiscard]] static bool IsRegistered(const AssetName& name);

		static bool Preload(const AssetName& name);

		//static bool PreloadByTag(const AssetTag& tag);

		//static bool PreloadAll();

		static void Release(const AssetName& name);

		//static void ReleaseByTag(const AssetTag& tag);

		static void ReleaseAll();

		static void Unregister(const AssetName& name);

		//static void UnregisterByTag(const AssetTag& tag);

		static void UnregisterAll();

		[[nodiscard]] static bool IsReady(const AssetName& name);
	};
}
