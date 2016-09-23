//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr uint32 HexToDecimal(const wchar c)
		{
			return (c & 0xF) + ((c & 0x40) >> 6) * 9;
		}
	}

	Color::Color(const HSV& hsv) noexcept
	{
		*this = hsv.toColor();
	}

	Color& Color::operator =(const HSV& hsv) noexcept
	{
		return *this = hsv.toColor();
	}

	Color::Color(const StringView& code) noexcept
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
		else
		{
			r = g = b = 0;
			a = 255;
		}
	}

	Color Color::gamma(const double gamma) const noexcept
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

	ColorF::ColorF(const HSV& hsv) noexcept
	{
		*this = hsv.toColorF();
	}

	ColorF& ColorF::operator =(const HSV& hsv) noexcept
	{
		return *this = hsv.toColorF();
	}

	ColorF ColorF::gamma(const double gamma) const noexcept
	{
		if (gamma <= 0.0)
		{
			return{ 0.0, 0.0, 0.0, a };
		}

		const double ig = 1.0 / gamma;

		return{ std::pow(r, ig), std::pow(g, ig), std::pow(b, ig), a };
	}
}
