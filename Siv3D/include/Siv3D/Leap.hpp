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

			/// @brief スクリーンに設置するモード
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

			/// @brief 回転
			Quaternion rotation;
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

			[[nodiscard]]
			bool isLeftHand() const noexcept;

			[[nodiscard]]
			bool isRightHand() const noexcept;

			[[nodiscard]]
			Duration trackedDuration() const noexcept;

			[[nodiscard]]
			Vec3 palmPosition() const noexcept;

			[[nodiscard]]
			Vec3 stabilizedPalmPosition() const noexcept;

			[[nodiscard]]
			Vec3 palmVelocity() const noexcept;

			[[nodiscard]]
			Vec3 palmNormal() const noexcept;

			[[nodiscard]]
			double palmWidth() const noexcept;

			[[nodiscard]]
			Vec3 palmDirection() const noexcept;

			[[nodiscard]]
			Quaternion palmQuaternion() const noexcept;

			[[nodiscard]]
			Bone fingerBone(size_t fingerIndex, size_t boneIndex) const noexcept;

			[[nodiscard]]
			bool isExtended(size_t fingerIndex) const noexcept;

			[[nodiscard]]
			Vec3 armFrom() const noexcept;

			[[nodiscard]]
			Vec3 armTo() const noexcept;

			[[nodiscard]]
			double armWidth() const noexcept;

			[[nodiscard]]
			Quaternion armQuaternion() const noexcept;

		private:

			[[nodiscard]]
			Vec3 toVec3(const LEAP_VECTOR& v) const noexcept;

			[[nodiscard]]
			static Quaternion ToQuaternion(const LEAP_QUATERNION& q) noexcept
			{
				return{ q.x, q.y, q.z, q.w };
			}

			LEAP_HAND m_hand;

			TrackingMode m_trackingMode = TrackingMode::HeadMounted;
		};

		/// @brief 接続された Leap デバイスのハンドル
		class Connection
		{
		public:

			SIV3D_NODISCARD_CXX20
			Connection();

			SIV3D_NODISCARD_CXX20
			explicit Connection(TrackingMode trackingMode);

			[[nodiscard]]
			bool isOpen() const noexcept;

			[[nodiscard]]
			explicit operator bool() const noexcept;

			[[nodiscard]]
			TrackingMode getTrackingMode() const noexcept;

			void setTrackingMode(TrackingMode trackingMode);

			void update();

			[[nodiscard]]
			int64 trackingID() const noexcept;

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
