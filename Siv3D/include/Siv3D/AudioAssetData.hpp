//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "Audio.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct AudioAssetData : IAsset
	{
		FilePath path;

		Optional<AudioLoopTiming> loopTiming;

		bool streaming = false;

		GMInstrument instrument = GMInstrument::Piano1;

		uint8 key = 0;
		
		Duration noteOn{ 0.0 };
		
		Duration noteOff{ 0.0 };
		
		double velocity = 1.0;
		
		uint32 sampleRate = Wave::DefaultSampleRate;

		Audio audio;

		std::function<bool(AudioAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(AudioAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		AudioAssetData();

		SIV3D_NODISCARD_CXX20
		AudioAssetData(FilePathView _path, const Optional<AudioLoopTiming>& _loopTiming, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		AudioAssetData(Audio::FileStreaming, FilePathView _path, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		AudioAssetData(Audio::FileStreaming, FilePathView _path, Arg::loopBegin_<uint64> _loopBegin, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		AudioAssetData(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::sampleRate_<uint32> sampleRate, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(AudioAssetData& asset, const String& hint);

		static void DefaultRelease(AudioAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
