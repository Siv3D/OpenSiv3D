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
# include "CImageEncoder.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageFormat/BMPEncoder.hpp>
# include <Siv3D/ImageFormat/PNGEncoder.hpp>
# include <Siv3D/ImageFormat/JPEGEncoder.hpp>
# include <Siv3D/ImageFormat/WebPEncoder.hpp>
# include <Siv3D/ImageFormat/TGAEncoder.hpp>
# include <Siv3D/ImageFormat/GIFEncoder.hpp>
# include <Siv3D/ImageFormat/PPMEncoder.hpp>


namespace s3d
{
	CImageEncoder::~CImageEncoder()
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::~CImageEncoder()");
	}

# if SIV3D_PLATFORM(WEB)
	__attribute__((weak))
# endif
	void CImageEncoder::init()
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::init()");

		m_encoders.push_back(std::make_unique<BMPEncoder>());
		m_encoders.push_back(std::make_unique<PNGEncoder>());
		m_encoders.push_back(std::make_unique<JPEGEncoder>());
		m_encoders.push_back(std::make_unique<WebPEncoder>());
		m_encoders.push_back(std::make_unique<TGAEncoder>());
		m_encoders.push_back(std::make_unique<GIFEncoder>());
		m_encoders.push_back(std::make_unique<PPMEncoder>());
	}

	String CImageEncoder::getEncoderNameFromExtension(const StringView extension) const
	{
		if (not extension)
		{
			return{};
		}

		const String ext = String(extension);

		for (const auto& encoder : m_encoders)
		{
			if (encoder->possibleExtensions().contains(ext))
			{
				return String(encoder->name());
			}
		}

		return{};
	}

	bool CImageEncoder::save(const Image& image, const StringView encoderName, const FilePathView path) const
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::save({}, {})"_fmt(encoderName, path));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return{};
		}

		return (*it)->save(image, path);
	}

	bool CImageEncoder::encode(const Image& image, const StringView encoderName, IWriter& writer) const
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::encode({})"_fmt(encoderName));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return false;
		}

		return (*it)->encode(image, writer);
	}

	Blob CImageEncoder::encode(const Image& image, const StringView encoderName) const
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::encode({})"_fmt(encoderName));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return{};
		}

		return (*it)->encode(image);
	}

	bool CImageEncoder::add(std::unique_ptr<IImageEncoder>&& encoder)
	{
		const StringView name = encoder->name();

		const bool exisits = m_encoders.contains_if([name](const std::unique_ptr<IImageEncoder>& encoder)
			{
				return encoder->name() == name;
			});

		if (exisits)
		{
			return false;
		}

		m_encoders.push_back(std::move(encoder));

		return true;
	}

	void CImageEncoder::remove(const StringView name)
	{
		m_encoders.remove_if([name](const std::unique_ptr<IImageEncoder>& encoder)
			{
				return encoder->name() == name;
			});
	}

	const Array<std::unique_ptr<IImageEncoder>>& CImageEncoder::enumEncoder() const noexcept
	{
		return m_encoders;
	}

	Array<std::unique_ptr<IImageEncoder>>::const_iterator CImageEncoder::findEncoder(const StringView encoderName) const
	{
		for (auto it = m_encoders.begin(); it != m_encoders.end(); ++it)
		{
			if ((*it)->name() == encoderName)
			{
				return it;
			}
		}

		return m_encoders.end();
	}
}
