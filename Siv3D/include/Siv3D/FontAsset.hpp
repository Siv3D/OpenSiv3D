//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		int32 fontSize;

		FilePath path;

		FontStyle style;

		Font font;

		std::function<bool(FontAssetData&)> onPreload = DefaultPreload;

		std::function<bool(FontAssetData&)> onUpdate = DefaultUpdate;

		std::function<bool(FontAssetData&)> onRelease = DefaultRelease;

		static const String& Name()
		{
			static const String name = U"Font";

			return name;
		}

		static bool DefaultPreload(FontAssetData& asset)
		{
			if (asset.font)
			{
				return true;
			}

			asset.font = Font(asset.fontSize, asset.path, asset.style);

			return !asset.font.isEmpty();
		}

		static bool DefaultUpdate(FontAssetData&)
		{
			return true;
		}

		static bool DefaultRelease(FontAssetData& asset)
		{
			asset.font.release();

			return true;
		}

		FontAssetData() = default;

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

		bool preload() override
		{
			if (m_state == State::Uninitialized)
			{
				m_state = onPreload(*this) ? State::LoadSucceeded : State::LoadFailed;
			}

			return (m_state == State::LoadSucceeded);
		}

		void preloadAsync() override
		{
			if (m_state == State::Uninitialized)
			{
				launchLoading([this]() { return onPreload(*this); });

				m_state = State::PreloadingAsync;
			}
		}

		bool update() override
		{
			if (!isPreloaded())
			{
				return false;
			}

			return onUpdate(*this);
		}

		bool release() override
		{
			if (m_state == State::Uninitialized)
			{
				return true;
			}

			const bool result = onRelease(*this);

			m_state = State::Uninitialized;

			return result;
		}
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

		static bool IsRegistered(const AssetName& name);

		static bool Preload(const AssetName& name);

		//static bool PreloadByTag(const AssetTag& tag);

		//static bool PreloadAll();

		static void Release(const AssetName& name);

		//static void ReleaseByTag(const AssetTag& tag);

		static void ReleaseAll();

		static void Unregister(const AssetName& name);

		//static void UnregisterByTag(const AssetTag& tag);

		static void UnregisterAll();

		static bool IsReady(const AssetName& name);
	};
}
