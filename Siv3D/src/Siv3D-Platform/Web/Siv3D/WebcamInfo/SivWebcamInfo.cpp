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

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <Siv3D/WebcamInfo.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace System
	{
		Array<WebcamInfo> EnumerateWebcams()
		{
			Array<WebcamInfo> results;

			for (uint32 index = 0; index < 8; ++index)
			{
				const std::string name = "/dev/video" + std::to_string(index);

				int h = ::open(name.c_str(), O_RDONLY);

				if (h != -1)
				{
					::close(h);

					WebcamInfo info;
					info.cameraIndex = index;
					info.uniqueName = info.name = Unicode::Widen(name);				
					results << info;
				}
			}

			return results;
		}
	}
}
