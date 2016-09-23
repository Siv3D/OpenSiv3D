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

# include <cmath>
# include <Siv3D/HSV.hpp>

namespace s3d
{
	namespace detail
	{
		inline static double Fraction(const double x)
		{
			return (x - std::floor(x));
		}

		static constexpr size_t conversionTable[6][3] =
		{
			{ 3, 2, 0 },
			{ 1, 3, 0 },
			{ 0, 3, 2 },
			{ 0, 1, 3 },
			{ 2, 0, 3 },
			{ 3, 0, 1 },
		};
	}

	Color HSV::toColor() const noexcept
	{
		const double hue01 = detail::Fraction(h / 360.0);
		const double hueF = hue01 * 6.0;
		const int32 hueI = static_cast<int32>(hueF);
		const double fr = hueF - hueI;
		const uint8 vals[4] =
		{
			static_cast<uint8>(v * (1.0 - s)* 255.0 + 0.5),
			static_cast<uint8>(v * (1.0 - s*fr)* 255.0 + 0.5),
			static_cast<uint8>(v * (1.0 - s*(1.0 - fr))* 255.0 + 0.5),
			static_cast<uint8>(v * 255.0 + 0.5)
		};

		return Color(vals[detail::conversionTable[hueI][0]],
					 vals[detail::conversionTable[hueI][1]],
					 vals[detail::conversionTable[hueI][2]],
					 a >= 1.0 ? 255 : a <= 0.0 ? 0 : static_cast<uint8>(a * 255.0 + 0.5));
	}

	ColorF HSV::toColorF() const noexcept
	{
		const double hue01 = detail::Fraction(h / 360.0);
		const double hueF = hue01 * 6.0;
		const int32 hueI = static_cast<int32>(hueF);
		const double fr = hueF - hueI;
		const double vals[4] =
		{
			v * (1.0 - s),
			v * (1.0 - s * fr),
			v * (1.0 - s * (1.0 - fr)),
			v
		};

		return ColorF(vals[detail::conversionTable[hueI][0]],
					  vals[detail::conversionTable[hueI][1]],
					  vals[detail::conversionTable[hueI][2]],
					  a);
	}

	//
	// http://lol.zoy.org/blog/2013/01/13/fast-rgb-to-hsv
	//
	void HSV::convertFrom(double r, double g, double b, const double _a) noexcept
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
		const double chroma = r - std::min(g, b);

		h = std::fabs(K + delta / (chroma + 1e-20));
		s = chroma / (r + 1e-20);
		v = r;
		a = _a;
	}

	Color HueToColor(const double hue) noexcept
	{
		const double hue01 = detail::Fraction(hue / 360.0);
		const double hueF = hue01 * 6.0;
		const int32 hueI = static_cast<int32>(hueF);
		const double fr = hueF - hueI;
		const uint8 vals[4] =
		{
			0,
			static_cast<uint8>((1.0 - fr)* 255.0 + 0.5),
			static_cast<uint8>((1.0 - (1.0 - fr))* 255.0 + 0.5),
			255
		};

		return Color(vals[detail::conversionTable[hueI][0]],
					 vals[detail::conversionTable[hueI][1]],
					 vals[detail::conversionTable[hueI][2]],
					 255);
	}

	ColorF HueToColorF(const double hue) noexcept
	{
		const double hue01 = detail::Fraction(hue / 360.0);
		const double hueF = hue01 * 6.0;
		const int32 hueI = static_cast<int32>(hueF);
		const double fr = hueF - hueI;
		const double vals[4] =
		{
			0.0,
			1.0 - fr,
			1.0 - (1.0 - fr),
			1.0
		};

		return ColorF(vals[detail::conversionTable[hueI][0]],
					  vals[detail::conversionTable[hueI][1]],
					  vals[detail::conversionTable[hueI][2]],
					  1.0);
	}
}
