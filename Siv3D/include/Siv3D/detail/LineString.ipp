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
}

template <>
void std::swap(s3d::LineString& a, s3d::LineString& b) noexcept
{
	a.swap(b);
}
