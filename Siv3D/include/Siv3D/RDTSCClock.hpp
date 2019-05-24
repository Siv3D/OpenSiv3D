//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PlatformDetail.hpp"
# include "Logger.hpp"
# include "Print.hpp"

namespace s3d
{
	/// <summary>
	/// CPU サイクルカウンター
	/// </summary>
	/// <remarks>
	/// 経過時間を CPU サイクル数で計測します。
	/// </remarks>
	class RDTSCClock
	{
	private:

		const uint64 m_start = Platform::Rdtsc();

	public:

		/// <summary>
		/// 経過時間（CPU サイクル数）
		/// </summary>
		[[nodiscard]] uint64 cycles() const
		{
			return Platform::Rdtsc() - m_start;
		}

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Logger(cycles(), U"cycles"_sv); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const { Print(cycles(), U"cycles"_sv); }
	};
}
