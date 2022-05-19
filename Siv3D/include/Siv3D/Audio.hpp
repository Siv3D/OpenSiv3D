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
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "Wave.hpp"
# include "AudioLoopTiming.hpp"
# include "AssetHandle.hpp"
# include "PredefinedYesNo.hpp"
# include "MixBus.hpp"
# include "IAudioStream.hpp"

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

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		SIV3D_NODISCARD_CXX20
		explicit Audio(Wave&& wave);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loop ループする場合は `Loop::Yes`, それ以外の場合は `Loop::No`
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, const Loop loop);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（サンプル）
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（サンプル）
		/// @param loopEnd ループの終端位置（サンプル）
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（秒）
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<Duration> loopBegin);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（秒）
		/// @param loopEnd ループの終端位置（秒）
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loop ループ情報
		SIV3D_NODISCARD_CXX20
		Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		SIV3D_NODISCARD_CXX20
		explicit Audio(const Wave& wave);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loop ループする場合は `Loop::Yes`, それ以外の場合は `Loop::No`
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, const Loop loop);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（サンプル）
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（サンプル）
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（秒）
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loopBegin ループの開始位置（秒）
		/// @param loopEnd ループの終端位置（秒）
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief Wave からオーディオを作成します。
		/// @param wave Wave
		/// @param loop ループ情報
		SIV3D_NODISCARD_CXX20
		Audio(const Wave& wave, const Optional<AudioLoopTiming>& loop);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path ファイルパス
		SIV3D_NODISCARD_CXX20
		explicit Audio(FilePathView path);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path ファイルパス
		/// @param loop ループする場合は `Loop::Yes`, それ以外の場合は `Loop::No`
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, const Loop loop);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path 
		/// @param loopBegin 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<Duration> loopBegin);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path 
		/// @param loopBegin 
		/// @param loopEnd 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		/// @brief オーディオファイルをロードしてオーディオを作成します。
		/// @param path 
		/// @param loop 
		SIV3D_NODISCARD_CXX20
		Audio(FilePathView path, const Optional<AudioLoopTiming>& loop);

		/// @brief オーディオファイルからストリーミング形式でロードするオーディオを作成します。
		/// @param  
		/// @param path 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path);

		/// @brief オーディオファイルからストリーミング形式でロードするオーディオを作成します。
		/// @param  
		/// @param path 
		/// @param loop 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Loop loop);

		/// @brief オーディオファイルからストリーミング形式でロードするオーディオを作成します。
		/// @param  
		/// @param path 
		/// @param loopBegin 
		/// @remark ストリーミング再生は WAVE, OggVorbis, FLAC, MP3 のみサポート。
		/// @remark 対応しない形式の場合、ストリーミング再生にはなりません。
		SIV3D_NODISCARD_CXX20
		Audio(FileStreaming, FilePathView path, Arg::loopBegin_<uint64> loopBegin);

		/// @brief 楽器の音のオーディオを作成します。
		/// @param instrument 楽器
		/// @param key 音階
		/// @param duration ノートオンの時間
		/// @param velocity ベロシティ
		/// @param sampleRate サンプルレート (Hz)
		SIV3D_NODISCARD_CXX20
		Audio(GMInstrument instrument, uint8 key, const Duration& duration, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		/// @brief 楽器の音のオーディオを作成します。
		/// @param instrument 楽器
		/// @param key 音階
		/// @param noteOn ノートオンの時間
		/// @param noteOff ノートオフの時間
		/// @param velocity ベロシティ
		/// @param sampleRate サンプルレート (Hz)
		SIV3D_NODISCARD_CXX20
		Audio(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		/// @brief IReader からオーディオを作成します。
		/// @param reader 
		/// @param format 
		SIV3D_NODISCARD_CXX20
		explicit Audio(IReader&& reader, AudioFormat format = AudioFormat::Unspecified);

		SIV3D_NODISCARD_CXX20
		explicit Audio(const std::shared_ptr<IAudioStream>& pAudioStream, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

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
		/// @param busIndex バスのインデックス
		/// @remark オーディオが一時停止中の場合 `busIndex` を無視して再生を再開します。
		/// @remark すでに再生中の場合は何もしません。
		void play(MixBus busIndex = MixBus0) const;

		/// @brief オーディオを指定したバスで再生するか、一時停止中の場合は再生を再開します。
		/// @param fadeTime フェードイン時間
		/// @param busIndex バスのインデックス
		/// @remark すでに再生中の場合は何もしません。
		void play(const Duration& fadeTime, MixBus busIndex = MixBus0) const;

		/// @brief オーディオを指定したバスで再生するか、一時停止中の場合は再生を再開します。
		/// @param busIndex バスのインデックス
		/// @param fadeTime フェードイン時間
		/// @remark すでに再生中の場合は何もしません。
		void play(MixBus busIndex, const Duration& fadeTime) const;

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

		/// @brief オーディオを重複可能にして一度だけ再生します。
		/// @param volume 音量
		/// @param pan パン
		/// @param speed 再生スピード
		void playOneShot(double volume = 1.0, double pan = 0.0, double speed = 1.0, MixBus = MixBus0) const;

		/// @brief オーディオを重複可能にして一度だけ再生します。
		/// @param busIndex バスのインデックス
		/// @param volume 音量
		/// @param pan パン
		/// @param speed 再生スピード
		void playOneShot(MixBus busIndex, double volume = 1.0, double pan = 0.0, double speed = 1.0) const;

		/// @brief `playOneShot()` で再生中のすべてのオーディオを一時停止します
		/// @param fadeTime 
		void pauseAllShots() const;

		/// @brief `playOneShot()` で再生中のすべてのオーディオを、指定した時間をかけて音量をフェードアウトさせたのち一時停止します
		/// @param fadeTime フェードアウト時間
		void pauseAllShots(const Duration& fadeTime) const;

		/// @brief `playOneShot()` 後に一時停止されたオーディオを再開します
		void resumeAllShots() const;
		
		/// @brief `playOneShot()` 後に一時停止されたすべてのオーディオを、指定した時間をかけて音量をフェードインさせながら再開します
		/// @param fadeTime フェードイン時間
		void resumeAllShots(const Duration& fadeTime) const;

		/// @brief `playOneShot()` で再生中のすべてのオーディオをすべて停止します
		void stopAllShots() const;

		/// @brief `playOneShot()` で再生中のすべてのオーディオを、指定した時間をかけて音量をフェードアウトさせたのち停止します
		/// @param fadeTime フェードアウト時間
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
		/// @return *this
		const Audio& setVolume(double volume) const;

		/// @brief 指定した時間をかけて目標の音量に変更します。
		/// @param volume 目標の音量 [0.0, 1.0]
		/// @param fadeTime フェード時間
		/// @return *this
		const Audio& fadeVolume(double volume, const Duration& fadeTime) const;

		/// @brief パンの設定 [-1.0, 1.0] を返します。
		/// @return パンの設定 [-1.0, 1.0]
		[[nodiscard]]
		double getPan() const;

		/// @brief パン [-1.0, 1.0] を設定します。
		/// @param pan パン [-1.0, 1.0]. -1.0 が左、0.0 が中央、1.0 が右
		/// @return *this
		const Audio& setPan(double pan) const;

		/// @brief 指定した時間をかけて目標のパンに変更します。
		/// @param pan パン [-1.0, 1.0]. -1.0 が左、0.0 が中央、1.0 が右
		/// @param fadeTime フェード時間
		/// @return *this
		const Audio& fadePan(double pan, const Duration& fadeTime) const;

		/// @brief スピードの設定を返します。
		/// @return スピードの設定
		[[nodiscard]]
		double getSpeed() const;

		/// @brief スピード（再生速度の倍率）を設定します。
		/// @param speed スピード（再生速度の倍率）
		/// @remark スピードが上下すると音の高さも上下します。
		/// @return *this
		const Audio& setSpeed(double speed) const;

		/// @brief 指定した時間をかけて目標のスピード（再生速度の倍率）に変更します。
		/// @param speed スピード（再生速度の倍率）
		/// @param fadeTime フェード時間
		/// @return *this
		const Audio& fadeSpeed(double speed, const Duration& fadeTime) const;

		/// @brief 半音単位で音階が変わるようスピード（再生速度の倍率）を設定します。
		/// @param semitone 目標の半音単位
		/// @remark `setSpeed(std::exp2(semitone / 12.0))` と同じです。
		/// @return *this
		const Audio& setSpeedBySemitone(int32 semitone) const;

		/// @brief 定した時間をかけて、半音単位で音階が変わるようスピード（再生速度の倍率）を設定します。
		/// @param semitone 目標の半音単位
		/// @param fadeTime フェード時間
		/// @remark `fadeSpeed(std::exp2(semitone / 12.0), fadeTime)` と同じです。
		/// @return *this
		const Audio& fadeSpeedBySemitone(int32 semitone, const Duration& fadeTime) const;

		/// @brief 音声波形のサンプルデータにアクセスします。
		/// @param channel 左チャンネルの場合 0, 右チャンネルの場合 1
		/// @remark ストリーミング再生の場合は利用できません。
		/// @return 指定したチャンネルの音声波形データの先頭ポインタ。ストリーミング再生の場合は nullptr
		[[nodiscard]]
		const float* getSamples(size_t channel) const;

		/// @brief オーディオを入れ替えます。
		/// @param other 入れ替える先のオーディオ
		void swap(Audio& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::Audio& a, s3d::Audio& b) noexcept;

# include "detail/Audio.ipp"
