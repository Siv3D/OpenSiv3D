//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "BasicCamera3D.hpp"

namespace s3d
{
	/// @brief 目標に追従するカメラクラス
	/// @note 追従方向、追従距離、追従高さを指定して、目標に追従するカメラを作成します。
	class SimpleFollowCamera3D : public BasicCamera3D
	{
	public:

		SimpleFollowCamera3D() = default;

		/// @brief 3D カメラを作成します。
		/// @param sceneSize シーンのサイズ
		/// @param verticalFOV 縦方向の視野角（ラジアン）
		/// @param focusPosition 注目点
		/// @param followAngle 追従方向（0 が Z 軸正方向、時計まわり）
		/// @param followDistance 追従距離
		/// @param followHeight 追従高さ
		SimpleFollowCamera3D(const Size& sceneSize, double verticalFOV, const Vec3& focusPosition, double followAngle, double followDistance, double followHeight) noexcept;

		virtual ~SimpleFollowCamera3D() = default;

		/// @brief カメラを更新します。
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する。
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		void update(double smoothTime, double deltaTime = Scene::DeltaTime());

		/// @brief 追従する対象の位置を設定します。
		/// @param targetFocus 追従する対象の位置
		/// @param direction 追従する対象を向く方向（0 が Z 軸正方向、時計まわり）
		void setTarget(const Vec3& targetFocus, double followAngle = 0.0) noexcept;

		/// @brief 追従する対象の位置を設定します（即座に移動します）。
		/// @param targetFocus 追従する対象の位置
		/// @param followAngle 追従する対象を向く方向（0 が Z 軸正方向、時計まわり）
		void jumpToTarget(const Vec3& targetFocus, double followAngle = 0.0) noexcept;

		/// @brief 追従距離と追従高さを設定します。
		/// @param distance 追従距離
		/// @param height 追従高さ
		void setFollowOffset(double followDistance, double followHeight) noexcept;

		/// @brief 追従対象に対するオフセットを計算します。
		/// @return 追従対象に対するオフセット
		[[nodiscard]]
		Vec3 getFollowOffset() const noexcept;

	protected:

		Vec3 m_currentFocus = Vec3{ 0, 0, 0 };

		Vec3 m_targetFocus = Vec3{ 0, 0, 0 };

		Vec3 m_focusVelocity = Vec3{ 0, 0, 0 };

		double m_followAngle = 0.0_deg;

		double m_followDistance = 10.0;

		double m_followHeight = 10.0;
	};
}
