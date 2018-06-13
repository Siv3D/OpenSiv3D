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

		std::function<bool(TextureAssetData&)> onPreload = DefaultPreload;

		std::function<bool(TextureAssetData&)> onUpdate = DefaultUpdate;

		std::function<bool(TextureAssetData&)> onRelease = DefaultRelease;

		static const String& Name()
		{
			static const String name = U"Texture";

			return name;
		}

		static bool DefaultPreload(TextureAssetData& asset)
		{
			if (asset.texture)
			{
				return true;
			}

			asset.texture = Texture(asset.path, asset.desc);

			return !asset.texture.isEmpty();
		}

		static bool DefaultUpdate(TextureAssetData&)
		{
			return true;
		}

		static bool DefaultRelease(TextureAssetData& asset)
		{
			asset.texture.release();

			return true;
		}

		TextureAssetData() = default;

		explicit TextureAssetData(
			const FilePath& _path,
			TextureDesc _desc = TextureDesc::Unmipped,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(TextureAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(TextureAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(TextureAssetData&)> _onRelease = DefaultRelease);

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
	/// Texture アセット
	/// </summary>
	class TextureAsset : public Texture
	{
	public:

		TextureAsset(const AssetName& name);

		static bool Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const FilePath& path, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Icon& icon, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Icon& icon, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Emoji& emoji, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const Emoji& emoji, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const TextureAssetData& data);

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
