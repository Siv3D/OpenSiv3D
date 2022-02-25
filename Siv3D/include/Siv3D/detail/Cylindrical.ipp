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
	inline constexpr CylindricalBase<Float>::CylindricalBase(const value_type _r, const value_type _phi, const value_type _y) noexcept
		: r{ _r }
		, phi{ _phi }
		, y{ _y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::r_<value_type> _r, const Arg::phi_<value_type> _phi, const Arg::y_<value_type> _y) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::r_<value_type> _r, const Arg::y_<value_type> _y, const Arg::phi_<value_type> _phi) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::phi_<value_type> _phi, const Arg::r_<value_type> _r, const Arg::y_<value_type> _y) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::phi_<value_type> _phi, const Arg::y_<value_type> _y, const Arg::r_<value_type> _r) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::y_<value_type> _y, const Arg::r_<value_type> _r, const Arg::phi_<value_type> _phi) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float>::CylindricalBase(const Arg::y_<value_type> _y, const Arg::phi_<value_type> _phi, const Arg::r_<value_type> _r) noexcept
		: r{ *_r }
		, phi{ *_phi }
		, y{ *_y } {}

	template <class Float>
	inline CylindricalBase<Float>::CylindricalBase(const position_type pos) noexcept
		: r{ pos.xz().length() }
		, phi{ std::atan2(pos.z, pos.x) }
		, y{ pos.y } {}

	template <class Float>
	inline constexpr CylindricalBase<Float> CylindricalBase<Float>::operator +() const noexcept
	{
		return *this;
	}

	template <class Float>
	inline constexpr CylindricalBase<Float> CylindricalBase<Float>::operator -() const noexcept
	{
		return{ r, (phi + Math::Pi), -y };
	}

	template <class Float>
	inline typename CylindricalBase<Float>::position_type CylindricalBase<Float>::operator +(const position_type v) const noexcept
	{
		return (toPosition() + v);
	}

	template <class Float>
	inline typename CylindricalBase<Float>::position_type CylindricalBase<Float>::operator -(const position_type v) const noexcept
	{
		return (toPosition() - v);
	}

	template <class Float>
	inline Float3 CylindricalBase<Float>::toFloat3() const noexcept
	{
		return{ (r * std::cos(phi)), y, (r * std::sin(phi)) };
	}

	template <class Float>
	inline Vec3 CylindricalBase<Float>::toVec3() const noexcept
	{
		return{ (r * std::cos(phi)), y, (r * std::sin(phi)) };
	}

	template <class Float>
	inline Float3 CylindricalBase<Float>::fastToFloat3() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(phi);
		return{ (r * c), y, (r * s) };
	}

	template <class Float>
	inline Vec3 CylindricalBase<Float>::fastToVec3() const noexcept
	{
		const auto [s, c] = FastMath::SinCos(phi);
		return{ (r * c), y, (r * s) };
	}

	template <class Float>
	inline typename CylindricalBase<Float>::position_type CylindricalBase<Float>::toPosition() const noexcept
	{
		return{ (r * std::cos(phi)), y, (r * std::sin(phi)) };
	}

	template <class Float>
	inline CylindricalBase<Float>::operator position_type() const noexcept
	{
		return{ (r * std::cos(phi)), y, (r * std::sin(phi)) };
	}

	template <class Float>
	inline size_t CylindricalBase<Float>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
