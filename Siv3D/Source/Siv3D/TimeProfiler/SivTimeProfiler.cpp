//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/TimeProfiler.hpp"
# include "../../../Include/Siv3D/Logger.hpp"

namespace s3d
{
	uint64* TimeProfiler::begin_impl(const String& label)
	{
		auto it = m_data.find(label);

		if (it == m_data.end())
		{
			if (m_index == UINT16_MAX)
			{
				return nullptr;
			}

			it = m_data.emplace(label, Detail{}).first;

			it->second.index = m_index++;
		}

		if (it->second.open)
		{
			return nullptr;
		}

		m_labels.push_back(label);

		return &(it->second.begin);
	}

	void TimeProfiler::end_impl(const uint64 end)
	{
		if (m_labels.isEmpty())
		{
			return;
		}

		auto& t = m_data[m_labels.back()];

		const uint64 time = end - t.begin;

		t.open = false;
		t.sum += time;
		t.min = Min(t.min, time);
		t.max = Max(t.max, time);
		++t.count;

		m_labels.pop_back();
	}

	String TimeProfiler::toString(const uint64 ns) const
	{
		String result;

		if (ns < 1'000'000ULL)
		{
			if (ns < 1'000ULL) // 0 - 999
			{
				result.append(ToString(ns));
				result.append(L"ns", 2);
			}
			else
			{
				if (ns < 10'000ULL) // 1,000 - 9,999
				{
					result.append(ToFixed(ns / 1'000.0, 2));
					result.append(L"us", 2);
				}
				else if (ns < 100'000ULL) // 10,000 - 99,999
				{
					result.append(ToFixed(ns / 1'000.0, 1));
					result.append(L"us", 2);
				}
				else // 100,000 - 999,999
				{
					result.append(ToString(ns / 1'000ULL));
					result.append(L"us", 2);
				}
			}
		}
		else if (ns < 1'000'000'000ULL)
		{
			if (ns < 10'000'000ULL) // 1,000,000 - 9,999,999
			{
				result.append(ToFixed(ns / 1'000'000.0, 2));
				result.append(L"ms", 2);
			}
			else if (ns < 100'000'000ULL) // 10,000,000 - 99,999,999
			{
				result.append(ToFixed(ns / 1'000'000.0, 1));
				result.append(L"ms", 2);
			}
			else // 100,000,000 - 999,999,999
			{
				result.append(ToString(ns / 1'000'000ULL));
				result.append(L"ms", 2);
			}
		}
		else
		{
			if (ns < 10'000'000'000ULL) // 1,000,000,000 - 9,999,999,999
			{
				result.append(ToFixed(ns / 1'000'000'000.0, 2));
				result.push_back(L's');
			}
			else if (ns < 100'000'000'000ULL) // 10,000,000,000 - 99,999,999,999
			{
				result.append(ToFixed(ns / 1'000'000'000.0, 1));
				result.push_back(L's');
			}
			else if (ns < 100'000'000'000ULL) // 100,000,000,000 - 999,999,999,999
			{
				result.append(ToString(ns / 1'000'000'000ULL));
				result.push_back(L's');
			}
			else // 1'000,000,000,000 -
			{
				result.assign(L">999s");
			}
		}

		return result;
	}

	void TimeProfiler::log(const uint64 end) const
	{
		if (m_data.empty())
		{
			Log(toString(end - m_start));

			return;
		}

		size_t maxLabelLength = 0;

		for (const auto& data : m_data)
		{
			if (data.second.count)
			{
				maxLabelLength = Max(maxLabelLength, data.first.length());
			}
		}

		Array<decltype(m_data)::const_iterator> its(m_index);

		for (auto it = m_data.begin(); it != m_data.end(); ++it)
		{
			its[it->second.index] = it;
		}

		Log(L'[', m_name, L']');

		Log(String(maxLabelLength, L' '), L" |  avg   |  min   |  max   |");

		for (const auto& it : its)
		{
			const auto& data = *it;

			if (data.second.count)
			{
				const uint64 average = data.second.sum / data.second.count;

				Log(data.first.rpadded(maxLabelLength), L" | ", toString(average).rpad(6), L" | ", toString(data.second.min).rpad(6), L" | ", toString(data.second.max).rpad(6), L" |");
			}
		}
	}
}
