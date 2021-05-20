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

				results.emplace_back(static_cast<uint32>(i), std::move(name));
			}

			return results;
		}
	}
}
