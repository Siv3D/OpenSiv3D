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
		[[nodiscard]]
		size_t GetActiveVoiceCount();

		void FadeVolume(double volume, const Duration& time);

		[[nodiscard]]
		Array<float> GetSamples();

		void GetSamples(Array<float>& samples);

		[[nodiscard]]
		Array<float> GetFFT();

		void GetFFT(Array<float>& result);


		[[nodiscard]]
		Array<float> GetBusSamples(size_t busIndex);

		void GetBusSamples(size_t busIndex, Array<float>& samples);

		[[nodiscard]]
		Array<float> GetBusFFT(size_t busIndex);

		void GetBusFFT(size_t busIndex, Array<float>& result);


		void ClearFilter(size_t busIndex, size_t filterIndex);

		void SetLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);

		void SetHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0);
	
		void SetEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay, double wet = 1.0);

		void SetReverbFilter(size_t busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet = 1.0);
	}
}
