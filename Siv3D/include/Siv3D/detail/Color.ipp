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
	namespace detail
	{
		inline constexpr uint32 HexToDecimal(const char32 c) noexcept
		{
			return (c & 0xF) + ((c & 0x40) >> 6) * 9;
		}
	}

	inline constexpr Color::Color(const uint32 _r, const uint32 _g, const uint32 _b, const uint32 _a) noexcept
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a) {}

	inline constexpr Color::Color(const uint32 rgb, const uint32 _a) noexcept
		: r(rgb)
		, g(rgb)
		, b(rgb)
		, a(_a) {}

	inline constexpr Color::Color(const Color rgb, const uint32 _a) noexcept
		: r(rgb.r)
		, g(rgb.g)
		, b(rgb.b)
		, a(_a) {}

	inline constexpr Color::Color(const ColorF& color) noexcept
		: r(Color::ToUint8(color.r))
		, g(Color::ToUint8(color.g))
		, b(Color::ToUint8(color.b))
		, a(Color::ToUint8(color.a)) {}

	inline constexpr Color::Color(const ColorF& color, const uint32 _a) noexcept
		: r(Color::ToUint8(color.r))
		, g(Color::ToUint8(color.g))
		, b(Color::ToUint8(color.b))
		, a(_a) {}

	inline Color::Color(const HSV& hsv) noexcept
	{
		*this = hsv.toColor();
	}

	inline Color::Color(const HSV& hsv, const uint32 _a) noexcept
	{
		*this = hsv.toColor(_a);
	}

	inline constexpr Color::Color(const StringView code) noexcept
		: r(0)
		, g(0)
		, b(0)
		, a(255)
	{
		if (code.length() == 4 || code.length() == 5)
		{
			r = detail::HexToDecimal(code[1]) * 17;
			g = detail::HexToDecimal(code[2]) * 17;
			b = detail::HexToDecimal(code[3]) * 17;
			a = code.length() == 5 ? detail::HexToDecimal(code[4]) * 17 : 255;
		}
		else if (code.length() == 7 || code.length() == 9)
		{
			r = detail::HexToDecimal(code[1]) * 16 + detail::HexToDecimal(code[2]);
			g = detail::HexToDecimal(code[3]) * 16 + detail::HexToDecimal(code[4]);
			b = detail::HexToDecimal(code[5]) * 16 + detail::HexToDecimal(code[6]);
			a = code.length() == 9 ? (detail::HexToDecimal(code[7]) * 16 + detail::HexToDecimal(code[8])) : 255;
		}
	}

	inline constexpr Color& Color::operator =(const ColorF& color) noexcept
	{
		return *this = color.toColor();
	}

	inline Color& Color::operator =(const HSV& hsva) noexcept
	{
		return *this = hsva.toColor();
	}

	inline constexpr Color Color::operator ~() const noexcept
	{
		return{ static_cast<uint8>(~r),
				static_cast<uint8>(~g),
				static_cast<uint8>(~b),
				a };
	}

	inline constexpr Color& Color::setR(const uint32 _r) noexcept
	{
		r = _r;
		return *this;
	}

	inline constexpr Color& Color::setG(const uint32 _g) noexcept
	{
		g = _g;
		return *this;
	}

	inline constexpr Color& Color::setB(const uint32 _b) noexcept
	{
		b = _b;
		return *this;
	}

	inline constexpr Color& Color::setA(const uint32 _a) noexcept
	{
		a = _a;
		return *this;
	}

	inline constexpr Color& Color::setRGB(const uint32 rgb) noexcept
	{
		r = rgb;
		g = rgb;
		b = rgb;
		return *this;
	}

	inline constexpr Color& Color::setRGB(const uint32 _r, const uint32 _g, const uint32 _b) noexcept
	{
		r = _r;
		g = _g;
		b = _b;
		return *this;
	}

	inline constexpr Color& Color::set(const uint32 rgb, const uint32 _a) noexcept
	{
		r = rgb;
		g = rgb;
		b = rgb;
		a = _a;
		return *this;
	}

	inline constexpr Color& Color::set(const uint32 _r, const uint32 _g, const uint32 _b, const uint32 _a) noexcept
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
		return *this;
	}

	inline constexpr Color& Color::set(const Color color) noexcept
	{
		return *this = color;
	}

	inline constexpr Color Color::withAlpha(const uint32 _a) const noexcept
	{
		return{ r, g, b, _a };
	}

	inline constexpr uint8 Color::grayscale0_255() const noexcept
	{
		return static_cast<uint8>(0.299 * r + 0.587 * g + 0.114 * b);
	}

	inline constexpr double Color::grayscale() const noexcept
	{
		return (0.299 / 255.0 * r) + (0.587 / 255.0 * g) + (0.114 / 255.0 * b);
	}

	inline constexpr uint8 Color::minRGBComponent() const noexcept
	{
		return Min({ static_cast<uint8>(r), static_cast<uint8>(g), static_cast<uint8>(b) });
	}

	inline constexpr uint8 Color::maxRGBComponent() const noexcept
	{
		return Max({ static_cast<uint8>(r), static_cast<uint8>(g), static_cast<uint8>(b) });
	}

	inline constexpr uint8 Color::minComponent() const noexcept
	{
		return Min({ static_cast<uint8>(r), static_cast<uint8>(g), static_cast<uint8>(b), static_cast<uint8>(a) });
	}

	inline constexpr uint8 Color::maxComponent() const noexcept
	{
		return Max({ static_cast<uint8>(r), static_cast<uint8>(g), static_cast<uint8>(b), static_cast<uint8>(a) });
	}

	inline constexpr uint32 Color::asUint32() const noexcept
	{
		# if __cpp_lib_is_constant_evaluated
			if (std::is_constant_evaluated()) // MSVC workaround
			{
				return ((a << 24) | (b << 16) | (g << 8) | r);
			}
			else
			{
			# if __cpp_lib_bit_cast
				return std::bit_cast<uint32>(*this);
			# else
				return *static_cast<const uint32*>(static_cast<const void*>(this));
			# endif
			}
		# else
			# if __cpp_lib_bit_cast
				return std::bit_cast<uint32>(*this);
			# else
				return *static_cast<const uint32*>(static_cast<const void*>(this));
			# endif
		# endif
	}

	inline constexpr Color Color::lerp(const Color other, const double f) const noexcept
	{
		return{ static_cast<uint32>(int32(r) + (int32(other.r) - int32(r)) * f),
				static_cast<uint32>(int32(g) + (int32(other.g) - int32(g)) * f),
				static_cast<uint32>(int32(b) + (int32(other.b) - int32(b)) * f),
				static_cast<uint32>(int32(a) + (int32(other.a) - int32(a)) * f) };
	}

	inline Color Color::gamma(const double gamma) const noexcept
	{
		if (gamma <= 0.0)
		{
			return{ 0, 0, 0, a };
		}

		const double ig = 1.0 / gamma;

		return{ static_cast<uint32>(std::pow(r / 255.0, ig)),
				static_cast<uint32>(std::pow(g / 255.0, ig)),
				static_cast<uint32>(std::pow(b / 255.0, ig)),
				a };
	}

	inline String Color::toHex() const
	{
		const uint32 rgb = ((r << 16) | (g << 8) | b);
		return U"{:0>6X}"_fmt(rgb);
	}

	inline size_t Color::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Color Color::Zero() noexcept
	{
		return{ 0, 0, 0, 0 };
	}

	inline constexpr uint8 Color::ToUint8(const float x) noexcept
	{
		if (x >= 1.0)
		{
			return 255;
		}
		else if (x <= 0.0)
		{
			return 0;
		}
		else
		{
			return static_cast<uint8>(x * 255.0 + 0.5);
		}
	}

	inline constexpr uint8 Color::ToUint8(const double x) noexcept
	{
		if (x >= 1.0)
		{
			return 255;
		}
		else if (x <= 0.0)
		{
			return 0;
		}
		else
		{
			return static_cast<uint8>(x * 255.0 + 0.5);
		}
	}

	inline constexpr Color Color::FromRGBA(const uint32 rgba) noexcept
	{
		return{ (rgba >> 24) & 0xFF,
				(rgba >> 16) & 0xFF,
				(rgba >>  8) & 0xFF,
				        rgba & 0xFF };
	}

	inline constexpr Color Color::FromABGR(const uint32 abgr) noexcept
	{
		return{         abgr & 0xFF,
				(abgr >>  8) & 0xFF,
				(abgr >> 16) & 0xFF,
				(abgr >> 24) & 0xFF };
	}

	inline constexpr Color Alpha(const uint32 alpha) noexcept
	{
		return Color{ 255, alpha };
	}

	inline constexpr Color ToColor(const float rgb) noexcept
	{
		return Color{ Color::ToUint8(rgb) };
	}

	inline constexpr Color ToColor(const double rgb) noexcept
	{
		return Color{ Color::ToUint8(rgb) };
	}
}
