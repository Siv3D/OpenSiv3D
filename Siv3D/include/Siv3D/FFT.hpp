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
# include "FFTResult.hpp"
# include "Scene.hpp"
# include "FFTSampleLength.hpp"
# include "WaveSample.hpp"

namespace s3d
{
	class Wave;
	class Audio;

	namespace FFT
	{
		void Analyze(FFTResult& result, const Audio& audio, FFTSampleLength sampleLength = FFTSampleLength::Default, double offsetTimeSec = Scene::DeltaTime());

		/// @brief FFT を実行します。
		/// @param result 結果の出力先
		/// @param wave 入力の波形
		/// @param pos 波形中の再生位置（サンプル）
		/// @param sampleLength FFT サンプル数
		void Analyze(FFTResult& result, const Wave& wave, size_t pos, FFTSampleLength sampleLength = FFTSampleLength::Default);

		/// @brief FFT を実行します。
		/// @param result 結果の出力先
		/// @param wave 入力の波形
		/// @param pos 波形中の再生位置（サンプル）
		/// @param sampleRate 入力波形のサンプリングレート
		/// @param sampleLength FFT サンプル数
		void Analyze(FFTResult& result, const Array<WaveSampleS16>& wave, size_t pos, uint32 sampleRate, FFTSampleLength sampleLength = FFTSampleLength::Default);

		/// @brief FFT を実行します。
		/// @param result 結果の出力先
		/// @param input 入力の波形
		/// @param length 入力波形の長さ
		/// @param sampleRate 入力波形のサンプリングレート
		/// @param sampleLength FFT サンプル数
		void Analyze(FFTResult& result, const float* input, size_t length, uint32 sampleRate, FFTSampleLength sampleLength = FFTSampleLength::Default);
	}
}
