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

# include <Siv3D/CustomStopwatch.hpp>

namespace s3d
{
	String CustomStopwatch::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}

	int64 CustomStopwatch::ns() const
	{
		const int64 t = Time::GetNanosec();

		if (!m_isStarted)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationNanosec;
		}

		const int64 delta = static_cast<int64>((t - m_lastTimeNanosec) * m_speed);

		m_accumulationNanosec += delta;

		m_lastTimeNanosec = t;

		return m_accumulationNanosec;
	}


	bool operator <(const CustomStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() < time;
	}

	bool operator <=(const CustomStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() <= time;
	}

	bool operator >(const CustomStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() > time;
	}

	bool operator >=(const CustomStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() >= time;
	}


	bool operator <(const MicrosecondsF& time, const CustomStopwatch& s)
	{
		return time < s.elapsed();
	}

	bool operator <=(const MicrosecondsF& time, const CustomStopwatch& s)
	{
		return time <= s.elapsed();
	}

	bool operator >(const MicrosecondsF& time, const CustomStopwatch& s)
	{
		return time > s.elapsed();
	}

	bool operator >=(const MicrosecondsF& time, const CustomStopwatch& s)
	{
		return time >= s.elapsed();
	}

	void Formatter(FormatData& formatData, const CustomStopwatch& value)
	{
		formatData.string.append(value.format());
	}
}
