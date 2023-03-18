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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	struct CursorState
	{
		template <class VectrorType>
		struct Internal
		{
			VectrorType previous = { 0,0 };
			VectrorType current = { 0,0 };
			VectrorType delta = { 0,0 };

			constexpr void update(const VectrorType& newPos) noexcept
			{
				previous	= current;
				current		= newPos;
				delta		= (current - previous);
			}
		};

		Internal<Point> raw;
		
		Internal<Vec2>	vec2;
		
		Internal<Point> point;

		Internal<Point> screen;

		constexpr void update(const Point& _raw, const Vec2& _vec2, const Point& _screen) noexcept
		{
			raw.update(_raw);
			
			vec2.update(_vec2);
			
			point.update(_vec2.asPoint());

			screen.update(_screen);
		}
	};
}
