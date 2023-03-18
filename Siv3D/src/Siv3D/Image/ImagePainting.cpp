//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/CPUInfo.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>
# include "ImagePainting.hpp"
# include "ShapePainting.hpp"

namespace s3d
{
	namespace ImagePainting
	{
		[[nodiscard]]
		inline uint32* AsUintPtr(Color* p)
		{
			return static_cast<uint32*>(static_cast<void*>(p));
		}

	# if SIV3D_INTRINSIC(SSE)

		namespace simd
		{
			static const __m128 c255 = ::_mm_set_ps1(255.0f);

			static const __m128i c255i = ::_mm_set1_epi32(255);

			static const __m128 inv255 = ::_mm_set_ps1(1.0f / 255.0f);

			static const __m128 inv255pow2 = ::_mm_set_ps1(1.0f / (255.0f * 255.0f));

			static const __m128 inv255pow3 = ::_mm_set_ps1(1.0f / (255.0f * 255.0f * 255.0f));

			static const __m128i toColorShuffleMask = ::_mm_setr_epi8(0, 4, 8, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
		}

		void Paint_SSE4_1(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
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

		void Paint_SSE3(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
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
							pDst->r = static_cast<uint8>((pDst->r * dstAlpha + pSrc->r * srcAlpha) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstAlpha + pSrc->g * srcAlpha) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstAlpha + pSrc->b * srcAlpha) / 255);
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

	# endif
		
		void Paint_Reference(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
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
							pDst->r = static_cast<uint8>((pDst->r * dstAlpha + pSrc->r * srcAlpha) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstAlpha + pSrc->g * srcAlpha) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstAlpha + pSrc->b * srcAlpha) / 255);
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

						pDst->r = static_cast<uint8>((pDst->r * dstAlpha + pSrc->r * srcAlpha) / (255 * 255));
						pDst->g = static_cast<uint8>((pDst->g * dstAlpha + pSrc->g * srcAlpha) / (255 * 255));
						pDst->b = static_cast<uint8>((pDst->b * dstAlpha + pSrc->b * srcAlpha) / (255 * 255));

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
							pDst->r = static_cast<uint8>((255 * pDst->r * dstAlpha + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255));
							pDst->g = static_cast<uint8>((255 * pDst->g * dstAlpha + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255));
							pDst->b = static_cast<uint8>((255 * pDst->b * dstAlpha + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255));
						}
						else
						{
							pDst->r = static_cast<uint8>((globalSrcRed * pSrc->r) / 255);
							pDst->g = static_cast<uint8>((globalSrcGreen * pSrc->g) / 255);
							pDst->b = static_cast<uint8>((globalSrcBlue * pSrc->b) / 255);
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

						pDst->r = static_cast<uint8>((255 * pDst->r * dstAlpha + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255 * 255));
						pDst->g = static_cast<uint8>((255 * pDst->g * dstAlpha + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255 * 255));
						pDst->b = static_cast<uint8>((255 * pDst->b * dstAlpha + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255 * 255));

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		void Paint(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
		{
		# if SIV3D_INTRINSIC(SSE)

			if (const CPUInfo& cpu = GetCPUInfo(); 
				cpu.features.sse4_1)
			{
				return Paint_SSE4_1(pSrc, pDst, width, height, srcWidth, dstWidth, color);
			}
			else if (cpu.features.sse3)
			{
				return  Paint_SSE3(pSrc, pDst, width, height, srcWidth, dstWidth, color);
			}

		# endif
		
			Paint_Reference(pSrc, pDst, width, height, srcWidth, dstWidth, color);
		}

		void Stamp_Reference(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
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
						const uint32 dstAlpha = pDst->a;

						if (srcAlpha == 255)
						{
							*pDst = *pSrc;
						}
						else if (dstAlpha == 0)
						{
							*pDst = *pSrc;
						}
						else
						{
							const uint32 dstBlend = (255 - srcAlpha);
							pDst->r = static_cast<uint8>((pDst->r * dstBlend + pSrc->r * srcAlpha) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + pSrc->g * srcAlpha) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + pSrc->b * srcAlpha) / 255);
							pDst->a = Max(pSrc->a, pDst->a);
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
						const uint32 srcAlpha = (pSrc->a * globalSrcAlpha);
						const uint32 dstBlend = (255 * 255) - srcAlpha;
						const uint32 dstAlpha = pDst->a;

						if (dstAlpha == 0)
						{
							pDst->r = pSrc->r;
							pDst->g = pSrc->g;
							pDst->b = pSrc->b;
							pDst->a = static_cast<uint8>(srcAlpha / 255);
						}
						else
						{
							pDst->r = static_cast<uint8>((pDst->r * dstBlend + pSrc->r * srcAlpha) / (255 * 255));
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + pSrc->g * srcAlpha) / (255 * 255));
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + pSrc->b * srcAlpha) / (255 * 255));
							pDst->a = static_cast<uint8>(Max((srcAlpha / 255), dstAlpha));
						}

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
							const uint32 dstBlend = 255 - srcAlpha;
							pDst->r = static_cast<uint8>((255 * pDst->r * dstBlend + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255));
							pDst->g = static_cast<uint8>((255 * pDst->g * dstBlend + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255));
							pDst->b = static_cast<uint8>((255 * pDst->b * dstBlend + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255));
							pDst->a = Max(pSrc->a, pDst->a);
						}
						else
						{
							pDst->r = static_cast<uint8>((globalSrcRed * pSrc->r) / 255);
							pDst->g = static_cast<uint8>((globalSrcGreen * pSrc->g) / 255);
							pDst->b = static_cast<uint8>((globalSrcBlue * pSrc->b) / 255);
							pDst->a = Max(pSrc->a, pDst->a);
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
						const uint32 dstBlend = (255 * 255) - srcAlpha;
						const uint32 dstAlpha = pDst->a;

						pDst->r = static_cast<uint8>((255 * pDst->r * dstBlend + globalSrcRed * pSrc->r * srcAlpha) / (255 * 255 * 255));
						pDst->g = static_cast<uint8>((255 * pDst->g * dstBlend + globalSrcGreen * pSrc->g * srcAlpha) / (255 * 255 * 255));
						pDst->b = static_cast<uint8>((255 * pDst->b * dstBlend + globalSrcBlue * pSrc->b * srcAlpha) / (255 * 255 * 255));
						pDst->a = static_cast<uint8>(Max((srcAlpha / 255), dstAlpha));

						++pSrc;
						++pDst;
					}

					pSrc += srcStepOffset;
					pDst += dstStepOffset;
				}
			}
		}

		void Stamp(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth, const Color color)
		{
			Stamp_Reference(pSrc, pDst, width, height, srcWidth, dstWidth, color);
		}

		void Overwrite(const Color* pSrc, Color* pDst,
			const int32 width, const int32 height, const int32 srcWidth, const int32 dstWidth)
		{
			const size_t stride_bytes = (width * sizeof(Color));

			for (int32 y = 0; y < height; ++y)
			{
				std::memcpy(pDst, pSrc, stride_bytes);
				pSrc += srcWidth;
				pDst += dstWidth;
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
				pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
				pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
				pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
			}
		}
	}

	const Line& Line::paint(Image& dst, const Color& color) const
	{
		return paint(dst, 1, color);
	}

	const Line& Line::paint(Image& dst, int32 thickness, const Color& color) const
	{
		if ((not dst) || (thickness < 1))
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		ShapePainting::PaintLine(paintBuffer, *this, dst.width(), dst.height(), thickness);

		if (paintBuffer)
		{
			ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);
		}

		return *this;
	}

	const Line& Line::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const Line& Line::overwrite(Image& dst, int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		if ((not dst) || (thickness < 1))
		{
			return *this;
		}

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);
		cv::line(mat,
			{ static_cast<int32>(begin.x), static_cast<int32>(begin.y) },
			{ static_cast<int32>(end.x), static_cast<int32>(end.y) },
			cv::Scalar(color.r, color.g, color.b, color.a), thickness, (antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}

	const Circle& Circle::paint(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		const int32 yBegin = Max(static_cast<int32>(y - r - 1), 0);
		const int32 yEnd = Min(static_cast<int32>(y + r + 1), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - r - 1), 0);
		const int32 xEnd = Min(static_cast<int32>(x + r + 1), dst.width());
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
						else if (d > 0.0)
						{
							const uint32 srcBlend2 = static_cast<uint32>(255 * d);
							const uint32 premulSrcR = srcBlend2 * color.r;
							const uint32 premulSrcG = srcBlend2 * color.g;
							const uint32 premulSrcB = srcBlend2 * color.b;
							const uint32 dstBlend = 255 - srcBlend2;

							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
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
							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
						}
						else if (d > 0.0)
						{
							const uint32 srcBlend2 = static_cast<uint32>(srcBlend * d);
							const uint32 premulSrcR2 = srcBlend2 * color.r;
							const uint32 premulSrcG2 = srcBlend2 * color.g;
							const uint32 premulSrcB2 = srcBlend2 * color.b;
							const uint32 dstBlend2 = 255 - srcBlend2;

							pDst->r = static_cast<uint8>((pDst->r * dstBlend2 + premulSrcR2) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend2 + premulSrcG2) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend2 + premulSrcB2) / 255);
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
							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
		}

		return *this;
	}

	const Circle& Circle::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		const int32 yBegin = Max(static_cast<int32>(y - r), 0);
		const int32 yEnd = Min(static_cast<int32>(y + r + 1), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - r), 0);
		const int32 xEnd = Min(static_cast<int32>(x + r + 1), dst.width());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

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

						pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
						pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
						pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
						pDst->a = static_cast<uint8>((pDst->a * dstBlend + premulSrcA) / 255);
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

	const Circle& Circle::paintFrame(Image& dst, const double innerThickness, const double outerThickness, const Color& color, const Antialiased antialiased) const
	{
		const int32 yBegin = Max(static_cast<int32>(y - r - outerThickness), 0);
		const int32 yEnd = Min(static_cast<int32>(y + r + 1 + outerThickness), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - r - outerThickness), 0);
		const int32 xEnd = Min(static_cast<int32>(x + r + 1 + outerThickness), dst.width());

		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

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

								pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
								pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
								pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
							}
							else if (lengthOuter0 < length)
							{
								const double d = lengthOuter1 - length;
								const uint32 srcBlend2 = static_cast<uint32>(255 * d);
								const uint32 premulSrcR = srcBlend2 * color.r;
								const uint32 premulSrcG = srcBlend2 * color.g;
								const uint32 premulSrcB = srcBlend2 * color.b;
								const uint32 dstBlend = 255 - srcBlend2;

								pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
								pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
								pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
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

								pDst->r = static_cast<uint8>((pDst->r * dstBlend2 + premulSrcR2) / 255);
								pDst->g = static_cast<uint8>((pDst->g * dstBlend2 + premulSrcG2) / 255);
								pDst->b = static_cast<uint8>((pDst->b * dstBlend2 + premulSrcB2) / 255);
							}
							else if (lengthOuter0 < length)
							{
								const double d = lengthOuter1 - length;
								const uint32 srcBlend2 = static_cast<uint32>(srcBlend * d);
								const uint32 premulSrcR2 = srcBlend2 * color.r;
								const uint32 premulSrcG2 = srcBlend2 * color.g;
								const uint32 premulSrcB2 = srcBlend2 * color.b;
								const uint32 dstBlend2 = 255 - srcBlend2;

								pDst->r = static_cast<uint8>((pDst->r * dstBlend2 + premulSrcR2) / 255);
								pDst->g = static_cast<uint8>((pDst->g * dstBlend2 + premulSrcG2) / 255);
								pDst->b = static_cast<uint8>((pDst->b * dstBlend2 + premulSrcB2) / 255);
							}
							else
							{
								pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
								pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
								pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
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
							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
						}

						++pDst;
					}

					pDst += stepOffset;
				}
			}
		}

		return *this;
	}

	const Circle& Circle::overwriteFrame(Image& dst, const double innerThickness, const double outerThickness, const Color& color, const Antialiased antialiased) const
	{
		const int32 yBegin = Max(static_cast<int32>(y - r - outerThickness), 0);
		const int32 yEnd = Min(static_cast<int32>(y + r + 1 + outerThickness), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - r - outerThickness), 0);
		const int32 xEnd = Min(static_cast<int32>(x + r + 1 + outerThickness), dst.width());

		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

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

							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
							pDst->a = static_cast<uint8>((pDst->a * dstBlend + premulSrcA) / 255);
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

							pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
							pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
							pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
							pDst->a = static_cast<uint8>((pDst->a * dstBlend + premulSrcA) / 255);
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
		const int32 yBegin = Max(static_cast<int32>(y - b), 0);
		const int32 yEnd = Min(static_cast<int32>(y + b + 1), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - a), 0);
		const int32 xEnd = Min(static_cast<int32>(x + a + 1), dst.width());
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
						pDst->r = static_cast<uint8>((pDst->r * dstBlend + premulSrcR) / 255);
						pDst->g = static_cast<uint8>((pDst->g * dstBlend + premulSrcG) / 255);
						pDst->b = static_cast<uint8>((pDst->b * dstBlend + premulSrcB) / 255);
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
		const int32 yBegin = Max(static_cast<int32>(y - b), 0);
		const int32 yEnd = Min(static_cast<int32>(y + b + 1), dst.height());
		const int32 xBegin = Max(static_cast<int32>(x - a), 0);
		const int32 xEnd = Min(static_cast<int32>(x + a + 1), dst.width());
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
		if (not dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		ShapePainting::PaintTriangle(paintBuffer, *this, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Triangle& Triangle::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		if (not dst)
		{
			return *this;
		}

		const cv::Point pts[3] =
		{
			cv::Point(static_cast<int32>(p0.x), static_cast<int32>(p0.y)),
			cv::Point(static_cast<int32>(p1.x), static_cast<int32>(p1.y)),
			cv::Point(static_cast<int32>(p2.x), static_cast<int32>(p2.y)),
		};

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);
		cv::fillConvexPoly(mat, pts, 3, cv::Scalar(color.r, color.g, color.b, color.a), (antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}

	const Quad& Quad::paint(Image& dst, const Color& color) const
	{
		if (not dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;

		ShapePainting::PaintQuad(paintBuffer, *this, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Quad& Quad::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		if (not dst)
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

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);
		cv::fillConvexPoly(mat, pts, 4, cv::Scalar(color.r, color.g, color.b, color.a), antialiased ? cv::LINE_AA : cv::LINE_8);

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

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);

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

		ShapePainting::PaintPolygon(paintBuffer, ppts, npts, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Polygon& Polygon::paint(Image& dst, const double x, const double y, const Color& color) const
	{
		return paint(dst, Vec2{ x, y }, color);
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

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);

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

		ShapePainting::PaintPolygon(paintBuffer, ppts, npts, dst.width(), dst.height());

		if (paintBuffer.empty())
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const Polygon& Polygon::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
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

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);

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
			(antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}

	const Polygon& Polygon::overwrite(Image& dst, const double x, const double y, const Color& color, const Antialiased antialiased) const
	{
		return overwrite(dst, Vec2{ x, y }, color, antialiased);
	}

	const Polygon& Polygon::overwrite(Image& dst, const Vec2& pos, const Color& color, const Antialiased antialiased) const
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

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);

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
			(antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}

	const LineString& LineString::paint(Image& dst, const int32 thickness, const Color& color) const
	{
		if (not dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;
		ShapePainting::PaintLineString(paintBuffer, *this, dst.width(), dst.height(), thickness, false);

		if (not paintBuffer)
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const LineString& LineString::paintClosed(Image& dst, const int32 thickness, const Color& color) const
	{
		if (not dst)
		{
			return *this;
		}

		Array<uint32> paintBuffer;
		ShapePainting::PaintLineString(paintBuffer, *this, dst.width(), dst.height(), thickness, true);

		if (not paintBuffer)
		{
			return *this;
		}

		ImagePainting::WritePaintBufferReference(dst[0], paintBuffer.data(), paintBuffer.size(), color);

		return *this;
	}

	const LineString& LineString::overwrite(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		if ((not dst) || isEmpty())
		{
			return *this;
		}

		Array<cv::Point> points(Arg::reserve = size());

		for (const auto& p : *this)
		{
			points.emplace_back(static_cast<int32>(p.x), static_cast<int32>(p.y));
		}

		const int32 n = static_cast<int32>(points.size());
		const cv::Point* ptr = points.data();
		const cv::Point** pptr = &ptr;

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);
		cv::polylines(mat, pptr, &n, 1, false, cv::Scalar(color.r, color.g, color.b, color.a), thickness, (antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}

	const LineString& LineString::overwriteClosed(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		if ((not dst) || isEmpty())
		{
			return *this;
		}

		Array<cv::Point> points(Arg::reserve = size());

		for (const auto& p : *this)
		{
			points.emplace_back(static_cast<int32>(p.x), static_cast<int32>(p.y));
		}

		const int32 n = static_cast<int32>(points.size());
		const cv::Point* ptr = points.data();
		const cv::Point** pptr = &ptr;

		cv::Mat mat = OpenCV_Bridge::GetMatView(dst);
		cv::polylines(mat, pptr, &n, 1, true, cv::Scalar(color.r, color.g, color.b, color.a), thickness, (antialiased ? cv::LINE_AA : cv::LINE_8));

		return *this;
	}
}
