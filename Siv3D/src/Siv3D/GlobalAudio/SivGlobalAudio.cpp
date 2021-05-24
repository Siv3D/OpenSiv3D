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

		Array<float> GetBusSamples(const size_t busIndex)
		{
			Array<float> result;

			GetBusSamples(busIndex, result);

			return result;
		}

		void GetBusSamples(const size_t busIndex, Array<float>& samples)
		{
			SIV3D_ENGINE(Audio)->getBusSamples(busIndex, samples);
		}

		Array<float> GetBusFFT(size_t busIndex)
		{
			Array<float> result;

			GetBusFFT(busIndex, result);

			return result;
		}

		void GetBusFFT(const size_t busIndex, Array<float>& result)
		{
			SIV3D_ENGINE(Audio)->getBusFFT(busIndex, result);
		}
	}
}
