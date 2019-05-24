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
# include <Siv3D/TimeProfiler.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	struct TimeProfile
	{
		uint64 sum = 0;

		uint64 begin = 0;

		uint64 min = UINT64_MAX;

		uint64 max = 0;

		uint32 count = 0;

		uint16 index = 0;

		bool open = false;
	};

	class TimeProfiler::TimeProfilerDetail
	{
	private:

		String m_name;

		uint16 m_index;

		const uint64 m_startNanosec;

		HashTable<String, TimeProfile> m_data;

		Array<String> m_labels;

		uint64* begin_impl(const String& label);

		void end_impl(const uint64 endNanosec);

		void writeLog(uint64 endNanosec);

	public:

		TimeProfilerDetail(const String& name);

		~TimeProfilerDetail();

		void begin(const String& label);

		void end();
	};
}
