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
# include "Mat4x4.hpp"
# include "Scene.hpp"

namespace s3d::experimental
{
	class alignas(16) BasicCamera3D
	{
	protected:

		Mat4x4 m_proj = Mat4x4::Identity();

		Mat4x4 m_view = Mat4x4::Identity();

		Mat4x4 m_viewProj = Mat4x4::Identity();

		Mat4x4 m_invViewProj = Mat4x4::Identity();

		//
		// Proj
		//
		Size m_sceneSize = Scene::Size();

		double m_fov = 45_deg;

		double m_nearClip = DefaultNearClip;

		double m_farClip = DefaultFarClip;

		//
		// View
		//
		Vec3 m_eyePosition = Vec3(0, 4, -4);

		Vec3 m_focusPosition = Vec3(0, 0, 0);

		Vec3 m_upDirection = Vec3(0, 1, 0);

		void updateProj();

		void updateView();

		void updateViewProj();

	public:

		static constexpr double DefaultNearClip = 0.1;

		static constexpr double DefaultFarClip = 1000000.0;

		BasicCamera3D() = default;

		BasicCamera3D(const BasicCamera3D&) = default;

		BasicCamera3D& operator=(const BasicCamera3D&) = default;

		BasicCamera3D(BasicCamera3D&&) = default;

		BasicCamera3D& operator=(BasicCamera3D&&) = default;

		BasicCamera3D(const Size & sceneSize, double fov, const Vec3 & eyePosition, const Vec3 & focusPosition, const Vec3 & upDirection = Vec3(0, 1, 0)) noexcept;

		virtual ~BasicCamera3D() = default;

		void setProjection(const Size & sceneSize, double fov, double nearClip = DefaultNearClip, double farClip = DefaultFarClip);

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3(0, 1, 0)) noexcept;

		[[nodiscard]] const Size& getSceneSize() const noexcept
		{
			return m_sceneSize;
		}

		[[nodiscard]] double getFov() const noexcept
		{
			return m_fov;
		}

		[[nodiscard]] double getNearClip() const noexcept
		{
			return m_nearClip;
		}

		[[nodiscard]] double getFarClip() const noexcept
		{
			return m_farClip;
		}

		[[nodiscard]] const Vec3& getEyePosition() const noexcept
		{
			return m_eyePosition;
		}

		[[nodiscard]] const Vec3& getFocusPosition() const noexcept
		{
			return m_focusPosition;
		}

		[[nodiscard]] const Vec3& getUpDirection() const noexcept
		{
			return m_upDirection;
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL getMat4x4() const noexcept
		{
			return m_viewProj;
		}

		[[nodiscard]] Float3 worldToScreenPoint(const Float3& pos) const noexcept;

		[[nodiscard]] Float3 screenToWorldPoint(const Float2& pos, float depth) const noexcept;
	};
}
