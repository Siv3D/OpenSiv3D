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
# include "Optional.hpp"
# include "ACLineStatus.hpp"
# include "BatteryStatus.hpp"

namespace s3d
{
	/// @brief システムの電源の状態
	struct PowerStatus
	{
		/// @brief 電源の接続状態
		ACLineStatus ac = ACLineStatus::Unknown;

		/// @brief バッテリーの残量
		BatteryStatus battery = BatteryStatus::Unknown;

		/// @brief バッテリーの残量 (%)
		Optional<int32> batteryLifePercent;

		/// @brief バッテリーの残り時間（秒）
		Optional<int32> batteryLifeTimeSec;

		/// @brief フル充電までの所要時間（秒）
		Optional<int32> batteryTimeToFullChargeSec;

		/// @brief 充電中であるか
		bool charging = false;

		/// @brief バッテリーセーブモードになっているか
		bool batterySaver = false;
	};

	namespace System
	{
		/// @brief システムの電源の状態を返します。
		/// @remark macOS では結果の取得に時間がかかるため、`AsyncTask` でラップすることを推奨
		/// @return システムの電源の状態
		[[nodiscard]]
		PowerStatus GetPowerStatus();
	}
}
