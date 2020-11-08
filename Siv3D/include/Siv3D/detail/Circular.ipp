//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float>::CircularBase(const value_type _r, const value_type _theta) noexcept
		: r(_r)
		, theta(_theta) {}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float>::CircularBase(const Arg::r_<value_type> _r, const Arg::theta_<value_type> _theta) noexcept
		: r(*_r)
		, theta(*_theta) {}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float>::CircularBase(const Arg::theta_<value_type> _theta, const Arg::r_<value_type> _r) noexcept
		: r(*_r)
		, theta(*_theta) {}

	template <int32 Oclock, class Float>
	inline CircularBase<Oclock, Float>::CircularBase(const Vector2D<value_type> v) noexcept
		: r(v.length())
		, theta(Offset(std::atan2(v.x, -v.y))) {}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float> CircularBase<Oclock, Float>::operator +() const noexcept
	{
		return *this;
	}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float> CircularBase<Oclock, Float>::operator -() const noexcept
	{
		return{ r, ClampAngle(theta - Math::Constants::Pi) };
	}

	template <int32 Oclock, class Float>
	inline Vector2D<Float> CircularBase<Oclock, Float>::operator +(const Vector2D<value_type> v) const noexcept
	{
		return (toVec2() + v);
	}

	template <int32 Oclock, class Float>
	inline Vector2D<Float> CircularBase<Oclock, Float>::operator -(const Vector2D<value_type> v) const noexcept
	{
		return (toVec2() - v);
	}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float> CircularBase<Oclock, Float>::rotated(const value_type angle) const noexcept
	{
		return CircularBase(*this).rotate(angle);
	}

	template <int32 Oclock, class Float>
	inline constexpr CircularBase<Oclock, Float>& CircularBase<Oclock, Float>::rotate(const value_type angle) noexcept
	{
		theta += angle;

		return *this;
	}

	template <int32 Oclock, class Float>
	inline Float2 CircularBase<Oclock, Float>::toFloat2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <int32 Oclock, class Float>
	inline Vec2 CircularBase<Oclock, Float>::toVec2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <int32 Oclock, class Float>
	inline Float2 CircularBase<Oclock, Float>::fastToFloat2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r), (-c * r) };
	}

	template <int32 Oclock, class Float>
	inline Vec2 CircularBase<Oclock, Float>::fastToVec2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r), (-c * r) };
	}

	template <int32 Oclock, class Float>
	inline CircularBase<Oclock, Float>::operator Vector2D<Float>() const noexcept
	{
		return toVec2();
	}

	template <int32 Oclock, class Float>
	inline constexpr Float CircularBase<Oclock, Float>::ClampAngle(const value_type theta) noexcept
	{
		if (theta <= -Math::Constants::Pi)
		{
			return (theta + Math::Constants::TwoPi);
		}
		else
		{
			return theta;
		}
	}

	template <int32 Oclock, class Float>
	inline constexpr Float CircularBase<Oclock, Float>::Clock() noexcept
	{
		return (Oclock * (Math::Constants::TwoPi / 12));
	}

	template <int32 Oclock, class Float>
	inline constexpr Float CircularBase<Oclock, Float>::Offset(const value_type theta) noexcept
	{
		return ClampAngle(theta - Clock());
	}
}
