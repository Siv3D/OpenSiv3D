//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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
		static constexpr uint32 HexToDecimal(const char32 c)
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
		return ToHex(r).lpad(2, U'0') + ToHex(g).lpad(2, U'0') + ToHex(b).lpad(2, U'0');
	}

	size_t Color::hash() const noexcept
	{
		return std::hash<uint32>()(asUint32());
	}

	void Formatter(FormatData& formatData, const Color& value)
	{
		const size_t bufferSize = 12 * 4 + 9;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt(&p, value.r);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.g);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.b);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.a);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}

	ColorF::ColorF(const Vec3& rgb, const double _a) noexcept
		: ColorF(rgb.x, rgb.y, rgb.z, _a)
	{

	}

	ColorF::ColorF(const Vec4& rgba) noexcept
		: ColorF(rgba.x, rgba.y, rgba.z, rgba.w)
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

	size_t ColorF::hash() const noexcept
	{
		return std::hash<s3d::Vec4>()(rgba());
	}

	void Formatter(FormatData& formatData, const ColorF& value)
	{
		Formatter(formatData, value.rgba());
	}

	template <class CharType>
	inline std::basic_istream<CharType>& IStream(std::basic_istream<CharType>& input, Color& value)
	{
		CharType unused;
		input >> unused;

		if (unused == CharType('#'))
		{
			String code;
			input >> code;
			value = ColorF(U'#' + code);
		}
		else
		{
			uint32 cols[4];
			input
				>> cols[0] >> unused
				>> cols[1] >> unused
				>> cols[2] >> unused;

			if (unused == CharType(','))
			{
				input >> cols[3] >> unused;
			}
			else
			{
				cols[3] = 255;
			}

			value.r = cols[0];
			value.g = cols[1];
			value.b = cols[2];
			value.a = cols[3];
		}

		return input;
	}

	std::istream& operator >>(std::istream& input, Color& value)
	{
		return IStream<char>(input, value);
	}

	std::wistream& operator >>(std::wistream& input, Color& value)
	{
		return IStream<wchar_t>(input, value);
	}

	template <class CharType>
	inline std::basic_istream<CharType>& IStream(std::basic_istream<CharType>& input, ColorF& value)
	{
		CharType unused;
		input >> unused;

		if (unused == CharType('#'))
		{
			String code;
			input >> code;
			value = ColorF(U'#' + code);
		}
		else
		{
			input >> value.r >> unused
				>> value.g >> unused
				>> value.b >> unused;

			if (unused == CharType(','))
			{
				input >> value.a >> unused;
			}
			else
			{
				value.a = 1.0;
			}
		}

		return input;
	}

	std::istream& operator >>(std::istream& input, ColorF& value)
	{
		return IStream<char>(input, value);
	}

	std::wistream& operator >>(std::wistream& input, ColorF& value)
	{
		return IStream<wchar_t>(input, value);
	}
}
