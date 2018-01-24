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

# pragma once
# include "Fwd.hpp"
# include "Asset.hpp"
# include "Audio.hpp"

namespace s3d
{
	/// <summary>
	/// Audio アセットデータ
	/// </summary>
	struct AudioAssetData : IAsset
	{
		FilePath path;

		Optional<AudioLoopTiming> loop;

		Audio audio;

		std::function<bool(AudioAssetData&)> onPreload = DefaultPreload;

		std::function<bool(AudioAssetData&)> onUpdate = DefaultUpdate;

		std::function<bool(AudioAssetData&)> onRelease = DefaultRelease;

		static const String& Name()
		{
			static const String name = U"Audio";

			return name;
		}

		static bool DefaultPreload(AudioAssetData& asset)
		{
			if (asset.audio)
			{
				return true;
			}

			asset.audio = Audio(asset.path, asset.loop);

			return !asset.audio.isEmpty();
		}

		static bool DefaultUpdate(AudioAssetData&)
		{
			return true;
		}

		static bool DefaultRelease(AudioAssetData& asset)
		{
			asset.audio.release();

			return true;
		}

		AudioAssetData() = default;

		explicit AudioAssetData(
			const FilePath& _path,
			const Optional<AudioLoopTiming>& _loop = none,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(AudioAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(AudioAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(AudioAssetData&)> _onRelease = DefaultRelease);

		bool preload() override
		{
			if (m_state == State::Uninitialized)
			{
				m_state = onPreload(*this) ? State::LoadScceeded : State::LoadFailed;
			}

			return (m_state == State::LoadScceeded);
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
	/// Audio アセット
	/// </summary>
	class AudioAsset : public Audio
	{
	public:

		AudioAsset(const AssetName& name);

		static bool Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const FilePath& path, const Optional<AudioLoopTiming>& loop, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const AudioAssetData& data);

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
