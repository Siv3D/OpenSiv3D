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
	namespace detail
	{
		inline static double Fraction(const double x) noexcept
		{
			return (x - std::floor(x));
		}

		inline constexpr uint8 HSVConversionTable[6][3] =
		{
			{ 3, 2, 0 },
			{ 1, 3, 0 },
			{ 0, 3, 2 },
			{ 0, 1, 3 },
			{ 2, 0, 3 },
			{ 3, 0, 1 },
		};

		//
		// http://lol.zoy.org/blog/2013/01/13/fast-rgb-to-hsv
		//
		inline HSV RGBAToHSV(double r, double g, double b, double a) noexcept
		{
			double K = 0.0;

			if (g < b)
			{
				std::swap(g, b);
				K = -360.0;
			}

			if (r < g)
			{
				std::swap(r, g);
				K = -720.0 / 6.0 - K;
			}

			const double delta = (g - b) * (360.0 / 6.0);
			const double chroma = r - Min(g, b);
			return HSV(Abs(K + delta / (chroma + 1e-20)), chroma / (r + 1e-20), r, a);
		}
	}

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

	inline HSV::HSV(const Color color) noexcept
	{
		*this = detail::RGBAToHSV(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	}

	inline HSV::HSV(const ColorF& color) noexcept
	{
		*this = detail::RGBAToHSV(color.r, color.g, color.b, color.a);
	}

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

	inline ColorF HSV::removeSRGBCurve() const noexcept
	{
		return toColorF().removeSRGBCurve();
	}

	inline ColorF HSV::applySRGBCurve() const noexcept
	{
		return toColorF().applySRGBCurve();
	}

	inline Color HSV::toColor() const noexcept
	{
		return toColor(Color::ToUint8(a));
	}

	inline Color HSV::toColor(const uint32 alpha) const noexcept
	{
		const double hue01	= detail::Fraction(h / 360.0);
		const double hueF	= (hue01 * 6.0);
		const int32 hueI	= static_cast<int32>(hueF);
		const double fr		= (hueF - hueI);
		const uint8 vals[4] =
		{
			static_cast<uint8>(v * (1.0 - s) * 255.0 + 0.5),
			static_cast<uint8>(v * (1.0 - s * fr) * 255.0 + 0.5),
			static_cast<uint8>(v * (1.0 - s * (1.0 - fr)) * 255.0 + 0.5),
			static_cast<uint8>(v * 255.0 + 0.5)
		};

		return{ vals[detail::HSVConversionTable[hueI][0]],
				vals[detail::HSVConversionTable[hueI][1]],
				vals[detail::HSVConversionTable[hueI][2]],
				static_cast<uint8>(alpha) };
	}

	inline ColorF HSV::toColorF() const noexcept
	{
		return toColorF(a);
	}

	inline ColorF HSV::toColorF(const double alpha) const noexcept
	{
		const double hue01	= detail::Fraction(h / 360.0);
		const double hueF	= (hue01 * 6.0);
		const int32 hueI	= static_cast<int32>(hueF);
		const double fr		= (hueF - hueI);
		const double vals[4] =
		{
			v * (1.0 - s),
			v * (1.0 - s * fr),
			v * (1.0 - s * (1.0 - fr)),
			v
		};

		return{ vals[detail::HSVConversionTable[hueI][0]],
				vals[detail::HSVConversionTable[hueI][1]],
				vals[detail::HSVConversionTable[hueI][2]],
				alpha };
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

	inline Color HueToColor(const double hue) noexcept
	{
		const double hue01	= detail::Fraction(hue / 360.0);
		const double hueF	= (hue01 * 6.0);
		const int32 hueI	= static_cast<int32>(hueF);
		const double fr		= (hueF - hueI);
		const uint8 vals[4] =
		{
			0,
			static_cast<uint8>((1.0 - fr) * 255.0 + 0.5),
			static_cast<uint8>((1.0 - (1.0 - fr)) * 255.0 + 0.5),
			255
		};

		return{ vals[detail::HSVConversionTable[hueI][0]],
				vals[detail::HSVConversionTable[hueI][1]],
				vals[detail::HSVConversionTable[hueI][2]],
				255 };
	}

	inline ColorF HueToColorF(const double hue) noexcept
	{
		const double hue01	= detail::Fraction(hue / 360.0);
		const double hueF	= (hue01 * 6.0);
		const int32 hueI	= static_cast<int32>(hueF);
		const double fr		= (hueF - hueI);
		const double vals[4] =
		{
			0.0,
			1.0 - fr,
			1.0 - (1.0 - fr),
			1.0
		};

		return{ vals[detail::HSVConversionTable[hueI][0]],
				vals[detail::HSVConversionTable[hueI][1]],
				vals[detail::HSVConversionTable[hueI][2]],
				1.0 };
	}
}
