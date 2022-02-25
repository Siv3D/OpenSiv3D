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
# include "../Utility.hpp"
# include "../Hash.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr int32 TimeToMillisecCount(const int32 hour, const int32 minute, const int32 second, const int32 milliseconds) noexcept
		{
			return hour * (60 * 60 * 1000)
				+ minute * (60 * 1000)
				+ second * (1000)
				+ milliseconds;
		}
	}

	inline constexpr DateTime::DateTime(
		const int32 _year,
		const int32 _month,
		const int32 _day,
		const int32 _hour,
		const int32 _minute,
		const int32 _second,
		const int32 _milliseconds) noexcept
		: Date{ _year, _month, _day }
		, hour{ _hour }
		, minute{ _minute }
		, second{ _second }
		, milliseconds{ _milliseconds } {}

	inline constexpr DateTime::DateTime(
		const Date& date,
		const int32 _hour,
		const int32 _minute,
		const int32 _second,
		const int32 _milliseconds) noexcept
		: Date{ date }
		, hour{ _hour }
		, minute{ _minute }
		, second{ _second }
		, milliseconds{ _milliseconds } {}

	inline constexpr bool DateTime::isValid() const noexcept
	{
		return Date::isValid()
			&& InRange(hour, 0, 23)
			&& InRange(minute, 0, 59)
			&& InRange(second, 0, 59)
			&& InRange(milliseconds, 0, 999);
	}

	inline String DateTime::format(const StringView format) const
	{
		return FormatDateTime(*this, format);
	}

	inline DateTime DateTime::operator +(const Days& days) const noexcept
	{
		return DateTime{ *this } += days;
	}

	inline DateTime DateTime::operator +(const Milliseconds& _milliseconds) const noexcept
	{
		return DateTime{ *this } += _milliseconds;
	}

	inline DateTime DateTime::operator -(const Days& days) const noexcept
	{
		return DateTime{ *this } -= days;
	}

	inline DateTime DateTime::operator -(const Milliseconds& _milliseconds) const noexcept
	{
		return DateTime{ *this } -= _milliseconds;
	}

	inline DateTime& DateTime::operator +=(const Days& days) noexcept
	{
		Date::operator +=(days);
		
		return *this;
	}

	inline DateTime& DateTime::operator +=(const Milliseconds& _milliseconds) noexcept
	{
		const int64 millisecIn1Day = (86400 * 1000);

		int64 count = _milliseconds.count();

		if (const int64 days = (count / millisecIn1Day))
		{
			Date::operator +=(Days{ days });

			count -= days * millisecIn1Day;
		}

		int64 newCount = detail::TimeToMillisecCount(hour, minute, second, milliseconds) + count;

		if (newCount >= millisecIn1Day)
		{
			Date::operator +=(Days{ 1 });

			newCount -= millisecIn1Day;
		}
		else if (newCount < 0)
		{
			Date::operator -=(Days{ 1 });

			newCount += millisecIn1Day;
		}

		hour			= static_cast<int32>(newCount / (60 * 60 * 1000));
		minute			= static_cast<int32>(newCount / (60 * 1000) % 60);
		second			= static_cast<int32>(newCount / (1000) % 60);
		milliseconds	= static_cast<int32>(newCount % 1000);

		return *this;
	}

	inline DateTime& DateTime::operator -=(const Days& days) noexcept
	{
		Date::operator -=(days);
		
		return *this;
	}

	inline DateTime& DateTime::operator -=(const Milliseconds& _milliseconds) noexcept
	{
		return operator +=(-_milliseconds);
	}

	inline size_t DateTime::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline DateTime DateTime::Yesterday() noexcept
	{
		return Date::Yesterday();
	}

	inline DateTime DateTime::Today() noexcept
	{
		return Date::Today();
	}

	inline DateTime DateTime::Tomorrow() noexcept
	{
		return Date::Tomorrow();
	}

	inline constexpr Duration DateTime::Subtract(const DateTime& a, const DateTime& b) noexcept
	{
		const Days diffDays = Date{ a } - Date{ b };
		const int32 aMillisec = detail::TimeToMillisecCount(a.hour, a.minute, a.second, a.milliseconds);
		const int32 bMillisec = detail::TimeToMillisecCount(b.hour, b.minute, b.second, b.milliseconds);

		return Duration((static_cast<int64>(diffDays.count()) * (86400 * 1000) + (aMillisec - bMillisec)) / 1000.0);
	}
}
