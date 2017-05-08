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
# include "Logger.hpp"

namespace s3d
{
	namespace detail
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		__forceinline uint64 rdtsc()
		{
			return ::__rdtsc();
		}

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		static __inline__ uint64 rdtsc()
		{
			uint32 hi, lo;
			__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
			return static_cast<uint64>(lo) | (static_cast<uint64>(hi) << 32);
		}

	# endif
	}

	/// <summary>
	/// CPU サイクルカウンター
	/// </summary>
	/// <remarks>
	/// 経過時間を CPU サイクル数で計測します。
	/// </remarks>
	class RDTSCClock
	{
	private:

		const uint64 m_start = detail::rdtsc();

	public:

		/// <summary>
		/// 経過時間（CPU サイクル数）
		/// </summary>
		uint64 cycles() const
		{
			return detail::rdtsc() - m_start;
		}

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Log(cycles(), S3DSTR("cycles")); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(cycles(), S3DSTR("cycles")); }
	};
}
