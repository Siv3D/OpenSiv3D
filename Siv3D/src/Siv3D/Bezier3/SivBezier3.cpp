//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Bezier3.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
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

	void Bezier3::_Formatter(FormatData& formatData, const Bezier3& value)
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
}
