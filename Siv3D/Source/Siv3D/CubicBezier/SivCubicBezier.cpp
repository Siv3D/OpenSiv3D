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

# include <Siv3D/CubicBezier.hpp>

namespace s3d
{
	LineString CubicBezier::getLineString(const double start, const double end, const uint32 quality) const
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

	void CubicBezier::draw(const double thickness, const ColorF& color) const
	{
		getLineString().draw(thickness, color);
	}
}
