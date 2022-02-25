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
# include "Duration.hpp"
# include "Array.hpp"
# include "FFTResult.hpp"
# include "AudioGroup.hpp"
# include "MixBus.hpp"

namespace s3d
{
	namespace GlobalAudio
	{
		/// @brief 再生中のオーディオとバスの合計数を返します。
		/// @return 再生中のオーディオとバスの合計数
		[[nodiscard]]
		size_t GetActiveVoiceCount();

		/// @brief すべてのアクティブな Audio を一時停止します。
		void PauseAll();

		/// @brief 一時停止しているすべてのアクティブな Audio を再開します。
		void ResumeAll();

		/// @brief 最終出力の音量の設定を返します。
		/// @return 最終出力の音量の設定 [0.0, 1.0]
		[[nodiscard]]
		double GetVolume();

		/// @brief 最終出力の音量を変更します。
		/// @param volume 音量 [0.0, 1.0]
		void SetVolume(double volume);

		/// @brief 最終出力の音量をフェードさせて変更します。
		/// @param volume 音量 [0.0, 1.0]
		/// @param time フェードの時間
		void FadeVolume(double volume, const Duration& time);

		/// @brief 最終出力の直近 256 サンプルを取得します。
		/// @return 最終出力の直近 256 サンプル
		[[nodiscard]]
		Array<float> GetSamples();
		
		/// @brief 最終出力の直近 256 サンプルを取得します。
		/// @param samples 最終出力の直近 256 サンプルを格納する配列
		void GetSamples(Array<float>& samples);

		[[nodiscard]]
		FFTResult GetFFT();

		/// @brief 最終出力の直近 256 サンプルでの FFT 結果を取得します。
		/// @return FFT 結果の格納先
		void GetFFT(FFTResult& result);

		[[nodiscard]]
		Array<float> BusGetSamples(MixBus busIndex);

		/// @brief 指定したバスの直近 256 サンプルを取得します。
		/// @param busIndex バスのインデックス
		/// @param samples 指定したバスの直近 256 サンプルを格納する配列
		void BusGetSamples(MixBus busIndex, Array<float>& samples);

		[[nodiscard]]
		FFTResult BusGetFFT(MixBus busIndex);

		/// @brief 指定したバスの直近 256 サンプルでの FFT 結果を取得します。
		/// @param busIndex バスのインデックス
		/// @param result FFT 結果の格納先
		void BusGetFFT(MixBus busIndex, FFTResult& result);

		[[nodiscard]]
		double BusGetVolume(MixBus busIndex);

		void BusSetVolume(MixBus busIndex, double volume);

		void BusFadeVolume(MixBus busIndex, double volume, const Duration& time);

		void BusClearFilter(MixBus busIndex, size_t filterIndex);

		void BusSetLowPassFilter(MixBus busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);

		void BusSetHighPassFilter(MixBus busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);

		void BusSetEchoFilter(MixBus busIndex, size_t filterIndex, double delay, double decay, double wet = 1.0);

		void BusSetReverbFilter(MixBus busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet = 1.0);

		void BusSetPitchShiftFilter(MixBus busIndex, size_t filterIndex, double pitchShift);

		/// @brief ピッチシフトフィルタが利用できるかを返します。
		/// @return ピッチシフトフィルタを利用できる場合 true, それ以外の場合は false
		[[nodiscard]]
		bool SupportsPitchShift();
	}
}
