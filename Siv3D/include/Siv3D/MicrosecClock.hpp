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

namespace s3d
{
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
		[[nodiscard]] uint64 cycles() const
		{
			return Time::GetMicrosec() - m_start;
		}

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { Logger(cycles(), U"us"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		//void print() const { Println(cycles(), U"us"); }
	};
}
