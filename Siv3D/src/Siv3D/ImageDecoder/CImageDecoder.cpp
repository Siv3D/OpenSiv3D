﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FileSystem.hpp>
# include "CImageDecoder.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageFormat/BMPDecoder.hpp>
# include <Siv3D/ImageFormat/PNGDecoder.hpp>
# include <Siv3D/ImageFormat/SVGDecoder.hpp>

namespace s3d
{
	CImageDecoder::~CImageDecoder()
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::~CImageDecoder()");
	}

	void CImageDecoder::init()
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::init()");

		m_decoders.push_back(std::make_unique<BMPDecoder>());
		m_decoders.push_back(std::make_unique<PNGDecoder>());
		m_decoders.push_back(std::make_unique<SVGDecoder>());
	}

	Optional<ImageInfo> CImageDecoder::getImageInfo(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::getImageInfo()");

		const auto it = findDecoder(reader, pathHint);

		if (it == m_decoders.end())
		{
			return{};
		}

		return (*it)->getImageInfo(reader, pathHint);
	}

	Image CImageDecoder::decode(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::decode()");

		const auto it = findDecoder(reader, pathHint);

		if (it == m_decoders.end())
		{
			return{};
		}

		LOG_TRACE(U"Image decoder name: {}"_fmt((*it)->name()));

		return (*it)->decode(reader, pathHint);
	}

	Grid<uint16> CImageDecoder::decodeGray16(IReader& reader, const FilePathView pathHint, const ImageFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::decodeGray16()");

		const auto it = findDecoder(reader, pathHint);

		if (it == m_decoders.end())
		{
			return{};
		}

		LOG_TRACE(U"Image decoder name: {}"_fmt((*it)->name()));

		return (*it)->decodeGray16(reader, pathHint);
	}

	bool CImageDecoder::add(std::unique_ptr<IImageDecoder>&& decoder)
	{
		const StringView name = decoder->name();

		const bool exisits = m_decoders.includes_if([name](const std::unique_ptr<IImageDecoder>& decoder)
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

	Array<std::unique_ptr<IImageDecoder>>::const_iterator CImageDecoder::findDecoder(const IReader& reader, const FilePathView pathHint) const
	{
		if (!reader.isOpen())
		{
			return m_decoders.end();
		}

		if (!reader.supportsLookahead())
		{
			return m_decoders.end();
		}

		uint8 header[16] = {};

		if (!reader.lookahead(header))
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
				if ((*it)->possibleExtensions().includes(extension))
				{
					return it;
				}
			}
		}

		return m_decoders.end();
	}
}
