//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# include <Siv3D/FFT.hpp>
# include <Siv3D/Audio.hpp>
# include <Siv3D/FFT/IFFT.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace FFT
	{
		void Analyze(FFTResult& result, const Audio& audio, const FFTSampleLength sampleLength, const double offsetTimeSec)
		{
			if (audio.isStreaming())
			{
				return;
			}

			const float* pLeftSmaples = audio.getSamples(0);
			const float* pRightSmaples = audio.getSamples(1);
			const uint32 sampleRate = audio.sampleRate();

			const int32 samples = (256 << static_cast<int32>(sampleLength));
			const int32 offset = static_cast<int32>(sampleRate * offsetTimeSec);
			const int32 pos = Max(static_cast<int32>(audio.posSample()) + samples / 2 + offset, 0);
			const int32 begin = Max(static_cast<int32>(pos) - 1 - samples, 0);
			const int32 end = Min(begin + samples, static_cast<int32>(audio.samples()));

			Array<float> inputs(samples);

			size_t ii = 0;

			for (int32 i = begin; i < end; ++i)
			{
				inputs[ii] = ((pLeftSmaples[i] + pRightSmaples[i]) * 0.5f);
				++ii;
			}

			Analyze(result, inputs.data(), inputs.size(), sampleRate, sampleLength);
		}

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
