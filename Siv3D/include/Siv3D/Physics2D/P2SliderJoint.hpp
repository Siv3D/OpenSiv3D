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
# include "../Common.hpp"
# include "../2DShapesFwd.hpp"
# include "../ColorHSV.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	class P2SliderJoint
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		P2SliderJoint() = default;

		/// @brief ジョイントを破棄します。
		void release();

		/// @brief BodyA のアンカーポイントをワールド座標で返します。
		/// @return BodyA のアンカーポイントのワールド座標
		[[nodiscard]]
		Vec2 getAnchorPosA() const;

		/// @brief BodyB のアンカーポイントをワールド座標で返します。
		/// @return BodyB のアンカーポイントのワールド座標
		[[nodiscard]]
		Vec2 getAnchorPosB() const;

		/// @brief ジョイントの反力 (N) を返します。
		/// @param timeStep タイムステップ（秒）
		/// @return ジョイントの反力 (N)
		[[nodiscard]]
		Vec2 getReactionForce(double timeStep) const;

		/// @brief ジョイントの反力トルク (N・m) を返します。
		/// @param timeStep タイムステップ（秒）
		/// @return ジョイントの反力トルク (N・m) 
		[[nodiscard]]
		double getReactionTorque(double timeStep) const;

		/// @brief ジョイントの移動量を返します。
		/// @return ジョイントの移動量
		[[nodiscard]]
		double getJointTranslation() const;

		/// @brief ジョイントの移動の速さを返します。
		/// @return ジョイントの移動の速さ
		[[nodiscard]]
		double getJointSpeed() const;

		/// @brief ジョイントの長さ制限の有効無効を設定します。
		/// @param enabled 有効にする場合 true, それ以外の場合は false
		/// @return *this
		P2SliderJoint& setLimitEnabled(bool enabled);

		/// @brief ジョイントの長さ制限が有効かを返します。
		/// @return ジョイントの長さ制限が有効な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool getLimitEnabled() const;

		/// @brief ジョイントの長さの下限と上限を設定します。
		/// @param lower 長さの下限
		/// @param upper 長さの上限
		/// @return *this
		P2SliderJoint& setLimits(double lower, double upper);

		/// @brief 現在設定されているジョイントの長さの下限と上限を返します。
		/// @return 現在設定されているジョイントの長さの下限と上限
		[[nodiscard]]
		std::pair<double, double> getLimits() const;

		/// @brief モーターの ON / OFF を設定します。
		/// @param enabled モーターを ON にする場合 true, OFF にする場合は false
		/// @return *this
		P2SliderJoint& setMotorEnabled(bool enabled);

		/// @brief モーターが ON であるかを返します。
		/// @return モーターが ON である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool getMotorEnabled() const;

		/// @brief モーターの速さを設定します。
		/// @param speed モーターの速さ
		/// @return *this
		P2SliderJoint& setMotorSpeed(double speed);

		/// @brief 現在設定されているモーターの速さを返します。
		/// @return 現在設定されているモーターの速さ
		[[nodiscard]]
		double getMotorSpeed() const;

		/// @brief モーターが発揮できる最大の力の強さを設定します。
		/// @param force 力の強さ (N)
		/// @return *this
		P2SliderJoint& setMaxMotorForce(double force);

		/// @brief モーターが発揮できる最大の力の強さを返します。
		/// @return モーターが発揮できる最大の力の強さ (N)
		[[nodiscard]]
		double getMaxMotorForce() const;

		/// @brief 現在モーターが発揮している力の強さを返します。
		/// @param timeStep タイムステップ（秒）
		/// @return 現在モーターが発揮している力の強さ (N)
		[[nodiscard]]
		double getCurrentMotorForce(double timeStep) const;

		/// @brief ジョイントをデバッグ表示します。
		/// @param color 色
		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2SliderJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2SliderJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, EnableCollision enableCollision);
	};
}
