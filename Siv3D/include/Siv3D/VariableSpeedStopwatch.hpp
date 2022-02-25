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
# include "Common.hpp"
# include "ISteadyClock.hpp"
# include "Duration.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class VariableSpeedStopwatch
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit VariableSpeedStopwatch(StartImmediately startImmediately = StartImmediately::No, ISteadyClock* pSteadyClock = nullptr);

		SIV3D_NODISCARD_CXX20
		explicit VariableSpeedStopwatch(double speed, StartImmediately startImmediately = StartImmediately::No, ISteadyClock* pSteadyClock = nullptr);

		SIV3D_NODISCARD_CXX20
		explicit VariableSpeedStopwatch(const Duration& startTime, double speed = 1.0, StartImmediately startImmediately = StartImmediately::No, ISteadyClock* pSteadyClock = nullptr);

		[[nodiscard]]
		bool isStarted() const noexcept;

		[[nodiscard]]
		bool isPaused() const noexcept;

		[[nodiscard]]
		bool isRunning() const noexcept;

		void start();

		void pause();

		void resume();

		void reset() noexcept;

		void restart();

		void set(const Duration& time);

		void setSpeed(double speed);

		[[nodiscard]]
		double getSpeed() const noexcept;

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
		Duration elapsed() const;

		[[nodiscard]]
		String format(StringView format = U"H:mm:ss.xx"_sv) const;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend auto operator <=>(const VariableSpeedStopwatch& s, const MicrosecondsF& timeUs)
		{
			return (s.usF() <=> timeUs.count());
		}

	# else

		[[nodiscard]]
		friend bool operator <(const VariableSpeedStopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() < time);
		}

		[[nodiscard]]
		friend bool operator <=(const VariableSpeedStopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() <= time);
		}

		[[nodiscard]]
		friend bool operator >(const VariableSpeedStopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() > time);
		}

		[[nodiscard]]
		friend bool operator >=(const VariableSpeedStopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() >= time);
		}

		[[nodiscard]]
		friend bool operator <(const MicrosecondsF& time, const VariableSpeedStopwatch& s)
		{
			return (time < s.elapsed());
		}

		[[nodiscard]]
		friend bool operator <=(const MicrosecondsF& time, const VariableSpeedStopwatch& s)
		{
			return (time <= s.elapsed());
		}

		[[nodiscard]]
		friend bool operator >(const MicrosecondsF& time, const VariableSpeedStopwatch& s)
		{
			return (time > s.elapsed());
		}

		[[nodiscard]]
		friend bool operator >=(const MicrosecondsF& time, const VariableSpeedStopwatch& s)
		{
			return (time >= s.elapsed());
		}

	# endif

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const VariableSpeedStopwatch& value)
		{
			return output << value.format();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const VariableSpeedStopwatch& value)
		{
			formatData.string.append(value.format());
		}

	private:

		double m_speed = 1.0;

		mutable int64 m_lastTimeNanosec = 0;

		mutable int64 m_accumulationNanosec = 0;

		ISteadyClock* m_pSteadyClock = nullptr;

		bool m_isStarted = false;

		bool m_pausing = true;

		[[nodiscard]]
		int64 ns() const;
	};
}

# include "detail/VariableSpeedStopwatch.ipp"
