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

# include <Siv3D/FileSystem.hpp>
# include "CImageDecoder.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageFormat/BMPDecoder.hpp>
# include <Siv3D/ImageFormat/PNGDecoder.hpp>
# include <Siv3D/ImageFormat/JPEGDecoder.hpp>
# include <Siv3D/ImageFormat/WebPDecoder.hpp>
# include <Siv3D/ImageFormat/TGADecoder.hpp>
# include <Siv3D/ImageFormat/TIFFDecoder.hpp>
# include <Siv3D/ImageFormat/SVGDecoder.hpp>
# include <Siv3D/ImageFormat/GIFDecoder.hpp>
# include <Siv3D/ImageFormat/PPMDecoder.hpp>

namespace s3d
{
	CImageDecoder::~CImageDecoder()
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::~CImageDecoder()");
	}

# if SIV3D_PLATFORM(WEB)
	__attribute__((weak))
# endif
	void CImageDecoder::init()
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::init()");

		m_decoders.push_back(std::make_unique<BMPDecoder>());
		m_decoders.push_back(std::make_unique<PNGDecoder>());
		m_decoders.push_back(std::make_unique<JPEGDecoder>());
		m_decoders.push_back(std::make_unique<WebPDecoder>());
		m_decoders.push_back(std::make_unique<TGADecoder>());
		m_decoders.push_back(std::make_unique<TIFFDecoder>());
		m_decoders.push_back(std::make_unique<SVGDecoder>());
		m_decoders.push_back(std::make_unique<GIFDecoder>());
		m_decoders.push_back(std::make_unique<PPMDecoder>());
	}

	Optional<ImageInfo> CImageDecoder::getImageInfo(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::getImageInfo()");

		auto it = findDecoder(imageFormat);

		if (it == m_decoders.end())
		{
			it = findDecoder(reader, pathHint);

			if (it == m_decoders.end())
			{
				return{};
			}
		}

		LOG_TRACE(U"Image decoder name: {}"_fmt((*it)->name()));

		return (*it)->getImageInfo(reader, pathHint);
	}

	Image CImageDecoder::decode(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::decode()");

		auto it = findDecoder(imageFormat);

		if (it == m_decoders.end())
		{
			it = findDecoder(reader, pathHint);

			if (it == m_decoders.end())
			{
				return{};
			}
		}

		LOG_TRACE(U"Image decoder name: {}"_fmt((*it)->name()));

		return (*it)->decode(reader, pathHint);
	}

	Grid<uint16> CImageDecoder::decodeGray16(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::decodeGray16()");

		auto it = findDecoder(imageFormat);

		if (it == m_decoders.end())
		{
			it = findDecoder(reader, pathHint);

			if (it == m_decoders.end())
			{
				return{};
			}
		}

		LOG_TRACE(U"Image decoder name: {}"_fmt((*it)->name()));

		return (*it)->decodeGray16(reader, pathHint);
	}

	bool CImageDecoder::add(std::unique_ptr<IImageDecoder>&& decoder)
	{
		const StringView name = decoder->name();

		const bool exisits = m_decoders.contains_if([name](const std::unique_ptr<IImageDecoder>& decoder)
			{
				return decoder->name() == name;
			});

		if (exisits)
		{
			return false;
		}

		m_decoders.push_back(std::move(decoder));

		return true;
	}

	void CImageDecoder::remove(const StringView name)
	{
		m_decoders.remove_if([name](const std::unique_ptr<IImageDecoder>& decoder)
			{
				return decoder->name() == name;
			});
	}

	const Array<std::unique_ptr<IImageDecoder>>& CImageDecoder::enumDecoder() const noexcept
	{
		return m_decoders;
	}

	Array<std::unique_ptr<IImageDecoder>>::const_iterator CImageDecoder::findDecoder(const ImageFormat imageFormat) const
	{
		if (imageFormat == ImageFormat::Unknown)
		{
			return m_decoders.end();
		}

		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
		{
			if ((*it)->imageFormat() == imageFormat)
			{
				return it;
			}
		}

		return m_decoders.end();
	}

	Array<std::unique_ptr<IImageDecoder>>::const_iterator CImageDecoder::findDecoder(const IReader& reader, const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return m_decoders.end();
		}

		if (not reader.supportsLookahead())
		{
			return m_decoders.end();
		}

		uint8 header[16] = {};

		if (not reader.lookahead(header))
		{
			return m_decoders.end();
		}

		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
		{
			if ((*it)->isHeader(header))
			{
				return it;
			}
		}

		if (pathHint)
		{
			const String extension = FileSystem::Extension(pathHint);

			for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
			{
				if ((*it)->possibleExtensions().contains(extension))
				{
					return it;
				}
			}
		}

		return m_decoders.end();
	}
}
