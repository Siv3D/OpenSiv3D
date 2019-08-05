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

# include <Siv3D/Time.hpp>
# include <Siv3D/Logger.hpp>
# include "TimeProfilerDetail.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] static String NsToString(const uint64 ns)
		{
			String result;

			if (ns < 1'000'000ULL) // < 1000us
			{
				if (ns < 1'000ULL) // < 1us
				{
					result.append(ToString(ns));
					result.append(U"ns", 2);
				}
				else
				{
					if (ns < 10'000ULL) // < 10us
					{
						result.append(ToFixed(ns / 1'000.0, 2));
						result.append(U"us", 2);
					}
					else if (ns < 100'000ULL) // < 100us
					{
						result.append(ToFixed(ns / 1'000.0, 1));
						result.append(U"us", 2);
					}
					else // < 1000us
					{
						result.append(ToString(ns / 1'000ULL));
						result.append(U"us", 2);
					}
				}
			}
			else if (ns < 1'000'000'000ULL) // < 1000ms
			{
				if (ns < 10'000'000ULL) // < 10ms
				{
					result.append(ToFixed(ns / 1'000'000.0, 2));
					result.append(U"ms", 2);
				}
				else if (ns < 100'000'000ULL) // < 100ms
				{
					result.append(ToFixed(ns / 1'000'000.0, 1));
					result.append(U"ms", 2);
				}
				else // < 1000ms
				{
					result.append(ToString(ns / 1'000'000ULL));
					result.append(U"ms", 2);
				}
			}
			else // >= 1s
			{
				if (ns < 10'000'000'000ULL) // < 10s
				{
					result.append(ToFixed(ns / 1'000'000'000.0, 2));
					result.push_back(U's');
				}
				else if (ns < 100'000'000'000ULL) // < 100s
				{
					result.append(ToFixed(ns / 1'000'000'000.0, 1));
					result.push_back(U's');
				}
				else if (ns <= 1000'000'000'000ULL) // <= 1000s
				{
					result.append(ToString(ns / 1'000'000'000ULL));
					result.push_back(U's');
				}
				else // > 1000s
				{
					result.assign(U">1000s");
				}
			}

			return result;
		}
	}

	TimeProfiler::TimeProfilerDetail::TimeProfilerDetail(const String& name)
		: m_name(name)
		, m_index(0)
		, m_startNanosec(Time::GetNanosec())
	{

	}

	TimeProfiler::TimeProfilerDetail::~TimeProfilerDetail()
	{
		const uint64 endNanosec = Time::GetNanosec();

		writeLog(endNanosec);
	}

	void TimeProfiler::TimeProfilerDetail::begin(const String& label)
	{
		begin_impl(label);
	}

	void TimeProfiler::TimeProfilerDetail::end()
	{
		const uint64 endNanosec = Time::GetNanosec();

		end_impl(endNanosec);
	}

	void TimeProfiler::TimeProfilerDetail::begin_impl(const String& label)
	{
		auto it = m_data.find(label);

		if (it == m_data.end())
		{
			if (m_index == UINT16_MAX)
			{
				return;
			}

			it = m_data.emplace(label, TimeProfile{}).first;

			it.value().index = m_index++;
		}

		if (it->second.open)
		{
			return;
		}

		m_labels.push_back(label);

		it.value().begin = Time::GetNanosec();
	}

	void TimeProfiler::TimeProfilerDetail::end_impl(const uint64 end)
	{
		if (m_labels.isEmpty())
		{
			return;
		}

		auto& t = m_data[m_labels.back()];

		const uint64 time = end - t.begin;

		t.open = false;
		t.sum += time;
		t.min = std::min(t.min, time);
		t.max = std::max(t.max, time);
		++t.count;

		m_labels.pop_back();
	}

	void TimeProfiler::TimeProfilerDetail::writeLog(const uint64 endNanosec)
	{
		if (m_data.empty())
		{
			Logger(detail::NsToString(endNanosec - m_startNanosec));

			return;
		}

		size_t maxLabelLength = 0;

		for (const auto& data : m_data)
		{
			if (data.second.count)
			{
				maxLabelLength = std::max(maxLabelLength, data.first.length());
			}
		}

		Array<decltype(m_data)::const_iterator> its(m_index);

		for (auto it = m_data.begin(); it != m_data.end(); ++it)
		{
			its[it->second.index] = it;
		}

		Logger(U'[', m_name, U']');

		Logger(String(maxLabelLength, U' '), U" |  avg   |  min   |  max   |");

		for (const auto& it : its)
		{
			const auto& data = *it;

			if (data.second.count)
			{
				const uint64 average = data.second.sum / data.second.count;

				Logger(data.first.rpadded(maxLabelLength), U" | ", detail::NsToString(average).rpad(6), U" | ", detail::NsToString(data.second.min).rpad(6), U" | ", detail::NsToString(data.second.max).rpad(6), U" |");
			}
		}
	}
}
