//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "ISteadyClock.hpp"
# include "Time.hpp"
# include "Duration.hpp"

namespace s3d
{
	class Timer
	{
	private:

		int64 m_initialTimeMicrosec = 0;

		int64 m_startTimeMicrosec = 0;

		int64 m_remainingMicrosec = 0;

		ISteadyClock* m_pSteadyClock = nullptr;

		bool m_isStarted = false;

		bool m_pausing = true;

	public:

		SIV3D_NODISCARD_CXX20
		explicit Timer(const Duration& startRemaining, bool startImmediately = false, ISteadyClock* pSteadyClock = nullptr);

		[[nodiscard]]
		bool isStarted() const;

		[[nodiscard]]
		bool isPaused() const;

		[[nodiscard]]
		bool isRunning() const;

		[[nodiscard]]
		bool reachedZero() const;

		void start();

		void pause();

		void resume();

		void restart();

		void restart(const Duration& startRemaining);

		void setRemaining(const Duration& remaining);

		[[nodiscard]]
		int32 d() const;

		[[nodiscard]]
		int64 d64() const;

		[[nodiscard]]
		double dF() const;

		[[nodiscard]]
		int32 h() const;

		[[nodiscard]]
		int64 h64() const;

		[[nodiscard]]
		double hF() const;

		[[nodiscard]]
		int32 min() const;

		[[nodiscard]]
		int64 min64() const;

		[[nodiscard]]
		double minF() const;

		[[nodiscard]]
		int32 s() const;

		[[nodiscard]]
		int64 s64() const;

		[[nodiscard]]
		double sF() const;

		[[nodiscard]]
		int32 ms() const;

		[[nodiscard]]
		int64 ms64() const;

		[[nodiscard]]
		double msF() const;

		[[nodiscard]]
		int64 us() const;

		[[nodiscard]]
		int64 us64() const;

		[[nodiscard]]
		double usF() const;

		[[nodiscard]]
		Duration duration() const;

		[[nodiscard]]
		Duration remaining() const;

		[[nodiscard]]
		double progress1_0() const;

		[[nodiscard]]
		double progress0_1() const;

		[[nodiscard]]
		String format(StringView format = U"H:mm:ss.xx"_sv) const;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend auto operator <=>(const Timer& t, const MicrosecondsF& timeUs)
		{
			return (t.usF() <=> timeUs.count());
		}

	# else

		[[nodiscard]]
		friend bool operator <(const Timer& t, const MicrosecondsF& time)
		{
			return (t.remaining() < time);
		}

		[[nodiscard]]
		friend bool operator <=(const Timer& t, const MicrosecondsF& time)
		{
			return (t.remaining() <= time);
		}

		[[nodiscard]]
		friend bool operator >(const Timer& t, const MicrosecondsF& time)
		{
			return (t.remaining() > time);
		}

		[[nodiscard]]
		friend bool operator >=(const Timer& t, const MicrosecondsF& time)
		{
			return (t.remaining() >= time);
		}

		[[nodiscard]]
		friend bool operator <(const MicrosecondsF& time, const Timer& t)
		{
			return (time < t.remaining());
		}

		[[nodiscard]]
		friend bool operator <=(const MicrosecondsF& time, const Timer& t)
		{
			return (time <= t.remaining());
		}

		[[nodiscard]]
		friend bool operator >(const MicrosecondsF& time, const Timer& t)
		{
			return (time > t.remaining());
		}

		[[nodiscard]]
		friend bool operator >=(const MicrosecondsF& time, const Timer& t)
		{
			return (time >= t.remaining());
		}

	# endif

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Timer& value)
		{
			return output << value.format();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Timer& value)
		{
			formatData.string.append(value.format());
		}
	};
}

# include "detail/Timer.ipp"
