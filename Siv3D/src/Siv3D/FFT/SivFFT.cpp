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

# include <Siv3DEngine.hpp>
# include <Siv3D/FFT.hpp>
//# include <Siv3D/Audio.hpp>
# include "IFFT.hpp"

namespace s3d
{
	FFTResult::FFTResult()
	{

	}

	namespace FFT
	{
		//void Analyze(FFTResult& result, const Audio& audio, const FFTSampleLength sampleLength, double offsetTime)
		//{
		//	const int32 samples = 256 << static_cast<int32>(sampleLength);

		//	const int32 offset = static_cast<int32>(audio.samplingRate() * offsetTime);

		//	Analyze(result, audio.getWave(), Max(static_cast<int32>(audio.posSample()) + samples / 2 + offset, 0), sampleLength);
		//}

		void Analyze(FFTResult& result, const Wave& wave, const uint32 pos, const FFTSampleLength sampleLength)
		{
			Siv3DEngine::Get<ISiv3DFFT>()->fft(result, wave, pos, sampleLength);
		}

		void Analyze(FFTResult& result, const Array<WaveSampleS16>& wave, uint32 pos, uint32 samplingRate, const FFTSampleLength sampleLength)
		{
			Siv3DEngine::Get<ISiv3DFFT>()->fft(result, wave, pos, samplingRate, sampleLength);
		}

		void Analyze(FFTResult& result, const float* input, const uint32 length, const uint32 samplingRate, const FFTSampleLength sampleLength)
		{
			Siv3DEngine::Get<ISiv3DFFT>()->fft(result, input, length, samplingRate, sampleLength);
		}
	}
}
