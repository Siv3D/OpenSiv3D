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

# include <Siv3D/ImageROI.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>
# include <Siv3D/Image/ImagePainting.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Rect FitRect(const Size& size, Rect rect) noexcept
		{
			if (rect.w < 0 || rect.h < 0)
			{
				return{ 0, 0, 0, 0 };
			}

			if (rect.x < 0)
			{
				rect.w -= -rect.x;
				rect.x = 0;
			}
			else if (size.x <= rect.x)
			{
				return{ 0, 0, 0, 0 };
			}

			if (rect.y < 0)
			{
				rect.h -= -rect.y;
				rect.y = 0;
			}
			else if (size.y <= rect.y)
			{
				return{ 0, 0, 0, 0 };
			}

			if (size.x < (rect.x + rect.w))
			{
				rect.w = (size.x - rect.x);
			}
			else if ((rect.x + rect.w) <= 0)
			{
				return{ 0, 0, 0, 0 };
			}

			if (size.y < (rect.y + rect.h))
			{
				rect.h= (size.y - rect.y);
			}
			else if ((rect.y + rect.h) <= 0)
			{
				return{ 0, 0, 0, 0 };
			}

			return rect;
		}
	}

	ImageROI::ImageROI(Image& image, const Rect& rect) noexcept
		: imageRef{ image }
		, region{ detail::FitRect(image.size(), rect) } {}

	bool ImageROI::isEmpty() const noexcept
	{
		return (region.isEmpty());
	}

	ImageROI& ImageROI::negate()
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			Color* p = pLine;

			for (int32 x = 0; x < region.w; ++x)
			{
				*p = ~*p;
				++p;
			}

			pLine += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::grayscale()
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			Color* p = pLine;

			for (int32 x = 0; x < region.w; ++x)
			{
				const uint8 gray = p->grayscale0_255();
				p->r = gray;
				p->g = gray;
				p->b = gray;
				++p;
			}

			pLine += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::brighten(const int32 level)
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		if (level < 0)
		{
			for (int32 y = 0; y < region.h; ++y)
			{
				Color* p = pLine;

				for (int32 x = 0; x < region.w; ++x)
				{
					p->r = static_cast<uint8>(Max(static_cast<int32>(p->r) + level, 0));
					p->g = static_cast<uint8>(Max(static_cast<int32>(p->g) + level, 0));
					p->b = static_cast<uint8>(Max(static_cast<int32>(p->b) + level, 0));
					++p;
				}

				pLine += imageWidth;
			}
		}
		else if (level > 0)
		{
			for (int32 y = 0; y < region.h; ++y)
			{
				Color* p = pLine;

				for (int32 x = 0; x < region.w; ++x)
				{
					p->r = static_cast<uint8>(Min(static_cast<int32>(p->r) + level, 255));
					p->g = static_cast<uint8>(Min(static_cast<int32>(p->g) + level, 255));
					p->b = static_cast<uint8>(Min(static_cast<int32>(p->b) + level, 255));
					++p;
				}

				pLine += imageWidth;
			}
		}

		return *this;
	}

	ImageROI& ImageROI::mirror()
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* p = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			std::reverse(p, p + region.w);
			p += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::flip()
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* pLineFrom = &imageRef[region.y][region.x];
		Color* pLineTo = &imageRef[region.y + region.h - 1][region.x];

		for (int32 y = 0; y < (region.h / 2); ++y)
		{
			std::swap_ranges(pLineFrom, pLineFrom + region.w, pLineTo);
			pLineFrom += imageWidth;
			pLineTo -= imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::rotate180()
	{
		mirror();

		flip();

		return *this;
	}

	ImageROI& ImageROI::threshold(const uint8 threshold, const InvertColor invertColor)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const size_t imageWidth = imageRef.width();
			Color* pLine = &imageRef[region.y][region.x];
			const double thresholdF = (threshold / 255.0);

			if (invertColor)
			{
				for (int32 y = 0; y < region.h; ++y)
				{
					Color* p = pLine;

					for (int32 x = 0; x < region.w; ++x)
					{
						if (thresholdF < p->grayscale())
						{
							p->setRGB(0);
						}
						else
						{
							p->setRGB(255);
						}

						++p;
					}

					pLine += imageWidth;
				}
			}
			else 
			{
				for (int32 y = 0; y < region.h; ++y)
				{
					Color* p = pLine;

					for (int32 x = 0; x < region.w; ++x)
					{
						if (thresholdF < p->grayscale())
						{
							p->setRGB(255);
						}
						else
						{
							p->setRGB(0);
						}

						++p;
					}

					pLine += imageWidth;
				}
			}
		}

		return *this;
	}

	ImageROI& ImageROI::mosaic(const int32 size)
	{
		return mosaic(size, size);
	}

	ImageROI& ImageROI::spread(const int32 size)
	{
		return spread(size, size);
	}

	ImageROI& ImageROI::spread(const int32 horizontal, const int32 vertical)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image tmp{ region.size };
			DefaultRNG rng{ 12345 };

			UniformIntDistribution<int32> hu{ -horizontal, horizontal };
			UniformIntDistribution<int32> vu{ -vertical, vertical };

			Color* pDst = tmp.data();

			for (int32 y = region.y; y < static_cast<int32>(region.y + region.h); ++y)
			{
				for (int32 x = region.x; x < static_cast<int32>(region.x + region.w); ++x)
				{
					const int32 xOffset = hu(rng);
					const int32 yOffset = vu(rng);
					*pDst++ = imageRef.getPixel(x + xOffset, y + yOffset, ImageAddressMode::Mirror);
				}
			}

			tmp.overwrite(imageRef, region.pos);
		}

		return *this;
	}

	ImageROI& ImageROI::blur(const int32 size, const BorderType borderType)
	{
		return blur(size, size, borderType);
	}

	ImageROI& ImageROI::blur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(imageRef);
			cv::Mat srcROI = matSrc(roi);

			cv::blur(srcROI, srcROI, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), cv::Point(-1, -1), OpenCV_Bridge::ConvertBorderType(borderType));
		}

		return *this;
	}

	ImageROI& ImageROI::medianBlur(int32 apertureSize)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (apertureSize < 1)
			{
				return *this;
			}

			if (IsEven(apertureSize))
			{
				++apertureSize;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(imageRef);
			cv::Mat srcROI = matSrc(roi);

			cv::medianBlur(srcROI, srcROI, apertureSize);
		}

		return *this;
	}

	ImageROI& ImageROI::gaussianBlur(const int32 size, const BorderType borderType)
	{
		return gaussianBlur(size, size, borderType);
	}

	ImageROI& ImageROI::gaussianBlur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0)
				|| (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(imageRef);
			cv::Mat srcROI = matSrc(roi);

			cv::GaussianBlur(srcROI, srcROI, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, OpenCV_Bridge::ConvertBorderType(borderType));
		}

		return *this;
	}

	//ImageROI& ImageROI::bilateralFilter(const int32 d, const double sigmaColor, const double sigmaSpace, const BorderType borderType)
	//{

	//}

	ImageROI& ImageROI::dilate(const int32 iterations)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(imageRef);
			cv::Mat srcROI = matSrc(roi);

			cv::dilate(srcROI, srcROI, cv::Mat(), cv::Point(-1, -1), iterations);
		}

		return *this;
	}

	ImageROI& ImageROI::erode(const int32 iterations)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(imageRef);
			cv::Mat srcROI = matSrc(roi);

			cv::erode(srcROI, srcROI, cv::Mat(), cv::Point(-1, -1), iterations);
		}

		return *this;
	}

	void ImageROI::paint(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paint(dst, Point{ x, y }, color);
	}

	void ImageROI::paint(Image& dst, const Point& pos, const Color& color) const
	{
		ImageConstROI{ *this }.paint(dst, pos, color);
	}

	void ImageROI::stamp(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stamp(dst, Point{ x, y }, color);
	}

	void ImageROI::stamp(Image& dst, const Point& pos, const Color& color) const
	{
		ImageConstROI{ *this }.stamp(dst, pos, color);
	}

	void ImageROI::overwrite(Image& dst, const int32 x, const int32 y) const
	{
		overwrite(dst, Point{ x, y });
	}

	void ImageROI::overwrite(Image& dst, const Point pos) const
	{
		ImageConstROI{ *this }.overwrite(dst, pos);
	}

	void ImageROI::paintAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paintAt(dst, Point{ x, y }, color);
	}

	void ImageROI::paintAt(Image& dst, const Point& pos, const Color& color) const
	{
		paint(dst, (pos - (region.size / 2)), color);
	}

	void ImageROI::stampAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stampAt(dst, Point{ x, y }, color);
	}

	void ImageROI::stampAt(Image& dst, const Point& pos, const Color& color) const
	{
		stamp(dst, (pos - (region.size / 2)), color);
	}

	void ImageROI::overwriteAt(Image& dst, const int32 x, const int32 y) const
	{
		overwriteAt(dst, Point{ x, y });
	}

	void ImageROI::overwriteAt(Image& dst, const Point pos) const
	{
		overwrite(dst, (pos - (region.size / 2)));
	}

	ImageConstROI::ImageConstROI(const ImageROI& imageROI) noexcept
		: imageRef{ imageROI.imageRef }
		, region{ imageROI.region } {}

	ImageConstROI::ImageConstROI(const Image& image, const Rect& rect) noexcept
		: imageRef{ image }
		, region{ detail::FitRect(image.size(), rect) } {}

	bool ImageConstROI::isEmpty() const noexcept
	{
		return (region.isEmpty());
	}

	void ImageConstROI::paint(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paint(dst, Point{ x, y }, color);
	}

	void ImageConstROI::paint(Image& dst, const Point& pos, const Color& color) const
	{
		if (&imageRef == &dst)
		{
			return;
		}

		const int32 dstXBegin = Max(pos.x, 0);
		const int32 dstYBegin = Max(pos.y, 0);
		const int32 dstXEnd = Min(pos.x + region.w, dst.width());
		const int32 dstYEnd = Min(pos.y + region.h, dst.height());
		const int32 writeWidth = ((dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0);
		const int32 writeHeight = ((dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0);

		if ((writeWidth * writeHeight) == 0)
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);
		const Color* pSrc = &imageRef[region.y + srcYBegin][region.x + srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];
		const int32 srcWidth = imageRef.width();
		const int32 dstWidth = dst.width();

		ImagePainting::Paint(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
	}

	void ImageConstROI::stamp(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stamp(dst, Point{ x, y }, color);
	}

	void ImageConstROI::stamp(Image& dst, const Point& pos, const Color& color) const
	{
		if (&imageRef == &dst)
		{
			return;
		}

		const int32 dstXBegin = Max(pos.x, 0);
		const int32 dstYBegin = Max(pos.y, 0);
		const int32 dstXEnd = Min(pos.x + region.w, dst.width());
		const int32 dstYEnd = Min(pos.y + region.h, dst.height());
		const int32 writeWidth = ((dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0);
		const int32 writeHeight = ((dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0);

		if ((writeWidth * writeHeight) == 0)
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);
		const Color* pSrc = &imageRef[region.y + srcYBegin][region.x + srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];
		const int32 srcWidth = imageRef.width();
		const int32 dstWidth = dst.width();

		ImagePainting::Stamp(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
	}

	void ImageConstROI::overwrite(Image& dst, const int32 x, const int32 y) const
	{
		overwrite(dst, Point{ x, y });
	}

	void ImageConstROI::overwrite(Image& dst, const Point pos) const
	{
		if (&imageRef == &dst)
		{
			return;
		}

		const int32 dstXBegin = Max(pos.x, 0);
		const int32 dstYBegin = Max(pos.y, 0);
		const int32 dstXEnd = Min(pos.x + region.w, dst.width());
		const int32 dstYEnd = Min(pos.y + region.h, dst.height());
		const int32 writeWidth = ((dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0);
		const int32 writeHeight = ((dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0);

		if ((writeWidth * writeHeight) == 0)
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);
		const Color* pSrc = &imageRef[region.y + srcYBegin][region.x + srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];
		const int32 srcWidth = imageRef.width();
		const int32 dstWidth = dst.width();

		ImagePainting::Overwrite(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth);
	}

	void ImageConstROI::paintAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paintAt(dst, Point{ x, y }, color);
	}

	void ImageConstROI::paintAt(Image& dst, const Point& pos, const Color& color) const
	{
		paint(dst, (pos - (region.size / 2)), color);
	}

	void ImageConstROI::stampAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stampAt(dst, Point{ x, y }, color);
	}

	void ImageConstROI::stampAt(Image& dst, const Point& pos, const Color& color) const
	{
		stamp(dst, (pos - (region.size / 2)), color);
	}

	void ImageConstROI::overwriteAt(Image& dst, const int32 x, const int32 y) const
	{
		overwriteAt(dst, Point{ x, y });
	}

	void ImageConstROI::overwriteAt(Image& dst, const Point pos) const
	{
		overwrite(dst, (pos - (region.size / 2)));
	}
}
