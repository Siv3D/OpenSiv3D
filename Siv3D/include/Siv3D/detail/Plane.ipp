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
}
