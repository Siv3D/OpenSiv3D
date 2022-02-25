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
	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock>::CircularBase(const value_type _r, const value_type _theta) noexcept
		: r{ _r }
		, theta{ _theta } {}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock>::CircularBase(const Arg::r_<value_type> _r, const Arg::theta_<value_type> _theta) noexcept
		: r{ *_r }
		, theta{ *_theta } {}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock>::CircularBase(const Arg::theta_<value_type> _theta, const Arg::r_<value_type> _r) noexcept
		: r{ *_r }
		, theta{ *_theta } {}

	template <class Float, int32 Oclock>
	inline CircularBase<Float, Oclock>::CircularBase(const position_type v) noexcept
		: r{ v.length() }
		, theta{ Offset(std::atan2(v.x, -v.y)) } {}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock> CircularBase<Float, Oclock>::operator +() const noexcept
	{
		return *this;
	}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock> CircularBase<Float, Oclock>::operator -() const noexcept
	{
		return{ r, ClampAngle(theta - Math::Pi) };
	}

	template <class Float, int32 Oclock>
	inline typename CircularBase<Float, Oclock>::position_type CircularBase<Float, Oclock>::operator +(const position_type v) const noexcept
	{
		return (toPosition() + v);
	}

	template <class Float, int32 Oclock>
	inline typename CircularBase<Float, Oclock>::position_type CircularBase<Float, Oclock>::operator -(const position_type v) const noexcept
	{
		return (toPosition() - v);
	}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock> CircularBase<Float, Oclock>::rotated(const value_type angle) const noexcept
	{
		return CircularBase{ *this }.rotate(angle);
	}

	template <class Float, int32 Oclock>
	inline constexpr CircularBase<Float, Oclock>& CircularBase<Float, Oclock>::rotate(const value_type angle) noexcept
	{
		theta += angle;

		return *this;
	}

	template <class Float, int32 Oclock>
	inline Float2 CircularBase<Float, Oclock>::toFloat2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <class Float, int32 Oclock>
	inline Vec2 CircularBase<Float, Oclock>::toVec2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <class Float, int32 Oclock>
	inline Float2 CircularBase<Float, Oclock>::fastToFloat2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r), (-c * r) };
	}

	template <class Float, int32 Oclock>
	inline Vec2 CircularBase<Float, Oclock>::fastToVec2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r), (-c * r) };
	}

	template <class Float, int32 Oclock>
	inline typename CircularBase<Float, Oclock>::position_type CircularBase<Float, Oclock>::toPosition() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <class Float, int32 Oclock>
	inline CircularBase<Float, Oclock>::operator position_type() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r),
				(-std::cos(theta + Clock()) * r) };
	}

	template <class Float, int32 Oclock>
	inline size_t CircularBase<Float, Oclock>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Float, int32 Oclock>
	inline constexpr Float CircularBase<Float, Oclock>::ClampAngle(const value_type theta) noexcept
	{
		if (theta <= -Math::Pi)
		{
			return (theta + Math::TwoPi_v<Float>);
		}
		else
		{
			return theta;
		}
	}

	template <class Float, int32 Oclock>
	inline constexpr Float CircularBase<Float, Oclock>::Clock() noexcept
	{
		return (Oclock * (Math::TwoPi_v<Float> / 12));
	}

	template <class Float, int32 Oclock>
	inline constexpr Float CircularBase<Float, Oclock>::Offset(const value_type theta) noexcept
	{
		return ClampAngle(theta - Clock());
	}
}
