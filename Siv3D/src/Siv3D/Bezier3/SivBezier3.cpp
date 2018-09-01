//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Bezier3.hpp>

namespace s3d
{
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

	const Bezier3& Bezier3::draw(const double thickness, const ColorF& color) const
	{
		getLineString().draw(thickness, color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Bezier3& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.p0);
		formatData.string.append(U", ");
		Formatter(formatData, value.p1);
		formatData.string.append(U", ");
		Formatter(formatData, value.p2);
		formatData.string.append(U", ");
		Formatter(formatData, value.p3);
		formatData.string.push_back(U')');
	}
}
