//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TimeProfiler.hpp>
# include "TimeProfilerDetail.hpp"

namespace s3d
{
	TimeProfiler::TimeProfiler(const String& name)
		: pImpl(std::make_unique<TimeProfilerDetail>(name))
	{

	}

	TimeProfiler::~TimeProfiler()
	{

	}

	void TimeProfiler::begin(const String& label)
	{
		pImpl->begin(label);
	}

	void TimeProfiler::end()
	{
		pImpl->end();
	}
}
