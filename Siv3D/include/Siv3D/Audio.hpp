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
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "Wave.hpp"
# include "AudioLoopTiming.hpp"
# include "AssetHandle.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief オーディオ
	class Audio : public AssetHandle<Audio>
	{
	public:

		static constexpr struct FileStreaming {} Stream{};

		static constexpr size_t MaxBusCount = 4;

		static constexpr size_t MaxFilterCount = 8;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Audio();

		/// @brief 
		/// @param wave 
		SIV3D_NODISCARD_CXX20
		explicit Audio(Wave&& wave);

		/// @brief 
		/// @param wave 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, const Loop loop);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<Duration> loopBegin);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief 
		/// @param wave 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop);

		/// @brief 
		/// @param wave 
		SIV3D_NODISCARD_CXX20
		explicit Audio(const Wave& wave);

		/// @brief 
		/// @param wave 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, const Loop loop);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin);

		/// @brief 
		/// @param wave 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief 
		/// @param wave 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, const Optional<AudioLoopTiming>& loop);

		/// @brief 
		/// @param path 
		SIV3D_NODISCARD_CXX20
		explicit Audio(FilePathView path);

		/// @brief 
		/// @param path 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, const Loop loop);

		/// @brief 
		/// @param path 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		/// @brief 
		/// @param path 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief 
		/// @param path 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<Duration> loopBegin);

		/// @brief 
		/// @param path 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief 
		/// @param path 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, const Optional<AudioLoopTiming>& loop);

		/// @brief 
		/// @param  
		/// @param path 
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Loop loop);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		/// @brief 
		/// @param instrument 
		/// @param key 
		/// @param duration 
		/// @param velocity 
		/// @param sampleRate 
		/// @return 
		SIV3D_NODISCARD_CXX20
		Audio(GMInstrument instrument, uint8 key, const Duration& duration, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		/// @brief 
		/// @param instrument 
		/// @param key 
		/// @param noteOn 
		/// @param noteOff 
		/// @param velocity 
		/// @param sampleRate 
		/// @return 
		SIV3D_NODISCARD_CXX20
		Audio(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		/// @brief 
		/// @param reader 
		/// @param format 
		SIV3D_NODISCARD_CXX20
		explicit Audio(IReader&& reader, AudioFormat format = AudioFormat::Unspecified);

		/// @brief 
		virtual ~Audio();

		[[nodiscard]]
		bool isStreaming() const;

		[[nodiscard]]
		uint32 sampleRate() const;

		[[nodiscard]]
		size_t samples() const;

		[[nodiscard]]
		double lengthSec() const;
	};
}
