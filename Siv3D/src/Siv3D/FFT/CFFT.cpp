//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CFFT.hpp"
# include <Siv3D/FFT.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CFFT::CFFT()
	{
		m_setups.fill(nullptr);
	}

	CFFT::~CFFT()
	{
		AlignedFree(m_workBuffer);

		AlignedFree(m_inoutBuffer);

		for (auto& setup : m_setups)
		{
			::pffft_destroy_setup(setup);

			setup = nullptr;
		}
	}

	bool CFFT::init()
	{
		int32 i = 0;

		for (auto& setup : m_setups)
		{
			setup = ::pffft_new_setup(256 << i++, PFFFT_REAL);
		}

		m_inoutBuffer = AlignedMalloc<float, 16>(16384);

		m_workBuffer = AlignedMalloc<float, 16>(16384);

		LOG_INFO(U"ℹ️ FFT initialized");

		return true;
	}

	void CFFT::fft(FFTResult& result, const Wave& wave, uint32 pos, const FFTSampleLength sampleLength)
	{
		const int32 samples = 256 << static_cast<int32>(sampleLength);
		const int32 begin = std::max(static_cast<int32>(pos) - 1 - samples, 0);
		const int32 end = std::min(begin + samples, static_cast<int32>(wave.samples()));
		const int32 fillCount = end - begin;

		float* pDst = m_inoutBuffer;

		if (fillCount)
		{
			const WaveSample* pSrc = &wave[begin];

			for (int32 i = 0; i < fillCount; ++i)
			{
				*pDst++ = (pSrc->left + pSrc->right) / 2;
				
				++pSrc;
			}
		}

		for (int32 i = fillCount; i < samples; ++i)
		{
			*pDst++ = 0.0f;
		}

		doFFT(result, wave.samplingRate(), sampleLength);
	}

	void CFFT::fft(FFTResult& result, const float* input, size_t size, const uint32 samplingRate, const FFTSampleLength sampleLength)
	{
		::memcpy(m_inoutBuffer, input, sizeof(float) * size);

		doFFT(result, samplingRate, sampleLength);
	}

	void CFFT::doFFT(FFTResult& result, const uint32 samplingRate, const FFTSampleLength sampleLength)
	{
		result.buffer.resize(128 << static_cast<int32>(sampleLength));

		::pffft_transform_ordered(m_setups[static_cast<size_t>(sampleLength)], m_inoutBuffer, m_inoutBuffer, m_workBuffer, PFFFT_FORWARD);

		const float m = 1.0f / result.buffer.size();
		const float* pSrc = m_inoutBuffer;
		float* pDst = result.buffer.data();

		for (size_t i = 0; i < result.buffer.size(); ++i)
		{
			const float f0 = *pSrc++;
			const float f1 = *pSrc++;
			*pDst++ = std::sqrt(f0 * f0 + f1 * f1) * m;
		}

		result.samplingRate = samplingRate;
		result.resolution = static_cast<double>(samplingRate) / (256 << static_cast<int32>(sampleLength));
	}
}
