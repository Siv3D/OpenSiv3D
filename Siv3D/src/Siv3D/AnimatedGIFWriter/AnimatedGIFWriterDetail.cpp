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

# include <Siv3D/Image.hpp>
# include "AnimatedGIFWriterDetail.hpp"

namespace s3d
{
	AnimatedGIFWriter::AnimatedGIFWriterDetail::AnimatedGIFWriterDetail() {}

	AnimatedGIFWriter::AnimatedGIFWriterDetail::~AnimatedGIFWriterDetail()
	{
		close();
	}

	bool AnimatedGIFWriter::AnimatedGIFWriterDetail::open(const FilePathView path, const Size size, const Dither dither, const HasAlpha hasAlpha)
	{
		if (m_opened)
		{
			close();
		}

		if (not m_writer.open(path))
		{
			return false;
		}

		m_gif.w = &m_writer;

		m_imageSize = size;

		m_dither = dither.getBool();

		m_hasAlpha = hasAlpha.getBool();

		if (not GifBegin(&m_gif, m_imageSize.x, m_imageSize.y, 6, 8, m_dither))
		{
			m_writer.close();

			m_gif = GifWriter();

			return false;
		}

		m_opened = true;

		return true;
	}

	bool AnimatedGIFWriter::AnimatedGIFWriterDetail::close()
	{
		if (not m_opened)
		{
			return false;
		}

		GifEnd(&m_gif);

		m_writer.close();

		m_frameCount = 0;

		m_opened = false;

		return true;
	}

	bool AnimatedGIFWriter::AnimatedGIFWriterDetail::isOpen() const
	{
		return m_opened;
	}

	bool AnimatedGIFWriter::AnimatedGIFWriterDetail::writeFrame(const Image& image, const int32 delay)
	{
		if (not m_opened)
		{
			return false;
		}

		if (image.size() != m_imageSize)
		{
			return false;
		}

		if (GifWriteFrame(&m_gif, image.dataAsUint8(), image.width(), image.height(), delay, m_hasAlpha ? GifEncodingMode::AnimatedRGBA : GifEncodingMode::AnimatedRGB, 8, m_dither))
		{
			++m_frameCount;
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t AnimatedGIFWriter::AnimatedGIFWriterDetail::frameCount() const
	{
		if (not m_opened)
		{
			return 0;
		}

		return m_frameCount;
	}

	Size AnimatedGIFWriter::AnimatedGIFWriterDetail::imageSize() const
	{
		if (not m_opened)
		{
			return{ 0,0 };
		}

		return m_imageSize;
	}
}
