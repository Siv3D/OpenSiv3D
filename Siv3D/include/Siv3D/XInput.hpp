//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "DeadZone.hpp"
# include "Input.hpp"

namespace s3d
{
	namespace detail
	{
		struct XInput_impl
		{
			SIV3D_NODISCARD_CXX20
			explicit XInput_impl(size_t userIndex);

			[[nodiscard]]
			bool isConnected() const;

			[[nodiscard]]
			explicit operator bool() const;

			/// @brief 左トリガーにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setLeftTriggerDeadZone(const DeadZone& deadZone = { .size = 0.12, .maxValue = 1.0, .type = DeadZoneType::Independent });

			/// @brief 右トリガーにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setRightTriggerDeadZone(const DeadZone& deadZone = { .size = 0.12, .maxValue = 1.0, .type = DeadZoneType::Independent });

			void setLeftThumbDeadZone(const DeadZone& deadZone = { .size = 0.24, .maxValue = 1.0, .type = DeadZoneType::Circular });

			void setRightThumbDeadZone(const DeadZone& deadZone = { .size = 0.26, .maxValue = 1.0, .type = DeadZoneType::Circular });

			/// @brief ユーザインデックス
			uint32 userIndex;

			/// @brief 十字ボタンの上ボタン
			Input buttonUp;

			/// @brief 十字ボタンの下ボタン
			Input buttonDown;

			/// @brief 十字ボタンの左ボタン
			Input buttonLeft;

			/// @brief 十字ボタンの右ボタン
			Input buttonRight;

			/// @brief START ボタン
			Input buttonStart;

			/// @brief BACK ボタン
			Input buttonBack;

			/// @brief 左スティックの押し込み
			Input buttonLThumb;

			/// @brief 右スティックの押し込み
			Input buttonRThumb;

			/// @brief LB ボタン
			Input buttonLB;

			/// @brief RB ボタン
			Input buttonRB;

			/// @brief A ボタン
			Input buttonA;

			/// @brief B ボタン
			Input buttonB;

			/// @brief X ボタン
			Input buttonX;

			/// @brief Y ボタン
			Input buttonY;

			/// @brief 左トリガーの値 [0.0, 1.0]
			double leftTrigger;

			/// @brief 右トリガーの値 [0.0, 1.0]
			double rightTrigger;

			/// @brief 左スティックの X 軸の値 [-1.0, 1.0]
			double leftThumbX;

			/// @brief 左スティックの Y 軸の値 [-1.0, 1.0]
			double leftThumbY;

			/// @brief 右スティックの X 軸の値 [-1.0, 1.0]
			double rightThumbX;

			/// @brief 右スティックの Y 軸の値 [-1.0, 1.0]
			double rightThumbY;

			[[nodiscard]]
			Optional<int32> leftThumbD4(double threshold = 0.2) const;

			[[nodiscard]]
			Optional<int32> leftThumbD8(double threshold = 0.2) const;

			[[nodiscard]]
			Optional<int32> rightThumbD4(double threshold = 0.2) const;

			[[nodiscard]]
			Optional<int32> rightThumbD8(double threshold = 0.2) const;

			/// @brief バイブレーションを設定します。
			/// @param leftMotorSpeed 低周波の左モータのスピード、0 は停止、1.0 は最大の振動
			/// @param rightMotorSpeed 高周波の右モータのスピード、0 は停止、1.0 は最大の振動
			void setVibration(double leftMotorSpeed, double rightMotorSpeed) const;

			/// @brief バイブレーションの現在の設定を返します。
			/// @return バイブレーションの現在の設定（左モータ、右モータ）
			[[nodiscard]]
			std::pair<double, double> getVibration() const;

			/// @brief バイブレーションを停止します。
			void stopVibration() const;

			/// @brief バイブレーションを一時停止します。
			void pauseVibration() const;

			/// @brief 一時停止したバイブレーションを再開します。
			void resumeVibration() const;
		};

		struct XInput_helper
		{
			[[nodiscard]]
			const XInput_impl& operator()(size_t userIndex) const;

			static constexpr size_t MaxUserCount = 4;
		};
	}

	inline constexpr auto XInput = detail::XInput_helper();
}
