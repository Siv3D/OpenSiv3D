//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ImageProcessing.hpp>

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
	}
}
