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

# include <Siv3D/Bezier3.hpp>

namespace s3d
{
	Vec2 Bezier3::getPos(const double t) const noexcept
	{
		return (1 - t) * (1 - t) * (1 - t) * p0 + 3 * (1 - t) * (1 - t) * t * p1 + 3 * (1 - t) * t * t * p2 + t * t * t * p3;
	}

	Vec2 Bezier3::getTangent(const double t) const noexcept
	{
		return (-3 * p0 * (1 - t) * (1 - t) +
			p1 * (3 * (1 - t) * (1 - t) - 6 * (1 - t) * t) +
			p2 * (6 * (1 - t) * t - 3 * t * t) + 3 * p3 * t * t).normalized();
	}

	LineString Bezier3::getLineString(const uint32 quality) const
	{
		return getLineString(0.0, 1.0, quality);
	}

	LineString Bezier3::getLineString(const double start, const double end, const uint32 quality) const
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

	const Bezier3& Bezier3::draw(const ColorF& color, const uint32 quality) const
	{
		return draw(1.0, color, quality);
	}

	const Bezier3& Bezier3::draw(const double thickness, const ColorF& color, const uint32 quality) const
	{
		getLineString(quality).draw(thickness, color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Bezier3& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.p0);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.p1);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.p2);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.p3);
		formatData.string.push_back(U')');
	}

	Bezier3Path::Bezier3Path(const Bezier3& bezier) noexcept
		: m_v0(-3 * bezier.p0 + 9 * bezier.p1 - 9 * bezier.p2 + 3 * bezier.p3)
		, m_v1(6 * bezier.p0 - 12 * bezier.p1 + 6 * bezier.p2)
		, m_v2(-3 * bezier.p0 + 3 * bezier.p1)
	{
	
	}

	double Bezier3Path::advance(const double distance, const int32 quality) noexcept
	{
		for (int i = 0; i < quality; ++i)
		{
			m_t = m_t + (distance / quality) / (m_t * m_t * m_v0 + m_t * m_v1 + m_v2).length();
		}

		return m_t;
	}
}
