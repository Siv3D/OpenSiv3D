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

# include <Siv3D/Common.hpp>
# include <Siv3D/FFT.hpp>
# include <Siv3D/FFT/IFFT.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace FFT
	{
		//void Analyze(FFTResult& result, const Audio& audio, const FFTSampleLength sampleLength, const double offsetTimeSec)
		//{
		//	const int32 samples = 256 << static_cast<int32>(sampleLength);

		//	const int32 offset = static_cast<int32>(audio.samplingRate() * offsetTimeSec);

		//	Analyze(result, audio.getWave(), Max(static_cast<int32>(audio.posSample()) + samples / 2 + offset, 0), sampleLength);
		//}

		void Analyze(FFTResult& result, const Wave& wave, const size_t pos, const FFTSampleLength sampleLength)
		{
			SIV3D_ENGINE(FFT)->fft(result, wave, static_cast<uint32>(pos), sampleLength);
		}

		void Analyze(FFTResult& result, const Array<WaveSampleS16>& wave, const size_t pos, const uint32 sampleRate, const FFTSampleLength sampleLength)
		{
			SIV3D_ENGINE(FFT)->fft(result, wave, static_cast<uint32>(pos), sampleRate, sampleLength);
		}

		void Analyze(FFTResult& result, const float* input, const size_t length, const uint32 sampleRate, const FFTSampleLength sampleLength)
		{
			SIV3D_ENGINE(FFT)->fft(result, input, static_cast<uint32>(length), sampleRate, sampleLength);
		}
	}
}
