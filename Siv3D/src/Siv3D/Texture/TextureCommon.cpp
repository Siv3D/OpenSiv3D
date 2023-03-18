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

# include "TextureCommon.hpp"
# include <Siv3D/HalfFloat.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat& format)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return{};
		}

		const size_t num_pixels = (size.x * size.y);
		Array<Byte> bytes(num_pixels * format.pixelSize());

		if ((format == TextureFormat::R8G8B8A8_Unorm)
			|| (format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			const uint32 value = Color{ color }.asUint32();
			uint32* pDst = static_cast<uint32*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}
		else if (format == TextureFormat::R16G16_Float)
		{
			const struct R16G16
			{
				HalfFloat r;
				HalfFloat g;
			} value = { color.r, color.g };

			R16G16* pDst = static_cast<R16G16*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}
		else if (format == TextureFormat::R32_Float)
		{
			const float value = static_cast<float>(color.r);
			float* pDst = static_cast<float*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}
		else if (format == TextureFormat::R10G10B10A2_Unorm)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R10G10B10A2_Unorm is not yet implemented");
		}
		else if (format == TextureFormat::R11G11B10_UFloat)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R11G11B10_UFloat is not yet implemented");
		}
		else if (format == TextureFormat::R16G16B16A16_Float)
		{
			const struct R16G16B16A16
			{
				HalfFloat r;
				HalfFloat g;
				HalfFloat b;
				HalfFloat a;
			} value = { color.r, color.g, color.b, color.a };

			R16G16B16A16* pDst = static_cast<R16G16B16A16*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}
		else if (format == TextureFormat::R32G32_Float)
		{
			const Float2 value = color.rg();
			Float2* pDst = static_cast<Float2*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}
		else if (format == TextureFormat::R32G32B32A32_Float)
		{
			const Float4 value = color.rgba();
			Float4* pDst = static_cast<Float4*>(static_cast<void*>(bytes.data()));

			for (size_t i = 0; i < num_pixels; ++i)
			{
				*pDst++ = value;
			}
		}

		return bytes;
	}

	void FillByColor(void* const buffer, const Size& size, const uint32 dstStride, const ColorF& color, const TextureFormat& format)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return;
		}

		if ((format == TextureFormat::R8G8B8A8_Unorm)
			|| (format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			const uint32 value = Color{ color }.asUint32();

			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				uint32* pDst = static_cast<uint32*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					uint32* pDstLine = static_cast<uint32*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
		else if (format == TextureFormat::R16G16_Float)
		{
			const struct R16G16
			{
				HalfFloat r;
				HalfFloat g;
			} value = { color.r, color.g };

			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				R16G16* pDst = static_cast<R16G16*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					R16G16* pDstLine = static_cast<R16G16*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
		else if (format == TextureFormat::R32_Float)
		{
			const float value = static_cast<float>(color.r);

			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				float* pDst = static_cast<float*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					float* pDstLine = static_cast<float*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
		else if (format == TextureFormat::R10G10B10A2_Unorm)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R10G10B10A2_Unorm is not yet implemented");
		}
		else if (format == TextureFormat::R11G11B10_UFloat)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R11G11B10_UFloat is not yet implemented");
		}
		else if (format == TextureFormat::R16G16B16A16_Float)
		{
			const struct R16G16B16A16
			{
				HalfFloat r;
				HalfFloat g;
				HalfFloat b;
				HalfFloat a;
			} value = { color.r, color.g, color.b, color.a };

			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				R16G16B16A16* pDst = static_cast<R16G16B16A16*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					R16G16B16A16* pDstLine = static_cast<R16G16B16A16*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
		else if (format == TextureFormat::R32G32_Float)
		{
			const Float2 value = color.rg();

			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				Float2* pDst = static_cast<Float2*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					Float2* pDstLine = static_cast<Float2*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
		else if (format == TextureFormat::R32G32B32A32_Float)
		{
			const Float4 value = color.rgba();
			
			if (dstStride == (size.x * format.pixelSize()))
			{
				const size_t num_pixels = (size.x * size.y);
				Float4* pDst = static_cast<Float4*>(static_cast<void*>(buffer));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
			}
			else
			{
				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					Float4* pDstLine = static_cast<Float4*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = value;
					}

					pDst += dstStride;
				}
			}
		}
	}

	void FillRegionByColor(void* const buffer, const Size& size, const uint32 dstStride, const Rect& rect, const ColorF& color, const TextureFormat& format)
	{
		const int32 leftX	= Clamp(rect.x, 0, size.x);
		const int32 rightX	= Clamp(rect.x + rect.w, 0, size.x);
		const int32 topY	= Clamp(rect.y, 0, size.y);
		const int32 bottomY	= Clamp(rect.y + rect.h, 0, size.y);
		const int32 width	= (rightX - leftX);
		const int32 height	= (bottomY - topY);

		if ((width <= 0) || (height <= 0))
		{
			return;
		}

		const uint32 pixelSize = format.pixelSize();

		if ((format == TextureFormat::R8G8B8A8_Unorm)
			|| (format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			const uint32 value = Color{ color }.asUint32();
			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				uint32* pDstLine = static_cast<uint32*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
		else if (format == TextureFormat::R16G16_Float)
		{
			const struct R16G16
			{
				HalfFloat r;
				HalfFloat g;
			} value = { color.r, color.g };

			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				R16G16* pDstLine = static_cast<R16G16*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
		else if (format == TextureFormat::R32_Float)
		{
			const float value = static_cast<float>(color.r);

			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				float* pDstLine = static_cast<float*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
		else if (format == TextureFormat::R10G10B10A2_Unorm)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R10G10B10A2_Unorm is not yet implemented");
		}
		else if (format == TextureFormat::R11G11B10_UFloat)
		{
			LOG_FAIL(U"DynamicTexture color fill with TextureFormat::R11G11B10_UFloat is not yet implemented");
		}
		else if (format == TextureFormat::R16G16B16A16_Float)
		{
			const struct R16G16B16A16
			{
				HalfFloat r;
				HalfFloat g;
				HalfFloat b;
				HalfFloat a;
			} value = { color.r, color.g, color.b, color.a };

			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				R16G16B16A16* pDstLine = static_cast<R16G16B16A16*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
		else if (format == TextureFormat::R32G32_Float)
		{
			const Float2 value = color.rg();

			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				Float2* pDstLine = static_cast<Float2*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
		else if (format == TextureFormat::R32G32B32A32_Float)
		{
			const Float4 value = color.rgba();

			uint8* pDst = static_cast<uint8*>(buffer);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			for (int32 y = 0; y < height; ++y)
			{
				Float4* pDstLine = static_cast<Float4*>(static_cast<void*>(pDst));

				for (int32 x = 0; x < width; ++x)
				{
					*pDstLine++ = value;
				}

				pDst += dstStride;
			}
		}
	}

	void FillByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const TextureFormat& format)
	{
		if ((format == TextureFormat::R8G8B8A8_Unorm)
			|| (format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			uint8* pDst = static_cast<uint8*>(buffer);
			const uint8* pSrc = static_cast<const uint8*>(pData);

			if (dstStride == srcStride)
			{
				std::memcpy(pDst, pSrc, dstStride * size.y);
			}
			else
			{
				const size_t minStride = Min(dstStride, srcStride);

				for (int32 y = 0; y < size.y; ++y)
				{
					std::memcpy(pDst, pSrc, minStride);
					pDst += dstStride;
					pSrc += srcStride;
				}
			}
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(format.name()));
		}
	}

	void FillRegionByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const Rect& rect, const TextureFormat& format)
	{
		const int32 leftX	= Clamp(rect.x, 0, size.x);
		const int32 topY	= Clamp(rect.y, 0, size.y);
		const int32 rightX	= Clamp(rect.x + rect.w, 0, size.x);
		const int32 bottomY	= Clamp(rect.y + rect.h, 0, size.y);
		const int32 width	= (rightX - leftX);
		const int32 height	= (bottomY - topY);

		if ((width <= 0) || (height <= 0))
		{
			return;
		}

		const uint32 pixelSize = format.pixelSize();

		if ((format == TextureFormat::R8G8B8A8_Unorm)
			|| (format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			uint8* pDst = static_cast<uint8*>(buffer);
			const uint8* pSrc = static_cast<const uint8*>(pData);

			pDst += (dstStride * topY);
			pDst += (pixelSize * leftX);

			pSrc += (srcStride * topY);
			pSrc += (pixelSize * leftX);

			const uint32 copyStride = pixelSize * width;

			for (int32 y = 0; y < height; ++y)
			{
				std::memcpy(pDst, pSrc, copyStride);

				if (y + 1 < height)
				{
					pDst += dstStride;
					pSrc += srcStride;
				}
			}
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(format.name()));
		}
	}
}
