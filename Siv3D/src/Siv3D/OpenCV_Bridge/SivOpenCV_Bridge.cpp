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

# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	namespace OpenCV_Bridge
	{
		cv::Mat_<uint8> ToGrayScale(const Image& image)
		{
			const int32 height	= image.height();
			const int32 width	= image.width();
			cv::Mat_<uint8> result(height, width);

			if (result.isContinuous())
			{
				const Color* pSrc = image.data();
				const Color* pSrcEnd = pSrc + image.num_pixels();
				uint8* pDst = result.data;

				while (pSrc != pSrcEnd)
				{
					*pDst = pSrc->grayscale0_255();
					++pDst; ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = image.data();
				uint8* pDstLine = result.data;
				const size_t dstStepBytes = result.step.p[0];

				for (int32 y = 0; y < height; ++y)
				{
					uint8* pDst = pDstLine;

					for (int32 x = 0; x < width; ++x)
					{
						*pDst = pSrc->grayscale0_255();
						++pDst; ++pSrc;
					}

					pDstLine += dstStepBytes;
				}
			}

			return result;
		}

		void FromGrayScale(const cv::Mat_<uint8>& from, Image& to, const OverwriteAlpha overwriteAlpha)
		{
			const int32 width	= from.cols;
			const int32 height	= from.rows;
			to.resize(width, height);

			if (not to)
			{
				return;
			}

			if (overwriteAlpha)
			{
				if (from.isContinuous())
				{
					Color* pDst = to.data();
					const Color* pDstEnd = pDst + to.num_pixels();
					const uint8* pSrc = from.data;

					while (pDst != pDstEnd)
					{
						pDst->r = pDst->g = pDst->b = *pSrc;
						pDst->a = 255;
						++pDst; ++pSrc;
					}
				}
				else
				{
					Color* pDst = to.data();
					uint8* pSrcLine = from.data;
					const size_t srcStepBytes = from.step.p[0];

					for (int32 y = 0; y < height; ++y)
					{
						uint8* pSrc = pSrcLine;

						for (int32 x = 0; x < width; ++x)
						{
							pDst->r = pDst->g = pDst->b = *pSrc;
							pDst->a = 255;
							++pDst; ++pSrc;
						}

						pSrcLine += srcStepBytes;
					}
				}
			}
			else
			{
				if (from.isContinuous())
				{
					Color* pDst = to.data();
					const Color* pDstEnd = pDst + to.num_pixels();
					const uint8* pSrc = from.data;

					while (pDst != pDstEnd)
					{
						pDst->r = pDst->g = pDst->b = *pSrc;
						++pDst; ++pSrc;
					}
				}
				else
				{
					Color* pDst = to.data();
					uint8* pSrcLine = from.data;
					const size_t srcStepBytes = from.step.p[0];

					for (int32 y = 0; y < height; ++y)
					{
						uint8* pSrc = pSrcLine;

						for (int32 x = 0; x < width; ++x)
						{
							pDst->r = pDst->g = pDst->b = *pSrc;
							++pDst; ++pSrc;
						}

						pSrcLine += srcStepBytes;
					}
				}
			}
		}
	}
}
