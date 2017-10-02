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
# include "Duration.hpp"
# include "Stopwatch.hpp"

namespace s3d
{
	/// <summary>
	/// タイマー
	/// </summary>
	class Timer
	{
	private:

		int64 m_initialTimeMicrosec = 0;

		int64 m_startTimeMicrosec = 0;

		int64 m_accumulationMicrosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

	public:

		/// <summary>
		/// タイマーを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit Timer(const MicrosecondsF& time = MicrosecondsF(0.0), bool startImmediately = false)
			: m_initialTimeMicrosec(static_cast<int64>(time.count()))
		{
			set(time);

			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// タイマーを開始・再開します。
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

			m_startTimeMicrosec = Time::GetMicrosec();
		}

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		int32 d() const { return static_cast<int32>(d64()); }

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		int64 d64() const { return us() / (1000LL * 1000LL * 60LL * 60LL * 24LL); }

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		double dF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL)); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		int32 h() const { return static_cast<int32>(h64()); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		int64 h64() const { return us() / (1000LL * 1000LL * 60LL * 60LL); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		double hF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		int32 min() const { return static_cast<int32>(min64()); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		int64 min64() const { return us() / (1000LL * 1000LL * 60LL); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		double minF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		int32 s() const { return static_cast<int32>(s64()); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		int64 s64() const { return us() / (1000LL * 1000LL); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		double sF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		int32 ms() const { return static_cast<int32>(ms64()); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		int64 ms64() const { return us() / (1000LL); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		double msF() const { return static_cast<double>(us() / static_cast<double>(1000LL)); }

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		int64 us() const
		{
			const int64 t = Time::GetMicrosec();

			if (!m_isStarted)
			{
				return 0;
			}

			if (m_pausing)
			{
				return Max<int64>(m_accumulationMicrosec, 0);
			}

			return Max<int64>(m_accumulationMicrosec - (t - m_startTimeMicrosec), 0);
		}

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		int64 us64() const
		{
			return us();
		}

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		double usF() const { return static_cast<double>(us()); }

		/// <summary>
		/// タイマーの初期設定時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの初期設定時間
		/// </returns>
		Milliseconds duration() const { return Milliseconds(m_initialTimeMicrosec / 1'000); }

		/// <summary>
		/// タイマーの初期設定時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの初期設定時間
		/// </returns>
		MillisecondsF durationF() const { return MillisecondsF(m_initialTimeMicrosec / 1'000.0); }

		/// <summary>
		/// タイマーの残り時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間
		/// </returns>
		Milliseconds remaining() const { return Milliseconds(ms()); }

		/// <summary>
		/// タイマーの残り時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間
		/// </returns>
		MillisecondsF remainingF() const { return MillisecondsF(msF()); }

		/// <summary>
		/// タイマーの進み具合を 1 から 0 の範囲で返します。
		/// </summary>
		/// <returns>
		/// タイマーの進み具合 (1.0 から始まり、0.0 で終わる)
		/// </returns>
		double progress1_0() const
		{
			return static_cast<double>(us()) / m_initialTimeMicrosec;
		}

		/// <summary>
		/// タイマーの進み具合を 0 から 1 の範囲で返します。
		/// </summary>
		/// <returns>
		/// タイマーの進み具合 (0.0 から始まり、1.0 で終わる)
		/// </returns>
		double progress0_1() const
		{
			return 1.0 - progress1_0();
		}

		/// <summary>
		/// タイマーが 0 に達しているかを返します。
		/// </summary>
		/// <returns>
		/// タイマーが 0 に達している場合は true, それ以外の場合は false
		/// </returns>
		bool reachedZero() const
		{
			return us() <= 0;
		}

		/// <summary>
		/// タイマーが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isStarted() const { return m_isStarted; }

		/// <summary>
		/// タイマーが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const { return m_isStarted && m_pausing; }

		/// <summary>
		/// タイマーが時間を計測中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始されていて、なおかつ一時停止中でない場合 true, それ以外の場合は false
		/// </remarks>
		bool isRunning() const { return m_isStarted && !m_pausing; }

		/// <summary>
		/// タイマーを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause()
		{
			m_accumulationMicrosec = us();

			m_pausing = true;
		}

		/// <summary>
		/// タイマーが一時停止中である場合、再開します。
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
		/// タイマーを最初の設定時刻から開始しなおします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart()
		{
			set(MicrosecondsF(m_initialTimeMicrosec));
			
			start();
		}
		
		/// <summary>
		/// タイマーの残り時間を変更して、タイマーを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart(const MicrosecondsF& time)
		{
			set(time);

			start();
		}

		/// <summary>
		/// タイマーの残り時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する残り時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MicrosecondsF& time)
		{
			m_isStarted = true;

			m_accumulationMicrosec = static_cast<int64>(time.count());

			m_startTimeMicrosec = Time::GetMicrosec();
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
		/// フォーマットされた残り時間
		/// </returns>
		String format(const String& pattern = S3DSTR("H:mm:ss.xx")) const
		{
			return Stopwatch(remainingF(), false).format(pattern);
		}
	};


	inline bool operator <(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remainingF() < time;
	}

	inline bool operator <=(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remainingF() <= time;
	}

	inline bool operator >(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remainingF() > time;
	}

	inline bool operator >=(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remainingF() >= time;
	}


	inline bool operator <(const MicrosecondsF& time, const Timer& timer)
	{
		return time < timer.remainingF();
	}

	inline bool operator <=(const MicrosecondsF& time, const Timer& timer)
	{
		return time <= timer.remainingF();
	}

	inline bool operator >(const MicrosecondsF& time, const Timer& timer)
	{
		return time > timer.remainingF();
	}

	inline bool operator >=(const MicrosecondsF& time, const Timer& timer)
	{
		return time >= timer.remainingF();
	}

	inline void Formatter(FormatData& formatData, const Timer& timer)
	{
		formatData.string.append(timer.format());
	}
}
