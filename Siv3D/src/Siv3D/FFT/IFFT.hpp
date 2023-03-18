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
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/WaveSample.hpp>

namespace s3d
{
	struct FFTResult;
	class Wave;
	enum class FFTSampleLength : uint8;

	class SIV3D_NOVTABLE ISiv3DFFT
	{
	public:

		static ISiv3DFFT* Create();

		virtual ~ISiv3DFFT() = default;

		virtual void init() = 0;

		virtual void fft(FFTResult& result, const Wave& wave, uint32 pos, FFTSampleLength sampleLength) = 0;

		virtual void fft(FFTResult& result, const Array<WaveSampleS16>& wave, uint32 pos, uint32 sampleRate, FFTSampleLength sampleLength) = 0;

		virtual void fft(FFTResult& result, const float* input, size_t size, uint32 sampleRate, FFTSampleLength sampleLength) = 0;
	};
}
