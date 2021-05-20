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

# include <Siv3D/MicrophoneInfo.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace System
	{
		Array<MicrophoneInfo> EnumerateMicrophones()
		{
			Array<MicrophoneInfo> results;

			const size_t num_devices = ::waveInGetNumDevs();

			if (num_devices == 0)
			{
				return{};
			}

			for (size_t i = 0; i < num_devices; ++i)
			{
				WAVEINCAPSW caps{};

				if (MMSYSERR_NOERROR != ::waveInGetDevCapsW(i, &caps, sizeof(caps)))
				{
					continue;
				}

				String name;
				
				if (caps.szPname)
				{
					name = Unicode::FromWstring(caps.szPname);
				}

				Array<uint32> sampleRates;
				uint32 preferredSampleRate = 0;

				if ((caps.dwFormats & WAVE_FORMAT_1S16)
					|| (caps.dwFormats & WAVE_FORMAT_1M16))
				{
					sampleRates << 11'025u;
					preferredSampleRate = 11'025u;
				}

				if ((caps.dwFormats & WAVE_FORMAT_2S16)
					|| (caps.dwFormats & WAVE_FORMAT_2M16))
				{
					sampleRates << 22'050u;
					preferredSampleRate = 22'050u;
				}

				if ((caps.dwFormats & WAVE_FORMAT_44S16)
					|| (caps.dwFormats & WAVE_FORMAT_44M16))
				{
					sampleRates << 44'100u;
					preferredSampleRate = 44'100u;
				}

				if ((caps.dwFormats & WAVE_FORMAT_48S16)
					|| (caps.dwFormats & WAVE_FORMAT_48M16))
				{
					sampleRates << 48'000u;
					preferredSampleRate = 48'000u;
				}

				if ((caps.dwFormats & WAVE_FORMAT_96S16)
					|| (caps.dwFormats & WAVE_FORMAT_96M16))
				{
					sampleRates << 96'000u;
				}

				results.emplace_back(static_cast<uint32>(i), std::move(name), std::move(sampleRates), preferredSampleRate);
			}

			return results;
		}
	}
}
