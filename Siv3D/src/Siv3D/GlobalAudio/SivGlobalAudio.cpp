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

		void PauseAll()
		{
			SIV3D_ENGINE(Audio)->globalPause();
		}

		void ResumeAll()
		{
			SIV3D_ENGINE(Audio)->globalResume();
		}

		double GetVolume()
		{
			return SIV3D_ENGINE(Audio)->getGlobalVolume();
		}

		void SetVolume(double volume)
		{
			SIV3D_ENGINE(Audio)->setGlobalVolume(volume);
		}

		void FadeVolume(const double volume, const Duration& time)
		{
			SIV3D_ENGINE(Audio)->fadeGlobalVolume(volume, Max(time, SecondsF(0.0)));
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

		FFTResult GetFFT()
		{
			FFTResult result;

			GetFFT(result);

			return result;
		}

		void GetFFT(FFTResult& result)
		{
			SIV3D_ENGINE(Audio)->getGlobalFFT(result);
		}

		Array<float> BusGetSamples(const MixBus busIndex)
		{
			Array<float> result;

			BusGetSamples(busIndex, result);

			return result;
		}

		void BusGetSamples(const MixBus busIndex, Array<float>& samples)
		{
			SIV3D_ENGINE(Audio)->getBusSamples(FromEnum(busIndex), samples);
		}

		FFTResult BusGetFFT(MixBus busIndex)
		{
			FFTResult result;

			BusGetFFT(busIndex, result);

			return result;
		}

		void BusGetFFT(const MixBus busIndex, FFTResult& result)
		{
			SIV3D_ENGINE(Audio)->getBusFFT(FromEnum(busIndex), result);
		}

		double BusGetVolume(const MixBus busIndex)
		{
			return SIV3D_ENGINE(Audio)->getBusVolume(FromEnum(busIndex));
		}

		void BusSetVolume(const MixBus busIndex, const double volume)
		{
			SIV3D_ENGINE(Audio)->setBusVolume(FromEnum(busIndex), volume);
		}

		void BusFadeVolume(const MixBus busIndex, const double volume, const Duration& time)
		{
			SIV3D_ENGINE(Audio)->fadeBusVolume(FromEnum(busIndex), volume, time);
		}

		void BusClearFilter(const MixBus busIndex, const size_t filterIndex)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->clearFilter(FromEnum(busIndex), filterIndex);
		}

		void BusSetLowPassFilter(const MixBus busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setLowPassFilter(FromEnum(busIndex), filterIndex, cutoffFrequency, resonance, wet);
		}

		void BusSetHighPassFilter(const MixBus busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setHighPassFilter(FromEnum(busIndex), filterIndex, cutoffFrequency, resonance, wet);
		}

		void BusSetEchoFilter(const MixBus busIndex, const size_t filterIndex, const double delay, const double decay, const double wet)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setEchoFilter(FromEnum(busIndex), filterIndex, delay, decay, wet);
		}

		void BusSetReverbFilter(const MixBus busIndex, const size_t filterIndex, const bool freeze, const double roomSize, const double damp, const double width, const double wet)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setReverbFilter(FromEnum(busIndex), filterIndex, freeze, roomSize, damp, width, wet);
		}
		
		void BusSetPitchShiftFilter(const MixBus busIndex, const size_t filterIndex, const double pitchShift)
		{
			if (Audio::MaxFilterCount <= filterIndex)
			{
				return;
			}

			SIV3D_ENGINE(Audio)->setPitchShiftFilter(FromEnum(busIndex), filterIndex, pitchShift);
		}

		bool SupportsPitchShift()
		{
			return SIV3D_ENGINE(Audio)->supportsPitchShift();
		}
	}
}
