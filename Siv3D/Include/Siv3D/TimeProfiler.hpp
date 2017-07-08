//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Time.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "HashMap.hpp"

namespace s3d
{
	class TimeProfiler
	{
	private:

		struct Detail
		{
			uint64 sum = 0;

			uint64 begin = 0;

			uint64 min = UINT64_MAX;

			uint64 max = 0;

			uint32 count = 0;

			uint16 index = 0;

			bool open = false;
		};

		HashMap<String, Detail> m_data;

		Array<String> m_labels;

		String m_name;

		uint16 m_index;

		const uint64 m_start;

		uint64* begin_impl(const String& label);

		void end_impl(const uint64 end);

		String toString(const uint64 ns) const;

		void log(const uint64 end) const;

	public:

		TimeProfiler(const String& name = S3DSTR("Profiler"))
			: m_name(name)
			, m_index(0)
			, m_start(Time::GetNanosec()) {}

		~TimeProfiler()
		{
			const uint64 end = Time::GetNanosec();

			log(end);
		}

		void begin(const String& label)
		{
			if (auto p = begin_impl(label))
			{
				*p = Time::GetNanosec();
			}
		}

		void end()
		{
			const uint64 end = Time::GetNanosec();

			end_impl(end);
		}
	};
}
