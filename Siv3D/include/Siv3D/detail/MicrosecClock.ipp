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

namespace s3d
{
	inline uint64 MicrosecClock::us() const noexcept
	{
		return (Time::GetMicrosec() - m_start);
	}

	inline void MicrosecClock::log() const
	{
		Logger(Microseconds(us()));
	}

	inline void MicrosecClock::console() const
	{
		Console(Microseconds(us()));
	}

	//inline void MicrosecClock::print() const
	//{
	//	Print(Microseconds(us()));
	//}
}
