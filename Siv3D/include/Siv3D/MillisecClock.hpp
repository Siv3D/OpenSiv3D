//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Time.hpp"
# include "Logger.hpp"
# include "Print.hpp"

namespace s3d
{
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
		[[nodiscard]] uint64 ms() const
		{
			return Time::GetMillisec() - m_start;
		}

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Logger(ms(), U"ms"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const { Print(ms(), U"ms"); }
	};
}
