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
# include "Key.hpp"
# include "Optional.hpp"
# include "DeadZone.hpp"

namespace s3d
{
	namespace detail
	{
		struct XInput_impl
		{
			XInput_impl(size_t _userIndex);

			bool isConnected() const;

			explicit operator bool() const;

			/// <summary>
			/// 左トリガーにデッドゾーンを設定します。
			/// </summary>
			/// <param name="deadZone">
			/// 設定するデッドゾーン
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void setLeftTriggerDeadZone(const DeadZone& deadZone = { 0.12, 1.0, DeadZoneType::Independent });

			/// <summary>
			/// 右トリガーにデッドゾーンを設定します。
			/// </summary>
			/// <param name="deadZone">
			/// 設定するデッドゾーン
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void setRightTriggerDeadZone(const DeadZone& deadZone = { 0.12, 1.0, DeadZoneType::Independent });

			/// <summary>
			/// 左スティックにデッドゾーンを設定します。
			/// </summary>
			/// <param name="deadZone">
			/// 設定するデッドゾーン
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void setLeftThumbDeadZone(const DeadZone& deadZone = { 0.24, 1.0, DeadZoneType::Circular });

			/// <summary>
			/// 右スティックにデッドゾーンを設定します。
			/// </summary>
			/// <param name="deadZone">
			/// 設定するデッドゾーン
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void setRightThumbDeadZone(const DeadZone& deadZone = { 0.26, 1.0, DeadZoneType::Circular });

			/// <summary>
			/// ユーザインデックス
			/// </summary>
			uint32 userIndex;

			/// <summary>
			/// 十字ボタンの上ボタン
			/// </summary>
			Key buttonUp;

			/// <summary>
			/// 十字ボタンの下ボタン
			/// </summary>
			Key buttonDown;

			/// <summary>
			/// 十字ボタンの左ボタン
			/// </summary>
			Key buttonLeft;

			/// <summary>
			/// 十字ボタンの右ボタン
			/// </summary>
			Key buttonRight;

			/// <summary>
			/// START ボタン
			/// </summary>
			Key buttonStart;

			/// <summary>
			/// BACK ボタン
			/// </summary>
			Key buttonBack;

			/// <summary>
			/// 左スティックの押し込み
			/// </summary>
			Key buttonLThumb;

			/// <summary>
			/// 右スティックの押し込み
			/// </summary>
			Key buttonRThumb;

			/// <summary>
			/// LB ボタン
			/// </summary>
			Key buttonLB;

			/// <summary>
			/// RB ボタン
			/// </summary>
			Key buttonRB;

			/// <summary>
			/// A ボタン
			/// </summary>
			Key buttonA;

			/// <summary>
			/// B ボタン
			/// </summary>
			Key buttonB;

			/// <summary>
			/// X ボタン
			/// </summary>
			Key buttonX;

			/// <summary>
			/// Y ボタン
			/// </summary>
			Key buttonY;

			/// <summary>
			/// 左トリガーの値 [0.0, 1.0]
			/// </summary>
			double leftTrigger;

			/// <summary>
			/// 右トリガーの値 [0.0, 1.0]
			/// </summary>
			double rightTrigger;

			/// <summary>
			/// 左スティックの X 軸の値 [-1.0, 1.0]
			/// </summary>
			double leftThumbX;

			/// <summary>
			/// 左スティックの Y 軸の値 [-1.0, 1.0]
			/// </summary>
			double leftThumbY;

			/// <summary>
			/// 右スティックの X 軸の値 [-1.0, 1.0]
			/// </summary>
			double rightThumbX ;

			/// <summary>
			/// 右スティックの Y 軸の値 [-1.0, 1.0]
			/// </summary>
			double rightThumbY;
	
			[[nodiscard]] Optional<int32> leftThumbD4(double threshold = 0.2) const;

			[[nodiscard]] Optional<int32> leftThumbD8(double threshold = 0.2) const;

			[[nodiscard]] Optional<int32> rightThumbD4(double threshold = 0.2) const;

			[[nodiscard]] Optional<int32> rightThumbD8(double threshold = 0.2) const;
			
			/// <summary>
			/// バイブレーションを設定します。
			/// </summary>
			/// <param name="leftMotorSpeed">
			/// 低周波の左モータのスピード、0 は停止、1.0 は最大速度
			/// </param>
			/// <param name="rightMotorSpeed">
			/// 高周波の右モータのスピード、0 は停止、1.0 は最大速度
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void setVibration(double leftMotorSpeed, double rightMotorSpeed) const;

			[[nodiscard]] std::pair<double, double> getVibration() const;

			/// <summary>
			/// バイブレーションを停止します。
			/// </summary>
			/// <returns>
			/// なし
			/// </returns>
			void stopVibration() const;

			void pauseVibration() const;

			void resumeVibration() const;
		};

		struct XInput_helper
		{
			const XInput_impl& operator()(size_t userIndex) const;

			static constexpr size_t MaxUserCount = 4;
		};
	}

	constexpr auto XInput = detail::XInput_helper();
}
