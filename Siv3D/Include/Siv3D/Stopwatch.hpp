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

namespace s3d
{
	/// <summary>
	/// ストップウォッチ
	/// </summary>
	class Stopwatch
	{
	private:

		int64 m_startTimeMicrosec = 0;

		int64 m_accumulationMicrosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit Stopwatch(bool startImmediately = false)
		{
			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit Stopwatch(const MicrosecondsF& time, bool startImmediately = false)
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

			m_startTimeMicrosec = Time::GetMicrosec();
		}

		/// <summary>
		/// ストップウォッチの経過時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[日]
		/// </returns>
		int32 d() const { return static_cast<int32>(d64()); }

		int64 d64() const { return us() / (1000LL * 1000LL * 60LL * 60LL * 24LL); }

		double dF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int32 h() const { return static_cast<int32>(h64()); }

		int64 h64() const { return us() / (1000LL * 1000LL * 60LL * 60LL); }

		double hF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int32 min() const { return static_cast<int32>(min64()); }

		int64 min64() const { return us() / (1000LL * 1000LL * 60LL); }

		double minF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int32 s() const { return static_cast<int32>(s64()); }

		int64 s64() const { return us() / (1000LL * 1000LL); }

		double sF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int32 ms() const { return static_cast<int32>(ms64()); }

		int64 ms64() const { return us() / (1000LL); }

		double msF() const { return static_cast<double>(us() / static_cast<double>(1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
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
				return m_accumulationMicrosec;
			}

			return m_accumulationMicrosec + (t - m_startTimeMicrosec);
		}

		int64 us64() const
		{
			return us();
		}

		double usF() const { return static_cast<double>(us()); }

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
			m_accumulationMicrosec = us();

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
			m_accumulationMicrosec = 0;

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
		/// フォーマットされた経過時間
		/// </returns>
		String format(const String& pattern = S3DSTR("H:mm:ss.xx")) const;
	};

	inline bool operator <(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() < time;
	}

	inline bool operator <=(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() <= time;
	}

	inline bool operator >(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() > time;
	}

	inline bool operator >=(const Stopwatch& s, const MicrosecondsF& time)
	{
		return s.elapsedF() >= time;
	}


	inline bool operator <(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time < s.elapsedF();
	}

	inline bool operator <=(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time <= s.elapsedF();
	}

	inline bool operator >(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time > s.elapsedF();
	}

	inline bool operator >=(const MicrosecondsF& time, const Stopwatch& s)
	{
		return time >= s.elapsedF();
	}


	inline void Formatter(FormatData& formatData, const Stopwatch& stopwatch)
	{
		formatData.string.append(stopwatch.format());
	}
}
