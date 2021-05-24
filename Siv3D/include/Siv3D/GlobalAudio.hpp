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

# pragma once
# include "Common.hpp"
# include "Duration.hpp"
# include "Array.hpp"

namespace s3d
{
	namespace GlobalAudio
	{
		size_t GetActiveVoiceCount();

		void FadeVolume(double volume, const Duration& time);

		Array<float> GetSamples();

		void GetSamples(Array<float>& samples);

		Array<float> GetFFT();

		void GetFFT(Array<float>& result);


		Array<float> GetBusSamples(size_t busIndex);

		void GetBusSamples(size_t busIndex, Array<float>& samples);

		Array<float> GetBusFFT(size_t busIndex);

		void GetBusFFT(size_t busIndex, Array<float>& result);


		//void SetLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance);

		//void SetHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance);
	
		//void SetEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay);

		//void SetReverbFilter(size_t busIndex, size_t filterIndex, double mode, double roomSize, double damp, double width);
	}
}
