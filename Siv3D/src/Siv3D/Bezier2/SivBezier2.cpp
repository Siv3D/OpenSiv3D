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

# include <Siv3D/Bezier2.hpp>

namespace s3d
{
	Vec2 Bezier2::getPos(const double t) const noexcept
	{
		return (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;
	}

	Vec2 Bezier2::getTangent(const double t) const noexcept
	{
		return ((p1 - p0) * 2 * (1 - t) + (p2 - p1) * (2 * t)).normalized();
	}

	LineString Bezier2::getLineString(const uint32 quality) const
	{
		return getLineString(0.0, 1.0, quality);
	}

	LineString Bezier2::getLineString(const double start, const double end, const uint32 quality) const
	{
		const double length = end - start;
		const double d = length / (quality + 1);

		LineString pts(quality + 2);

		Vec2* pDst = pts.data();

		for (uint32 i = 0; i <= (quality + 1); ++i)
		{
			*pDst++ = getPos(start + d * i);
		}

		return pts;
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

	const Bezier2& Bezier2::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const Bezier2& Bezier2::overwrite(Image& dst, const int32 thickness, const Color& color, const bool antialiased) const
	{
		getLineString().overwrite(dst, thickness, color, antialiased);

		return *this;
	}

	const Bezier2& Bezier2::draw(const ColorF& color, const uint32 quality) const
	{
		return draw(1.0, color, quality);
	}

	const Bezier2& Bezier2::draw(const double thickness, const ColorF& color, const uint32 quality) const
	{
		getLineString(quality).draw(thickness, color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Bezier2& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.p0);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.p1);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.p2);
		formatData.string.push_back(U')');
	}

	Bezier2Path::Bezier2Path(const Bezier2& bezier) noexcept
		: m_v0(2 * bezier.p0 - 4 * bezier.p1 + 2 * bezier.p2)
		, m_v1(-2 * bezier.p0 + 2 * bezier.p1)
	{
	
	}

	double Bezier2Path::advance(const double distance, const int32 quality) noexcept
	{
		for (int32 i = 0; i < quality; ++i)
		{
			m_t = m_t + (distance / quality) / (m_t * m_v0 + m_v1).length();
		}

		return m_t;
	}
}
