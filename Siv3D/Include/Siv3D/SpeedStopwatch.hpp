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
# include "Stopwatch.hpp"

namespace s3d
{
	/// <summary>
	/// スピードが変更可能なストップウォッチ
	/// </summary>
	class SpeedStopwatch
	{
	private:

		double m_speed = 1.0;

		mutable int64 m_lastTimeNanosec = 0;

		mutable int64 m_accumulationNanosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

		int64 ns() const
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

	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="speed">
		/// 実際の時刻の進み方を 1.0 とした際のスピード
		/// </param>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit SpeedStopwatch(bool startImmediately = false)
			: SpeedStopwatch(1.0, startImmediately)
		{
			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="speed">
		/// 実際の時刻の進み方を 1.0 とした際のスピード
		/// </param>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit SpeedStopwatch(double speed, bool startImmediately = false)
			: m_speed(speed)
		{
			if (startImmediately)
			{
				start();
			}
		}

		explicit SpeedStopwatch(const MicrosecondsF& time, double speed = 1.0, bool startImmediately = false)
			: m_speed(speed)
		{
			set(time);

			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start()
		{
			if (!m_pausing)
			{
				return;
			}

			m_isStarted = true;

			m_pausing = false;

			m_lastTimeNanosec = Time::GetNanosec();
		}

		/// <summary>
		/// ストップウォッチの経過時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[日]
		/// </returns>
		int32 d() const { return static_cast<int32>(d64()); }

		int64 d64() const { return ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL); }

		double dF() const { return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int32 h() const { return static_cast<int32>(h64()); }

		int64 h64() const { return ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL); }

		double hF() const { return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int32 min() const { return static_cast<int32>(min64()); }

		int64 min64() const { return ns() / (1000LL * 1000LL * 1000LL * 60LL); }

		double minF() const { return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int32 s() const { return static_cast<int32>(s64()); }

		int64 s64() const { return ns() / (1000LL * 1000LL * 1000LL); }

		double sF() const { return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int32 ms() const { return static_cast<int32>(ms64()); }

		int64 ms64() const { return ns() / (1000LL * 1000LL); }

		double msF() const { return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
		/// </returns>
		int32 us() const { return static_cast<int32>(us64()); }

		int64 us64() const { return ns() / (1000LL); }

		double usF() const { return static_cast<double>(ns() / static_cast<double>(1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Milliseconds elapsed() const { return Milliseconds(ms()); }

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		MillisecondsF elapsedF() const { return MillisecondsF(msF()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します（一時停止していることもあります）。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isStarted() const { return m_isStarted; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const { return m_isStarted && m_pausing; }

		/// <summary>
		/// ストップウォッチが時間を計測中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されていて、なおかつ一時停止中でない場合 true, それ以外の場合は false
		/// </remarks>
		bool isRunning() const { return m_isStarted && !m_pausing; }

		/// <summary>
		/// ストップウォッチを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause()
		{
			m_accumulationNanosec = ns();

			m_pausing = true;
		}

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume()
		{
			if (!isPaused())
			{
				return;
			}

			start();
		}

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept
		{
			m_accumulationNanosec = 0;

			m_isStarted = false;

			m_pausing = true;
		}

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart()
		{
			reset();

			start();
		}

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MicrosecondsF& time)
		{
			m_isStarted = true;

			m_accumulationNanosec = static_cast<int64>(time.count() * 1000LL);

			m_lastTimeNanosec = Time::GetNanosec();
		}

		/// <summary>
		/// ストップウォッチのスピードを設定します。
		/// </summary>
		/// <param name="speed">
		/// 新しく設定するスピード (1.0 が通常)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setSpeed(const double speed)
		{
			if (speed == m_speed)
			{
				return;
			}

			m_accumulationNanosec = ns();

			m_speed = speed;
		}

		/// <summary>
		/// ストップウォッチのスピードを返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチのスピード
		/// </returns>
		double getSpeed() const noexcept
		{
			return m_speed;
		}

		/// <summary>
		/// DD		日 (00-)
		/// D		日 (0-)
		/// dd		日 (00-)
		/// d		日 (0-)
		/// HH		時 (00-)
		/// H		時 (0-)
		/// hh		時 (00-24)
		/// h		時 (0-24)
		/// MM		分 (00-)
		/// M		分 (0-)
		/// mm		分 (00-59)
		/// m		分 (0-59)
		/// SS		秒 (00-)
		/// S		秒 (0-)
		/// ss		秒 (00-59)
		/// s		秒 (0-59)
		/// X		ミリ秒 (0-)
		/// x		小数点以下 1 桁秒 (0-9)
		/// xx		小数点以下 2 桁秒 (00-99)
		/// xxx		小数点以下 3 桁秒 (000-999)
		/// </summary>
		/// <param name="format">
		/// フォーマット指定
		/// </param>
		/// <returns>
		/// フォーマットされた経過時間
		/// </returns>
		String format(const String& pattern = S3DSTR("H:mm:ss.xx")) const
		{
			return Stopwatch(elapsedF(), false).format(pattern);
		}
	};

	inline bool operator <(const SpeedStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() < time;
	}

	inline bool operator <=(const SpeedStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() <= time;
	}

	inline bool operator >(const SpeedStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() > time;
	}

	inline bool operator >=(const SpeedStopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() >= time;
	}


	inline bool operator <(const MicrosecondsF& time, const SpeedStopwatch& s)
	{
		return time < s.elapsedF();
	}

	inline bool operator <=(const MicrosecondsF& time, const SpeedStopwatch& s)
	{
		return time <= s.elapsedF();
	}

	inline bool operator >(const MicrosecondsF& time, const SpeedStopwatch& s)
	{
		return time > s.elapsedF();
	}

	inline bool operator >=(const MicrosecondsF& time, const SpeedStopwatch& s)
	{
		return time >= s.elapsedF();
	}

	inline void Formatter(FormatData& formatData, const SpeedStopwatch& stopwatch)
	{
		formatData.string.append(stopwatch.format());
	}
}
