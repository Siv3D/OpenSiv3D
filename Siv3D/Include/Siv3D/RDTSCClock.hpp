//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Logger.hpp"

namespace s3d
{
# if defined(SIV3D_TARGET_MACOS)

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
	/// CPU サイクルカウンター
	/// </summary>
	/// <remarks>
	/// 経過時間を CPU サイクル数で計測します。
	/// </remarks>
	class RDTSCClock
	{
	private:
	
	# if defined(SIV3D_TARGET_WINDOWS)

		const uint64 m_start = ::__rdtsc();

	# elif defined(SIV3D_TARGET_MACOS)

		const uint64 m_start = detail::rdtsc();

	# endif

	public:

		/// <summary>
		/// 経過時間（CPU サイクル数）
		/// </summary>
		uint64 cycles() const
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return ::__rdtsc() - m_start;

		# elif defined(SIV3D_TARGET_MACOS)

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
