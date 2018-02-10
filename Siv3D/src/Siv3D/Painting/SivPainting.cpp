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
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circle.hpp>

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

	const Rect& Rect::paint(Image& dst, const Color& color) const
	{
		const int32 xBegin = std::max(x, 0);
		const int32 xEnd = std::min(x + w, dst.width());
		const int32 yBegin = std::max(y, 0);
		const int32 yEnd = std::min(y + h, dst.height());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stride = dst.width();
		const int32 stepOffset = stride - fillWidth;

		const uint32 srcBlend = color.a;

		if (srcBlend == 255)
		{
			for (int32 _y = 0; _y < fillHeight; ++_y)
			{
				for (int32 _x = 0; _x < fillWidth; ++_x)
				{
					const uint8 a = pDst->a;
					*pDst = color;
					pDst->a = a;

					++pDst;
				}

				pDst += stepOffset;
			}
		}
		else
		{
			const uint32 premulSrcR	= srcBlend * color.r;
			const uint32 premulSrcG	= srcBlend * color.g;
			const uint32 premulSrcB	= srcBlend * color.b;
			const uint32 dstBlend	= 255 - srcBlend;

			for (int32 _y = 0; _y < fillHeight; ++_y)
			{
				for (int32 _x = 0; _x < fillWidth; ++_x)
				{
					pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
					pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
					pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;

					++pDst;
				}

				pDst += stepOffset;
			}
		}

		return *this;
	}

	const Rect& Rect::overwrite(Image& dst, const Color& color) const
	{
		const int32 xBegin	= std::max(x, 0);
		const int32 xEnd	= std::min(x + w, dst.width());
		const int32 yBegin	= std::max(y, 0);
		const int32 yEnd	= std::min(y + h, dst.height());
		const int32 fillWidth	= xEnd - xBegin;
		const int32 fillHeight	= yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stride = dst.width();
		const int32 stepOffset = stride - fillWidth;

		for (int32 _y = 0; _y < fillHeight; ++_y)
		{
			for (int32 _x = 0; _x < fillWidth; ++_x)
			{
				*pDst = color;

				++pDst;
			}

			pDst += stepOffset;
		}

		return *this;
	}

	const RectF& RectF::paint(Image& dst, const Color& color) const
	{
		Rect(*this).paint(dst, color);

		return *this;
	}

	const RectF& RectF::overwrite(Image& dst, const Color& color) const
	{
		Rect(*this).overwrite(dst, color);

		return *this;
	}

	const Circle& Circle::paint(Image& dst, const Color& color, bool antialiased) const
	{
		const int32 yBegin = std::max(static_cast<int32>(y - r - 1), 0);
		const int32 yEnd = std::min(static_cast<int32>(y + r + 1), dst.height());
		const int32 xBegin = std::max(static_cast<int32>(x - r - 1), 0);
		const int32 xEnd = std::min(static_cast<int32>(x + r + 1), dst.width());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stepOffset = dst.width() - fillWidth;
		const double lengthSq = (r + 0.5) * (r + 0.5);

		const uint32 srcBlend = color.a;

		if (antialiased)
		{
			const Vec2 center2(center.movedBy(-0.5, -0.5));
			const double length = std::sqrt(lengthSq);

			if (srcBlend == 255)
			{
				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						const double d = length - center2.distanceFrom(Vec2(_x, _y));

						if (d > 1.0)
						{
							const uint8 a = pDst->a;
							*pDst = color;
							pDst->a = a;
						}
						else if(d > 0.0)
						{			
							const uint32 srcBlend2 = static_cast<uint32>(255 * d);
							const uint32 premulSrcR = srcBlend2 * color.r;
							const uint32 premulSrcG = srcBlend2 * color.g;
							const uint32 premulSrcB = srcBlend2 * color.b;
							const uint32 dstBlend = 255 - srcBlend2;

							pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
							pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
							pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
			else
			{
				const uint32 premulSrcR = srcBlend * color.r;
				const uint32 premulSrcG = srcBlend * color.g;
				const uint32 premulSrcB = srcBlend * color.b;
				const uint32 dstBlend = 255 - srcBlend;

				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						const double d = length - center2.distanceFrom(Vec2(_x, _y));

						if (d > 1.0)
						{
							pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
							pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
							pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
						}
						else if (d > 0.0)
						{
							const uint32 srcBlend2 = static_cast<uint32>(srcBlend * d);
							const uint32 premulSrcR2 = srcBlend2 * color.r;
							const uint32 premulSrcG2 = srcBlend2 * color.g;
							const uint32 premulSrcB2 = srcBlend2 * color.b;
							const uint32 dstBlend2 = 255 - srcBlend2;

							pDst->r = (pDst->r * dstBlend2 + premulSrcR2) / 255;
							pDst->g = (pDst->g * dstBlend2 + premulSrcG2) / 255;
							pDst->b = (pDst->b * dstBlend2 + premulSrcB2) / 255;
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
		}
		else
		{
			if (srcBlend == 255)
			{
				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						if (center.distanceFromSq(Vec2(_x, _y)) <= lengthSq)
						{
							const uint8 a = pDst->a;
							*pDst = color;
							pDst->a = a;
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
			else
			{
				const uint32 premulSrcR = srcBlend * color.r;
				const uint32 premulSrcG = srcBlend * color.g;
				const uint32 premulSrcB = srcBlend * color.b;
				const uint32 dstBlend = 255 - srcBlend;

				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						if (center.distanceFromSq(Vec2(_x, _y)) <= lengthSq)
						{
							pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
							pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
							pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
		}

		return *this;
	}

	const Circle& Circle::overwrite(Image& dst, const Color& color) const
	{
		const int32 yBegin	= std::max(static_cast<int32>(y - r), 0);
		const int32 yEnd	= std::min(static_cast<int32>(y + r + 1), dst.height());
		const int32 xBegin	= std::max(static_cast<int32>(x - r), 0);
		const int32 xEnd	= std::min(static_cast<int32>(x + r + 1), dst.width());
		const int32 fillWidth	= xEnd - xBegin;
		const int32 fillHeight	= yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		const int32 stepOffset = dst.width() - fillWidth;
		const double lengthSq = (r + 0.5) * (r + 0.5);

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;

		for (int32 _y = yBegin; _y < yEnd; ++_y)
		{
			for (int32 _x = xBegin; _x < xEnd; ++_x)
			{
				if (center.distanceFromSq(Vec2(_x, _y)) <= lengthSq)
				{
					*pDst = color;
				}

				++pDst;
			}

			pDst += stepOffset;
		}

		return *this;
	}
}
