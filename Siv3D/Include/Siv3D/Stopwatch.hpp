//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Time.hpp"

namespace s3d
{
	/// <summary>
	/// ストップウォッチ
	/// </summary>
	template <class ResultType>
	class StopwatchBase
	{
	private:

		using InternalType = std::conditional_t<std::is_floating_point<ResultType>::value, double, int64>;

		uint64 m_startTimeMicrosec = 0;

		uint64 m_accumulationMicrosec = 0;

		bool m_isActive = false;

		bool m_pausing = true;

	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit StopwatchBase(bool startImmediately = false)
		{
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

			m_isActive = true;

			m_pausing = false;

			m_startTimeMicrosec = Time::GetMicrosec();
		}

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		ResultType h() const { return static_cast<ResultType>(us() / static_cast<InternalType>(1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		ResultType min() const { return static_cast<ResultType>(us() / static_cast<InternalType>(1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		ResultType s() const { return static_cast<ResultType>(us() / static_cast<InternalType>(1000LL * 1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		ResultType ms() const { return static_cast<ResultType>(us() / static_cast<InternalType>(1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
		/// </returns>
		int64 us() const
		{
			const uint64 t = Time::GetMicrosec();

			if (!m_isActive)
			{
				return 0;
			}

			if (m_pausing)
			{
				return m_accumulationMicrosec;
			}

			return m_accumulationMicrosec + (t - m_startTimeMicrosec);
		}

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Milliseconds elapsed() const { return Milliseconds(ms()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isActive() const { return m_isActive; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const { return m_isActive && m_pausing; }

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

			m_isActive = false;

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
			if (time.count() < 0.0)
			{
				return;
			}

			m_isActive |= (time.count() != 0);

			m_accumulationMicrosec = static_cast<uint64>(time.count());

			m_startTimeMicrosec = Time::GetMicrosec();
		}
	};

	using Stopwatch = StopwatchBase<int32>;

	using StopwatchF = StopwatchBase<double>;

	using Stopwatch64 = StopwatchBase<int64>;
}
