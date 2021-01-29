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

	bool Image::save(const FilePathView path, const ImageFormat format) const
	{
		return ImageEncoder::Save(*this, format, path);
	}

	bool Image::savePNG(const FilePathView path, const PNGFilter filter) const
	{
		return PNGEncoder{}.save(*this, path, filter);
	}
}
