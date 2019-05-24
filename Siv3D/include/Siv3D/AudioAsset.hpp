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

		std::function<bool(AudioAssetData&)> onPreload;

		std::function<bool(AudioAssetData&)> onUpdate;

		std::function<bool(AudioAssetData&)> onRelease;

		static const String& Name();

		static bool DefaultPreload(AudioAssetData& asset);

		static bool DefaultUpdate(AudioAssetData&);

		static bool DefaultRelease(AudioAssetData& asset);

		AudioAssetData();

		explicit AudioAssetData(
			const FilePath& _path,
			const Optional<AudioLoopTiming>& _loop = none,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(AudioAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(AudioAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(AudioAssetData&)> _onRelease = DefaultRelease);

		bool preload() override;

		void preloadAsync() override;

		bool update() override;

		bool release() override;
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
