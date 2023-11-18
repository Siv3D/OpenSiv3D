//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr HSV::HSV(const double _h, const double _a) noexcept
		: h{ _h }
		, s{ 1.0 }
		, v{ 1.0 }
		, a{ _a } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr HSV::HSV(const Arithmetic _h, const double _a) noexcept
		: h{ static_cast<double>(_h) }
		, s{ 1.0 }
		, v{ 1.0 }
		, a{ _a } {}

	inline constexpr HSV::HSV(const double _h, const double _s, const double _v, const double _a) noexcept
		: h{ _h }
		, s{ _s }
		, v{ _v }
		, a{ _a } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr HSV::HSV(const Arithmetic _h, const double _s, const double _v, const double _a) noexcept
		: h{ static_cast<double>(_h) }
		, s{ _s }
		, v{ _v }
		, a{ _a } {}

	inline constexpr HSV::HSV(const HSV& hsv, const double _a) noexcept
		: h{ hsv.h }
		, s{ hsv.s }
		, v{ hsv.v }
		, a{ _a } {}

	inline constexpr double HSV::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return h;
		}
		else if (index == 1)
		{
			return s;
		}
		else if (index == 2)
		{
			return v;
		}
		else if (index == 3)
		{
			return a;
		}
		else
		{
			return 0;
		}
	}

	inline double* HSV::getPointer() noexcept
	{
		return &h;
	}

	inline const double* HSV::getPointer() const noexcept
	{
		return &h;
	}

	inline constexpr HSV HSV::operator +(const HSV& hsv) const noexcept
	{
		return{ h + hsv.h, Clamp(s + hsv.s, 0.0, 1.0), Clamp(v + hsv.v, 0.0, 1.0), a };
	}

	inline constexpr HSV HSV::operator -(const HSV& hsv) const noexcept
	{
		return{ h - hsv.h, Clamp(s - hsv.s, 0.0, 1.0), Clamp(v - hsv.v, 0.0, 1.0), a };
	}

	inline constexpr HSV HSV::withH(const double _h) const noexcept
	{
		return{ _h, s, v, a };
	}

	inline constexpr HSV HSV::withS(const double _s) const noexcept
	{
		return{ h, _s, v, a };
	}

	inline constexpr HSV HSV::withV(const double _v) const noexcept
	{
		return{ h, s, _v, a };
	}

	inline constexpr HSV HSV::withA(const double _a) const noexcept
	{
		return{ h, s, v, _a };
	}

	inline constexpr HSV& HSV::setH(const double _h) noexcept
	{
		h = _h;
		return *this;
	}

	inline constexpr HSV& HSV::setS(const double _s) noexcept
	{
		s = _s;
		return *this;
	}

	inline constexpr HSV& HSV::setV(const double _v) noexcept
	{
		v = _v;
		return *this;
	}

	inline constexpr HSV& HSV::setA(const double _a) noexcept
	{
		a = _a;
		return *this;
	}

	inline constexpr HSV& HSV::setHSV(const double _h, const double _s, const double _v) noexcept
	{
		h = _h;
		s = _s;
		v = _v;
		return *this;
	}

	inline constexpr HSV& HSV::set(const double _h, const double _s, const double _v, const double _a) noexcept
	{
		h = _h;
		s = _s;
		v = _v;
		a = _a;
		return *this;
	}

	inline constexpr HSV& HSV::set(const HSV& hsva) noexcept
	{
		return *this = hsva;
	}

	inline constexpr HSV HSV::withAlpha(const double _a) const noexcept
	{
		return{ h, s, v, _a };
	}

	inline constexpr HSV HSV::lerp(const HSV& other, const double f) const noexcept
	{
		return{ h + (other.h - h) * f,
				s + (other.s - s) * f,
				v + (other.v - v) * f,
				a + (other.a - a) * f };
	}

	inline size_t HSV::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Vec3 HSV::hsv() const noexcept
	{
		return{ h, s, v };
	}

	inline constexpr Vec4 HSV::hsva() const noexcept
	{
		return{ h, s, v, a };
	}

	inline constexpr HSV HSV::Zero() noexcept
	{
		return{ 0.0, 0.0, 0.0, 0.0 };
	}
}
