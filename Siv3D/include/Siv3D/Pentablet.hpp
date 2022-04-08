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

namespace s3d
{
	namespace Pentablet
	{
		/// @brief ペンタブレットが使用可能かを調べます。
		/// @return ペンタブレットが使用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsAvailable();

		/// @brief 接続されているペンタブレットが筆圧取得に対応しているかを調べます。
		/// @return 筆圧取得に対応している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool SupportsPressure();

		[[nodiscard]]
		bool SupportsTangentPressure();

		/// @brief 接続されているペンタブレットが角度情報の取得に対応しているかを調べます。
		/// @return 角度情報の取得に対応している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool SupportsOrientation();

		/// @brief 筆圧を [0.0, 1.0] の範囲で返します。
		/// @return 筆圧 [0.0, 1.0]
		[[nodiscard]]
		double Pressure();
	
		[[nodiscard]]
		double TangentPressure();

		/// @brief 垂直な軸に対するペンの回転角度を取得します。
		/// @return 垂直な軸に対するペンの回転角度（°）。時計回りで [0.0, 360.0)
		[[nodiscard]]
		double Azimuth();

		/// @brief 地面に対するペンの傾きを取得します。
		/// @remark ペンが直立しているとき 90.0 を返します。
		/// @return 地面に対するペンの傾き（°）
		[[nodiscard]]
		double Altitude();

		[[nodiscard]]
		double Twist();
	}
}
