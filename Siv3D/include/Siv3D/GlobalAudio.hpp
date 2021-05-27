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
# include "Common.hpp"
# include "Duration.hpp"
# include "Array.hpp"
# include "FFTResult.hpp"

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

		void GetSamples(Array<float>& samples);

		[[nodiscard]]
		FFTResult GetFFT();

		void GetFFT(FFTResult& result);

		[[nodiscard]]
		Array<float> BusGetSamples(size_t busIndex);

		void BusGetSamples(size_t busIndex, Array<float>& samples);

		[[nodiscard]]
		FFTResult BusGetFFT(size_t busIndex);

		void BusGetFFT(size_t busIndex, FFTResult& result);

		[[nodiscard]]
		double BusGetVolume(size_t busIndex);

		void BusSetVolume(size_t busIndex, double volume);

		void BusFadeVolume(size_t busIndex, double volume, const Duration& time);

		void BusClearFilter(size_t busIndex, size_t filterIndex);

		void BusSetLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);

		void BusSetHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);

		void BusSetEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay, double wet = 1.0);

		void BusSetReverbFilter(size_t busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet = 1.0);

		void BusSetPitchShiftFilter(size_t busIndex, size_t filterIndex, double pitchShift);
	}
}
