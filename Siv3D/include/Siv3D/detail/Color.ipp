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
		inline constexpr uint32 HexToDecimal(const char32 c) noexcept
		{
			return (c & 0xF) + ((c & 0x40) >> 6) * 9;
		}
	}

	inline constexpr Color::Color(const value_type _r, const value_type _g, const value_type _b, const value_type _a) noexcept
		: r{ _r }
		, g{ _g }
		, b{ _b }
		, a{ _a } {}

	inline constexpr Color::Color(const value_type rgb, const value_type _a) noexcept
		: r{ rgb }
		, g{ rgb }
		, b{ rgb }
		, a{ _a } {}

	inline constexpr Color::Color(const Color rgb, const value_type _a) noexcept
		: r{ rgb.r }
		, g{ rgb.g }
		, b{ rgb.b }
		, a{ _a } {}

	inline constexpr Color::Color(const ColorF& color) noexcept
		: r{ Color::ToUint8(color.r) }
		, g{ Color::ToUint8(color.g) }
		, b{ Color::ToUint8(color.b) }
		, a{ Color::ToUint8(color.a) } {}

	inline constexpr Color::Color(const ColorF& color, const value_type _a) noexcept
		: r{ Color::ToUint8(color.r) }
		, g{ Color::ToUint8(color.g) }
		, b{ Color::ToUint8(color.b) }
		, a{ _a } {}

	inline Color::Color(const HSV& hsv) noexcept
	{
		*this = hsv.toColor();
	}

	inline Color::Color(const HSV& hsv, const value_type _a) noexcept
	{
		*this = hsv.toColor(_a);
	}

	inline constexpr Color::Color(const StringView code) noexcept
		: r{ 0 }
		, g{ 0 }
		, b{ 0 }
		, a{ 255 }
	{
		if (code.length() == 4 || code.length() == 5)
		{
			r = static_cast<uint8>(detail::HexToDecimal(code[1]) * 17);
			g = static_cast<uint8>(detail::HexToDecimal(code[2]) * 17);
			b = static_cast<uint8>(detail::HexToDecimal(code[3]) * 17);
			a = static_cast<uint8>((code.length() == 5) ? detail::HexToDecimal(code[4]) * 17 : 255);
		}
		else if (code.length() == 7 || code.length() == 9)
		{
			r = static_cast<uint8>(detail::HexToDecimal(code[1]) * 16 + detail::HexToDecimal(code[2]));
			g = static_cast<uint8>(detail::HexToDecimal(code[3]) * 16 + detail::HexToDecimal(code[4]));
			b = static_cast<uint8>(detail::HexToDecimal(code[5]) * 16 + detail::HexToDecimal(code[6]));
			a = static_cast<uint8>((code.length() == 9) ? (detail::HexToDecimal(code[7]) * 16 + detail::HexToDecimal(code[8])) : 255);
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
		r = static_cast<uint8>(_r);
		return *this;
	}

	inline constexpr Color& Color::setG(const uint32 _g) noexcept
	{
		g = static_cast<uint8>(_g);
		return *this;
	}

	inline constexpr Color& Color::setB(const uint32 _b) noexcept
	{
		b = static_cast<uint8>(_b);
		return *this;
	}

	inline constexpr Color& Color::setA(const uint32 _a) noexcept
	{
		a = static_cast<uint8>(_a);
		return *this;
	}

	inline constexpr Color& Color::setRGB(const uint32 rgb) noexcept
	{
		r = static_cast<uint8>(rgb);
		g = static_cast<uint8>(rgb);
		b = static_cast<uint8>(rgb);
		return *this;
	}

	inline constexpr Color& Color::setRGB(const uint32 _r, const uint32 _g, const uint32 _b) noexcept
	{
		r = static_cast<uint8>(_r);
		g = static_cast<uint8>(_g);
		b = static_cast<uint8>(_b);
		return *this;
	}

	inline constexpr Color& Color::set(const uint32 rgb, const uint32 _a) noexcept
	{
		r = static_cast<uint8>(rgb);
		g = static_cast<uint8>(rgb);
		b = static_cast<uint8>(rgb);
		a = static_cast<uint8>(_a);
		return *this;
	}

	inline constexpr Color& Color::set(const uint32 _r, const uint32 _g, const uint32 _b, const uint32 _a) noexcept
	{
		r = static_cast<uint8>(_r);
		g = static_cast<uint8>(_g);
		b = static_cast<uint8>(_b);
		a = static_cast<uint8>(_a);
		return *this;
	}

	inline constexpr Color& Color::set(const Color color) noexcept
	{
		return *this = color;
	}

	inline constexpr Color Color::withAlpha(const uint32 _a) const noexcept
	{
		return{ r, g, b, static_cast<uint8>(_a) };
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
		return{ static_cast<uint8>(int32(r) + (int32(other.r) - int32(r)) * f),
				static_cast<uint8>(int32(g) + (int32(other.g) - int32(g)) * f),
				static_cast<uint8>(int32(b) + (int32(other.b) - int32(b)) * f),
				static_cast<uint8>(int32(a) + (int32(other.a) - int32(a)) * f) };
	}

	inline Color Color::gamma(const double gamma) const noexcept
	{
		if (gamma <= 0.0)
		{
			return{ 0, 0, 0, a };
		}

		const double ig = 1.0 / gamma;

		return{ static_cast<uint8>(255 * std::pow(r / 255.0, ig)),
				static_cast<uint8>(255 * std::pow(g / 255.0, ig)),
				static_cast<uint8>(255 * std::pow(b / 255.0, ig)),
				a };
	}

	inline ColorF Color::removeSRGBCurve() const noexcept
	{
		return ColorF{ *this }.removeSRGBCurve();
	}

	inline ColorF Color::applySRGBCurve() const noexcept
	{
		return ColorF{ *this }.applySRGBCurve();
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
		return{ static_cast<uint8>((rgba >> 24) & 0xFF),
				static_cast<uint8>((rgba >> 16) & 0xFF),
				static_cast<uint8>((rgba >>  8) & 0xFF),
				        static_cast<uint8>(rgba & 0xFF) };
	}

	inline constexpr Color Color::FromABGR(const uint32 abgr) noexcept
	{
		return{         static_cast<uint8>(abgr & 0xFF),
				static_cast<uint8>((abgr >>  8) & 0xFF),
				static_cast<uint8>((abgr >> 16) & 0xFF),
				static_cast<uint8>((abgr >> 24) & 0xFF) };
	}

	inline constexpr Color Alpha(const uint32 alpha) noexcept
	{
		return Color{ 255, static_cast<uint8>(alpha) };
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
