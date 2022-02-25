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

# if SIV3D_PLATFORM(WINDOWS) && __has_include(<LeapC.h>)

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
# include <LeapC.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# pragma comment (lib, "LeapC")

namespace s3d
{
	namespace Leap
	{
		/// @brief トラッキングモード
		enum class TrackingMode
		{
			/// @brief 机に設置するモード
			Desktop,

			/// @brief ヘッドマウントディスプレイモード
			HeadMounted,

			/// @brief 見下ろしモード
			Screentop,
		};

		/// @brief ボーンの情報
		struct Bone
		{
			/// @brief ボーンの開始位置（心臓に近いほう）
			Vec3 from;

			/// @brief ボーンの開始位置（心臓から遠いほう）
			Vec3 to;

			/// @brief 幅（ミリメートル）
			double width;
		};

		/// @brief 手の情報
		class Hand
		{
		public:

			SIV3D_NODISCARD_CXX20
			Hand() = default;

			SIV3D_NODISCARD_CXX20
			explicit Hand(const LEAP_HAND& hand, TrackingMode trackingMode);

			[[nodiscard]]
			uint32 id() const noexcept;

			/// @brief 左手であるかを返します。
			/// @return 左手である場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isLeftHand() const noexcept;

			/// @brief 右手であるかを返します。
			/// @return 右手である場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isRightHand() const noexcept;

			/// @brief トラッキングが継続している時間を返します。
			/// @return トラッキング継続時間
			[[nodiscard]]
			Duration trackedDuration() const noexcept;

			/// @brief 親指と人差し指の間の推定距離 [mm] を返します。
			/// @return 親指と人差し指の間の推定距離 [mm]
			[[nodiscard]]
			double pinchDistance() const noexcept;

			[[nodiscard]]
			/// @brief 指と手のひらのなす角をラジアン角で返します。
			/// @return 指と手のひらのなすラジアン角
			double grabAngle() const noexcept;

			/// @brief つまむジェスチャーの強さを [0.0, 1.0] の範囲で返します。
			/// @return つまむジェスチャーの強さ
			[[nodiscard]]
			double pinchStrength() const noexcept;

			/// @brief 握るジェスチャーの強さを [0.0, 1.0] の範囲で返します。
			/// @return 握るジェスチャーの強さ
			[[nodiscard]]
			double grabStrength() const noexcept;

			/// @brief てのひらの中心位置を返します [mm]
			/// @return てのひらの中心位置
			[[nodiscard]]
			Vec3 palmPosition() const noexcept;

			//[[nodiscard]]
			//Vec3 stabilizedPalmPosition() const noexcept;

			[[nodiscard]]
			Vec3 palmVelocity() const noexcept;

			[[nodiscard]]
			Vec3 palmNormal() const noexcept;

			[[nodiscard]]
			double palmWidth() const noexcept;

			[[nodiscard]]
			Vec3 palmDirection() const noexcept;

			//[[nodiscard]]
			//Quaternion palmQuaternion() const noexcept;

			/// @brief 指のボーン情報を返します。
			/// @param fingerIndex 指のインデックス。親指が 0, 人差し指が 1, ..., 小指が 4
			/// @param boneIndex ボーンのインデックス。手首側から 0, 1, ..., 指の先端が 3
			/// @return 指のボーン情報
			[[nodiscard]]
			Bone fingerBone(size_t fingerIndex, size_t boneIndex) const noexcept;

			/// @brief 指が伸びている状態であるを返します。
			/// @param fingerIndex 指のインデックス。親指が 0, 人差し指が 1, ..., 小指が 4
			/// @return 指が伸びている場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isExtended(size_t fingerIndex) const noexcept;

			[[nodiscard]]
			Vec3 armFrom() const noexcept;

			[[nodiscard]]
			Vec3 armTo() const noexcept;

			[[nodiscard]]
			double armWidth() const noexcept;

			//[[nodiscard]]
			//Quaternion armQuaternion() const noexcept;

		private:

			[[nodiscard]]
			Vec3 toVec3(const LEAP_VECTOR& v) const noexcept;

			[[nodiscard]]
			Quaternion toQuaternion(const LEAP_QUATERNION& q) noexcept;

			LEAP_HAND m_hand;

			TrackingMode m_trackingMode = TrackingMode::HeadMounted;
		};

		/// @brief 接続された Leap デバイスのハンドル
		class Connection
		{
		public:

			SIV3D_NODISCARD_CXX20
			Connection();

			/// @brief 接続の確立を試みます。
			/// @param trackingMode トラッキングモード
			SIV3D_NODISCARD_CXX20
			explicit Connection(TrackingMode trackingMode);

			/// @brief 接続が確立しているかを返します。
			/// @return 接続が確立している場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isOpen() const noexcept;

			/// @brief 接続が確立しているかを返します。
			/// @return 接続が確立している場合 true, それ以外の場合は false
			[[nodiscard]]
			explicit operator bool() const noexcept;

			/// @brief 現在のトラッキングモードを返します。
			/// @return 現在のトラッキングモード
			[[nodiscard]]
			TrackingMode getTrackingMode() const noexcept;

			/// @brief トラッキングモードを変更します。
			/// @param trackingMode 新しいトラッキングモード
			void setTrackingMode(TrackingMode trackingMode);

			/// @brief トラッキング情報を更新します。
			/// @remark 毎フレーム呼びます。
			void update();

			[[nodiscard]]
			/// @brief 最新のトラッキング情報の ID を返します。
			/// @return 最新のトラッキング情報の ID
			int64 trackingID() const noexcept;

			/// @brief トラッキングされた手の一覧を返します。
			/// @return トラッキングされたての一覧
			[[nodiscard]]
			const Array<Hand>& getHands() const noexcept;

		private:

			class ConnectionDetail;

			std::shared_ptr<ConnectionDetail> pImpl;
		};
	}
}

# include "detail/Leap.ipp"

# endif
