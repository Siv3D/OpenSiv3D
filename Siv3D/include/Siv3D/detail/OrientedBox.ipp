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
	inline OrientedBox::OrientedBox(const double _size, const Quaternion _orientation) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _size, _size, _size }
		, orientation{ _orientation } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline OrientedBox::OrientedBox(const Arithmetic _size, const Quaternion _orientation) noexcept
		: OrientedBox{ static_cast<double>(_size), _orientation } {}

	inline OrientedBox::OrientedBox(const double _w, const double _h, const double _d, const Quaternion _orientation) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ _w, _h, _d }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline OrientedBox::OrientedBox(const W _w, const H _h, const D _d, const Quaternion _orientation) noexcept
		: center{ 0.0, 0.0 , 0.0 }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const Vec3& _size, const Quaternion _orientation) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, size{ _size }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const double cx, const double cy, const double cz, const double _size, const Quaternion _orientation) noexcept
		: center{ cx, cy, cz }
		, size{ _size, _size, _size }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
# else
	template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>*>
# endif
	inline OrientedBox::OrientedBox(const X cx, const Y cy, const Z cz, const S _size, const Quaternion _orientation) noexcept
		: OrientedBox{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz), static_cast<double>(_size), _orientation } {}

	inline OrientedBox::OrientedBox(const double cx, const double cy, const double cz, const double _w, const double _h, const double _d, const Quaternion _orientation) noexcept
		: center{ cx, cy, cz }
		, size{ _w, _h, _d }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class X, class Y, class Z, class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline OrientedBox::OrientedBox(const X cx, const Y cy, const Z cz, const W _w, const H _h, const D _d, const Quaternion _orientation) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const double cx, const double cy, const double cz, const Vec3& _size, const Quaternion _orientation) noexcept
		: center{ cx, cy, cz }
		, size{ _size }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
# else
	template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>*>
# endif
	inline OrientedBox::OrientedBox(const X cx, const Y cy, const Z cz, const Vec3& _size, const Quaternion _orientation) noexcept
		: center{ static_cast<double>(cx), static_cast<double>(cy), static_cast<double>(cz) }
		, size{ _size }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const Vec3& _center, const double _size, const Quaternion _orientation) noexcept
		: center{ _center }
		, size{ _size, _size, _size }
		, orientation{ _orientation } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline OrientedBox::OrientedBox(const Vec3& _center, const Arithmetic _size, const Quaternion _orientation) noexcept
		: OrientedBox{ _center, static_cast<double>(_size), _orientation } {}

	inline OrientedBox::OrientedBox(const Vec3& _center, const double _w, const double _h, const double _d, const Quaternion _orientation) noexcept
		: center{ _center }
		, size{ _w, _h, _d }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline OrientedBox::OrientedBox(const Vec3& _center, const W _w, const H _h, const D _d, const Quaternion _orientation) noexcept
		: center{ _center }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const Vec3& _center, const Vec3& _size, const Quaternion _orientation) noexcept
		: center{ _center }
		, size{ _size }
		, orientation{ _orientation } {}


	inline OrientedBox::OrientedBox(const Arg::bottomCenter_<Vec3> bottomCenter, const double _size, const Quaternion _orientation) noexcept
		: center{ bottomCenter->movedBy(0, (_size * 0.5), 0) }
		, size{ _size, _size, _size }
		, orientation{ _orientation } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline OrientedBox::OrientedBox(const Arg::bottomCenter_<Vec3> bottomCenter, const Arithmetic _size, const Quaternion _orientation) noexcept
		: OrientedBox{ bottomCenter, static_cast<double>(_size), _orientation } {}

	inline OrientedBox::OrientedBox(const Arg::bottomCenter_<Vec3> bottomCenter, const double _w, const double _h, const double _d, const Quaternion _orientation) noexcept
		: center{ bottomCenter->movedBy(0, (_h * 0.5), 0) }
		, size{ _w, _h, _d }
		, orientation{ _orientation } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
# else
	template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>*>
# endif
	inline OrientedBox::OrientedBox(const Arg::bottomCenter_<Vec3> bottomCenter, const W _w, const H _h, const D _d, const Quaternion _orientation) noexcept
		: center{ bottomCenter->movedBy(0, (_h * 0.5), 0) }
		, size{ static_cast<double>(_w), static_cast<double>(_h), static_cast<double>(_d) }
		, orientation{ _orientation } {}

	inline OrientedBox::OrientedBox(const Arg::bottomCenter_<Vec3> bottomCenter, const Vec3& _size, const Quaternion _orientation) noexcept
		: center{ bottomCenter->movedBy(0, (_size.y * 0.5), 0) }
		, size{ _size }
		, orientation{ _orientation } {}


	inline OrientedBox::OrientedBox(const Box& box, const Quaternion _orientation) noexcept
		: center{ box.center }
		, size{ box.size }
		, orientation{ _orientation } {}

	inline OrientedBox& OrientedBox::setPos(const value_type cx, const value_type cy, const value_type cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline OrientedBox& OrientedBox::setPos(const position_type _center) noexcept
	{
		center.set(_center);
		return *this;
	}

	inline OrientedBox& OrientedBox::setSize(const value_type _w, const value_type _h, const value_type _d) noexcept
	{
		size.set(_w, _h, _d);
		return *this;
	}

	inline OrientedBox& OrientedBox::setSize(const size_type _size) noexcept
	{
		size.set(_size);
		return *this;
	}

	inline OrientedBox& OrientedBox::setOrientation(const Quaternion _orientation) noexcept
	{
		orientation = _orientation;
		return *this;
	}

	inline OrientedBox OrientedBox::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), size, orientation };
	}

	inline OrientedBox OrientedBox::movedBy(const size_type v) const noexcept
	{
		return{ center.movedBy(v), size, orientation };
	}

	inline OrientedBox& OrientedBox::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline OrientedBox& OrientedBox::moveBy(const size_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	inline OrientedBox OrientedBox::stretched(const double xyz) const noexcept
	{
		return stretched(xyz, xyz, xyz);
	}

	inline OrientedBox OrientedBox::stretched(const double _x, const double _y, const double _z) const noexcept
	{
		return stretched({ _x, _y, _z });
	}

	inline OrientedBox OrientedBox::stretched(const Vec3 xyz) const noexcept
	{
		return{ center, (size + xyz), orientation };
	}

	inline OrientedBox OrientedBox::scaled(const double s) const noexcept
	{
		return{ center, (size * s), orientation };
	}

	inline OrientedBox OrientedBox::scaled(const double sx, const double sy, const double sz) const noexcept
	{
		return{ center, (size * Vec3{ sx, sy, sz }), orientation };
	}

	inline OrientedBox OrientedBox::scaled(const Vec3 s) const noexcept
	{
		return{ center, (size * s), orientation };
	}

	inline bool OrientedBox::hasVolume() const noexcept
	{
		return ((size.x != 0.0) && (size.y != 0.0) && (size.z != 0.0));
	}

	inline OrientedBox OrientedBox::lerp(const OrientedBox& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), size.lerp(other.size, f), orientation.slerp(other.orientation, f) };
	}
}
