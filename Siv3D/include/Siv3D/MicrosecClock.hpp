//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Time.hpp"
# include "Duration.hpp"

namespace s3d
{
	/// @brief マイクロ秒カウンター
	/// @remark 経過時間をマイクロ秒で計測します。
	class MicrosecClock
	{
	public:

		/// @brief 経過時間（マイクロ秒）を返します。
		/// @return 経過時間（マイクロ秒）
		[[nodiscard]]
		uint64 us() const noexcept;

		/// @brief ログに経過時間を出力します。
		void log() const;

		/// @brief コンソールに経過時間を出力します。
		void console() const;

		/// @brief 経過時間をデバッグ表示します。
		void print() const;

	private:

		const uint64 m_start = Time::GetMicrosec();
	};
}

# include "detail/MicrosecClock.ipp"
