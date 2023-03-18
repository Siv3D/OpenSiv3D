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

# include <Siv3D/BasicCamera3D.hpp>

namespace s3d
{
	BasicCamera3D::BasicCamera3D(const Size& sceneSize, const double verticalFOV, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection, const double nearClip) noexcept
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

	Mat4x4 BasicCamera3D::getMat4x4() const
	{
		return m_viewProj;
	}

	void BasicCamera3D::setSceneSize(const Size& sceneSize) noexcept
	{
		m_sceneSize = sceneSize;

		updateProj();
		updateViewProj();
	}

	void BasicCamera3D::setProjection(const Size& sceneSize, const double verticalFOV, const double nearClip) noexcept
	{
		m_sceneSize = sceneSize;
		m_verticalFOV = verticalFOV;
		m_nearClip = nearClip;

		updateProj();
		updateViewProj();
	}

	void BasicCamera3D::setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection) noexcept
	{
		m_eyePosition = eyePosition;
		m_focusPosition = focusPosition;
		m_upDirection = upDirection;

		updateView();
		updateViewProj();
	}

	void BasicCamera3D::setUpDirection(const Vec3& upDirection) noexcept
	{
		m_upDirection = upDirection;

		updateView();
		updateViewProj();
	}

	Quaternion BasicCamera3D::getLookAtOrientation() const noexcept
	{
		return Quaternion::FromUnitVectorPairs({ Vec3::Forward(), Vec3::Up() },
			{ getLookAtVector(), Vec3::Up() });
	}

	Float3 BasicCamera3D::worldToScreenPoint(const Float3& pos) const noexcept
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

	Float3 BasicCamera3D::screenToWorldPoint(const Float2& pos, const float depth) const noexcept
	{
		Float3 v{ pos, depth };
		v.x /= (m_sceneSize.x * 0.5f);
		v.y /= (m_sceneSize.y * 0.5f);
		v.x -= 1.0f;
		v.y -= 1.0f;
		v.y *= -1.0f;

		const SIMD_Float4 worldPos = DirectX::XMVector3TransformCoord(SIMD_Float4{ v, 0.0f }, m_invViewProj);

		return worldPos.xyz();
	}

	Ray BasicCamera3D::screenToRay(const Vec2& pos) const noexcept
	{
		const Vec3 rayEnd = screenToWorldPoint(pos, 0.1f);

		return Ray{ m_eyePosition, (rayEnd - m_eyePosition).normalized() };
	}

	void BasicCamera3D::updateProj() noexcept
	{
		const double g = (1.0 / std::tan(m_verticalFOV * 0.5));
		const double s = (static_cast<double>(m_sceneSize.x) / m_sceneSize.y);
		constexpr float e = 0.000001f;

		m_proj = Mat4x4{
			static_cast<float>(g / s), 0.0f, 0.0f, 0.0f,
			0.0f, static_cast<float>(g), 0.0f, 0.0f,
			0.0f, 0.0f, e, 1.0f,
			0.0f, 0.0f, static_cast<float>(m_nearClip * (1.0 - e)), 0.0f
		};
	}

	void BasicCamera3D::updateView() noexcept
	{
		const SIMD_Float4 eyePosition{ m_eyePosition, 0.0f };
		const SIMD_Float4 focusPosition{ m_focusPosition, 0.0f };
		const SIMD_Float4 upDirection{ m_upDirection, 0.0f };
		m_view = DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
		m_invView = m_view.inverse();
	}

	void BasicCamera3D::updateViewProj() noexcept
	{
		m_viewProj = (m_view * m_proj);
		m_invViewProj = m_viewProj.inverse();
	}
}
