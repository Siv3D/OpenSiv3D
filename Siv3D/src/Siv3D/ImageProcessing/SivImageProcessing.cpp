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

# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/Number.hpp>

namespace s3d
{
	namespace detail
	{
		static Image GenerateMip(const Image& src)
		{
			if (!src)
			{
				return Image();
			}

			const Color* pSrc = src.data();
			const int32 srcW = src.width();
			const int32 srcH = src.height();

			const int32 targetWidth = std::max(src.width() / 2, 1);
			const int32 targetHeight = std::max(src.height() / 2, 1);
			Image result(targetWidth, targetHeight);
			Color* pDst = result.data();

			const float sddx = (srcW - 1.0f) / std::max(targetWidth - 1, 1);
			const float sddy = (srcH - 1.0f) / std::max(targetHeight - 1, 1);

			for (int32 y = 0; y < targetHeight; ++y)
			{
				float sy = y * sddy;

				const int32 dy = static_cast<int32>(sy);

				sy -= dy;

				const int32 dyO = std::min(dy + 1, srcH - 1);

				for (int32 x = 0; x < targetWidth; ++x)
				{
					float sx = x * sddx;

					const int32 dx = static_cast<int32>(sx);

					sx -= dx;

					const int32 dxO = std::min(dx + 1, srcW - 1);
			
					const Color& c0 = pSrc[dy * srcW + dx];
					const Color& c1 = pSrc[dy * srcW + dxO];
					const Color& c2 = pSrc[dyO * srcW + dx];
					const Color& c3 = pSrc[dyO * srcW + dxO];

					const uint8 r = static_cast<uint8>((c0.r * (1 - sx) + c1.r * sx) * (1 - sy) + (c2.r * (1 - sx) + c3.r * sx) * sy);
					const uint8 g = static_cast<uint8>((c0.g * (1 - sx) + c1.g * sx) * (1 - sy) + (c2.g * (1 - sx) + c3.g * sx) * sy);
					const uint8 b = static_cast<uint8>((c0.b * (1 - sx) + c1.b * sx) * (1 - sy) + (c2.b * (1 - sx) + c3.b * sx) * sy);
					const uint8 a = static_cast<uint8>((c0.a * (1 - sx) + c1.a * sx) * (1 - sy) + (c2.a * (1 - sx) + c3.a * sx) * sy);

					(pDst++)->set(r, g, b, a);
				}
			}

			return result;
		}

		struct SDFPixel
		{
			Point border;
			
			float distance;
			
			bool white;
		};

		inline float CalcDistance(const int32 x, const int32 y, const Point pos) noexcept
		{
			return std::sqrt(static_cast<float>((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y)));
		}
	}

	namespace ImageProcessing
	{
		Array<Image> GenerateMips(const Image& src)
		{
			const uint32 mipCount = CalculateMipCount(src.width(), src.height()) - 1;

			if (mipCount == 0)
			{
				return Array<Image>();
			}

			Array<Image> mipImages(mipCount);

			mipImages[0] = detail::GenerateMip(src);

			for (uint32 i = 1; i < mipCount; ++i)
			{
				mipImages[i] = detail::GenerateMip(mipImages[i - 1]);
			}

			return mipImages;
		}

		Image GenerateSDF(const Image& image, const uint32 scale, const double spread)
		{
			if (!image)
			{
				return Image();
			}

			const size_t num_pixels = image.num_pixels();
			const int32 imageWidth = image.width();
			const int32 imageHeight = image.height();
			const int32 resultWidth = imageWidth / scale;
			const int32 resultHeight = imageHeight / scale;

			Array<detail::SDFPixel> pixels(num_pixels);
			{
				const Color* pSrc = image.data();
				const Color* const pSrcEnd = pSrc + num_pixels;
				detail::SDFPixel* pDst = pixels.data();

				while (pSrc != pSrcEnd)
				{
					pDst->distance = Largest<float>;
					pDst->border.set(-1, -1);
					pDst->white = (pSrc->r == 255);

					++pSrc;
					++pDst;
				}
			}

			{
				detail::SDFPixel* pDst = pixels.data();

				for (int32 y = 0; y < imageHeight; ++y)
				{
					for (int32 x = 0; x < imageWidth; ++x)
					{
						const bool center = pDst->white;
						const bool isEdge = (center &&
							(((0 < x) && (pDst - 1)->white != center)
								|| ((x < imageWidth - 1) && (pDst + 1)->white != center)
								|| ((0 < y) && (pDst - imageWidth)->white != center)
								|| ((y < imageHeight - 1) && (pDst + imageWidth)->white != center)
								));

						if (isEdge)
						{
							pDst->distance = 0.0f;
							pDst->border.set(x, y);
						}

						++pDst;
					}
				}
			}

			{
				constexpr float sqrt2 = 1.41421356237f;
				detail::SDFPixel* pixel = pixels.data();

				for (int32 y = 0; y < imageHeight; ++y)
				{
					const bool y0 = (0 < y);

					for (int32 x = 0; x < imageWidth; ++x)
					{
						{
							const detail::SDFPixel* offsetPixel = (pixel - imageWidth - 1);

							if ((0 < x) && y0 && (offsetPixel->distance + sqrt2) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel - imageWidth);

							if (y0 && (offsetPixel->distance + 1.0f) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel - imageWidth + 1);

							if ((x < imageWidth - 1) && y0 && (offsetPixel->distance + sqrt2) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel - 1);

							if ((0 < x) && (offsetPixel->distance + 1.0f) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						++pixel;
					}
				}

				pixel = pixels.data() + num_pixels - 1;

				for (int32 y = imageHeight - 1; y >= 0; --y)
				{
					const bool yH = (y < imageHeight - 1);

					for (int32 x = imageWidth - 1; x >= 0; --x)
					{
						{
							const detail::SDFPixel* offsetPixel = (pixel + 1);

							if ((x < imageWidth - 1) && (offsetPixel->distance + 1.0f) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel + imageWidth - 1);

							if ((0 < x) && yH && (offsetPixel->distance + sqrt2) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel + imageWidth);

							if (yH && (offsetPixel->distance + 1.0f) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						{
							const detail::SDFPixel* offsetPixel = (pixel + imageWidth + 1);

							if ((x < imageWidth - 1) && yH && (offsetPixel->distance + sqrt2) < pixel->distance)
							{
								pixel->border = offsetPixel->border;
								pixel->distance = detail::CalcDistance(x, y, pixel->border);
							}
						}

						--pixel;
					}
				}
			}

			{
				detail::SDFPixel* pDst = pixels.data();
				detail::SDFPixel* const pDstEnd = pDst + num_pixels;

				while (pDst != pDstEnd)
				{
					if (!pDst->white)
					{
						pDst->distance = -pDst->distance;
					}

					++pDst;
				}
			}

			Image result(resultWidth, resultHeight, Color(255, 255));
			{
				const float div = 1.0f / (scale * scale * static_cast<float>(spread));
				const detail::SDFPixel* pSrcLine = pixels.data();
				Color* pDst = result.data();

				for (int32 y = 0; y < imageHeight; y += scale)
				{
					for (int32 x = 0; x < imageWidth; x += scale)
					{
						const detail::SDFPixel* pSrc = pSrcLine + x;

						float sum = 0.0f;

						for (size_t dy = 0u; dy < scale; ++dy)
						{
							for (size_t dx = 0u; dx < scale; ++dx)
							{
								sum += pSrc[dx].distance;
							}

							pSrc += imageWidth;
						}

						const float d = sum * div;

						const uint8 sd = (d <= -1.0f) ? 0 : (1.0f <= d) ? 255 : static_cast<uint8>((d + 1.0f) * 127.5f + 0.5f);

						(pDst++)->a = sd;
					}

					pSrcLine += (imageWidth * scale);
				}
			}

			return result;
		}
	}
}
