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
	inline uint64 MillisecClock::ms() const noexcept
	{
		return (Time::GetMillisec() - m_start);
	}

	inline void MillisecClock::log() const
	{
		Logger(Milliseconds{ ms() });
	}

	inline void MillisecClock::console() const
	{
		Console(Milliseconds{ ms() });
	}

	inline void MillisecClock::print() const
	{
		Print(Milliseconds{ ms() });
	}
}
