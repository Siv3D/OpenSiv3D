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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	class TimeProfiler
	{
	private:

		class TimeProfilerDetail;

		std::unique_ptr<TimeProfilerDetail> pImpl;

	public:

		TimeProfiler(const String& name = U"Profiler");

		~TimeProfiler();

		void begin(const String& label);

		void end();
	};
}
