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
	inline LineString::LineString(const LineString& lines)
		: base_type{ lines } {}

	inline LineString::LineString(LineString&& lines) noexcept
		: base_type(std::move(lines)) {}

	inline LineString::LineString(const Array<Point>& points)
		: base_type{ points.begin(), points.end() } {}

	inline LineString::LineString(const Array<Vec2>& points)
		: base_type{ points } {}

	inline LineString::LineString(Array<Vec2>&& points) noexcept
		: base_type(std::move(points)) {}

	inline LineString& LineString::operator =(const Array<Point>& other)
	{
		base_type::assign(other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::operator =(const Array<Vec2>& other)
	{
		base_type::operator =(other);

		return *this;
	}

	inline LineString& LineString::operator =(Array<Vec2>&& other) noexcept
	{
		base_type::operator =(std::move(other));

		return *this;
	}

	inline LineString& LineString::operator =(const LineString& other)
	{
		base_type::operator =(other);

		return *this;
	}

	inline LineString& LineString::operator =(LineString&& other) noexcept
	{
		base_type::operator =(std::move(other));

		return *this;
	}

	inline void LineString::assign(const Array<Point>& other)
	{
		base_type::assign(other.begin(), other.end());
	}

	inline void LineString::assign(const LineString& other)
	{
		base_type::operator =(other);
	}

	inline void LineString::assign(LineString&& other) noexcept
	{
		base_type::operator =(std::move(other));
	}

	inline LineString& LineString::operator <<(const Vec2& value)
	{
		base_type::push_back(value);

		return *this;
	}

	inline void LineString::swap(LineString& other) noexcept
	{
		base_type::swap(other);
	}

	inline LineString& LineString::append(const Array<Vec2>& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::append(const LineString& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::remove(const Vec2& value)
	{
		base_type::remove(value);

		return *this;
	}

	inline LineString& LineString::remove_at(const size_t index)
	{
		base_type::remove_at(index);

		return *this;
	}

	template <class Fty>
	inline LineString& LineString::remove_if(Fty f)
	{
		base_type::remove_if(f);

		return *this;
	}

	inline LineString& LineString::reverse()
	{
		base_type::reverse();

		return *this;
	}

	inline LineString LineString::reversed() const
	{
		return LineString(rbegin(), rend());
	}

	inline LineString& LineString::shuffle()
	{
		base_type::shuffle();

		return *this;
	}

	SIV3D_CONCEPT_URBG_
	inline LineString& LineString::shuffle(URBG&& rbg)
	{
		base_type::shuffle(std::forward<URBG>(rbg));

		return *this;
	}

	inline LineString LineString::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, end());
	}

	inline LineString LineString::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, begin() + Min(index + length, size()));
	}

	inline size_t LineString::num_lines() const noexcept
	{
		if (const size_t s = size();
			s < 2)
		{
			return 0;
		}
		else
		{
			return (s - 1);
		}
	}

	inline Line LineString::line(const size_t index) const
	{
		if (num_lines() <= index)
		{
			throw std::out_of_range("LineString::line() index out of range");
		}

		const Vec2* pData = data();

		return{ pData[index], pData[index + 1] };
	}

	inline LineString LineString::movedBy(const double x, const double y) const
	{
		LineString lines{ *this };
		
		lines.moveBy(x, y);
		
		return lines;
	}

	inline LineString LineString::movedBy(const Vec2 v) const
	{
		return movedBy(v.x, v.y);
	}

	inline LineString& LineString::moveBy(const double x, const double y) noexcept
	{
		for (auto& point : *this)
		{
			point.moveBy(x, y);
		}

		return *this;
	}

	inline LineString& LineString::moveBy(const Vec2 v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline RectF LineString::calculateBoundingRect() const noexcept
	{
		return Geometry2D::BoundingRect(*this);
	}

	template <class Shape2DType>
	inline constexpr bool LineString::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> LineString::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}
}

template <>
void std::swap(s3d::LineString& a, s3d::LineString& b) noexcept
{
	a.swap(b);
}
