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

# pragma once
# include <array>
# include "IFFT.hpp"
# include <ThirdParty/pffft/pffft.h>

namespace s3d
{
	class CFFT final : public ISiv3DFFT
	{
	public:

		CFFT();

		~CFFT() override;

		void init() override;

		void fft(FFTResult& result, const Wave& wave, uint32 pos, FFTSampleLength sampleLength) override;

		void fft(FFTResult& result, const Array<WaveSampleS16>& wave, uint32 pos, uint32 sampleRate, FFTSampleLength sampleLength) override;

		void fft(FFTResult& result, const float* input, size_t size, uint32 sampleRate, FFTSampleLength sampleLength) override;

	private:

		std::array<PFFFT_Setup*, 7> m_setups;

		float* m_inoutBuffer = nullptr;

		float* m_workBuffer = nullptr;

		void doFFT(FFTResult& result, uint32 samplingRate, FFTSampleLength sampleLength);
	};
}
