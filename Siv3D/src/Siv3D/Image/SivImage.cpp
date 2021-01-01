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

	bool Image::save(const FilePathView path, const ImageFormat format) const
	{
		return ImageEncoder::Save(*this, format, path);
	}

	bool Image::savePNG(const FilePathView path, const PNGFilter filter) const
	{
		return PNGEncoder{}.save(*this, path, filter);
	}
}
