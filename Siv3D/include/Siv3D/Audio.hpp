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

		/// @brief ストリーミング再生を指定するフラグ
		static constexpr struct FileStreaming {} Stream{};

		/// @brief バスの最大数
		static constexpr size_t MaxBusCount = 4;

		/// @brief フィルターの最大数
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
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loop 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Loop loop);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loopBegin 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート
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

		/// @brief デストラクタ
		virtual ~Audio();

		/// @brief ストリーミングオーディオであるかを返します。
		/// @return ストリーミングオーディオである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isStreaming() const;

		/// @brief オーディオのサンプリングレートを返します。
		/// @return オーディオのサンプリングレート
		[[nodiscard]]
		uint32 sampleRate() const;

		/// @brief オーディオの長さ（サンプル）を返します。
		/// @return オーディオの長さ（サンプル）
		[[nodiscard]]
		size_t samples() const;

		/// @brief オーディオの長さ（秒）を返します。
		/// @return オーディオの長さ（秒）
		[[nodiscard]]
		double lengthSec() const;

		/// @brief ループを含め再生したサンプル数の累計を返します。
		/// @return 再生したサンプル数の累計
		[[nodiscard]]
		int64 samplesPlayed() const;

		/// @brief オーディオがアクティブであるかを返します。
		/// @remark 再生して、stop していないオーディオはアクティブです。
		/// @return オーディオがアクティブな場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isActive() const;

		/// @brief オーディオが再生中であるかを返します。
		/// @return オーディオが再生中の場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isPlaying() const;

		/// @brief オーディオが一時停止中であるかを返します。
		/// @return オーディオが一時停止中の場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isPaused() const;

		/// @brief 新しく再生したときにループが有効になるかを返します。
		/// @return 新しく再生したときにループが有効になる場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isLoop() const;

		/// @brief ループ再生する場合のループ範囲を返します。
		/// @return ループ再生する場合のループ範囲
		[[nodiscard]]
		AudioLoopTiming getLoopTiming() const;

		/// @brief 新しく再生するときのループの有無を設定します。
		/// @param loop ループの有無
		void setLoop(bool loop) const;

		/// @brief 新しくループ再生するときのループ開始位置（サンプル）を設定します。
		/// @param loopBegin ループ開始位置（サンプル）
		void setLoopPoint(uint64 loopBegin) const;

		/// @brief 新しくループ再生するときのループ開始位置（秒）を設定します。
		/// @param loopBegin ループ開始位置（秒）
		void setLoopPoint(const Duration& loopBegin) const;

		void play(size_t busIndex = 0) const;

		void play(const Duration& duration, size_t busIndex = 0) const;

		void play(size_t busIndex, const Duration& duration) const;

		void pause() const;

		void pause(const Duration& duration) const;

		void stop() const;

		void stop(const Duration& duration) const;

		//void playOneShot(size_t busIndex = 0) const;

		//void pauseAllShots() const;

		//void resumeAllShots() const;

		//void stopAllShots() const;

		/// @brief 再生位置（サンプル）を返します。
		/// @return 再生位置（サンプル）
		[[nodiscard]]
		int64 posSample() const;

		/// @brief 再生位置（秒）を返します。
		/// @return 再生位置（秒）
		[[nodiscard]]
		double posSec() const;

		void seekSamples(size_t posSample) const;

		void seekTime(double posSec) const;

		void seekTime(const Duration& pos) const;

		[[nodiscard]]
		size_t loopCount() const;

		[[nodiscard]]
		double getVolume() const;

		void setVolume(double volume) const;

		void fadeVolume(double volume, const Duration& time) const;

		[[nodiscard]]
		double getPan() const;

		void setPan(double pan) const;

		void fadePan(double pan, const Duration& time) const;

		[[nodiscard]]
		double getSpeed() const;

		void setSpeed(double speed) const;

		void fadeSpeed(double speed, const Duration& time) const;

		void setSpeedBySemitone(int32 semitone) const;

		const float* getSamples(size_t channel) const;
	};
}
