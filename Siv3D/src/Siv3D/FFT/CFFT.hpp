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
# include <array>
# include <pffft/pffft.h>
# include "IFFT.hpp"

namespace s3d
{
	class CFFT : public ISiv3DFFT
	{
	private:

		std::array<PFFFT_Setup*, 7> m_setups;

		float* m_inoutBuffer = nullptr;

		float* m_workBuffer = nullptr;

		void doFFT(FFTResult& result, uint32 samplingRate, FFTSampleLength sampleLength);

	public:

		CFFT();

		~CFFT() override;

		void init() override;

		void fft(FFTResult& result, const Wave& wave, uint32 pos, FFTSampleLength sampleLength) override;

		void fft(FFTResult& result, const Array<WaveSampleS16>& wave, uint32 pos, uint32 samplingRate, FFTSampleLength sampleLength) override;

		void fft(FFTResult& result, const float* input, size_t size, uint32 samplingRate, FFTSampleLength sampleLength) override;
	};
}
