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
	inline Camera2D::Camera2D(const Vec2 center, const double scale, const CameraControl cameraControl) noexcept
		: Camera2D{ center, scale, Camera2DParameters::Make(cameraControl) } {}

	inline Camera2D::Camera2D(const Vec2 center, const double scale, const Camera2DParameters& parameters) noexcept
		: BasicCamera2D{ center, scale }
		, m_parameters{ parameters } {}

	inline void Camera2D::setParameters(const Camera2DParameters& parameters) noexcept
	{
		m_parameters = parameters;
	}

	inline const Camera2DParameters& Camera2D::getParameters() const noexcept
	{
		return m_parameters;
	}

	inline void Camera2D::setTargetCenter(const Vec2 targetCenter) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetCenter = targetCenter;
	}

	inline const Vec2& Camera2D::getTargetCenter() const noexcept
	{
		return m_targetCenter;
	}

	inline void Camera2D::setTargetScale(const double targetScale) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetScale = targetScale;
	}

	inline double Camera2D::getTargetScale() const noexcept
	{
		return m_targetScale;
	}

	inline void Camera2D::jumpTo(const Vec2 center, const double scale) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetCenter = m_center = center;
		m_targetScale = m_scale = scale;
		m_positionChangeVelocity = Vec2::Zero();
		m_scaleChangeVelocity = 0.0;
	}
}
