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
	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const value_type _r, const value_type _theta, const value_type _phi) noexcept
		: r{ _r }
		, theta{ _theta }
		, phi{ _phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::r_<value_type> _r, const Arg::theta_<value_type> _theta, const Arg::phi_<value_type> _phi) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::r_<value_type> _r, const Arg::phi_<value_type> _phi, const Arg::theta_<value_type> _theta) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::theta_<value_type> _theta, const Arg::r_<value_type> _r, const Arg::phi_<value_type> _phi) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::theta_<value_type> _theta, const Arg::phi_<value_type> _phi, const Arg::r_<value_type> _r) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::phi_<value_type> _phi, const Arg::r_<value_type> _r, const Arg::theta_<value_type> _theta) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline constexpr SphericalBase<Float>::SphericalBase(const Arg::phi_<value_type> _phi, const Arg::theta_<value_type> _theta, const Arg::r_<value_type> _r) noexcept
		: r{ *_r }
		, theta{ *_theta }
		, phi{ *_phi } {}

	template <class Float>
	inline SphericalBase<Float>::SphericalBase(const position_type pos) noexcept
		: r{ pos.length() }
		, theta{ std::acos(pos.y / r) }
		, phi{ std::atan2(pos.z, pos.x) } {}

	template <class Float>
	inline constexpr SphericalBase<Float> SphericalBase<Float>::operator +() const noexcept
	{
		return *this;
	}

	template <class Float>
	inline constexpr SphericalBase<Float> SphericalBase<Float>::operator -() const noexcept
	{
		return{ r, (theta + Math::Pi), (phi + Math::Pi) };
	}

	template <class Float>
	inline typename SphericalBase<Float>::position_type SphericalBase<Float>::operator +(const position_type v) const noexcept
	{
		return (toPosition() + v);
	}

	template <class Float>
	inline typename SphericalBase<Float>::position_type SphericalBase<Float>::operator -(const position_type v) const noexcept
	{
		return (toPosition() - v);
	}

	template <class Float>
	inline Float3 SphericalBase<Float>::toFloat3() const noexcept
	{
		const auto s = std::sin(theta);
		return{ (r * s * std::cos(phi)), (r * std::cos(theta)), (r * s * std::sin(phi)) };
	}

	template <class Float>
	inline Vec3 SphericalBase<Float>::toVec3() const noexcept
	{
		const auto s = std::sin(theta);
		return{ (r * s * std::cos(phi)), (r * std::cos(theta)), (r * s * std::sin(phi)) };
	}

	template <class Float>
	inline Float3 SphericalBase<Float>::fastToFloat3() const noexcept
	{
		const auto [ts, tc] = FastMath::SinCos(theta);
		const auto [ps, pc] = FastMath::SinCos(phi);
		return{ (r * ts * pc), (r * tc), (r * ts * ps) };
	}

	template <class Float>
	inline Vec3 SphericalBase<Float>::fastToVec3() const noexcept
	{
		const auto [ts, tc] = FastMath::SinCos(theta);
		const auto [ps, pc] = FastMath::SinCos(phi);
		return{ (r * ts * pc), (r * tc), (r * ts * ps) };
	}

	template <class Float>
	inline typename SphericalBase<Float>::position_type SphericalBase<Float>::toPosition() const noexcept
	{
		const auto s = std::sin(theta);
		return{ (r * s * std::cos(phi)), (r * std::cos(theta)), (r * s * std::sin(phi)) };
	}

	template <class Float>
	inline SphericalBase<Float>::operator position_type() const noexcept
	{
		const auto s = std::sin(theta);
		return{ (r * s * std::cos(phi)), (r * std::cos(theta)), (r * s * std::sin(phi)) };
	}

	template <class Float>
	inline size_t SphericalBase<Float>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
