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

# include <Siv3D/MicrophoneInfo.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace System
	{
		Array<MicrophoneInfo> EnumerateMicrophones()
		{
			LOG_SCOPED_TRACE(U"System::EnumerateMicrophones()");

			Array<MicrophoneInfo> results;

			return results;
		}
	}
}
