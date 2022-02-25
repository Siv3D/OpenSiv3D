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
# include "MonitorInfo.hpp"

namespace s3d
{
	namespace System
	{
		/// @brief ウィンドウが配置されているモニターのインデックスを取得します。
		/// @return ウィンドウが配置されているモニターのインデックス
		[[nodiscard]]
		size_t GetCurrentMonitorIndex();

		/// @brief ウィンドウが配置されているモニターの情報を取得します。
		/// @return ウィンドウが配置されているモニターの情報
		[[nodiscard]]
		MonitorInfo GetCurrentMonitor();
	}
}
