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
# include <Siv3D/Physics2D.hpp>
# include <Box2D/Box2D.h>

namespace s3d
{
	namespace detail
	{
		inline constexpr double P2LineThickness = 3.0;
		inline constexpr double P2AnchorR = 4.0;

		[[nodiscard]] inline constexpr Vec2 ToVec2(const b2Vec2& b2Vec2)
		{
			return{ b2Vec2.x, b2Vec2.y };
		}

		[[nodiscard]] inline b2Vec2 ToB2Vec2(const Vec2& vec2)
		{
			return b2Vec2(static_cast<float32>(vec2.x), static_cast<float32>(vec2.y));
		}

		[[nodiscard]] inline b2FixtureDef MakeFixtureDef(b2Shape* shape, const P2Material& material, const P2Filter& filter)
		{
			b2FixtureDef fixtureDef;
			fixtureDef.shape = shape;
			fixtureDef.density = static_cast<float32>(material.density);
			fixtureDef.friction = static_cast<float32>(material.friction);
			fixtureDef.restitution = static_cast<float32>(material.restitution);
			fixtureDef.filter.categoryBits = filter.categoryBits;
			fixtureDef.filter.maskBits = filter.maskBits;
			fixtureDef.filter.groupIndex = filter.groupIndex;
			return fixtureDef;
		}

		[[nodiscard]] inline Vec2 CalcVec2(const b2Vec2& vertex, const b2Transform& transform)
		{
			return Vec2(vertex.x * transform.q.c - vertex.y * transform.q.s + transform.p.x, vertex.x * transform.q.s + vertex.y * transform.q.c + transform.p.y);
		}
	}
}
