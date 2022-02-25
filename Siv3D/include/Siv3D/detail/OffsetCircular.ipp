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
	inline constexpr OffsetCircularBase<Float, Oclock>::OffsetCircularBase(const position_type& _center, const value_type _r, const value_type _theta) noexcept
		: center{ _center }
		, r{ _r }
		, theta{ _theta } {}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>::OffsetCircularBase(const position_type& _center, const Arg::r_<value_type> _r, const Arg::theta_<value_type> _theta) noexcept
		: center{ _center }
		, r{ *_r }
		, theta{ *_theta } {}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>::OffsetCircularBase(const position_type& _center, const Arg::theta_<value_type> _theta, const Arg::r_<value_type> _r) noexcept
		: center{ _center }
		, r{ *_r }
		, theta{ *_theta } {}

	template <class Float, int32 Oclock>
	inline OffsetCircularBase<Float, Oclock>::OffsetCircularBase(const position_type& _center, const position_type& target) noexcept
		: center{ _center }
	{
		setTarget(target);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock> OffsetCircularBase<Float, Oclock>::operator +(const position_type v) const noexcept
	{
		return movedBy(v);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock> OffsetCircularBase<Float, Oclock>::operator -(const position_type v) const noexcept
	{
		return movedBy(-v);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::operator +=(const position_type v) noexcept
	{
		return moveBy(v);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::operator -=(const position_type v) noexcept
	{
		return moveBy(-v);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock> OffsetCircularBase<Float, Oclock>::movedBy(const value_type x, const value_type y) const noexcept
	{
		return movedBy(Vec2{ x, y });
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock> OffsetCircularBase<Float, Oclock>::movedBy(const position_type v) const noexcept
	{
		return OffsetCircularBase{ *this }.moveBy(v);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::moveBy(const value_type x, const value_type y) noexcept
	{
		return moveBy(Vec2{ x, y });
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);

		return *this;
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::setCenter(const value_type x, const value_type y) noexcept
	{
		return setCenter(Vec2{ x, y });
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::setCenter(const position_type _center) noexcept
	{
		center = _center;

		return *this;
	}

	template <class Float, int32 Oclock>
	inline OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::setTarget(const value_type x, const value_type y) noexcept
	{
		return setTarget(Vec2{ x, y });
	}

	template <class Float, int32 Oclock>
	inline OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::setTarget(const position_type target) noexcept
	{
		const Vec2 v = (target - center);

		r = v.length();

		theta = Offset(std::atan2(v.x, -v.y));

		return *this;
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock> OffsetCircularBase<Float, Oclock>::rotated(const value_type angle) const noexcept
	{
		return OffsetCircularBase{ *this }.rotate(angle);
	}

	template <class Float, int32 Oclock>
	inline constexpr OffsetCircularBase<Float, Oclock>& OffsetCircularBase<Float, Oclock>::rotate(const value_type angle) noexcept
	{
		theta += angle;

		return *this;
	}

	template <class Float, int32 Oclock>
	inline Float2 OffsetCircularBase<Float, Oclock>::toFloat2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r + center.x),
				(-std::cos(theta + Clock()) * r + center.y) };
	}

	template <class Float, int32 Oclock>
	inline Vec2 OffsetCircularBase<Float, Oclock>::toVec2() const noexcept
	{
		return{ (std::sin(theta + Clock()) * r + center.x),
				(-std::cos(theta + Clock()) * r + center.y) };
	}

	template <class Float, int32 Oclock>
	inline Float2 OffsetCircularBase<Float, Oclock>::fastToFloat2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r + center.x), (-c * r + center.y) };
	}

	template <class Float, int32 Oclock>
	inline Vec2 OffsetCircularBase<Float, Oclock>::fastToVec2() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(theta + Clock());
		return{ (s * r + center.x), (-c * r + center.y) };
	}

	template <class Float, int32 Oclock>
	inline typename OffsetCircularBase<Float, Oclock>::position_type OffsetCircularBase<Float, Oclock>::toPosition() const noexcept
	{
		return toVec2();
	}

	template <class Float, int32 Oclock>
	inline OffsetCircularBase<Float, Oclock>::operator position_type() const noexcept
	{
		return toVec2();
	}

	template <class Float, int32 Oclock>
	inline size_t OffsetCircularBase<Float, Oclock>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Float, int32 Oclock>
	constexpr typename OffsetCircularBase<Float, Oclock>::value_type OffsetCircularBase<Float, Oclock>::ClampAngle(const value_type theta) noexcept
	{
		if (theta <= -Math::Pi)
		{
			return (theta + Math::TwoPi);
		}
		else
		{
			return theta;
		}
	}

	template <class Float, int32 Oclock>
	constexpr typename OffsetCircularBase<Float, Oclock>::value_type OffsetCircularBase<Float, Oclock>::Clock() noexcept
	{
		return (Oclock * (Math::TwoPi / 12));
	}

	template <class Float, int32 Oclock>
	constexpr typename OffsetCircularBase<Float, Oclock>::value_type OffsetCircularBase<Float, Oclock>::Offset(value_type theta) noexcept
	{
		return ClampAngle(theta - Clock());
	}
}
