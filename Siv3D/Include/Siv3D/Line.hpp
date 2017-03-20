//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Line
	{
		using position_type = Vec2;

		using value_type = typename position_type::value_type;
		
		/// <summary>
		/// 線分の開始位置
		/// </summary>
		position_type begin;
		
		/// <summary>
		/// 線分の終点位置
		/// </summary>
		position_type end;
		
		Line() = default;
		
		constexpr Line(value_type x0, value_type y0, value_type x1, value_type y1) noexcept
			: begin(x0, y0)
			, end(x1, y1) {}
		
		constexpr Line(const position_type& p0, value_type x1, value_type y1) noexcept
			: begin(p0)
			, end(x1, y1) {}
		
		constexpr Line(value_type x0, value_type y0, const position_type& p1) noexcept
			: begin(x0, y0)
			, end(p1) {}
		
		constexpr Line(const position_type& p0, const position_type& p1) noexcept
			: begin(p0)
			, end(p1) {}
		
		constexpr bool operator ==(const Line& line) const noexcept
		{
			return begin == line.begin
				&& end == line.end;
		}
		
		constexpr bool operator !=(const Line& line) const noexcept
		{
			return !(*this == line);
		}
		
		constexpr Line& set(value_type x0, value_type y0, value_type x1, value_type y1) noexcept
		{
			begin.set(x0, y0);
			end.set(x1, y1);
			return *this;
		}
		
		constexpr Line& set(const position_type& p0, value_type x1, value_type y1) noexcept
		{
			return set(p0.x, p0.y, x1, y1);
		}
		
		constexpr Line& set(value_type x0, value_type y0, const position_type& p1) noexcept
		{
			return set(x0, y0, p1.x, p1.y);
		}
		
		constexpr Line& set(const position_type& p0, const position_type& p1) noexcept
		{
			return set(p0.x, p0.y, p1.x, p1.y);
		}
		
		constexpr Line& set(const Line& line) noexcept
		{
			begin.set(line.begin);
			end.set(line.end);
			return *this;
		}
		
		constexpr Line movedBy(value_type x, value_type y) const noexcept
		{
			return{ begin.movedBy(x, y), end.movedBy(x, y) };
		}
		
		constexpr Line movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}
		
		constexpr Line& moveBy(value_type x, value_type y) noexcept
		{
			begin.movedBy(x, y);
			end.movedBy(x, y);
			return *this;
		}
		
		constexpr Line& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}
		
		constexpr position_type vector() const noexcept
		{
			return end - begin;
		}
		
		constexpr Line& reverse() noexcept
		{
			const position_type t = begin;
			begin = end;
			end = t;
			return *this;
		}
		
		constexpr Line reversed() const
		{
			return{ end, begin };
		}
		
		value_type length() const
		{
			return begin.distanceFrom(end);
		}
		
		constexpr value_type lengthSq() const
		{
			return begin.distanceFromSq(end);
		}
		
		constexpr position_type center() const noexcept
		{
			return (begin + end) * 0.5;
		}
		
		position_type closest(const position_type& pos) const;

		// intersects
		
		Optional<Vec2> intersectsAt(const Line& line) const;
		
		// rotated
		
		// rotatedAt
		
		// paint
		
		// paintArrow
		
		// overpaint
		
		// overpaintArrow
		
		// draw
		
		// drawArrow
		
		// asPolygon;
	};
}
