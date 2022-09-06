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

# include <Siv3D/Bezier3.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	Vec2 Bezier3::getTangent(const double t) const noexcept
	{
		return (-3 * p0 * (1 - t) * (1 - t) +
			p1 * (3 * (1 - t) * (1 - t) - 6 * (1 - t) * t) +
			p2 * (6 * (1 - t) * t - 3 * t * t) + 3 * p3 * t * t).normalized();
	}

	LineString Bezier3::getLineString(const int32 quality) const
	{
		return getLineString(0.0, 1.0, quality);
	}

	LineString Bezier3::getLineString(const double start, const double end, int32 quality) const
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

	const Bezier3& Bezier3::paint(Image& dst, const Color& color) const
	{
		return paint(dst, 1, color);
	}

	const Bezier3& Bezier3::paint(Image& dst, const int32 thickness, const Color& color) const
	{
		getLineString().paint(dst, thickness, color);

		return *this;
	}

	const Bezier3& Bezier3::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const Bezier3& Bezier3::overwrite(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		getLineString().overwrite(dst, thickness, color, antialiased);

		return *this;
	}

	const Bezier3& Bezier3::draw(const ColorF& color, const int32 quality) const
	{
		return draw(1.0, color, quality);
	}

	const Bezier3& Bezier3::draw(double thickness, const ColorF& color, const int32 quality) const
	{
		getLineString(quality).draw(thickness, color);

		return *this;
	}

	const Bezier3& Bezier3::draw(const LineStyle& style, const double thickness, const ColorF& color, const int32 quality) const
	{
		getLineString(quality).draw(style, thickness, color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Bezier3& value)
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
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p3.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p3.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}

	double Bezier3Path::advance(const double distance, const int32 quality) noexcept
	{
		for (int32 i = 0; i < quality; ++i)
		{
			m_t += (distance / quality) / (m_t * m_t * m_v0 + m_t * m_v1 + m_v2).length();
		}

		return m_t;
	}
}
