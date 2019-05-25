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

# include <Siv3D/IReader.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CImageFormat.hpp"
# include "BMP/ImageFormat_BMP.hpp"
# include "PNG/ImageFormat_PNG.hpp"
# include "JPEG/ImageFormat_JPEG.hpp"
# include "GIF/ImageFormat_GIF.hpp"
# include "PPM/ImageFormat_PPM.hpp"
# include "TGA/ImageFormat_TGA.hpp"
# include "WebP/ImageFormat_WebP.hpp"

namespace s3d
{
	CImageFormat::CImageFormat()
	{

	}

	CImageFormat::~CImageFormat()
	{
		LOG_TRACE(U"CImageFormat::~CImageFormat()");
	}

	void CImageFormat::init()
	{
		LOG_TRACE(U"CImageFormat::init()");

		m_imageFormats.push_back(std::make_unique<ImageFormat_BMP>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_PNG>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_JPEG>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_GIF>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_PPM>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_TGA>());
		m_imageFormats.push_back(std::make_unique<ImageFormat_WebP>());

		Array<String> extensions;
		for (const auto& format : m_imageFormats)
		{
			extensions.append(format->possibleExtexsions());
		}

		LOG_DEBUG(U"Supported image file extensions: {}"_fmt(extensions.join(U", "_sv, U""_sv, U""_sv)));
		LOG_INFO(U"ℹ️ CImageFormat initialized");
	}

	ImageFormat CImageFormat::getFormatFromReader(const IReader& reader, const FilePath& pathHint) const
	{
		const auto it = findFormat(reader, pathHint);

		if (it == m_imageFormats.end())
		{
			return ImageFormat::Unknown;
		}

		return (*it)->format();
	}

	ImageFormat CImageFormat::getFormatFromFilePath(const FilePath& path) const
	{
		if (!path.isEmpty())
		{
			const String extension = FileSystem::Extension(path);

			for (const auto& imageFormat : m_imageFormats)
			{
				if (imageFormat->possibleExtexsions().includes(extension))
				{
					return imageFormat->format();
				}
			}
		}

		return ImageFormat::Unknown;
	}

	Size CImageFormat::getSize(const IReader& reader, const FilePath& pathHint) const
	{
		const auto it = findFormat(reader, pathHint);

		if (it == m_imageFormats.end())
		{
			return{ 0, 0 };
		}

		return (*it)->getSize(reader);
	}

	Image CImageFormat::load(const FilePath& path) const
	{
		BinaryReader reader(path);

		const auto it = findFormat(reader, path);

		if (it == m_imageFormats.end())
		{
			return Image();
		}

		return (*it)->decode(reader);
	}

	Image CImageFormat::decode(IReader&& reader, ImageFormat format) const
	{
		if (format == ImageFormat::Unknown)
		{
			format = getFormatFromReader(reader, String());
		}

		const auto it = findFormat(format);

		if (it == m_imageFormats.end())
		{
			return Image();
		}

		return (*it)->decode(reader);
	}

	bool CImageFormat::save(const Image& image, const ImageFormat format, const FilePath& path) const
	{
		const auto it = findFormat(format);

		if (it == m_imageFormats.end())
		{
			return false;
		}

		return (*it)->save(image, path);
	}

	ByteArray CImageFormat::encode(const Image& image, ImageFormat format) const
	{
		const auto it = findFormat(format);

		if (it == m_imageFormats.end())
		{
			return ByteArray();
		}

		MemoryWriter writer;

		if (!(*it)->encode(image, writer))
		{
			return ByteArray();
		}

		return writer.retrieve();
	}

	bool CImageFormat::encodePNG(IWriter& writer, const Image& image, int32 filterFlag) const
	{
		const auto p = findFormat(ImageFormat::PNG);

		if (p == m_imageFormats.end())
		{
			return false;
		}

		if (const ImageFormat_PNG* png = dynamic_cast<ImageFormat_PNG*>(p->get()))
		{
			return png->encode(image, writer, filterFlag);
		}

		return false;
	}

	bool CImageFormat::encodeJPEG(IWriter& writer, const Image& image, const int32 quality) const
	{
		const auto p = findFormat(ImageFormat::JPEG);

		if (p == m_imageFormats.end())
		{
			return false;
		}

		if (const ImageFormat_JPEG* jpeg = dynamic_cast<ImageFormat_JPEG*>(p->get()))
		{
			return jpeg->encode(image, writer, quality);
		}

		return false;
	}

	bool CImageFormat::encodePPM(IWriter & writer, const Image & image, const PPMType type) const
	{
		const auto p = findFormat(ImageFormat::PPM);

		if (p == m_imageFormats.end())
		{
			return false;
		}

		if (const ImageFormat_PPM* ppm = dynamic_cast<ImageFormat_PPM*>(p->get()))
		{
			return ppm->encode(image, writer, type);
		}

		return false;
	}

	bool CImageFormat::encodeWebP(IWriter& writer, const Image& image, const bool lossless, const double quality, const WebPMethod method) const
	{
		const auto p = findFormat(ImageFormat::WebP);

		if (p == m_imageFormats.end())
		{
			return false;
		}

		if (const ImageFormat_WebP* webP = dynamic_cast<ImageFormat_WebP*>(p->get()))
		{
			return webP->encode(image, writer, lossless, quality, method);
		}

		return false;
	}

	Array<std::unique_ptr<IImageFormat>>::const_iterator CImageFormat::findFormat(const ImageFormat format) const
	{
		for (auto it = m_imageFormats.begin(); it != m_imageFormats.end(); ++it)
		{
			if ((*it)->format() == format)
			{
				return it;
			}
		}

		return m_imageFormats.end();
	}

	Array<std::unique_ptr<IImageFormat>>::const_iterator CImageFormat::findFormat(const IReader& reader, const FilePath& pathHint) const
	{
		if (!reader.isOpened())
		{
			return m_imageFormats.end();
		}

		if (!reader.supportsLookahead())
		{
			return m_imageFormats.end();
		}

		uint8 header[16] = {};

		if (!reader.lookahead(header))
		{
			return m_imageFormats.end();
		}

		for (auto it = m_imageFormats.begin(); it != m_imageFormats.end(); ++it)
		{
			if ((*it)->isHeader(header))
			{
				return it;
			}
		}

		if (!pathHint.isEmpty())
		{
			const String extension = FileSystem::Extension(pathHint);

			for (auto it = m_imageFormats.begin(); it != m_imageFormats.end(); ++it)
			{
				if ((*it)->possibleExtexsions().includes(extension))
				{
					return it;
				}
			}
		}

		return m_imageFormats.end();
	}
}
