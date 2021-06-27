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
# include "PointVector.hpp"
# include "Scene.hpp"
# include "Ray.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	class alignas(16) BasicCamera3D
	{
	public:

		static constexpr double DefaultNearClip = 0.1;

		BasicCamera3D() = default;

		BasicCamera3D(const BasicCamera3D&) = default;

		BasicCamera3D(const Size& sceneSize, double verticalFOV, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }, double nearClip = DefaultNearClip) noexcept
			: m_sceneSize{ sceneSize }
			, m_verticalFOV{ verticalFOV }
			, m_nearClip{ nearClip }
			, m_eyePosition{ eyePosition }
			, m_focusPosition{ focusPosition }
			, m_upDirection{ upDirection }
		{
			updateProj();
			updateView();
			updateViewProj();
		}

		virtual ~BasicCamera3D() = default;

		void setSceneSize(const Size& sceneSize)
		{
			m_sceneSize = sceneSize;

			updateProj();
			updateViewProj();
		}

		void setProjection(const Size& sceneSize, double verticalFOV, double nearClip = DefaultNearClip) noexcept
		{
			m_sceneSize = sceneSize;
			m_verticalFOV = verticalFOV;
			m_nearClip = nearClip;

			updateProj();
			updateViewProj();
		}

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept
		{
			m_eyePosition = eyePosition;
			m_focusPosition = focusPosition;
			m_upDirection = upDirection;

			updateView();
			updateViewProj();
		}

		[[nodiscard]]
		const Size& getSceneSize() const noexcept
		{
			return m_sceneSize;
		}

		[[nodiscard]]
		double getVerticlaFOV() const noexcept
		{
			return m_verticalFOV;
		}

		[[nodiscard]]
		double getNearClip() const noexcept
		{
			return m_nearClip;
		}

		[[nodiscard]]
		const Vec3& getEyePosition() const noexcept
		{
			return m_eyePosition;
		}

		[[nodiscard]]
		const Vec3& getFocusPosition() const noexcept
		{
			return m_focusPosition;
		}

		[[nodiscard]]
		const Vec3& getUpDirection() const noexcept
		{
			return m_upDirection;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getProj() const noexcept
		{
			return m_proj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getView() const noexcept
		{
			return m_view;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getViewProj() const noexcept
		{
			return m_viewProj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getMat4x4() const noexcept
		{
			return m_viewProj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getInvViewProj() const noexcept
		{
			return m_invViewProj;
		}

		[[nodiscard]]
		Float3 worldToScreenPoint(const Float3& pos) const noexcept
		{
			Float3 v = SIMD_Float4{ DirectX::XMVector3TransformCoord(SIMD_Float4{ pos, 0.0f }, m_viewProj) }.xyz();
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * m_sceneSize.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= m_sceneSize.y;
			return v;
		}

		[[nodiscard]]
		Float3 screenToWorldPoint(const Float2& pos, float depth) const noexcept;

		[[nodiscard]]
		Ray screenToRay(const Vec2& pos) const noexcept;

	protected:

		Mat4x4 m_proj = Mat4x4::Identity();

		Mat4x4 m_view = Mat4x4::Identity();

		Mat4x4 m_viewProj = Mat4x4::Identity();

		Mat4x4 m_invViewProj = Mat4x4::Identity();

		//
		// Proj
		//
		Size m_sceneSize = Scene::Size();

		double m_verticalFOV = 30_deg;

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
