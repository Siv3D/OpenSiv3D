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
# include "AudioAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class AudioAsset : public Audio
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit AudioAsset(AssetNameView name);

		static bool Register(AssetNameView name, FilePathView path);

		static bool Register(AssetNameView name, FilePathView path, const Loop loop);

		static bool Register(AssetNameView name, FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		static bool Register(AssetNameView name, FilePathView path, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		//static bool Register(AssetNameView name, FilePathView path, Arg::loopBegin_<Duration> loopBegin);
	
		//static bool Register(AssetNameView name, FilePathView path, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);
	
		static bool Register(AssetNameView name, FilePathView path, const Optional<AudioLoopTiming>& loop);
		
		static bool Register(AssetNameView name, Audio::FileStreaming, FilePathView path);
		
		static bool Register(AssetNameView name, Audio::FileStreaming, FilePathView path, Loop loop);
	
		static bool Register(AssetNameView name, Audio::FileStreaming, FilePathView path, Arg::loopBegin_<uint64> loopBegin);
			
		static bool Register(AssetNameView name, GMInstrument instrument, uint8 key, const Duration& duration, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		static bool Register(AssetNameView name, GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		static bool Register(AssetNameView name, std::unique_ptr<AudioAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path);

		static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, const Loop loop);

		static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		//static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, Arg::loopBegin_<Duration> loopBegin);

		//static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		static bool Register(const AssetNameAndTags& nameAndTag, FilePathView path, const Optional<AudioLoopTiming>& loop);

		static bool Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, FilePathView path);

		static bool Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, FilePathView path, Loop loop);

		static bool Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		static bool Register(const AssetNameAndTags& nameAndTag, GMInstrument instrument, uint8 key, const Duration& duration, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		static bool Register(const AssetNameAndTags& nameAndTag, GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);


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

