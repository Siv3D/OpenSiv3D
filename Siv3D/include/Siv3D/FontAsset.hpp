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
# include "Font.hpp"

namespace s3d
{
	/// <summary>
	/// Font アセットデータ
	/// </summary>
	struct FontAssetData : IAsset
	{
		int32 fontSize = 0;

		FilePath path;

		FontStyle style = FontStyle::Default;

		Font font;

		std::function<bool(FontAssetData&)> onPreload;

		std::function<bool(FontAssetData&)> onUpdate;

		std::function<bool(FontAssetData&)> onRelease;

		static const String& Name();

		static bool DefaultPreload(FontAssetData& asset);

		static bool DefaultUpdate(FontAssetData&);

		static bool DefaultRelease(FontAssetData& asset);

		FontAssetData();

		explicit FontAssetData(
			int32 fontSize,
			Typeface typeface = Typeface::Default,
			FontStyle style = FontStyle::Default,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(FontAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(FontAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(FontAssetData&)> _onRelease = DefaultRelease);

		FontAssetData(
			int32 fontSize,
			const FilePath& path,
			FontStyle style = FontStyle::Default,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(FontAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(FontAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(FontAssetData&)> _onRelease = DefaultRelease);

		bool preload() override;

		void preloadAsync() override;

		bool update() override;

		bool release() override;
	};

	/// <summary>
	/// Font アセット
	/// </summary>
	class FontAsset : public Font
	{
	public:

		FontAsset(const AssetName& name);

		static bool Register(const AssetName& name, int32 fontSize, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, int32 fontSize, Typeface typeface, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, int32 fontSize, Typeface typeface, FontStyle style, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, int32 fontSize, const FilePath& path, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, int32 fontSize, const FilePath& path, FontStyle style, const AssetParameter& parameter = AssetParameter{});
		
		static bool Register(const AssetName& name, const FontAssetData& data);

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
