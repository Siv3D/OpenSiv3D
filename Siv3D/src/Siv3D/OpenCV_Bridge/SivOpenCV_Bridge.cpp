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

# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	namespace OpenCV_Bridge
	{
		void RedToBinary(const Image& from, cv::Mat_<uint8>& to, const uint32 threshold)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();

			if (to.isContinuous())
			{
				const Color* pSrc = from.data();
				const Color* pSrcEnd = pSrc + from.num_pixels();
				uint8* pDst = to.data;

				while (pSrc != pSrcEnd)
				{
					*pDst = (pSrc->r <= threshold ? 0 : 255);

					++pDst; ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = from.data();
				uint8* pDstLine = to.data;
				const size_t dstStepBytes = to.step.p[0];

				for (int32 y = 0; y < height; ++y)
				{
					uint8* pDst = pDstLine;

					for (int32 x = 0; x < width; ++x)
					{
						*pDst = (pSrc->r <= threshold ? 0 : 255);

						++pDst; ++pSrc;
					}

					pDstLine += dstStepBytes;
				}
			}
		}

		void RedToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold)
		{
			assert(from.width() * 2 == to.cols);
			assert(from.height() * 2 == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();
			const Color* pSrc = from.data();
			const size_t dstStride = to.step.p[0];

			for (int32 y = 0; y < height; ++y)
			{
				uint8* pDst = to.data + (2 * dstStride) * y;

				for (int32 x = 0; x < width; ++x)
				{
					const uint8 a = (pSrc->r <= threshold ? 0 : 255);
					*pDst = a;
					*(pDst + 1) = a;
					*(pDst + dstStride) = a;
					*(pDst + dstStride + 1) = a;
					++pSrc; pDst += 2;
				}
			}
		}

		void AlphaToBinary(const Image& from, cv::Mat_<uint8>& to, const uint32 threshold)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();

			if (to.isContinuous())
			{
				const Color* pSrc = from.data();
				const Color* pSrcEnd = pSrc + from.num_pixels();
				uint8* pDst = to.data;

				while (pSrc != pSrcEnd)
				{
					*pDst = (pSrc->a <= threshold ? 0 : 255);

					++pDst; ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = from.data();
				uint8* pDstLine = to.data;
				const size_t dstStepBytes = to.step.p[0];

				for (int32 y = 0; y < height; ++y)
				{
					uint8* pDst = pDstLine;

					for (int32 x = 0; x < width; ++x)
					{
						*pDst = (pSrc->a <= threshold ? 0 : 255);

						++pDst; ++pSrc;
					}

					pDstLine += dstStepBytes;
				}
			}
		}

		void AlphaToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold)
		{
			assert(from.width() * 2 == to.cols);
			assert(from.height() * 2 == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();
			const Color* pSrc = from.data();
			const size_t dstStride = to.step.p[0];

			for (int32 y = 0; y < height; ++y)
			{
				uint8* pDst = to.data + (2 * dstStride) * y;

				for (int32 x = 0; x < width; ++x)
				{
					const uint8 a = (pSrc->a <= threshold ? 0 : 255);
					*pDst = a;
					*(pDst + 1) = a;
					*(pDst + dstStride) = a;
					*(pDst + dstStride + 1) = a;
					++pSrc; pDst += 2;
				}
			}
		}

		void ToGrayScale(const Image& from, cv::Mat_<uint8>& to)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();

			if (to.isContinuous())
			{
				const Color* pSrc = from.data();
				const Color* pSrcEnd = pSrc + from.num_pixels();
				uint8* pDst = to.data;

				while (pSrc != pSrcEnd)
				{
					*pDst = pSrc->grayscale0_255();

					++pDst; ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = from.data();
				uint8* pDstLine = to.data;
				const size_t dstStepBytes = to.step.p[0];

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
		}

		void ToMatVec3b(const Image& from, cv::Mat_<cv::Vec3b>& to)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();
			const Color* pSrc = from.data();

			uint8* pDstLine = to.data;
			const size_t dstStepBytes = to.step.p[0];

			for (int32 y = 0; y < height; ++y)
			{
				uint8* pDst = pDstLine;

				for (int32 x = 0; x < width; ++x)
				{
					*pDst++ = pSrc->b;
					*pDst++ = pSrc->g;
					*pDst++ = pSrc->r;

					++pSrc;
				}

				pDstLine += dstStepBytes;
			}
		}

		void ToMatVec3f255(const Image& from, cv::Mat_<cv::Vec3f>& to)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			if (!from)
			{
				return;
			}

			const int32 height = from.height();
			const int32 width = from.width();
			const Color* pSrc = from.data();

			uint8* pDstLine = to.data;
			const size_t dstStepBytes = to.step.p[0];

			for (int32 y = 0; y < height; ++y)
			{
				cv::Vec3f* pDst = static_cast<cv::Vec3f*>(static_cast<void*>(pDstLine));

				for (int32 x = 0; x < width; ++x)
				{
					(*pDst)[0] = static_cast<float>(pSrc->b);
					(*pDst)[1] = static_cast<float>(pSrc->g);
					(*pDst)[2] = static_cast<float>(pSrc->r);

					++pDst; ++pSrc;
				}

				pDstLine += dstStepBytes;
			}
		}

		void FromMat(const cv::Mat_<cv::Vec3b>& from, Image& to, const bool preserveAlpha)
		{
			const int32 width = from.cols;
			const int32 height = from.rows;
			to.resize(width, height);

			if (!to)
			{
				return;
			}

			if (preserveAlpha)
			{
				if (from.isContinuous())
				{
					Color* pDst = to.data();
					const Color* pDstEnd = pDst + to.num_pixels();
					const uint8* pSrc = from.data;

					while (pDst != pDstEnd)
					{
						pDst->b = *pSrc++;
						pDst->g = *pSrc++;
						pDst->r = *pSrc++;
						++pDst;
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
							pDst->b = *pSrc++;
							pDst->g = *pSrc++;
							pDst->r = *pSrc++;
							++pDst;
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
						pDst->b = *pSrc++;
						pDst->g = *pSrc++;
						pDst->r = *pSrc++;
						pDst->a = 255;
						++pDst;
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
							pDst->b = *pSrc++;
							pDst->g = *pSrc++;
							pDst->r = *pSrc++;
							pDst->a = 255;
							++pDst;
						}

						pSrcLine += srcStepBytes;
					}
				}
			}
		}

		void FromGrayScale(const cv::Mat_<uint8>& from, Image& to, const bool preserveAlpha)
		{
			const int32 width = from.cols;
			const int32 height = from.rows;
			to.resize(width, height);

			if (!to)
			{
				return;
			}

			if (preserveAlpha)
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
		}

		cv::Mat_<uint8> ImRead_GrayScale(const FilePath& path)
		{
			return ImRead_GrayScale(Image(path));
		}

		cv::Mat_<uint8> ImRead_GrayScale(const Image& image)
		{
			cv::Mat_<uint8> mat(image.height(), image.width());

			ToGrayScale(image, mat);

			return mat;
		}

		cv::Mat_<cv::Vec3b> ImRead_BGR(const FilePath& path)
		{
			return ImRead_BGR(Image(path));
		}

		cv::Mat_<cv::Vec3b> ImRead_BGR(const Image& image)
		{
			cv::Mat_<cv::Vec3b> mat(image.height(), image.width());

			ToMatVec3b(image, mat);

			return mat;
		}
	}
}
