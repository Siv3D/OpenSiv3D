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
	inline constexpr ColorF::ColorF(const double _r, const double _g, const double _b, const double _a) noexcept
		: r{ _r }
		, g{ _g }
		, b{ _b }
		, a{ _a } {}

	inline constexpr ColorF::ColorF(const double rgb, const double _a) noexcept
		: r{ rgb }
		, g{ rgb }
		, b{ rgb }
		, a{ _a } {}

	inline constexpr ColorF::ColorF(const ColorF& rgb, const double _a) noexcept
		: r{ rgb.r }
		, g{ rgb.g }
		, b{ rgb.b }
		, a{ _a } {}

	inline constexpr ColorF::ColorF(const Vec3& rgb, const double _a) noexcept
		: r{ rgb.x }
		, g{ rgb.y }
		, b{ rgb.z }
		, a{ _a } {}

	inline constexpr ColorF::ColorF(const Vec4& rgba) noexcept
		: r{ rgba.x }
		, g{ rgba.y }
		, b{ rgba.z }
		, a{ rgba.w } {}

	inline constexpr ColorF::ColorF(const Color color) noexcept
		: r{ color.r / 255.0 }
		, g{ color.g / 255.0 }
		, b{ color.b / 255.0 }
		, a{ color.a / 255.0 } {}

	inline constexpr ColorF::ColorF(const Color rgb, const double _a) noexcept
		: r{ rgb.r / 255.0 }
		, g{ rgb.g / 255.0 }
		, b{ rgb.b / 255.0 }
		, a{ _a } {}

	inline ColorF::ColorF(const HSV& hsva) noexcept
	{
		*this = hsva.toColorF();
	}

	inline ColorF::ColorF(const HSV& hsv, const double _a) noexcept
	{
		*this = hsv.toColorF(_a);
	}

	inline constexpr ColorF::ColorF(const StringView code) noexcept
		: ColorF{ Color{code} } {}

	inline constexpr double ColorF::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return r;
		}
		else if (index == 1)
		{
			return g;
		}
		else if (index == 2)
		{
			return b;
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

	inline double* ColorF::getPointer() noexcept
	{
		return &r;
	}

	inline const double* ColorF::getPointer() const noexcept
	{
		return &r;
	}

	inline constexpr ColorF& ColorF::operator =(const Color color) noexcept
	{
		r = color.r / 255.0;
		g = color.g / 255.0;
		b = color.b / 255.0;
		a = color.a / 255.0;
		return *this;
	}

	inline ColorF& ColorF::operator =(const HSV& hsva) noexcept
	{
		return *this = hsva.toColorF();
	}

	inline constexpr ColorF ColorF::operator +(const ColorF& rgb) const noexcept
	{
		return{ r + rgb.r, g + rgb.g, b + rgb.b, a };
	}

	inline constexpr ColorF& ColorF::operator +=(const ColorF& rgb) noexcept
	{
		r += rgb.r;
		g += rgb.g;
		b += rgb.b;
		return *this;
	}

	inline constexpr ColorF ColorF::operator -(const ColorF& rgb) const noexcept
	{
		return{ r - rgb.r, g - rgb.g, b - rgb.b, a };
	}

	inline constexpr ColorF& ColorF::operator -=(const ColorF& rgb) noexcept
	{
		r -= rgb.r;
		g -= rgb.g;
		b -= rgb.b;
		return *this;
	}

	inline constexpr ColorF ColorF::operator *(const double s) const noexcept
	{
		return{ r * s, g * s, b * s, a };
	}

	inline constexpr ColorF& ColorF::operator *=(const double s) noexcept
	{
		r *= s;
		g *= s;
		b *= s;
		return *this;
	}

	inline constexpr ColorF ColorF::operator *(const ColorF& rgba) const noexcept
	{
		return{ r * rgba.r, g * rgba.g, b * rgba.b, a * rgba.a };
	}

	inline constexpr ColorF& ColorF::operator *=(const ColorF& rgba) noexcept
	{
		r *= rgba.r;
		g *= rgba.g;
		b *= rgba.b;
		a *= rgba.a;
		return *this;
	}

	inline constexpr ColorF& ColorF::setR(const double _r) noexcept
	{
		r = _r;
		return *this;
	}

	inline constexpr ColorF& ColorF::setG(const double _g) noexcept
	{
		g = _g;
		return *this;
	}

	inline constexpr ColorF& ColorF::setB(const double _b) noexcept
	{
		b = _b;
		return *this;
	}

	inline constexpr ColorF& ColorF::setA(const double _a) noexcept
	{
		a = _a;
		return *this;
	}

	inline constexpr ColorF& ColorF::setRGB(const double rgb) noexcept
	{
		r = rgb;
		g = rgb;
		b = rgb;
		return *this;
	}

	inline constexpr ColorF& ColorF::setRGB(const double _r, const double _g, const double _b) noexcept
	{
		r = _r;
		g = _g;
		b = _b;
		return *this;
	}

	inline constexpr ColorF& ColorF::set(const double rgb, const double _a) noexcept
	{
		r = rgb;
		g = rgb;
		b = rgb;
		a = _a;
		return *this;
	}

	inline constexpr ColorF& ColorF::set(const double _r, const double _g, const double _b, const double _a) noexcept
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
		return *this;
	}

	inline constexpr ColorF& ColorF::set(const ColorF& color) noexcept
	{
		return *this = color;
	}

	inline constexpr ColorF ColorF::withAlpha(const double _a) const noexcept
	{
		return{ r, g, b, _a };
	}

	inline constexpr double ColorF::grayscale() const noexcept
	{
		return (0.299 * r) + (0.587 * g) + (0.114 * b);
	}

	inline constexpr double ColorF::minRGBComponent() const noexcept
	{
		return Min({ r, g, b });
	}

	inline constexpr double ColorF::maxRGBComponent() const noexcept
	{
		return Max({ r, g, b });
	}

	inline constexpr double ColorF::minComponent() const noexcept
	{
		return Min({ r, g, b ,a });
	}

	inline constexpr double ColorF::maxComponent() const noexcept
	{
		return Max({ r, g, b ,a });
	}

	inline constexpr ColorF ColorF::lerp(const ColorF& other, const double f) const noexcept
	{
		return{ r + (other.r - r) * f,
				g + (other.g - g) * f,
				b + (other.b - b) * f,
				a + (other.a - a) * f };
	}

	inline ColorF ColorF::gamma(const double gamma) const noexcept
	{
		if (gamma <= 0.0)
		{
			return{ 0.0, 0.0, 0.0, a };
		}

		const double ig = 1.0 / gamma;

		return{ std::pow(r, ig), std::pow(g, ig), std::pow(b, ig), a };
	}

	inline size_t ColorF::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Color ColorF::toColor() const noexcept
	{
		return{ Color::ToUint8(r),
				Color::ToUint8(g),
				Color::ToUint8(b),
				Color::ToUint8(a) };
	}

	inline constexpr Float4 ColorF::toFloat4() const noexcept
	{
		return{ r, g, b, a };
	}

	inline constexpr Vec4 ColorF::toVec4() const noexcept
	{
		return{ r, g, b, a };
	}

	inline constexpr Vec2 ColorF::rg() const noexcept
	{
		return{ r, g };
	}

	inline constexpr Vec2 ColorF::gb() const noexcept
	{
		return{ g, b };
	}

	inline constexpr Vec2 ColorF::ba() const noexcept
	{
		return{ b, a };
	}

	inline constexpr Vec3 ColorF::rgb() const noexcept
	{
		return{ r, g, b };
	}

	inline constexpr Vec3 ColorF::gba() const noexcept
	{
		return{ g, b, a };
	}

	inline constexpr Vec3 ColorF::bgr() const noexcept
	{
		return{ b, g, r };
	}

	inline constexpr Vec4 ColorF::rgba() const noexcept
	{
		return{ r, g, b, a };
	}

	inline constexpr Vec4 ColorF::rgb0() const noexcept
	{
		return{ r, g, b, 0.0 };
	}

	inline constexpr Vec4 ColorF::rgb1() const noexcept
	{
		return{ r, g, b, 1.0 };
	}

	inline constexpr Vec4 ColorF::argb() const noexcept
	{
		return{ a, r, g, b };
	}

	inline constexpr Vec4 ColorF::abgr() const noexcept
	{
		return{ a, b, g, r };
	}

	inline constexpr ColorF ColorF::Zero() noexcept
	{
		return{ 0.0, 0.0, 0.0, 0.0 };
	}

	inline constexpr ColorF ColorF::One() noexcept
	{
		return{ 1.0, 1.0, 1.0, 1.0 };
	}

	inline constexpr ColorF AlphaF(const double alpha) noexcept
	{
		return ColorF{ 1.0, alpha };
	}

	inline constexpr ColorF Transparency(const double transparency) noexcept
	{
		return ColorF{ 1.0, (1.0 - transparency) };
	}
}
