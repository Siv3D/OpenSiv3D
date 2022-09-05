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

# include <Siv3D/Bezier2.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	Vec2 Bezier2::getTangent(const double t) const noexcept
	{
		return ((p1 - p0) * 2 * (1 - t) + (p2 - p1) * (2 * t)).normalized();
	}

	LineString Bezier2::getLineString(const int32 quality) const
	{
		return getLineString(0.0, 1.0, quality);
	}

	LineString Bezier2::getLineString(const double start, const double end, int32 quality) const
	{
		quality = Max(2, quality);

		const double length = (end - start);
		const double d = (length / (quality));

		LineString pts(quality + 1);

		Vec2* pDst = pts.data();

		for (int32 i = 0; i <= quality; ++i)
		{
			*pDst++ = getPos(start + d * i);
		}

		return pts;
	}

	RectF Bezier2::boundingRect() const noexcept
	{
		const auto [a1, a2] = p0 - 2 * p1 + p2;
		const auto [b1, b2] = -2 * (p0 - p1);
		const auto [c1, c2] = p0;

		double minX = Min(p0.x, p2.x);
		double maxX = Max(p0.x, p2.x);

		if (a1 != 0.0)
		{
			const double t = -0.5 * b1 / a1;

			if (InRange(t, 0.0, 1.0))
			{
				// k = a1 t^2 + b1 t + c1
				const double k = std::fma(std::fma(a1, t, b1), t, c1);

				minX = Min(minX, k);
				maxX = Max(maxX, k);
			}
		}

		double minY = Min(p0.y, p2.y);
		double maxY = Max(p0.y, p2.y);

		if (a2 != 0.0)
		{
			const double t = -0.5 * b2 / a2;

			if (InRange(t, 0.0, 1.0))
			{
				// k = a2 t^2 + b2 t + c2
				const double k = std::fma(std::fma(a2, t, b2), t, c2);

				minY = Min(minY, k);
				maxY = Max(maxY, k);
			}
		}

		return { minX, minY, (maxX - minX), (maxY - minY) };
	}

	const Bezier2& Bezier2::paint(Image& dst, const Color& color) const
	{
		return paint(dst, 1, color);
	}

	const Bezier2& Bezier2::paint(Image& dst, const int32 thickness, const Color& color) const
	{
		getLineString().paint(dst, thickness, color);

		return *this;
	}

	const Bezier2& Bezier2::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const Bezier2& Bezier2::overwrite(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		getLineString().overwrite(dst, thickness, color, antialiased);

		return *this;
	}

	const Bezier2& Bezier2::draw(const ColorF& color, const int32 quality) const
	{
		return draw(1.0, color, quality);
	}

	const Bezier2& Bezier2::draw(double thickness, const ColorF& color, const int32 quality) const
	{
		getLineString(quality).draw(thickness, color);

		return *this;
	}

	const Bezier2& Bezier2::draw(const LineStyle& style, const double thickness, const ColorF& color, const int32 quality) const
	{
		getLineString(quality).draw(style, thickness, color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Bezier2& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.p0.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p0.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p1.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p1.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p2.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p2.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}

	double Bezier2Path::advance(const double distance, const int32 quality) noexcept
	{
		for (int32 i = 0; i < quality; ++i)
		{
			m_t += (distance / quality) / (m_t * m_v0 + m_v1).length();
		}

		return m_t;
	}
}
