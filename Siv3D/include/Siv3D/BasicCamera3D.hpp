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
# include "PointVector.hpp"
# include "Scene.hpp"
# include "Ray.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	/// @brief 3D カメラの基本クラス
	class alignas(16) BasicCamera3D
	{
	public:

		static constexpr double DefaultVerticalFOV = 30_deg;

		static constexpr double DefaultNearClip = 0.2;

		BasicCamera3D() = default;

		BasicCamera3D(const BasicCamera3D&) = default;

		/// @brief 3D カメラを作成します。
		/// @param sceneSize シーンのサイズ
		/// @param verticalFOV 縦方向の視野角（ラジアン）
		/// @param eyePosition 目（カメラ）の位置
		/// @param focusPosition 注目点
		/// @param upDirection 上方向ベクトル
		/// @param nearClip ニア・クリップ（これより近いとカメラに写らない）
		explicit BasicCamera3D(const Size& sceneSize, double verticalFOV = DefaultVerticalFOV, const Vec3& eyePosition = Vec3{ 0, 4, -4 }, const Vec3& focusPosition = Vec3{ 0, 0, 0 }, const Vec3& upDirection = Vec3{ 0, 1, 0 }, double nearClip = DefaultNearClip) noexcept;

		virtual ~BasicCamera3D() = default;

		[[nodiscard]]
		virtual Mat4x4 getMat4x4() const;

		void setSceneSize(const Size& sceneSize) noexcept;

		void setProjection(const Size& sceneSize, double verticalFOV, double nearClip = DefaultNearClip) noexcept;

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept;

		void setUpDirection(const Vec3& upDirection) noexcept;

		[[nodiscard]]
		const Size& getSceneSize() const noexcept;

		[[nodiscard]]
		double getVerticalFOV() const noexcept;

		[[nodiscard]]
		double getNearClip() const noexcept;

		[[nodiscard]]
		const Vec3& getEyePosition() const noexcept;

		[[nodiscard]]
		const Vec3& getFocusPosition() const noexcept;

		[[nodiscard]]
		const Vec3& getUpDirection() const noexcept;

		[[nodiscard]]
		Vec3 getLookAtVector() const noexcept;

		[[nodiscard]]
		Quaternion getLookAtOrientation() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getProj() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getView() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getInvView() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getViewProj() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getInvViewProj() const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL billboard(Float3 pos) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL billboard(Float3 pos, Arithmetic scale) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL billboard(Float3 pos, Float2 scale) const noexcept;

		[[nodiscard]]
		Float3 worldToScreenPoint(const Float3& pos) const noexcept;

		[[nodiscard]]
		Float3 screenToWorldPoint(const Float2& pos, float depth) const noexcept;

		[[nodiscard]]
		Ray screenToRay(const Vec2& pos) const noexcept;

	protected:

		Mat4x4 m_proj = Mat4x4::Identity();

		Mat4x4 m_view = Mat4x4::Identity();

		Mat4x4 m_invView = Mat4x4::Identity();

		Mat4x4 m_viewProj = Mat4x4::Identity();

		Mat4x4 m_invViewProj = Mat4x4::Identity();

		//
		// Proj
		//
		Size m_sceneSize = Scene::Size();

		double m_verticalFOV = DefaultVerticalFOV;

		double m_nearClip = DefaultNearClip;

		//
		// View
		//
		Vec3 m_eyePosition = Vec3{ 0, 4, -4 };

		Vec3 m_focusPosition = Vec3{ 0, 0, 0 };

		Vec3 m_upDirection = Vec3{ 0, 1, 0 };

		void updateProj() noexcept;

		void updateView() noexcept;

		void updateViewProj() noexcept;
	};
}

# include "detail/BasicCamera3D.ipp"
