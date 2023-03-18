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

# pragma once
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Physics2D/P2Material.hpp>
# include <Siv3D/Physics2D/P2Filter.hpp>
# include <ThirdParty/box2d/box2d.h>

namespace s3d
{
	namespace detail
	{
		inline constexpr double P2LineThickness = 3.0;
		inline constexpr double P2AnchorR		= 4.0;
		inline constexpr double P2DensityScale		= (1.0 / 10000.0);
		inline constexpr double P2DensityScaleInv	= 10000.0;
		inline constexpr double P2RestitutionThresholdScale		= 100.0;
		inline constexpr double P2RestitutionThresholdScaleInv	= (1.0 / 100.0);

		[[nodiscard]]
		inline constexpr Vec2 ToVec2(const b2Vec2& b2Vec2) noexcept
		{
			return{ b2Vec2.x, b2Vec2.y };
		}

		[[nodiscard]]
		inline b2Vec2 ToB2Vec2(const Vec2& vec2) noexcept
		{
			return{ static_cast<float>(vec2.x), static_cast<float>(vec2.y) };
		}

		[[nodiscard]]
		inline b2FixtureDef MakeFixtureDef(b2Shape* shape, const P2Material& material, const P2Filter& filter, const bool isSensor = false) noexcept
		{
			b2FixtureDef fixtureDef;
			fixtureDef.shape		= shape;
			fixtureDef.density		= static_cast<float>(material.density * P2DensityScale);
			fixtureDef.friction		= static_cast<float>(material.friction);
			fixtureDef.restitution	= static_cast<float>(material.restitution);
			fixtureDef.isSensor		= isSensor;
			fixtureDef.restitutionThreshold	= static_cast<float>(material.restitutionThreshold * P2RestitutionThresholdScale);
			fixtureDef.filter.categoryBits	= filter.categoryBits;
			fixtureDef.filter.maskBits		= filter.maskBits;
			fixtureDef.filter.groupIndex	= filter.groupIndex;
			return fixtureDef;
		}

		[[nodiscard]]
		inline Vec2 CalcVec2(const b2Vec2& vertex, const b2Transform& transform) noexcept
		{
			return{ (vertex.x * transform.q.c - vertex.y * transform.q.s + transform.p.x), (vertex.x * transform.q.s + vertex.y * transform.q.c + transform.p.y) };
		}

		[[nodiscard]]
		inline double AdjustThickness(const double thickness) noexcept
		{
			return (thickness / Graphics2D::GetMaxScaling());
		}
	}
}
