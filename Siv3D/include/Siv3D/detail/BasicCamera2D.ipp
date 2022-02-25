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
	inline constexpr BasicCamera2D::BasicCamera2D(const Vec2 center, const double scale) noexcept
		: m_center{ center }
		, m_scale{ scale } {}

	inline constexpr void BasicCamera2D::setCenter(const Vec2 center) noexcept
	{
		m_center = center;
	}

	inline constexpr const Vec2& BasicCamera2D::getCenter() const noexcept
	{
		return m_center;
	}

	inline constexpr void BasicCamera2D::setScale(const double scale) noexcept
	{
		m_scale = scale;
	}

	inline constexpr double BasicCamera2D::getScale() const noexcept
	{
		return m_scale;
	}

	inline constexpr RectF BasicCamera2D::getRegion(const Size renderTargetSize) const noexcept
	{
		return{ (m_center - ((renderTargetSize * 0.5) / m_scale)), (renderTargetSize / m_scale) };
	}

	inline constexpr Mat3x2 BasicCamera2D::getMat3x2(const Size renderTargetSize) const noexcept
	{
		return Mat3x2::Scale(m_scale)
			.translated((renderTargetSize * 0.5) - m_scale * m_center);
	}

	inline Transformer2D BasicCamera2D::createTransformer() const
	{
		return Transformer2D{ getMat3x2(), TransformCursor::Yes, Transformer2D::Target::PushCamera };
	}
}
