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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/WaveSample.hpp>

namespace s3d
{
	class ISiv3DFFT
	{
	public:

		static ISiv3DFFT* Create();

		virtual ~ISiv3DFFT() = default;

		virtual void init() = 0;

		virtual void fft(FFTResult& result, const Wave& wave, uint32 pos, FFTSampleLength sampleLength) = 0;

		virtual void fft(FFTResult& result, const Array<WaveSampleS16>& wave, const uint32 pos, uint32 samplingRate, FFTSampleLength sampleLength) = 0;

		virtual void fft(FFTResult& result, const float* input, size_t size, uint32 samplingRate, FFTSampleLength sampleLength) = 0;
	};
}
