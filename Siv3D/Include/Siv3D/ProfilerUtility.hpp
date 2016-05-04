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
# include "Logger.hpp"

namespace s3d
{
# if defined (SIV3D_TARGET_OSX)
	namespace detail
	{
		static __inline__ uint64 rdtsc()
		{
			uint32 hi, lo;
			__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
			return static_cast<uint64>(lo) | (static_cast<uint64>(hi) << 32);
		}
	}
# endif

	/// <summary>
	/// ミリ秒カウンター
	/// </summary>
	/// <remarks>
	/// 経過時間をミリ秒で計測します。
	/// </remarks>
	class MillisecClock
	{
	private:

		const uint64 m_start = Time::GetMillisec();

	public:

		/// <summary>
		/// 経過時間（ミリ秒）
		/// </summary>
		uint64 ms() const { return Time::GetMillisec() - m_start; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Log(ms(), L"ms"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(ms(), L"ms"); }
	};

	/// <summary>
	/// マイクロ秒カウンター
	/// </summary>
	/// <remarks>
	/// 経過時間をマイクロ秒で計測します。
	/// </remarks>
	class MicrosecClock
	{
	private:

		const uint64 m_start = Time::GetMicrosec();

	public:

		/// <summary>
		/// 経過時間（マイクロ秒）
		/// </summary>
		uint64 us() const { return Time::GetMicrosec() - m_start; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Log(us(), L"us"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(us(), L"us"); }
	};

	/// <summary>
	/// ナノ秒カウンター
	/// </summary>
	/// <remarks>
	/// 経過時間をナノ秒で計測します。
	/// </remarks>
	class NanosecClock
	{
	private:

		const uint64 m_start = Time::GetNanosec();

	public:

		/// <summary>
		/// 経過時間（ナノ秒）
		/// </summary>
		uint64 ns() const { return Time::GetNanosec() - m_start; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Log(ns(), L"ns"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(ns(), L"ns"); }
	};

	/// <summary>
	/// CPU サイクルカウンター
	/// </summary>
	/// <remarks>
	/// 経過時間を CPU サイクル数で計測します。
	/// </remarks>
	class RDTSCClock
	{
	private:
	
		# if defined (SIV3D_TARGET_WINDOWS)

			const uint64 m_start = ::__rdtsc();

		# elif defined (SIV3D_TARGET_OSX)

			const uint64 m_start = detail::rdtsc();

		# endif

	public:

		/// <summary>
		/// 経過時間（CPU サイクル数）
		/// </summary>
		uint64 cycles() const
		{
			# if defined (SIV3D_TARGET_WINDOWS)

				return ::__rdtsc() - m_start;

			# elif defined (SIV3D_TARGET_OSX)

				return detail::rdtsc() - m_start;

			# endif
		}

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Log(cycles(), L"cycles"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(cycles(), L"cycles"); }
	};
}
