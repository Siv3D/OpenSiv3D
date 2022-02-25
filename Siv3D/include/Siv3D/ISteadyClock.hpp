//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Time.hpp"

namespace s3d
{
	class ISteadyClock
	{
	public:

		virtual ~ISteadyClock() = default;

		virtual uint64 getMicrosec() = 0;

		virtual uint64 getNanosec();

		static uint64 GetMicrosec(ISteadyClock* pSteadyClock);

		static uint64 GetNanosec(ISteadyClock* pSteadyClock);
	};
}

# include "detail/ISteadyClock.ipp"
