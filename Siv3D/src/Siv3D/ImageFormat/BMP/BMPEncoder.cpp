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

# include <Siv3D/ImageFormat/BMPEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>
# include "BMPHeader.hpp"

namespace s3d
{
	StringView BMPEncoder::name() const
	{
		return U"BMP"_sv;
	}

	ImageFormat BMPEncoder::imageFormat() const noexcept
	{
		return ImageFormat::BMP;
	}

	const Array<String>& BMPEncoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"bmp" };

		return extensions;
	}

	bool BMPEncoder::save(const Image& image, const FilePathView path) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer);
	}

	bool BMPEncoder::encode(const Image& image, IWriter& writer) const
	{
		if (not writer.isOpen())
		{
			return false;
		}

		const int32 width			= image.width();
		const int32 height			= image.height();
		const uint32 stride_bytes	= (width * 3) + (width % 4);
		const uint32 size_bytes		= (stride_bytes * height);
		const BMPHeader header		= BMPHeader::Make(width, height, size_bytes);

		std::unique_ptr<uint8[]> line;
		try
		{
			line = std::make_unique<uint8[]>(stride_bytes);
		}
		catch (const std::bad_alloc&)
		{
			return false;
		}

		writer.write(header);

		const Color* pSrcLine = image[height - 1];

		for (int32 y = 0; y < height; ++y)
		{
			uint8* pDst = line.get();
			const Color* pSrc = pSrcLine;

			for (int32 x = 0; x < width; ++x)
			{
				*pDst++ = pSrc->b;
				*pDst++ = pSrc->g;
				*pDst++ = pSrc->r;
				++pSrc;
			}

			writer.write(line.get(), stride_bytes);
			pSrcLine -= width;
		}

		return true;
	}

	Blob BMPEncoder::encode(const Image& image) const
	{
		const int32 width			= image.width();
		const int32 height			= image.height();
		const uint32 stride_bytes	= (width * 3) + (width % 4);
		const uint32 size_bytes		= (stride_bytes * height);
		const BMPHeader header		= BMPHeader::Make(width, height, size_bytes);
	
		std::unique_ptr<uint8[]> line;
		try
		{
			line = std::make_unique<uint8[]>(stride_bytes);
		}
		catch (const std::bad_alloc&)
		{
			return{};
		}

		Blob blob(static_cast<uint32>(sizeof(BMPHeader) + size_bytes));

		std::memcpy(blob.data(), &header, sizeof(header));

		const Color* pSrcLine = image[height - 1];
		Byte* pDstLine = (blob.data() + sizeof(header));

		for (int32 y = 0; y < height; ++y)
		{
			uint8* pDst = line.get();
			const Color* pSrc = pSrcLine;

			for (int32 x = 0; x < width; ++x)
			{
				*pDst++ = pSrc->b;
				*pDst++ = pSrc->g;
				*pDst++ = pSrc->r;
				++pSrc;
			}

			std::memcpy(pDstLine, line.get(), stride_bytes);
			pDstLine += stride_bytes;
			pSrcLine -= width;
		}

		return blob;
	}
}
