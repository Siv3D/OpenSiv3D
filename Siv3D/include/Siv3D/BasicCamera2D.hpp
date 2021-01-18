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
# include "2DShapes.hpp"
# include "Mat3x2.hpp"
# include "Transformer2D.hpp"
# include "Graphics2D.hpp"

namespace s3d
{
	class BasicCamera2D
	{
	protected:

		Vec2 m_center = Vec2{ 0, 0 };

		double m_scale = 1.0;

	public:

		SIV3D_NODISCARD_CXX20
		BasicCamera2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr BasicCamera2D(Vec2 center, double scale = 1.0) noexcept;

		constexpr void setCenter(Vec2 center) noexcept;

		[[nodiscard]]
		constexpr const Vec2& getCenter() const noexcept;

		constexpr void setScale(double scale) noexcept;

		[[nodiscard]]
		constexpr double getScale() const noexcept;

		[[nodiscard]]
		constexpr RectF getRegion(Size renderTargetSize = Graphics2D::GetRenderTargetSize()) const;

		[[nodiscard]]
		constexpr Mat3x2 getMat3x2(Size renderTargetSize = Graphics2D::GetRenderTargetSize()) const;

		[[nodiscard]]
		Transformer2D createTransformer() const;
	};
}

# include "detail/BasicCamera2D.ipp"
