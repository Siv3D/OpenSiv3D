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

# include <opencv2/imgproc.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageRegion.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Quad.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/CPU.hpp>
# include "PaintShape.hpp"

namespace s3d
{
	namespace detail
	{
		namespace simd
		{
			static const __m128 c255 = ::_mm_set_ps1(255.0f);

			static const __m128i c255i = ::_mm_set1_epi32(255);

			static const __m128 inv255 = ::_mm_set_ps1(1.0f / 255.0f);

			static const __m128 inv255pow2 = ::_mm_set_ps1(1.0f / (255.0f*255.0f));

			static const __m128 inv255pow3 = ::_mm_set_ps1(1.0f / (255.0f*255.0f*255.0f));

			static const __m128i toColorShuffleMask = ::_mm_setr_epi8(0, 4, 8, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
		}

		inline uint32* AsUintPtr(Color* p)
		{
			return static_cast<uint32*>(static_cast<void*>(p));
		}

		static void WriteSSE4_1(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;
			const uint32 globalSrcAlpha = color.a;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a;
						const uint32 dstAlpha = 255 - srcAlpha;

						const __m128i dstA = ::_mm_set1_epi32(dstAlpha);
						const __m128i srcA = ::_mm_set1_epi32(srcAlpha);

						const __m128i dsti = ::_mm_cvtepu8_epi32((__m128i&)*pDst); //SSE4.1
						const __m128i srci = ::_mm_cvtepu8_epi32((const __m128i&)*pSrc); //SSE4.1

						const __m128i left = ::_mm_mullo_epi32(dsti, dstA); //SSE4.1
						const __m128i right = ::_mm_mullo_epi32(srci, srcA); //SSE4.1
						const __m128i sumi = ::_mm_add_epi32(left, right);
						const __m128 sum = ::_mm_cvtepi32_ps(sumi);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.r == 255 && color.g == 255 && color.b == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;

						const __m128i dstA = ::_mm_set1_epi32(dstAlpha);
						const __m128i srcA = ::_mm_set1_epi32(srcAlpha);

						const __m128i dsti = ::_mm_cvtepu8_epi32((__m128i&)*pDst); //SSE4.1
						const __m128i srci = ::_mm_cvtepu8_epi32((const __m128i&)*pSrc); //SSE4.1

						const __m128i left = ::_mm_mullo_epi32(dsti, dstA); //SSE4.1
						const __m128i right = ::_mm_mullo_epi32(srci, srcA); //SSE4.1
						const __m128i sumi = ::_mm_add_epi32(left, right);
						const __m128 sum = ::_mm_cvtepi32_ps(sumi);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow2);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.a == 255)
			{
				const __m128i gi = ::_mm_cvtepu8_epi32((__m128i&)color); //SSE4.1

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a;
						const uint32 dstAlpha = 255 - srcAlpha;

						const __m128i dstA = ::_mm_set1_epi32(dstAlpha);
						const __m128i srcA = ::_mm_set1_epi32(srcAlpha);

						const __m128i dsti = ::_mm_cvtepu8_epi32((__m128i&)*pDst); //SSE4.1
						const __m128i srci = ::_mm_cvtepu8_epi32((const __m128i&)*pSrc); //SSE4.1

						const __m128i left = ::_mm_mullo_epi32(::_mm_mullo_epi32(simd::c255i, dsti), dstA); //SSE4.1
						const __m128i right = ::_mm_mullo_epi32(::_mm_mullo_epi32(gi, srci), srcA); //SSE4.1
						const __m128i sumi = ::_mm_add_epi32(left, right);
						const __m128 sum = ::_mm_cvtepi32_ps(sumi);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow2);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else
			{
				const __m128i gi = ::_mm_cvtepu8_epi32((__m128i&)color); //SSE4.1
				const __m128 g = ::_mm_cvtepi32_ps(gi);

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;
						const __m128 dstA = ::_mm_set_ps1(float(dstAlpha));
						const __m128 srcA = ::_mm_set_ps1(float(srcAlpha));

						const __m128i dsti = ::_mm_cvtepu8_epi32((__m128i&)*pDst); //SSE4.1
						const __m128 dst = ::_mm_cvtepi32_ps(dsti);

						const __m128i srci = ::_mm_cvtepu8_epi32((const __m128i&)*pSrc); //SSE4.1
						const __m128 src = ::_mm_cvtepi32_ps(srci);

						const __m128 left = ::_mm_mul_ps(::_mm_mul_ps(simd::c255, dst), dstA);
						const __m128 right = ::_mm_mul_ps(::_mm_mul_ps(g, src), srcA);
						const __m128 sum = ::_mm_add_ps(left, right);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow3);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void WriteSSE3(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;
			const uint32 globalSrcRed = color.r;
			const uint32 globalSrcGreen = color.g;
			const uint32 globalSrcBlue = color.b;
			const uint32 globalSrcAlpha = color.a;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint32 srcAlpha = pSrc->a;

						if (srcAlpha != 255)
						{
							const uint32 dstAlpha = 255 - srcAlpha;
							pDst->r = (pDst->r * dstAlpha + pSrc->r * srcAlpha) / 255;
							pDst->g = (pDst->g * dstAlpha + pSrc->g * srcAlpha) / 255;
							pDst->b = (pDst->b * dstAlpha + pSrc->b * srcAlpha) / 255;
						}
						else
						{
							const uint8 a = pDst->a;

							*pDst = *pSrc;

							pDst->a = a;
						}

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.r == 255 && color.g == 255 && color.b == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;
						const __m128 dstA = ::_mm_set_ps1(float(dstAlpha));
						const __m128 srcA = ::_mm_set_ps1(float(srcAlpha));

						const __m128i dsti = ::_mm_set_epi32(pDst->a, pDst->b, pDst->g, pDst->r);
						const __m128 dst = ::_mm_cvtepi32_ps(dsti);

						const __m128i srci = ::_mm_set_epi32(pSrc->a, pSrc->b, pSrc->g, pSrc->r);
						const __m128 src = ::_mm_cvtepi32_ps(srci);

						const __m128 left = ::_mm_mul_ps(dst, dstA);
						const __m128 right = ::_mm_mul_ps(src, srcA);
						const __m128 sum = ::_mm_add_ps(left, right);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow2);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.a == 255)
			{
				const __m128i gi = ::_mm_set_epi32(255, globalSrcBlue, globalSrcGreen, globalSrcRed);
				const __m128 g = ::_mm_cvtepi32_ps(gi);

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a;
						const uint32 dstAlpha = 255 - srcAlpha;
						const __m128 dstA = ::_mm_set_ps1(float(dstAlpha));
						const __m128 srcA = ::_mm_set_ps1(float(srcAlpha));

						const __m128i dsti = ::_mm_set_epi32(pDst->a, pDst->b, pDst->g, pDst->r);
						const __m128 dst = ::_mm_cvtepi32_ps(dsti);

						const __m128i srci = ::_mm_set_epi32(pSrc->a, pSrc->b, pSrc->g, pSrc->r);
						const __m128 src = ::_mm_cvtepi32_ps(srci);

						const __m128 left = ::_mm_mul_ps(::_mm_mul_ps(simd::c255, dst), dstA);
						const __m128 right = ::_mm_mul_ps(::_mm_mul_ps(g, src), srcA);
						const __m128 sum = ::_mm_add_ps(left, right);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow2);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else
			{
				const __m128i gi = ::_mm_set_epi32(globalSrcAlpha, globalSrcBlue, globalSrcGreen, globalSrcRed);
				const __m128 g = ::_mm_cvtepi32_ps(gi);

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint8 t = pDst->a;
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;
						const __m128 dstA = ::_mm_set_ps1(float(dstAlpha));
						const __m128 srcA = ::_mm_set_ps1(float(srcAlpha));

						const __m128i dsti = ::_mm_set_epi32(pDst->a, pDst->b, pDst->g, pDst->r);
						const __m128 dst = ::_mm_cvtepi32_ps(dsti);

						const __m128i srci = ::_mm_set_epi32(pSrc->a, pSrc->b, pSrc->g, pSrc->r);
						const __m128 src = ::_mm_cvtepi32_ps(srci);

						const __m128 left = ::_mm_mul_ps(::_mm_mul_ps(simd::c255, dst), dstA);
						const __m128 right = ::_mm_mul_ps(::_mm_mul_ps(g, src), srcA);
						const __m128 sum = ::_mm_add_ps(left, right);

						const __m128 result = ::_mm_mul_ps(sum, simd::inv255pow3);
						const __m128i r = _mm_cvtps_epi32(result);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));
						pDst->a = t;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void WriteReference(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;
			const uint32 globalSrcRed = color.r;
			const uint32 globalSrcGreen = color.g;
			const uint32 globalSrcBlue = color.b;
			const uint32 globalSrcAlpha = color.a;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint32 srcAlpha = pSrc->a;

						if (srcAlpha != 255)
						{
							const uint32 dstAlpha = 255 - srcAlpha;
							pDst->r = (pDst->r * dstAlpha + pSrc->r * srcAlpha) / 255;
							pDst->g = (pDst->g * dstAlpha + pSrc->g * srcAlpha) / 255;
							pDst->b = (pDst->b * dstAlpha + pSrc->b * srcAlpha) / 255;
						}
						else
						{
							const uint8 a = pDst->a;

							*pDst = *pSrc;

							pDst->a = a;
						}

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.r == 255 && color.g == 255 && color.b == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;

						pDst->r = (pDst->r * dstAlpha + pSrc->r * srcAlpha) / (255 * 255);
						pDst->g = (pDst->g * dstAlpha + pSrc->g * srcAlpha) / (255 * 255);
						pDst->b = (pDst->b * dstAlpha + pSrc->b * srcAlpha) / (255 * 255);

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.a == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint32 srcAlpha = pSrc->a;

						if (srcAlpha != 255)
						{
							const uint32 dstAlpha = 255 - srcAlpha;
							pDst->r = (255 * pDst->r * dstAlpha + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255);
							pDst->g = (255 * pDst->g * dstAlpha + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255);
							pDst->b = (255 * pDst->b * dstAlpha + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255);
						}
						else
						{
							pDst->r = (globalSrcRed * pSrc->r) / 255;
							pDst->g = (globalSrcGreen * pSrc->g) / 255;
							pDst->b = (globalSrcBlue * pSrc->b) / 255;
						}

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const uint32 srcAlpha = pSrc->a * globalSrcAlpha;
						const uint32 dstAlpha = (255 * 255) - srcAlpha;

						pDst->r = (255 * pDst->r * dstAlpha + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255 * 255);
						pDst->g = (255 * pDst->g * dstAlpha + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255 * 255);
						pDst->b = (255 * pDst->b * dstAlpha + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255 * 255);

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void OverwriteSSE4_1(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					::memcpy(pDst, pSrc, (width * sizeof(Color)));

					pSrc += srcWidth;
					pDst += dstWidth;
				}
			}
			else
			{
				const __m128i gi = ::_mm_cvtepu8_epi32((__m128i&)color); //SSE4.1
				const __m128 g = ::_mm_cvtepi32_ps(gi);
				const __m128 gd = ::_mm_mul_ps(g, simd::inv255);

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const __m128i ci = ::_mm_cvtepu8_epi32((const __m128i&)*pSrc); //SSE4.1
						const __m128 c = ::_mm_cvtepi32_ps(ci);
						const __m128 cgd = ::_mm_mul_ps(c, gd);
						const __m128i r = _mm_cvtps_epi32(cgd);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(r, simd::toColorShuffleMask));

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void OverwriteSSE3(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const s3d::Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					::memcpy(pDst, pSrc, (width * sizeof(Color)));

					pSrc += srcWidth;
					pDst += dstWidth;
				}
			}
			else
			{
				const __m128i gi = ::_mm_set_epi32(color.a, color.b, color.g, color.r);
				const __m128 g = ::_mm_cvtepi32_ps(gi);
				const __m128 gd = ::_mm_mul_ps(g, simd::inv255);

				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						const __m128i ci = ::_mm_set_epi32(pSrc->a, pSrc->b, pSrc->g, pSrc->r);
						const __m128 c = ::_mm_cvtepi32_ps(ci);
						const __m128 cgd = ::_mm_mul_ps(c, gd);
						const __m128i r = _mm_cvtps_epi32(cgd);

						*AsUintPtr(pDst) = ::_mm_cvtsi128_si32(_mm_shuffle_epi8(r, simd::toColorShuffleMask));

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void OverwriteReference(
			const Color* pSrc,
			Color* pDst,
			int32 width,
			int32 height,
			int32 srcWidth,
			int32 dstWidth,
			const Color& color)
		{
			const int32 srcStepOffset = srcWidth - width;
			const int32 dstStepOffset = dstWidth - width;
			const uint32 globalSrcRed = color.r;
			const uint32 globalSrcGreen = color.g;
			const uint32 globalSrcBlue = color.b;
			const uint32 globalSrcAlpha = color.a;

			if (color == Palette::White)
			{
				for (int32 y = 0; y < height; ++y)
				{
					::memcpy(pDst, pSrc, (width * sizeof(Color)));

					pSrc += srcWidth;
					pDst += dstWidth;
				}
			}
			else if (color.r == 255 && color.g == 255 && color.b == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						*pDst = *pSrc;

						pDst->a = (pSrc->a * globalSrcAlpha) / 255;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else if (color.a == 255)
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						pDst->r = (pSrc->r * globalSrcRed) / 255;
						pDst->g = (pSrc->g * globalSrcGreen) / 255;
						pDst->b = (pSrc->b * globalSrcBlue) / 255;
						pDst->a = pSrc->a;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
			else
			{
				for (int32 y = 0; y < height; ++y)
				{
					for (int32 x = 0; x < width; ++x)
					{
						pDst->r = (pSrc->r * globalSrcRed) / 255;
						pDst->g = (pSrc->g * globalSrcGreen) / 255;
						pDst->b = (pSrc->b * globalSrcBlue) / 255;
						pDst->a = (pSrc->a * globalSrcAlpha) / 255;

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		static void WritePaintBufferReference(
			Color* dst,
			const uint32* offsets,
			size_t offsetCount,
			const Color& color)
		{
			const uint32 srcBlend = color.a;
			const uint32 dstBlend = 255 - srcBlend;
			const uint32 premulSrcR = srcBlend * color.r;
			const uint32 premulSrcG = srcBlend * color.g;
			const uint32 premulSrcB = srcBlend * color.b;
			
			for (size_t i = 0; i < offsetCount; ++i)
			{
				Color* pDst = dst + offsets[i];
				pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
				pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
				pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
			}
		}
	}

	void Image::paint(Image& dst, const Point& pos, const Color& color) const
	{
		if (this == &dst)
		{
			return;
		}

		const Image& src = *this;

		const int32 dstXBegin = std::max(pos.x, 0);
		const int32 dstYBegin = std::max(pos.y, 0);
		const int32 dstXEnd = std::min(pos.x + src.width(), dst.width());
		const int32 dstYEnd = std::min(pos.y + src.height(), dst.height());
		const int32 writeWidth = dstXEnd - dstXBegin;
		const int32 writeHeight = dstYEnd - dstYBegin;

		if (writeWidth <= 0 || writeHeight <= 0)
		{
			return;
		}

		const int32 srcXBegin = std::max(0, -pos.x);
		const int32 srcYBegin = std::max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();

		const CPUFeature cpu = CPU::GetFeature();

		if (cpu.SSE41)
		{
			detail::WriteSSE4_1(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else if (cpu.SSE3)
		{
			detail::WriteSSE3(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else
		{
			detail::WriteReference(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
	}

	void Image::overwrite(Image& dst, const Point& pos, const Color& color) const
	{
		if (this == &dst)
		{
			return;
		}

		const Image& src = *this;

		const int32 dstXBegin = std::max(pos.x, 0);
		const int32 dstYBegin = std::max(pos.y, 0);
		const int32 dstXEnd = std::min(pos.x + src.width(), dst.width());
		const int32 dstYEnd = std::min(pos.y + src.height(), dst.height());
		const int32 writeWidth = (dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0;
		const int32 writeHeight = (dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0;

		if (writeWidth*writeHeight == 0)
		{
			return;
		}

		const int32 srcXBegin = std::max(0, -pos.x);
		const int32 srcYBegin = std::max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();

		const CPUFeature cpu = CPU::GetFeature();

		if (cpu.SSE41)
		{
			detail::OverwriteSSE4_1(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else if (cpu.SSE3)
		{
			detail::OverwriteSSE3(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else
		{
			detail::OverwriteReference(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
	}

	void ImageRegion::paint(Image& dst, const Point& pos, const Color& color) const
	{
		if (&m_imageRef == &dst)
		{
			return;
		}

		const Image& src = m_imageRef;

		if (!src)
		{
			return;
		}

		const Rect& rect = m_rect;

		if (rect.w <= 0 || rect.h <= 0)
		{
			return;
		}

		const int32 srcMapOriginX = pos.x - rect.x;
		const int32 srcMapOriginY = pos.y - rect.y;

		const int32 srcMapXBegin = std::max(srcMapOriginX, pos.x);
		const int32 srcMapYBegin = std::max(srcMapOriginY, pos.y);

		const int32 srcMapXEnd = std::min(pos.x + rect.w, srcMapOriginX + src.width());
		const int32 srcMapYEnd = std::min(pos.y + rect.h, srcMapOriginY + src.height());

		const int32 fillMapXBegin = Clamp(srcMapXBegin, 0, dst.width());
		const int32 fillMapXEnd = Clamp(srcMapXEnd, 0, dst.width());

		const int32 fillMapYBegin = Clamp(srcMapYBegin, 0, dst.height());
		const int32 fillMapYEnd = Clamp(srcMapYEnd, 0, dst.height());

		const int32 writeWidth = fillMapXEnd - fillMapXBegin;
		const int32 writeHeight = fillMapYEnd - fillMapYBegin;

		if (writeWidth <= 0 || writeHeight <= 0)
		{
			return;
		}

		const int32 sY = fillMapYBegin - srcMapOriginY;
		const int32 sX = fillMapXBegin - srcMapOriginX;

		const Color* pSrc = &src[sY][sX];
		Color* pDst = &dst[fillMapYBegin][fillMapXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();

		const CPUFeature cpu = CPU::GetFeature();

		if (cpu.SSE41)
		{
			detail::WriteSSE4_1(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else if (cpu.SSE3)
		{
			detail::WriteSSE3(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else
		{
			detail::WriteReference(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
	}

	void ImageRegion::overwrite(Image& dst, const Point& pos, const Color& color) const
	{
		if (&m_imageRef == &dst)
		{
			return;
		}

		const Image& src = m_imageRef;

		if (!src)
		{
			return;
		}

		const Rect& rect = m_rect;

		if (rect.w <= 0 || rect.h <= 0)
		{
			return;
		}

		const int32 srcMapOriginX = pos.x - rect.x;
		const int32 srcMapOriginY = pos.y - rect.y;

		const int32 srcMapXBegin = std::max(srcMapOriginX, pos.x);
		const int32 srcMapYBegin = std::max(srcMapOriginY, pos.y);

		const int32 srcMapXEnd = std::min(pos.x + rect.w, srcMapOriginX + src.width());
		const int32 srcMapYEnd = std::min(pos.y + rect.h, srcMapOriginY + src.height());

		const int32 fillMapXBegin = Clamp(srcMapXBegin, 0, dst.width());
		const int32 fillMapXEnd = Clamp(srcMapXEnd, 0, dst.width());

		const int32 fillMapYBegin = Clamp(srcMapYBegin, 0, dst.height());
		const int32 fillMapYEnd = Clamp(srcMapYEnd, 0, dst.height());

		const int32 writeWidth = fillMapXEnd - fillMapXBegin;
		const int32 writeHeight = fillMapYEnd - fillMapYBegin;

		if (writeWidth <= 0 || writeHeight <= 0)
		{
			return;
		}

		const int32 sY = fillMapYBegin - srcMapOriginY;
		const int32 sX = fillMapXBegin - srcMapOriginX;

		const Color* pSrc = &src[sY][sX];
		Color* pDst = &dst[fillMapYBegin][fillMapXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();

		const CPUFeature cpu = CPU::GetFeature();

		if (cpu.SSE41)
		{
			detail::OverwriteSSE4_1(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else if (cpu.SSE3)
		{
			detail::OverwriteSSE3(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
		else
		{
			detail::OverwriteReference(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
		}
	}

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

	const Line& Line::paint(Image& dst, const Color& color) const
	{
		return paint(dst, 1, color);
	}

	const Line& Line::paint(Image& dst, int32 thickness, const Color& color) const
	{
		if (!dst || thickness < 1)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintLine(paintBuffer, *this, dst.width(), dst.height(), thickness);

		if (paintBuffer)
		{
			detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);
		}

		return *this;
	}

	const Line& Line::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const Line& Line::overwrite(Image& dst, int32 thickness, const Color& color, const bool antialiased) const
	{
		if (!dst || thickness < 1)
		{
			return *this;
		}

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		cv::line(mat,
			{ static_cast<int32>(begin.x), static_cast<int32>(begin.y) },
			{ static_cast<int32>(end.x), static_cast<int32>(end.y) },
			cv::Scalar(color.r, color.g, color.b, color.a), thickness, antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}

	const Circle& Circle::paint(Image& dst, const Color& color, const bool antialiased) const
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

	const Circle& Circle::overwrite(Image& dst, const Color& color, const bool antialiased) const
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

		if (antialiased)
		{
			const Vec2 center2(center.movedBy(-0.5, -0.5));
			const double length = std::sqrt(lengthSq);

			for (int32 _y = yBegin; _y < yEnd; ++_y)
			{
				for (int32 _x = xBegin; _x < xEnd; ++_x)
				{
					const double d = length - center2.distanceFrom(Vec2(_x, _y));

					if (d > 1.0)
					{
						*pDst = color;
					}
					else if (d > 0.0)
					{
						const uint32 srcBlend2 = static_cast<uint32>(255 * d);
						const uint32 premulSrcR = srcBlend2 * color.r;
						const uint32 premulSrcG = srcBlend2 * color.g;
						const uint32 premulSrcB = srcBlend2 * color.b;
						const uint32 premulSrcA = srcBlend2 * color.a;
						const uint32 dstBlend = 255 - srcBlend2;

						pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
						pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
						pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
						pDst->a = (pDst->a * dstBlend + premulSrcA) / 255;
					}

					++pDst;
				}

				pDst += stepOffset;
			}
		}
		else
		{
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
		}

		return *this;
	}

	const Circle& Circle::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color, const bool antialiased) const
	{
		const int32 yBegin	= std::max(static_cast<int32>(y - r - outerThickness), 0);
		const int32 yEnd	= std::min(static_cast<int32>(y + r + 1 + outerThickness), dst.height());
		const int32 xBegin	= std::max(static_cast<int32>(x - r - outerThickness), 0);
		const int32 xEnd	= std::min(static_cast<int32>(x + r + 1 + outerThickness), dst.width());

		const int32 fillWidth	= xEnd - xBegin;
		const int32 fillHeight	= yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stepOffset = dst.width() - fillWidth;
		const double lengthOuterSq = (r + outerThickness + 0.5) * (r + outerThickness + 0.5);
		const double lengthInnerSq = (r - innerThickness + 0.5) * (r - innerThickness + 0.5);

		const uint32 srcBlend = color.a;

		if (antialiased)
		{
			const double lengthInner0 = std::sqrt(lengthInnerSq) - 0.5;
			const double lengthInner1 = std::sqrt(lengthInnerSq) + 0.5;
			const double lengthOuter0 = std::sqrt(lengthOuterSq) - 0.5;
			const double lengthOuter1 = std::sqrt(lengthOuterSq) + 0.5;

			if (srcBlend == 255)
			{
				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						const double length = center.distanceFrom({ _x, _y });

						if (lengthInner0 < length && length < lengthOuter1)
						{
							if (length < lengthInner1)
							{
								const double d = length - lengthInner0;
								const uint32 srcBlend2 = static_cast<uint32>(255 * d);
								const uint32 premulSrcR = srcBlend2 * color.r;
								const uint32 premulSrcG = srcBlend2 * color.g;
								const uint32 premulSrcB = srcBlend2 * color.b;
								const uint32 dstBlend = 255 - srcBlend2;

								pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
								pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
								pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
							}
							else if (lengthOuter0 < length)
							{
								const double d = lengthOuter1 - length;
								const uint32 srcBlend2 = static_cast<uint32>(255 * d);
								const uint32 premulSrcR = srcBlend2 * color.r;
								const uint32 premulSrcG = srcBlend2 * color.g;
								const uint32 premulSrcB = srcBlend2 * color.b;
								const uint32 dstBlend = 255 - srcBlend2;

								pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
								pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
								pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
							}
							else
							{
								const uint8 a = pDst->a;
								*pDst = color;
								pDst->a = a;
							}
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
			else
			{
				const uint32 dstBlend = 255 - srcBlend;
				const uint32 premulSrcR = srcBlend * color.r;
				const uint32 premulSrcG = srcBlend * color.g;
				const uint32 premulSrcB = srcBlend * color.b;

				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						const double length = center.distanceFrom({ _x, _y });

						if (lengthInner0 < length && length < lengthOuter1)
						{
							if (length < lengthInner1)
							{
								const double d = length - lengthInner0;
								const uint32 srcBlend2 = static_cast<uint32>(srcBlend * d);
								const uint32 premulSrcR2 = srcBlend2 * color.r;
								const uint32 premulSrcG2 = srcBlend2 * color.g;
								const uint32 premulSrcB2 = srcBlend2 * color.b;
								const uint32 dstBlend2 = 255 - srcBlend2;

								pDst->r = (pDst->r * dstBlend2 + premulSrcR2) / 255;
								pDst->g = (pDst->g * dstBlend2 + premulSrcG2) / 255;
								pDst->b = (pDst->b * dstBlend2 + premulSrcB2) / 255;
							}
							else if (lengthOuter0 < length)
							{
								const double d = lengthOuter1 - length;
								const uint32 srcBlend2 = static_cast<uint32>(srcBlend * d);
								const uint32 premulSrcR2 = srcBlend2 * color.r;
								const uint32 premulSrcG2 = srcBlend2 * color.g;
								const uint32 premulSrcB2 = srcBlend2 * color.b;
								const uint32 dstBlend2 = 255 - srcBlend2;

								pDst->r = (pDst->r * dstBlend2 + premulSrcR2) / 255;
								pDst->g = (pDst->g * dstBlend2 + premulSrcG2) / 255;
								pDst->b = (pDst->b * dstBlend2 + premulSrcB2) / 255;
							}
							else
							{
								pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
								pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
								pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
							}
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
						const double lengthSq = center.distanceFromSq({ _x, _y });

						if (lengthInnerSq <= lengthSq && lengthSq <= lengthOuterSq)
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
				const uint32 dstBlend = 255 - srcBlend;
				const uint32 premulSrcR = srcBlend * color.r;
				const uint32 premulSrcG = srcBlend * color.g;
				const uint32 premulSrcB = srcBlend * color.b;

				for (int32 _y = yBegin; _y < yEnd; ++_y)
				{
					for (int32 _x = xBegin; _x < xEnd; ++_x)
					{
						const double lengthSq = center.distanceFromSq({ _x, _y });

						if (lengthInnerSq <= lengthSq && lengthSq <= lengthOuterSq)
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

	const Circle& Circle::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color, const bool antialiased) const
	{
		const int32 yBegin	= std::max(static_cast<int32>(y - r - outerThickness), 0);
		const int32 yEnd	= std::min(static_cast<int32>(y + r + 1 + outerThickness), dst.height());
		const int32 xBegin	= std::max(static_cast<int32>(x - r - outerThickness), 0);
		const int32 xEnd	= std::min(static_cast<int32>(x + r + 1 + outerThickness), dst.width());

		const int32 fillWidth	= xEnd - xBegin;
		const int32 fillHeight	= yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stepOffset = dst.width() - fillWidth;
		const double lengthOuterSq = (r + outerThickness + 0.5) * (r + outerThickness + 0.5);
		const double lengthInnerSq = (r - innerThickness + 0.5) * (r - innerThickness + 0.5);

		if (antialiased)
		{
			const double lengthInner0 = std::sqrt(lengthInnerSq) - 0.5;
			const double lengthInner1 = std::sqrt(lengthInnerSq) + 0.5;
			const double lengthOuter0 = std::sqrt(lengthOuterSq) - 0.5;
			const double lengthOuter1 = std::sqrt(lengthOuterSq) + 0.5;

			for (int32 _y = yBegin; _y < yEnd; ++_y)
			{
				for (int32 _x = xBegin; _x < xEnd; ++_x)
				{
					const double length = center.distanceFrom({ _x, _y });

					if (lengthInner0 < length && length < lengthOuter1)
					{
						if (length < lengthInner1)
						{
							const double d = length - lengthInner0;
							const uint32 srcBlend2 = static_cast<uint32>(255 * d);
							const uint32 premulSrcR = srcBlend2 * color.r;
							const uint32 premulSrcG = srcBlend2 * color.g;
							const uint32 premulSrcB = srcBlend2 * color.b;
							const uint32 premulSrcA = srcBlend2 * color.a;
							const uint32 dstBlend = 255 - srcBlend2;

							pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
							pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
							pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
							pDst->a = (pDst->a * dstBlend + premulSrcA) / 255;
						}
						else if (lengthOuter0 < length)
						{
							const double d = lengthOuter1 - length;
							const uint32 srcBlend2 = static_cast<uint32>(255 * d);
							const uint32 premulSrcR = srcBlend2 * color.r;
							const uint32 premulSrcG = srcBlend2 * color.g;
							const uint32 premulSrcB = srcBlend2 * color.b;
							const uint32 premulSrcA = srcBlend2 * color.a;
							const uint32 dstBlend = 255 - srcBlend2;

							pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
							pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
							pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;
							pDst->a = (pDst->a * dstBlend + premulSrcA) / 255;
						}
						else
						{
							*pDst = color;
						}
					}

					++pDst;
				}

				pDst += stepOffset;
			}
		}
		else
		{
			for (int32 _y = yBegin; _y < yEnd; ++_y)
			{
				for (int32 _x = xBegin; _x < xEnd; ++_x)
				{
					const double lengthSq = center.distanceFromSq({ _x, _y });

					if (lengthInnerSq <= lengthSq && lengthSq <= lengthOuterSq)
					{
						*pDst = color;
					}

					++pDst;
				}

				pDst += stepOffset;
			}
		}

		return *this;
	}

	const Ellipse& Ellipse::paint(Image& dst, const Color& color) const
	{
		const int32 yBegin = std::max(static_cast<int32>(y - b), 0);
		const int32 yEnd = std::min(static_cast<int32>(y + b + 1), dst.height());
		const int32 xBegin = std::max(static_cast<int32>(x - a), 0);
		const int32 xEnd = std::min(static_cast<int32>(x + a + 1), dst.width());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		const int32 stepOffset = dst.width() - fillWidth;
		const double aa = ((a + 0.5) * (a + 0.5));
		const double bb = ((b + 0.5) * (b + 0.5));
		const double aabb = aa * bb;

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;

		const uint32 srcBlend = color.a;

		if (srcBlend == 255)
		{
			for (int32 _y = yBegin; _y < yEnd; ++_y)
			{
				for (int32 _x = xBegin; _x < xEnd; ++_x)
				{
					const double xxh = (x - _x);
					const double yyk = (y - _y);

					if ((bb * xxh * xxh + aa * yyk * yyk) <= aabb)
					{
						const uint8 ta = pDst->a;
						*pDst = color;
						pDst->a = ta;
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
					const double xxh = (x - _x);
					const double yyk = (y - _y);

					if ((bb * xxh * xxh + aa * yyk * yyk) <= aabb)
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

		return *this;
	}

	const Ellipse& Ellipse::overwrite(Image& dst, const Color& color) const
	{
		const int32 yBegin	= std::max(static_cast<int32>(y - b), 0);
		const int32 yEnd	= std::min(static_cast<int32>(y + b + 1), dst.height());
		const int32 xBegin	= std::max(static_cast<int32>(x - a), 0);
		const int32 xEnd	= std::min(static_cast<int32>(x + a + 1), dst.width());
		const int32 fillWidth	= xEnd - xBegin;
		const int32 fillHeight	= yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		const int32 stepOffset = dst.width() - fillWidth;
		const double aa = ((a + 0.5) * (a + 0.5));
		const double bb = ((b + 0.5) * (b + 0.5));
		const double aabb = aa * bb;

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;

		for (int32 _y = yBegin; _y < yEnd; ++_y)
		{
			for (int32 _x = xBegin; _x < xEnd; ++_x)
			{
				const double xxh = (x - _x);
				const double yyk = (y - _y);

				if ((bb * xxh * xxh + aa * yyk * yyk) <= aabb)
				{
					*pDst = color;
				}

				++pDst;
			}

			pDst += stepOffset;
		}

		return *this;
	}

	const Triangle& Triangle::paint(Image& dst, const Color& color) const
	{
		if (!dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintTriangle(paintBuffer, *this, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Triangle& Triangle::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		if (!dst)
		{
			return *this;
		}

		const cv::Point pts[3] =
		{
			cv::Point(static_cast<int32>(p0.x), static_cast<int32>(p0.y)),
			cv::Point(static_cast<int32>(p1.x), static_cast<int32>(p1.y)),
			cv::Point(static_cast<int32>(p2.x), static_cast<int32>(p2.y)),
		};

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		cv::fillConvexPoly(mat, pts, 3, cv::Scalar(color.r, color.g, color.b, color.a), antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}

	const Quad& Quad::paint(Image& dst, const Color& color) const
	{
		if (!dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintQuad(paintBuffer, *this, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Quad& Quad::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		if (!dst)
		{
			return *this;
		}

		const cv::Point pts[4] =
		{
			cv::Point(static_cast<int32>(p0.x), static_cast<int32>(p0.y)),
			cv::Point(static_cast<int32>(p1.x), static_cast<int32>(p1.y)),
			cv::Point(static_cast<int32>(p2.x), static_cast<int32>(p2.y)),
			cv::Point(static_cast<int32>(p3.x), static_cast<int32>(p3.y)),
		};

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		cv::fillConvexPoly(mat, pts, 4, cv::Scalar(color.r, color.g, color.b, color.a), antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}

	const LineString& LineString::paint(Image& dst, const int32 thickness, const Color& color, const bool isClosed) const
	{
		if (!dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintLineString(paintBuffer, *this, dst.width(), dst.height(), thickness, isClosed);

		if (paintBuffer.empty())
		{
			return *this;
		}

		detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const LineString& LineString::overwrite(Image& dst, const int32 thickness, const Color& color, const bool isClosed, const bool antialiased) const
	{
		if (!dst || isEmpty())
		{
			return *this;
		}

		Array<cv::Point> points;

		points.reserve(size());

		for (const auto& p : *this)
		{
			points.emplace_back(static_cast<int32>(p.x), static_cast<int32>(p.y));
		}

		const int32 n = static_cast<int32>(points.size());
		const cv::Point* ptr = points.data();
		const cv::Point** pptr = &ptr;

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		cv::polylines(mat, pptr, &n, 1, isClosed, cv::Scalar(color.r, color.g, color.b, color.a), thickness, antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}

	const Polygon& Polygon::paint(Image& dst, const Color& color) const
	{
		if (!dst || isEmpty())
		{
			return *this;
		}

		//
		// outer
		//
		Array<Point> outerPts;

		for (const auto& pt : outer())
		{
			outerPts.push_back(pt.asPoint());
		}

		//
		//	holes
		//
		Array<Array<Point>> holePtsList(inners().size());

		uint32 holeIndex = 0;

		for (const auto& hole : inners())
		{
			for (const auto& pt : hole)
			{
				holePtsList[holeIndex].push_back(pt.asPoint());
			}

			++holeIndex;
		}

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		Array<const Point*> ppts;
		{
			ppts.push_back(outerPts.data());

			for (const auto& hole : holePtsList)
			{
				ppts.push_back(hole.data());
			}
		}

		Array<int32> npts;
		{
			npts.push_back(static_cast<int32>(outerPts.size()));

			for (const auto& hole : holePtsList)
			{
				npts.push_back(static_cast<int32>(hole.size()));
			}
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintPolygon(paintBuffer, ppts, npts, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Polygon& Polygon::paint(Image& dst, const double x, const double y, const Color& color) const
	{
		return paint(dst, Vec2(x, y), color);
	}

	const Polygon& Polygon::paint(Image& dst, const Vec2& pos, const Color& color) const
	{
		if (!dst || isEmpty())
		{
			return *this;
		}

		//
		// outer
		//
		Array<Point> outerPts;

		for (const auto& pt : outer())
		{
			outerPts.push_back((pt + pos).asPoint());
		}

		//
		//	holes
		//
		Array<Array<Point>> holePtsList(inners().size());

		uint32 holeIndex = 0;

		for (const auto& hole : inners())
		{
			for (const auto& pt : hole)
			{
				holePtsList[holeIndex].push_back((pt + pos).asPoint());
			}

			++holeIndex;
		}

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		Array<const Point*> ppts;
		{
			ppts.push_back(outerPts.data());

			for (const auto& hole : holePtsList)
			{
				ppts.push_back(hole.data());
			}
		}

		Array<int32> npts;
		{
			npts.push_back(static_cast<int32>(outerPts.size()));

			for (const auto& hole : holePtsList)
			{
				npts.push_back(static_cast<int32>(hole.size()));
			}
		}

		Array<uint32> paintBuffer;

		PaintShape::PaintPolygon(paintBuffer, ppts, npts, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		detail::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Polygon& Polygon::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		if (!dst || isEmpty())
		{
			return *this;
		}

		//
		// outer
		//
		Array<cv::Point> outerPts;

		for (const auto& pt : outer())
		{
			outerPts.emplace_back(static_cast<int32>(pt.x), static_cast<int32>(pt.y));
		}

		//
		//	holes
		//
		Array<Array<cv::Point>> holePtsList(inners().size());

		uint32 holeIndex = 0;

		for (const auto& hole : inners())
		{
			for (const auto& pt : hole)
			{
				holePtsList[holeIndex].emplace_back(static_cast<int32>(pt.x), static_cast<int32>(pt.y));
			}

			++holeIndex;
		}

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		Array<const cv::Point*> ppts;
		{
			ppts.push_back(outerPts.data());

			for (const auto& hole : holePtsList)
			{
				ppts.push_back(hole.data());
			}
		}

		Array<int32> npts;
		{
			npts.push_back(static_cast<int32>(outerPts.size()));

			for (const auto& hole : holePtsList)
			{
				npts.push_back(static_cast<int32>(hole.size()));
			}
		}

		cv::fillPoly(mat, ppts.data(), npts.data(), static_cast<int32>(ppts.size()),
			cv::Scalar(color.r, color.g, color.b, color.a),
			antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}

	const Polygon& Polygon::overwrite(Image& dst, const double x, const double y, const Color& color, const bool antialiased) const
	{
		return overwrite(dst, Vec2(x, y), color, antialiased);
	}

	const Polygon& Polygon::overwrite(Image& dst, const Vec2& pos, const Color& color, const bool antialiased) const
	{
		if (!dst || isEmpty())
		{
			return *this;
		}

		//
		// outer
		//
		Array<cv::Point> outerPts;

		for (const auto& pt : outer())
		{
			outerPts.emplace_back(static_cast<int32>(pt.x + pos.x), static_cast<int32>(pt.y + pos.y));
		}

		//
		//	holes
		//
		Array<Array<cv::Point>> holePtsList(inners().size());

		uint32 holeIndex = 0;

		for (const auto& hole : inners())
		{
			for (const auto& pt : hole)
			{
				holePtsList[holeIndex].emplace_back(static_cast<int32>(pt.x + pos.x), static_cast<int32>(pt.y + pos.y));
			}

			++holeIndex;
		}

		cv::Mat_<cv::Vec4b> mat(dst.height(), dst.width(), static_cast<cv::Vec4b*>(static_cast<void*>(dst.data())), dst.stride());

		Array<const cv::Point*> ppts;
		{
			ppts.push_back(outerPts.data());

			for (const auto& hole : holePtsList)
			{
				ppts.push_back(hole.data());
			}
		}

		Array<int32> npts;
		{
			npts.push_back(static_cast<int32>(outerPts.size()));

			for (const auto& hole : holePtsList)
			{
				npts.push_back(static_cast<int32>(hole.size()));
			}
		}

		cv::fillPoly(mat, ppts.data(), npts.data(), static_cast<int32>(ppts.size()),
			cv::Scalar(color.r, color.g, color.b, color.a),
			antialiased ? cv::LINE_AA : cv::LINE_8);

		return *this;
	}
}
