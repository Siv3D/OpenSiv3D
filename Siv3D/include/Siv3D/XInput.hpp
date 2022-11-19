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
# include "DeadZone.hpp"
# include "InputGroups.hpp"
# include "XInputVibration.hpp"

namespace s3d
{
	namespace detail
	{
		struct XInput_impl
		{
			SIV3D_NODISCARD_CXX20
			explicit XInput_impl(size_t playerIndex) noexcept;

			/// @brief コントローラが接続されているかを返します。
			/// @return コントローラが接続されている場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isConnected() const;

			/// @brief コントローラが接続されているかを返します。
			/// @remark `isConnected()` と同じです。
			/// @return コントローラが接続されている場合 true, それ以外の場合は false
			[[nodiscard]]
			explicit operator bool() const;

			/// @brief 左トリガーにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setLeftTriggerDeadZone(const DeadZone& deadZone = { .size = 0.12, .maxValue = 1.0, .type = DeadZoneType::Independent });

			/// @brief 右トリガーにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setRightTriggerDeadZone(const DeadZone& deadZone = { .size = 0.12, .maxValue = 1.0, .type = DeadZoneType::Independent });

			/// @brief 左スティックにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setLeftThumbDeadZone(const DeadZone& deadZone = { .size = 0.24, .maxValue = 1.0, .type = DeadZoneType::Circular });

			/// @brief 右スティックにデッドゾーンを設定します。
			/// @param deadZone 設定するデッドゾーン
			void setRightThumbDeadZone(const DeadZone& deadZone = { .size = 0.24, .maxValue = 1.0, .type = DeadZoneType::Circular });

			/// @brief プレイヤーインデックス
			uint32 playerIndex;

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

			/// @brief Menu ボタン
			/// @remark START ボタンと同じです。
			Input buttonMenu;

			/// @brief BACK ボタン
			Input buttonBack;

			/// @brief View ボタン
			/// @remark BACK ボタンと同じです。
			Input buttonView;

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

			/// @brief 左スティックが押されている方向を 0～3 で返します。
			/// @param threshold 押されていると判定する閾値
			/// @return 左スティックが押されている方向。押されていない場合は none
			[[nodiscard]]
			Optional<int32> leftThumbD4(double threshold = 0.2) const;

			/// @brief 左スティックが押されている方向を 0～7 で返します。
			/// @param threshold 押されていると判定する閾値
			/// @return 左スティックが押されている方向。押されていない場合は none
			[[nodiscard]]
			Optional<int32> leftThumbD8(double threshold = 0.2) const;

			/// @brief 右スティックが押されている方向を 0～3 で返します。
			/// @param threshold 押されていると判定する閾値
			/// @return 右スティックが押されている方向。押されていない場合は none
			[[nodiscard]]
			Optional<int32> rightThumbD4(double threshold = 0.2) const;

			/// @brief 右スティックが押されている方向を 0～7 で返します。
			/// @param threshold 押されていると判定する閾値
			/// @return 右スティックが押されている方向。押されていない場合は none
			[[nodiscard]]
			Optional<int32> rightThumbD8(double threshold = 0.2) const;

			/// @brief バイブレーションを設定します。
			/// @param vibration バイブレーション強度
			void setVibration(const XInputVibration& vibration) const;

			/// @brief 現在のバイブレーション設定を返します。
			/// @return 現在のバイブレーション設定
			[[nodiscard]]
			const XInputVibration& getVibration() const;

			/// @brief バイブレーションを停止します。
			void stopVibration() const;

			/// @brief バイブレーションを一時停止します。
			void pauseVibration() const;

			/// @brief 一時停止したバイブレーションを再開します。
			void resumeVibration() const;
		};

		struct XInput_helper
		{
			static constexpr size_t MaxPlayerCount = 4;

			[[nodiscard]]
			const XInput_impl& operator ()(size_t playerIndex) const;
		};
	}

	inline constexpr auto XInput = detail::XInput_helper{};
}
