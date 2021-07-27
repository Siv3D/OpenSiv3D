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
	inline constexpr Box::Box(const double _size) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _size, _size, _size } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Box::Box(const Arithmetic _size) noexcept
		: Box{ static_cast<double>(_size) } {}

	inline constexpr Box::Box(const double _w, const double _h, const double _d) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _w, _h, _d } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline constexpr Box::Box(const W _w, const H _h, const D _d) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) } {}

	inline constexpr Box::Box(const Vec3& _size) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, size{ _size } {}

	inline constexpr Box::Box(const double cx, const double cy, const double cz, const double _size) noexcept
		: center{ cx, cy, cz }
		, size{ _size, _size, _size } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
# else
	template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>*>
# endif
	inline constexpr Box::Box(const X cx, const Y cy, const Z cz, const S _size) noexcept
		: Box{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz), static_cast<double>(_size) } {}

	inline constexpr Box::Box(const double cx, const double cy, const double cz, const double _w, const double _h, const double _d) noexcept
		: center{ cx, cy, cz }
		, size{ _w, _h, _d } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class X, class Y, class Z, class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline constexpr Box::Box(const X cx, const Y cy, const Z cz, const W _w, const H _h, const D _d) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) } {}

	inline constexpr Box::Box(const double cx, const double cy, const double cz, const Vec3& _size) noexcept
		: center{ cx, cy, cz }
		, size{ _size } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
# else
	template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>*>
# endif
	inline constexpr Box::Box(const X cx, const Y cy, const Z cz, const Vec3& _size) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ _size } {}

	inline constexpr Box::Box(const Vec3& _center, const double _size) noexcept
		: center{ _center }
		, size{ _size, _size, _size } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Box::Box(const Vec3& _center, const Arithmetic _size) noexcept
		: Box{ _center, static_cast<double>(_size) } {}

	inline constexpr Box::Box(const Vec3& _center, const double _w, const double _h, const double _d) noexcept
		: center{ _center }
		, size{ _w, _h, _d } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline constexpr Box::Box(const Vec3& _center, const W _w, const H _h, const D _d) noexcept
		: center{ _center }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) } {}

	inline constexpr Box::Box(const Vec3& _center, const Vec3& _size) noexcept
		: center{ _center }
		, size{ _size } {}

	inline constexpr Box::Box(const Arg::bottomCenter_<Vec3> bottomCenter, const double _size) noexcept
		: center{ bottomCenter->movedBy(0, (_size * 0.5), 0) }
		, size{ _size, _size, _size } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Box::Box(const Arg::bottomCenter_<Vec3> bottomCenter, const Arithmetic _size) noexcept
		: Box{ bottomCenter, static_cast<double>(_size) } {}

	inline constexpr Box::Box(const Arg::bottomCenter_<Vec3> bottomCenter, const double _w, const double _h, const double _d) noexcept
		: center{ bottomCenter->movedBy(0, (_h * 0.5), 0) }
		, size{ _w, _h, _d } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline constexpr Box::Box(const Arg::bottomCenter_<Vec3> bottomCenter, const W _w, const H _h, const D _d) noexcept
		: center{ bottomCenter->movedBy(0, (_h * 0.5), 0) }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) } {}

	inline constexpr Box::Box(const Arg::bottomCenter_<Vec3> bottomCenter, const Vec3& _size) noexcept
		: center{ bottomCenter->movedBy(0, (_size.y * 0.5), 0) }
		, size{ _size } {}


	inline constexpr Box& Box::setPos(const double cx, const double cy, const double cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline constexpr Box& Box::setPos(const Vec3& _center) noexcept
	{
		center.set(_center);
		return *this;
	}

	inline constexpr Box& Box::setSize(const double w, const double h, const double d) noexcept
	{
		size.set(w, h, d);
		return *this;
	}

	inline constexpr Box& Box::setSize(const Vec3& _size) noexcept
	{
		size.set(_size);
		return *this;
	}

	inline constexpr Box Box::stretched(const double xyz) const noexcept
	{
		return stretched(xyz, xyz, xyz);
	}

	inline constexpr Box Box::stretched(const double x, const double y, const double z) const noexcept
	{
		return stretched({ x, y, z });
	}

	inline constexpr Box Box::stretched(const Vec3 xyz) const noexcept
	{
		return{ center, (size + xyz) };
	}

	inline constexpr Box Box::FromTwoPoints(const Vec3& a, const Vec3& b) noexcept
	{
		const Vec3 center = (a + b) * 0.5;
		const Vec3 size{ AbsDiff(a.x, b.x), AbsDiff(a.y, b.y), AbsDiff(a.z, b.z) };
		return{ center, size };
	}
}
