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

# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	String Stopwatch::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}


	bool operator <(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() < time;
	}

	bool operator <=(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() <= time;
	}

	bool operator >(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() > time;
	}

	bool operator >=(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsed() >= time;
	}


	bool operator <(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time < s.elapsed();
	}

	bool operator <=(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time <= s.elapsed();
	}

	bool operator >(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time > s.elapsed();
	}

	bool operator >=(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time >= s.elapsed();
	}

	void Formatter(FormatData& formatData, const Stopwatch& value)
	{
		formatData.string.append(value.format());
	}
}
