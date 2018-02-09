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

# include <Siv3D/Image.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	const Point& Point::paint(Image& dst, const Color& color) const
	{
		if (x < 0 || dst.width() <= x || y < 0 || dst.height() <= y)
		{
			return *this;
		}

		const uint32 srcBlend = color.a;
		const uint32 dstBlend = 255 - srcBlend;

		Color* const pDst = dst.data() + y * dst.width() + x;
		pDst->r = ((pDst->r * dstBlend) + (color.r * srcBlend)) / 255;
		pDst->g = ((pDst->g * dstBlend) + (color.g * srcBlend)) / 255;
		pDst->b = ((pDst->b * dstBlend) + (color.b * srcBlend)) / 255;

		return *this;
	}

	const Point& Point::overwrite(Image& dst, const Color& color) const
	{
		if (x < 0 || dst.width() <= x || y < 0 || dst.height() <= y)
		{
			return *this;
		}

		Color* const pDst = dst.data() + y * dst.width() + x;
		*pDst = color;

		return *this;
	}
}
