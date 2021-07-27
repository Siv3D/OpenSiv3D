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

namespace s3d
{
	inline const Size& BasicCamera3D::getSceneSize() const noexcept
	{
		return m_sceneSize;
	}

	inline double BasicCamera3D::getVerticlaFOV() const noexcept
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

	inline const Mat4x4& BasicCamera3D::getViewProj() const noexcept
	{
		return m_viewProj;
	}

	inline const Mat4x4& BasicCamera3D::getInvViewProj() const noexcept
	{
		return m_invViewProj;
	}
}
