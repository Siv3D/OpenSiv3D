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

# include <Siv3D/Camera3D.hpp>
# include <Siv3D/Print.hpp>

namespace s3d::experimental
{
	BasicCamera3D::BasicCamera3D(const Size& sceneSize, const double fov, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection) noexcept
		: m_eyePosition(eyePosition)
		, m_focusPosition(focusPosition)
		, m_upDirection(upDirection)
		, m_sceneSize(sceneSize)
		, m_fov(fov)
	{
		updateProj();
		updateView();
		updateViewProj();
	}

	void BasicCamera3D::setProjection(const Size& sceneSize, const double fov, const double nearClip, const double farClip)
	{
		m_sceneSize	= sceneSize;
		m_fov		= fov;
		m_nearClip	= nearClip;
		m_farClip	= farClip;

		updateProj();
		updateViewProj();
	}

	void BasicCamera3D::setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection) noexcept
	{
		m_eyePosition	= eyePosition;
		m_focusPosition	= focusPosition;
		m_upDirection	= upDirection;

		updateView();
		updateViewProj();
	}

	Float3 BasicCamera3D::worldToScreenPoint(const Float3& pos) const noexcept
	{
		Float3 v = SIMD::Vector3TransformCoord(SIMD_Float4(pos, 0.0f), m_viewProj).xyz();
		v.x += 1.0f;
		v.y += 1.0f;
		v.x *= 0.5f * m_sceneSize.x;
		v.y *= 0.5f;
		v.y = 1.0f - v.y;
		v.y *= m_sceneSize.y;
		return v;
	}

	Float3 BasicCamera3D::screenToWorldPoint(const Float2& pos, float depth) const noexcept
	{
		Float3 v(pos, depth);
		v.x /= (m_sceneSize.x * 0.5f);
		v.y /= (m_sceneSize.y * 0.5f);
		v.x -= 1.0f;
		v.y -= 1.0f;
		v.y *= -1.0f;

		const __m128 worldPos = SIMD::Vector3TransformCoord(SIMD_Float4(v, 0.0f), m_invViewProj);

		Float3 result;
		SIMD::StoreFloat3(&result, worldPos);

		return result;
	}

	Ray BasicCamera3D::screenToRay(const Vec2& pos) const noexcept
	{
		const Vec3 rayEnd = screenToWorldPoint(pos, 0.9f);
	
		return Ray(m_eyePosition, (rayEnd - m_eyePosition).normalized());
	}

	void BasicCamera3D::updateProj()
	{
		const float aspectRatio	= static_cast<float>(m_sceneSize.x) / m_sceneSize.y;
		const float fov			= static_cast<float>(m_fov);
		const float nearClip	= static_cast<float>(m_nearClip);
		const float farClip		= static_cast<float>(m_farClip);
		m_proj = Mat4x4::PerspectiveFovLH_ZO(fov, aspectRatio, nearClip, farClip);
	}

	void BasicCamera3D::updateView()
	{
		const SIMD_Float4 eyePosition(m_eyePosition, 0.0f);
		const SIMD_Float4 focusPosition(m_focusPosition, 0.0f);
		const SIMD_Float4 upDirection(m_upDirection, 0.0f);
		m_view = Mat4x4::LookAtLH(eyePosition, focusPosition, upDirection);
	}

	void BasicCamera3D::updateViewProj()
	{
		m_viewProj = m_view * m_proj;
		m_invViewProj = m_viewProj.inverse();
	}
}
