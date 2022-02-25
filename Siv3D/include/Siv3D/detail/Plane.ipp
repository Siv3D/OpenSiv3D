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
	inline constexpr Plane::Plane(const double _size) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _size, _size } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Plane::Plane(const Arithmetic _size) noexcept
		: Plane{ static_cast<double>(_size) } {}

	inline constexpr Plane::Plane(const double _w, const double _h) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H>
# else
	template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>*>
# endif
	inline constexpr Plane::Plane(const W _w, const H _h) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ static_cast<double>(_w), static_cast<double>(_h) } {}

	inline constexpr Plane::Plane(const Vec2& _size) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, size{ _size } {}

	inline constexpr Plane::Plane(const double cx, const double cy, const double cz, const double _size) noexcept
		: center{ cx, cy, cz }
		, size{ _size, _size } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
# else
	template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>*>
# endif
	inline constexpr Plane::Plane(const X cx, const Y cy, const Z cz, S _size) noexcept
		: Plane{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz), static_cast<double>(_size) } {}

	inline constexpr Plane::Plane(const double cx, const double cy, const double cz, const double _w, const double _h) noexcept
		: center{ cx, cy, cz }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H>
# else
	template <class X, class Y, class Z, class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>>>*>
# endif
	inline constexpr Plane::Plane(const X cx, const Y cy, const Z cz, const W _w, const H _h) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ static_cast<double>(_w), static_cast<double>(_h) } {}

	inline constexpr Plane::Plane(const double cx, const double cy, const double cz, const Vec2& _size) noexcept
		: center{ cx, cy, cz }
		, size{ _size } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
# else
	template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>*>
# endif
	inline constexpr Plane::Plane(const X cx, const Y cy, const Z cz, const Vec2& _size) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ _size } {}

	inline constexpr Plane::Plane(const Vec3& _center, const double _size) noexcept
		: center{ _center }
		, size{ _size, _size } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Plane::Plane(const Vec3& _center, const Arithmetic _size) noexcept
		: Plane{ _center, static_cast<double>(_size) } {}

	inline constexpr Plane::Plane(const Vec3& _center, const double _w, const double _h) noexcept
		: center{ _center }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H>
# else
	template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>*>
# endif
	inline constexpr Plane::Plane(const Vec3& _center, const W _w, const H _h) noexcept
		: center{ _center }
		, size{ static_cast<double>(_w), static_cast<double>(_h) } {}

	inline constexpr Plane::Plane(const Vec3& _center, const Vec2& _size) noexcept
		: center{ _center }
		, size{ _size } {}

	inline constexpr Plane& Plane::setPos(const value_type cx, const value_type cy, const value_type cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline constexpr Plane& Plane::setPos(const position_type _center) noexcept
	{
		center = _center;
		return *this;
	}

	inline constexpr Plane& Plane::setSize(const value_type _w, const value_type _d) noexcept
	{
		size.set(_w, _d);
		return *this;
	}

	inline constexpr Plane& Plane::setSize(const size_type _size) noexcept
	{
		size = _size;
		return *this;
	}

	inline constexpr Plane Plane::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), size };
	}

	inline constexpr Plane Plane::movedBy(const position_type v) const noexcept
	{
		return{ center.movedBy(v), size };
	}

	inline constexpr Plane& Plane::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline constexpr Plane& Plane::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	inline constexpr Plane Plane::stretched(const value_type xz) const noexcept
	{
		return stretched({ xz, xz });
	}

	inline constexpr Plane Plane::stretched(const value_type _x, const value_type _z) const noexcept
	{
		return stretched({ _x, _z });
	}

	inline constexpr Plane Plane::stretched(const size_type xz) const noexcept
	{
		return{ center, (size + xz * 2) };
	}

	inline constexpr Plane Plane::scaled(const double s) const noexcept
	{
		return{ center, (size * s) };
	}

	inline constexpr Plane Plane::scaled(const double sx, const double sz) const noexcept
	{
		return{ center, (size * Vec2{ sx, sz }) };
	}

	inline constexpr Plane Plane::scaled(const Vec2 s) const noexcept
	{
		return{ center, (size * s) };
	}

	inline constexpr bool Plane::hasArea() const noexcept
	{
		return ((size.x != 0) && (size.y != 0));
	}

	inline constexpr Plane Plane::lerp(const Plane& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), size.lerp(other.size, f) };
	}
}
