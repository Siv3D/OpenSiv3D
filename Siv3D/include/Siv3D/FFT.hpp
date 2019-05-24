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
# include "Array.hpp"
# include "Wave.hpp"
# include "Scene.hpp"

namespace s3d
{
	/// <summary>
	/// FFT サンプル数
	/// </summary>
	enum class FFTSampleLength
	{
		/// <summary>
		/// 256 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 172Hz
		/// </remarks>
		SL256,

		/// <summary>
		/// 512 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 86.1Hz
		/// </remarks>
		SL512,

		/// <summary>
		/// 1024 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 43.1Hz
		/// </remarks>
		SL1K,

		/// <summary>
		/// 2048 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 21.5Hz
		/// </remarks>
		SL2K,

		/// <summary>
		/// 4096 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 10.8Hz
		/// </remarks>
		SL4K,

		/// <summary>
		/// 8192 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 5.38Hz
		/// </remarks>
		SL8K,

		/// <summary>
		/// 16384 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 2.69Hz
		/// </remarks>
		SL16K,

		/// <summary>
		/// デフォルト (8192 サンプル)
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 5.38Hz
		/// </remarks>
		Default = SL8K
	};

	struct FFTResult
	{
		Array<float> buffer;

		double resolution = Wave::DefaultSamplingRate / 8192.0;

		uint32 samplingRate = Wave::DefaultSamplingRate;

		FFTResult();
	};

	namespace FFT
	{
		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="sound">
		/// 入力のサウンド
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		void Analyze(FFTResult& result, const Audio& audio, FFTSampleLength sampleLength = FFTSampleLength::Default, double offsetTime = -Scene::DeltaTime());

		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="wave">
		/// 入力の波形
		/// </param>
		/// <param name="pos">
		/// 波形中の位置（サンプル）
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		void Analyze(FFTResult& result, const Wave& wave, uint32 pos, FFTSampleLength sampleLength = FFTSampleLength::Default);

		void Analyze(FFTResult& result, const Array<WaveSampleS16>& wave, uint32 pos, uint32 samplingRate, FFTSampleLength sampleLength = FFTSampleLength::Default);

		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="input">
		/// 入力のデータ
		/// </param>
		/// <param name="length">
		/// データの長さ（サンプル）
		/// </param>
		/// <param name="samplingRate">
		/// データのサンプリングレート
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		void Analyze(FFTResult& result, const float* input, uint32 length, uint32 samplingRate, FFTSampleLength sampleLength = FFTSampleLength::Default);
	}
}
