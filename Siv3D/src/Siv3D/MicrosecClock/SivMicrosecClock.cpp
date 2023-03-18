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

# include <Siv3D/MicrosecClock.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/Console.hpp>
# include <Siv3D/Print.hpp>

namespace s3d
{
	void MicrosecClock::log() const
	{
		Logger(Microseconds{ us() });
	}

	void MicrosecClock::console() const
	{
		Console(Microseconds{ us() });
	}

	void MicrosecClock::print() const
	{
		Print(Microseconds{ us() });
	}
}
