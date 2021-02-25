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

# include <Siv3D/Image.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/ImageDecoder.hpp>
# include <Siv3D/ImageEncoder.hpp>
# include <Siv3D/ImageFormat/PNGEncoder.hpp>

namespace s3d
{
	Image::Image(const FilePathView path, const ImageFormat format)
	{
		*this = ImageDecoder::Decode(path, format);
	}

	Image::Image(IReader&& reader, const ImageFormat format)
	{
		*this = ImageDecoder::Decode(reader, format);
	}

	Image::Image(const FilePathView rgb, const FilePathView alpha)
		: Image{ rgb }
	{
		applyAlphaFromRChannel(alpha);
	}

	Image::Image(const Color rgb, const FilePathView alpha)
		: Image{ alpha }
	{
		for (auto& pixel : *this)
		{
			pixel.a = pixel.r;
			pixel.r = rgb.r;
			pixel.g = rgb.g;
			pixel.b = rgb.b;
		}
	}

	Image::Image(const Emoji& emoji)
		: Image{ Emoji::CreateImage(emoji.codePoints) } {}

	Image::Image(const Icon& icon, const int32 size)
		: Image{ Icon::CreateImage(icon.type, icon.code, size) } {}

	bool Image::applyAlphaFromRChannel(const FilePathView alpha)
	{
		if (isEmpty())
		{
			return false;
		}

		const Image alphaImage{ alpha };

		if (not alphaImage)
		{
			return false;
		}

		Color* pDst = data();
		const size_t dstStep = m_width;

		const Color* pSrc = alphaImage.data();
		const size_t srcStep = alphaImage.m_width;

		const uint32 w = Min(m_width, alphaImage.m_width);
		const uint32 h = Min(m_height, alphaImage.m_height);

		for (uint32 y = 0; y < h; ++y)
		{
			Color* pDstLine = pDst;
			const Color* pSrcLine = pSrc;

			for (uint32 x = 0; x < w; ++x)
			{
				(*pDstLine++).a = (*pSrcLine++).r;
			}

			pSrc += srcStep;
			pDst += dstStep;
		}

		return true;
	}

	void Image::overwrite(Image& dst, const int32 x, const int32 y) const
	{
		overwrite(dst, Point{ x, y });
	}

	void Image::overwrite(Image& dst, const Point pos) const
	{
		if (this == &dst)
		{
			return;
		}

		const Image& src = *this;

		const int32 dstXBegin	= Max(pos.x, 0);
		const int32 dstYBegin	= Max(pos.y, 0);
		const int32 dstXEnd		= Min(pos.x + src.width(), dst.width());
		const int32 dstYEnd		= Min(pos.y + src.height(), dst.height());
		const int32 writeWidth	= ((dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0);
		const int32 writeHeight = ((dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0);

		if ((writeWidth * writeHeight) == 0)
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];
		{
			const int32 srcWidth = src.width();
			const int32 dstWidth = dst.width();
			const size_t stride_bytes = (writeWidth * sizeof(Color));

			for (int32 y = 0; y < writeHeight; ++y)
			{
				std::memcpy(pDst, pSrc, stride_bytes);
				pSrc += srcWidth;
				pDst += dstWidth;
			}
		}
	}

	bool Image::save(const FilePathView path, const ImageFormat format) const
	{
		return ImageEncoder::Save(*this, format, path);
	}

	bool Image::savePNG(const FilePathView path, const PNGFilter filter) const
	{
		return PNGEncoder{}.save(*this, path, filter);
	}
}
