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

namespace s3d
{
	inline const Size& BasicCamera3D::getSceneSize() const noexcept
	{
		return m_sceneSize;
	}

	inline double BasicCamera3D::getVerticalFOV() const noexcept
	{
		return m_verticalFOV;
	}

	inline double BasicCamera3D::getNearClip() const noexcept
	{
		return m_nearClip;
	}

	inline const Vec3& BasicCamera3D::getEyePosition() const noexcept
	{
		return m_eyePosition;
	}

	inline const Vec3& BasicCamera3D::getFocusPosition() const noexcept
	{
		return m_focusPosition;
	}

	inline const Vec3& BasicCamera3D::getUpDirection() const noexcept
	{
		return m_upDirection;
	}

	inline Vec3 BasicCamera3D::getLookAtVector() const noexcept
	{
		return (m_focusPosition - m_eyePosition).normalized();
	}

	inline const Mat4x4& BasicCamera3D::getProj() const noexcept
	{
		return m_proj;
	}

	inline const Mat4x4& BasicCamera3D::getView() const noexcept
	{
		return m_view;
	}

	inline const Mat4x4& BasicCamera3D::getInvView() const noexcept
	{
		return m_invView;
	}

	inline const Mat4x4& BasicCamera3D::getViewProj() const noexcept
	{
		return m_viewProj;
	}

	inline const Mat4x4& BasicCamera3D::getInvViewProj() const noexcept
	{
		return m_invViewProj;
	}

	inline Mat4x4 BasicCamera3D::billboard(const Float3 pos) const noexcept
	{
		Mat4x4 m = m_invView;
		m.value.r[3] = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
		return m;
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 BasicCamera3D::billboard(const Float3 pos, const Arithmetic scale) const noexcept
	{
		const float s = static_cast<float>(scale);
		Mat4x4 m = m_invView;
		m.value.r[0] = DirectX::XMVectorScale(m.value.r[0], s);
		m.value.r[1] = DirectX::XMVectorScale(m.value.r[1], s);
		m.value.r[3] = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
		return m;
	}

	inline Mat4x4 BasicCamera3D::billboard(const Float3 pos, const Float2 scale) const noexcept
	{
		Mat4x4 m = m_invView;
		m.value.r[0] = DirectX::XMVectorScale(m.value.r[0], scale.x);
		m.value.r[1] = DirectX::XMVectorScale(m.value.r[1], scale.y);
		m.value.r[3] = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
		return m;
	}
}
