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
# include "CAudioEncoder.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioFormat/WAVEEncoder.hpp>
# include <Siv3D/AudioFormat/OggVorbisEncoder.hpp>

namespace s3d
{
	CAudioEncoder::~CAudioEncoder()
	{
		LOG_SCOPED_TRACE(U"CAudioEncoder::~CAudioEncoder()");
	}

	void CAudioEncoder::init()
	{
		LOG_SCOPED_TRACE(U"CAudioEncoder::init()");

		m_encoders.push_back(std::make_unique<WAVEEncoder>());
		m_encoders.push_back(std::make_unique<OggVorbisEncoder>());
	}

	String CAudioEncoder::getEncoderNameFromExtension(const StringView extension) const
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

	bool CAudioEncoder::save(const Wave& wave, const StringView encoderName, const FilePathView path) const
	{
		LOG_SCOPED_TRACE(U"CAudioEncoder::save({}, {})"_fmt(encoderName, path));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return{};
		}

		return (*it)->save(wave, path);
	}

	bool CAudioEncoder::encode(const Wave& wave, const StringView encoderName, IWriter& writer) const
	{
		LOG_SCOPED_TRACE(U"CAudioEncoder::encode({})"_fmt(encoderName));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return false;
		}

		return (*it)->encode(wave, writer);
	}

	Blob CAudioEncoder::encode(const Wave& wave, const StringView encoderName) const
	{
		LOG_SCOPED_TRACE(U"CAudioEncoder::encode({})"_fmt(encoderName));

		const auto it = findEncoder(encoderName);

		if (it == m_encoders.end())
		{
			return{};
		}

		return (*it)->encode(wave);
	}

	bool CAudioEncoder::add(std::unique_ptr<IAudioEncoder>&& encoder)
	{
		const StringView name = encoder->name();

		const bool exisits = m_encoders.contains_if([name](const std::unique_ptr<IAudioEncoder>& encoder)
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

	void CAudioEncoder::remove(const StringView name)
	{
		m_encoders.remove_if([name](const std::unique_ptr<IAudioEncoder>& encoder)
			{
				return encoder->name() == name;
			});
	}

	const Array<std::unique_ptr<IAudioEncoder>>& CAudioEncoder::enumEncoder() const noexcept
	{
		return m_encoders;
	}

	Array<std::unique_ptr<IAudioEncoder>>::const_iterator CAudioEncoder::findEncoder(const StringView encoderName) const
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
