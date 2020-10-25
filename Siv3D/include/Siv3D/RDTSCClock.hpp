﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Time.hpp"
# include "Duration.hpp"
# include "Logger.hpp"
# include "Console.hpp"
//# include "Print.hpp"
# if SIV3D_PLATFORM(WINDOWS)
#	include <intrin.h>
# endif

namespace s3d
{
	namespace Platform
	{
		inline uint64 Rdtsc() noexcept;
	}

	/// @brief CPU サイクル数カウンター
	/// @remark 経過時間を CPU サイクル数で計測します。
	class RDTSCClock
	{
	private:

		const uint64 m_start = Time::GetMillisec();

	public:

		/// @brief 経過時間（CPU サイクル数）を返します。
		/// @return 経過時間（CPU サイクル数）
		[[nodiscard]]
		uint64 cycles() const noexcept;

		/// @brief ログに経過時間を出力します。
		void log() const;

		/// @brief コンソールに経過時間を出力します。
		void console() const;

		/// @brief 経過時間をデバッグ表示します。
		//void print() const;
	};
}

# include "detail/RDTSCClock.ipp"
