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

# include <Siv3D/TimeProfiler.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/Console.hpp>
# include <Siv3D/Print.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static String NsToString(const uint64 ns)
		{
			String result;

			if (ns < 1'000'000ULL) // < 1000us
			{
				if (ns < 1'000ULL) // < 1us
				{
					result.append(ToString(ns));
					result.append(U"ns"_sv);
				}
				else
				{
					if (ns < 10'000ULL) // < 10us
					{
						result.append(ToFixed(ns / 1'000.0, 2));
					}
					else if (ns < 100'000ULL) // < 100us
					{
						result.append(ToFixed(ns / 1'000.0, 1));
					}
					else // < 1000us
					{
						result.append(ToString(ns / 1'000ULL));
					}

					result.append(U"us"_sv);
				}
			}
			else if (ns < 1'000'000'000ULL) // < 1000ms
			{
				if (ns < 10'000'000ULL) // < 10ms
				{
					result.append(ToFixed(ns / 1'000'000.0, 2));
				}
				else if (ns < 100'000'000ULL) // < 100ms
				{
					result.append(ToFixed(ns / 1'000'000.0, 1));
				}
				else // < 1000ms
				{
					result.append(ToString(ns / 1'000'000ULL));
				}

				result.append(U"ms"_sv);
			}
			else // >= 1s
			{
				if (ns < 10'000'000'000ULL) // < 10s
				{
					result.append(ToFixed(ns / 1'000'000'000.0, 2));
				}
				else if (ns < 100'000'000'000ULL) // < 100s
				{
					result.append(ToFixed(ns / 1'000'000'000.0, 1));
				}
				else if (ns <= 1000'000'000'000ULL) // <= 1000s
				{
					result.append(ToString(ns / 1'000'000'000ULL));
				}
				else // > 1000s
				{
					result.assign(U">1000");
				}

				result.push_back(U's');
			}

			return result;
		}
	}

	TimeProfiler::TimeProfiler(const String& name)
		: m_name{ name } {}

	void TimeProfiler::begin(const StringView name)
	{
		auto it = m_data.find(name);

		if (it == m_data.end())
		{
			it = m_data.emplace(name, Data{ .index = static_cast<uint32>(m_data.size()) }).first;
		}

		it->second.beginNS = Time::GetNanosec();
	}

	void TimeProfiler::end(const StringView name)
	{
		const uint64 ns = Time::GetNanosec();

		auto it = m_data.find(name);

		if (it == m_data.end())
		{
			return;
		}

		auto& data = it->second;

		if (data.beginNS == 0)
		{
			return;
		}

		const uint32 time = static_cast<uint32>(ns - data.beginNS);

		if (data.buffer.size() < BufferSize)
		{
			data.buffer.push_back(time);
		}
		else
		{
			data.buffer[data.ringBufferIndex] = time;
			++data.ringBufferIndex %= BufferSize;
		}

		data.beginNS = 0;
	}

	void TimeProfiler::log() const
	{
		Array<std::pair<String, Data>> ordered;
		size_t maxLabelLength = 0;
		getData(ordered, maxLabelLength);

		Logger(U'[', m_name, U']');
		Logger(String(maxLabelLength, U' '), U" |  min   |  med   | 95 ptl |  max   |");
		Array<uint32> sorted;

		for (const auto& data : ordered)
		{
			sorted.assign(data.second.buffer.begin(), data.second.buffer.end());
			sorted.sort();
			const uint64 min = sorted.front();
			const uint64 med = sorted[sorted.size() / 2];
			const uint64 max95 = sorted[static_cast<size_t>(sorted.size() * 0.95)];
			const uint64 max = sorted.back();

			Logger(data.first.rpadded(maxLabelLength), U" | ", detail::NsToString(min).rpad(6), U" | ", detail::NsToString(med).rpad(6), U" | ", detail::NsToString(max95).rpad(6), U" | ", detail::NsToString(max).rpad(6), U" |");
		}
	}

	void TimeProfiler::console() const
	{
		Array<std::pair<String, Data>> ordered;
		size_t maxLabelLength = 0;
		getData(ordered, maxLabelLength);

		Console(U'[', m_name, U']');
		Console(String(maxLabelLength, U' '), U" |  min   |  med   | 95 ptl |  max   |");
		Array<uint32> sorted;

		for (const auto& data : ordered)
		{
			sorted.assign(data.second.buffer.begin(), data.second.buffer.end());
			sorted.sort();
			const uint64 min = sorted.front();
			const uint64 med = sorted[sorted.size() / 2];
			const uint64 max95 = sorted[static_cast<size_t>(sorted.size() * 0.95)];
			const uint64 max = sorted.back();

			Console(data.first.rpadded(maxLabelLength), U" | ", detail::NsToString(min).rpad(6), U" | ", detail::NsToString(med).rpad(6), U" | ", detail::NsToString(max95).rpad(6), U" | ", detail::NsToString(max).rpad(6), U" |");
		}

		Console(); // 改行
	}

	void TimeProfiler::print() const
	{
		Array<std::pair<String, Data>> ordered;
		size_t maxLabelLength = 0;
		getData(ordered, maxLabelLength);

		Print(U'[', m_name, U']');
		Print(String(maxLabelLength, U' '), U"  |   min   |   med   |  95 ptl |   max   |");
		Array<uint32> sorted;

		for (const auto& data : ordered)
		{
			sorted.assign(data.second.buffer.begin(), data.second.buffer.end());
			sorted.sort();
			const uint64 min = sorted.front();
			const uint64 med = sorted[sorted.size() / 2];
			const uint64 max95 = sorted[static_cast<size_t>(sorted.size() * 0.95)];
			const uint64 max = sorted.back();

			Print(data.first.rpadded(maxLabelLength), U" | ", detail::NsToString(min).rpad(6), U" | ", detail::NsToString(med).rpad(6), U" | ", detail::NsToString(max95).rpad(6), U" | ", detail::NsToString(max).rpad(6), U" |");
		}
	}

	void TimeProfiler::getData(Array<std::pair<String, Data>>& ordered, size_t& maxLabelLength) const
	{
		for (const auto& data : m_data)
		{
			if (data.second.buffer)
			{
				ordered.emplace_back(data.first, data.second);

				maxLabelLength = Max(maxLabelLength, data.first.size());
			}
		}

		ordered.sort_by([](const std::pair<String, Data>& a, const std::pair<String, Data>& b)
			{
				return (a.second.index < b.second.index);
			});
	}
}
