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
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loop 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Loop loop);

		/// @brief 
		/// @param  
		/// @param path 
		/// @param loopBegin 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
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

		/// @brief オーディオを指定したバスで再生するか、一時停止中の場合は再生を再開します。
		/// @param busIndex バスのインデックス（`Audio::MaxBusCount` 未満）
		/// @remark オーディオが一時停止中の場合 `busIndex` を無視して再生を再開します。
		/// @remark すでに再生中の場合は何もしません。
		void play(size_t busIndex = 0) const;

		/// @brief オーディオを指定したバスで再生するか、一時停止中の場合は再生を再開します。
		/// @param fadeTime フェードイン時間
		/// @param busIndex バスのインデックス（`Audio::MaxBusCount` 未満）
		/// @remark すでに再生中の場合は何もしません。
		void play(const Duration& fadeTime, size_t busIndex = 0) const;

		/// @brief オーディオを指定したバスで再生するか、一時停止中の場合は再生を再開します。
		/// @param busIndex バスのインデックス（`Audio::MaxBusCount` 未満）
		/// @param fadeTime フェードイン時間
		/// @remark すでに再生中の場合は何もしません。
		void play(size_t busIndex, const Duration& fadeTime) const;

		/// @brief 再生中のオーディオを一時停止します。
		void pause() const;

		/// @brief 指定した時間をかけて音量をフェードアウトさせたのち一時停止します。
		/// @param fadeTime フェードアウト時間
		void pause(const Duration& fadeTime) const;

		/// @brief オーディオを即座に停止し、非アクティブにします。
		void stop() const;

		/// @brief 指定した時間をかけて音量をフェードアウトさせたのち停止します。
		/// @param fadeTime フェードアウト時間
		void stop(const Duration& fadeTime) const;

		void playOneShot(size_t busIndex = 0, double volume = 1.0, double pan = 0.0, double speed = 1.0) const;

		void pauseAllShots() const;

		void pauseAllShots(const Duration& fadeTime) const;

		void resumeAllShots() const;

		void resumeAllShots(const Duration& fadeTime) const;

		void stopAllShots() const;

		void stopAllShots(const Duration& fadeTime) const;

		/// @brief 再生位置（サンプル）を返します。
		/// @return 再生位置（サンプル）
		[[nodiscard]]
		int64 posSample() const;

		/// @brief 再生位置（秒）を返します。
		/// @return 再生位置（秒）
		[[nodiscard]]
		double posSec() const;

		/// @brief 再生位置を指定した位置（サンプル）に設定します。
		/// @param posSample 再生位置（サンプル）
		void seekSamples(size_t posSample) const;

		/// @brief 再生位置を指定した位置（秒）に設定します。
		/// @param posSec 再生位置（秒）
		void seekTime(double posSec) const;

		/// @brief 再生位置を指定した位置に設定します。
		/// @param pos 再生位置
		void seekTime(const Duration& pos) const;

		/// @brief ループ再生された回数を返します。
		/// @return ループ再生された回数
		[[nodiscard]]
		size_t loopCount() const;

		/// @brief 音量の設定 [0.0, 1.0] を返します。
		/// @return 音量の設定 [0.0, 1.0]
		[[nodiscard]]
		double getVolume() const;

		/// @brief 音量 [0.0, 1.0] を設定します。
		/// @param volume 音量 [0.0, 1.0]
		void setVolume(double volume) const;

		/// @brief 指定した時間をかけて目標の音量に変更します。
		/// @param volume 目標の音量 [0.0, 1.0]
		/// @param fadeTime フェード時間
		void fadeVolume(double volume, const Duration& fadeTime) const;

		/// @brief パンの設定 [-1.0, 1.0] を返します。
		/// @return パンの設定 [-1.0, 1.0]
		[[nodiscard]]
		double getPan() const;

		/// @brief パン [-1.0, 1.0] を設定します。
		/// @param pan パン [-1.0, 1.0]. -1.0 が左、0.0 が中央、1.0 が右
		void setPan(double pan) const;

		/// @brief 指定した時間をかけて目標のパンに変更します。
		/// @param pan パン [-1.0, 1.0]. -1.0 が左、0.0 が中央、1.0 が右
		/// @param fadeTime フェード時間
		void fadePan(double pan, const Duration& fadeTime) const;

		/// @brief スピードの設定を返します。
		/// @return スピードの設定
		[[nodiscard]]
		double getSpeed() const;

		/// @brief スピード（再生速度の倍率）を設定します。
		/// @param speed スピード（再生速度の倍率）
		/// @remark スピードが上下すると音の高さも上下します。
		void setSpeed(double speed) const;

		void fadeSpeed(double speed, const Duration& fadeTime) const;

		void setSpeedBySemitone(int32 semitone) const;

		/// @brief 音声波形のサンプルデータにアクセスします。
		/// @param channel 左チャンネルの場合 0, 右チャンネルの場合 1
		/// @remark ストリーミング再生の場合は利用できません。
		/// @return 指定したチャンネルの音声波形データの先頭ポインタ。ストリーミング再生の場合は nullptr
		[[nodiscard]]
		const float* getSamples(size_t channel) const;
	};
}
