//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/PointVector.hpp>

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

	Color::Color(const StringView code) noexcept
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

	String Color::toHex() const
	{
		return ToHex(r).lpad(2, L'0') + ToHex(g).lpad(2, L'0') + ToHex(b).lpad(2, L'0');
	}

	void Formatter(FormatData& formatData, const Color& value)
	{
		const size_t bufferSize = 12 * 4 + 6;
		wchar buf[bufferSize];
		wchar* p = buf;

		*(p++) = L'(';
		detail::AppendInt(&p, value.r);
		*(p++) = L',';
		detail::AppendInt(&p, value.g);
		*(p++) = L',';
		detail::AppendInt(&p, value.b);
		*(p++) = L',';
		detail::AppendInt(&p, value.a);
		*(p++) = L')';

		formatData.string.append(buf, p - buf);
	}

	ColorF::ColorF(const Vec3& rgb, const double _a) noexcept
		: ColorF(rgb.x, rgb.y, rgb.z, _a)
	{

	}

	ColorF::ColorF(const HSV& hsv) noexcept
	{
		*this = hsv.toColorF();
	}

	ColorF& ColorF::operator =(const HSV& hsv) noexcept
	{
		return *this = hsv.toColorF();
	}

	Float4 ColorF::toFloat4() const
	{
		return Float4(r, g, b, a);
	}

	Vec4 ColorF::toVec4() const
	{
		return Vec4(r, g, b, a);
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

	Vec2 ColorF::rg() const noexcept
	{
		return{ r, g };
	}

	Vec2 ColorF::gb() const noexcept
	{
		return{ g, b };
	}

	Vec2 ColorF::ba() const noexcept
	{
		return{ b, a };
	}

	Vec3 ColorF::rgb() const noexcept
	{
		return{ r, g, b };
	}

	Vec3 ColorF::gba() const noexcept
	{
		return{ g, b, a };
	}

	Vec3 ColorF::bgr() const noexcept
	{
		return{ b, g, r };
	}

	Vec4 ColorF::rgba() const noexcept
	{
		return{ r, g, b, a };
	}

	Vec4 ColorF::argb() const noexcept
	{
		return{ a, r, g, b };
	}

	Vec4 ColorF::abgr() const noexcept
	{
		return{ a, b, g, r };
	}

	void Formatter(FormatData& formatData, const ColorF& value)
	{
		Formatter(formatData, value.rgba());
	}
}
