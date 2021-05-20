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
# include <ThirdParty/rtaudio/RtAudio.h>

namespace s3d
{
	namespace System
	{
		Array<MicrophoneInfo> EnumerateMicrophones()
		{
			LOG_SCOPED_TRACE(U"System::EnumerateMicrophones()");

			RtAudio device;

			const uint32 num_devices = device.getDeviceCount();

			Array<MicrophoneInfo> results;

			uint32 deviceIndex = 0;

			for (uint32 i = 0; i < num_devices; ++i)
			{
				const auto info = device.getDeviceInfo(i);

				if (info.inputChannels == 0)
				{
					continue;
				}

				const String name = Unicode::FromUTF8(info.name);
				const Array<uint32> sampleRates(info.sampleRates.begin(), info.sampleRates.end());

				results.push_back(MicrophoneInfo{ deviceIndex, name, sampleRates, info.preferredSampleRate });
				++deviceIndex;
			}

			return results;
		}
	}
}
