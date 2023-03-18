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

# pragma once

namespace s3d
{
	inline uint64 ISteadyClock::getNanosec()
	{
		return (getMicrosec() * 1000);
	}

	inline uint64 ISteadyClock::GetMicrosec(ISteadyClock* pSteadyClock)
	{
		if (pSteadyClock)
		{
			return pSteadyClock->getMicrosec();
		}
		else
		{
			return Time::GetMicrosec();
		}
	}

	inline uint64 ISteadyClock::GetNanosec(ISteadyClock* pSteadyClock)
	{
		if (pSteadyClock)
		{
			return pSteadyClock->getNanosec();
		}
		else
		{
			return Time::GetNanosec();
		}
	}
}
