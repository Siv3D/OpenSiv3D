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

# include <Siv3D/GlobalAudio.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace GlobalAudio
	{
		size_t GetActiveVoiceCount()
		{
			return SIV3D_ENGINE(Audio)->getActiveVoiceCount();
		}

		void FadeVolume(const double volume, const Duration& time)
		{
			SIV3D_ENGINE(Audio)->fadeGlobalVolume(volume, Max(time, Duration{ 0.0 }));
		}

		Array<float> GetSamples()
		{
			Array<float> result;
			
			GetSamples(result);

			return result;
		}

		void GetSamples(Array<float>& samples)
		{
			SIV3D_ENGINE(Audio)->getGlobalSamples(samples);
		}

		Array<float> GetFFT()
		{
			Array<float> result;

			GetFFT(result);

			return result;
		}

		void GetFFT(Array<float>& result)
		{
			SIV3D_ENGINE(Audio)->getGlobalFFT(result);
		}

		Array<float> BusGetSamples(const size_t busIndex)
		{
			Array<float> result;

			BusGetSamples(busIndex, result);

			return result;
		}

		void BusGetSamples(const size_t busIndex, Array<float>& samples)
		{
			SIV3D_ENGINE(Audio)->getBusSamples(busIndex, samples);
		}

		Array<float> BusGetBFFT(size_t busIndex)
		{
			Array<float> result;

			BusGetFFT(busIndex, result);

			return result;
		}

		void BusGetFFT(const size_t busIndex, Array<float>& result)
		{
			SIV3D_ENGINE(Audio)->getBusFFT(busIndex, result);
		}

		void BusClearFilter(const size_t busIndex, const size_t filterIndex)
		{
			if ((Audio::MaxBusCount <= busIndex)
				|| (Audio::MaxFilterCount <= filterIndex))
			{
				return;
			}

			SIV3D_ENGINE(Audio)->clearFilter(busIndex, filterIndex);
		}

		void BusSetLowPassFilter(const size_t busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
		{
			if ((Audio::MaxBusCount <= busIndex)
				|| (Audio::MaxFilterCount <= filterIndex))
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setLowPassFilter(busIndex, filterIndex, cutoffFrequency, resonance, wet);
		}

		void BusSetHighPassFilter(const size_t busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
		{
			if ((Audio::MaxBusCount <= busIndex)
				|| (Audio::MaxFilterCount <= filterIndex))
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setHighPassFilter(busIndex, filterIndex, cutoffFrequency, resonance, wet);
		}

		void BusSetEchoFilter(const size_t busIndex, const size_t filterIndex, const double delay, const double decay, const double wet)
		{
			if ((Audio::MaxBusCount <= busIndex)
				|| (Audio::MaxFilterCount <= filterIndex))
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setEchoFilter(busIndex, filterIndex, delay, decay, wet);
		}

		void BusSetReverbFilter(const size_t busIndex, const size_t filterIndex, const bool freeze, const double roomSize, const double damp, const double width, const double wet)
		{
			if ((Audio::MaxBusCount <= busIndex)
				|| (Audio::MaxFilterCount <= filterIndex))
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setReverbFilter(busIndex, filterIndex, freeze, roomSize, damp, width, wet);
		}
	}
}
