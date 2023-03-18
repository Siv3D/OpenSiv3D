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
# include <Siv3D/IReader.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CAudioDecoder.hpp"
# include <Siv3D/AudioFormat/WAVEDecoder.hpp>
# include <Siv3D/AudioFormat/OggVorbisDecoder.hpp>
# include <Siv3D/AudioFormat/OpusDecoder.hpp>
# include <Siv3D/AudioFormat/MP3Decoder.hpp>
# include <Siv3D/AudioFormat/AACDecoder.hpp>
# include <Siv3D/AudioFormat/WMADecoder.hpp>
# include <Siv3D/AudioFormat/AIFFDecoder.hpp>
# include <Siv3D/AudioFormat/FLACDecoder.hpp>
# include <Siv3D/AudioFormat/MIDIDecoder.hpp>

namespace s3d
{
	CAudioDecoder::~CAudioDecoder()
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::~CAudioDecoder()");
	}

	void CAudioDecoder::init()
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::init()");

		m_decoders.push_back(std::make_unique<WAVEDecoder>());
		m_decoders.push_back(std::make_unique<OggVorbisDecoder>());
		m_decoders.push_back(std::make_unique<OpusDecoder>());
		m_decoders.push_back(std::make_unique<MIDIDecoder>());

	# if SIV3D_PLATFORM(WINDOWS)
		m_decoders.push_back(std::make_unique<MP3Decoder>());
		m_decoders.push_back(std::make_unique<AACDecoder>());
		m_decoders.push_back(std::make_unique<WMADecoder>());
		m_decoders.push_back(std::make_unique<FLACDecoder>());
	# elif SIV3D_PLATFORM(MACOS)
		m_decoders.push_back(std::make_unique<MP3Decoder>());
		m_decoders.push_back(std::make_unique<AACDecoder>());
		m_decoders.push_back(std::make_unique<AIFFDecoder>());
		m_decoders.push_back(std::make_unique<FLACDecoder>());
	# elif SIV3D_PLATFORM(LINUX)
		m_decoders.push_back(std::make_unique<MP3Decoder>());
		m_decoders.push_back(std::make_unique<AACDecoder>());
	# elif SIV3D_PLATFORM(WEB)
		m_decoders.push_back(std::make_unique<MP3Decoder>());
		m_decoders.push_back(std::make_unique<AACDecoder>());
	# endif
	}

	AudioFormat CAudioDecoder::getAudioFormat(IReader& reader)
	{
		if (not reader.isOpen())
		{
			return AudioFormat::Unknown;
		}

		if (not reader.supportsLookahead())
		{
			return AudioFormat::Unknown;
		}

		uint8 header[48] = {};
		constexpr int64 MinimumAudioHeaderSize = 16;

		if (reader.lookahead(header, sizeof(header)) < MinimumAudioHeaderSize)
		{
			return AudioFormat::Unknown;
		}

		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
		{
			if ((*it)->isHeader(header))
			{
				return it->get()->audioFormat();
			}
		}

		return AudioFormat::Unknown;
	}

	Wave CAudioDecoder::decode(IReader& reader, const FilePathView pathHint, const AudioFormat imageFormat)
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::decode()");

		auto it = findDecoder(imageFormat);

		if (it == m_decoders.end())
		{
			it = findDecoder(reader, pathHint);

			if (it == m_decoders.end())
			{
				return{};
			}
		}

		LOG_TRACE(U"Audio decoder name: {}"_fmt((*it)->name()));

		return (*it)->decode(reader, pathHint);
	}

	Wave CAudioDecoder::decode(IReader& reader, const StringView decoderName)
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::decode({})"_fmt(decoderName));

		const auto it = findDecoder(decoderName);

		if (it == m_decoders.end())
		{
			return{};
		}

		return (*it)->decode(reader, {});
	}

	bool CAudioDecoder::add(std::unique_ptr<IAudioDecoder>&& decoder)
	{
		const StringView name = decoder->name();

		const bool exisits = m_decoders.contains_if([name](const std::unique_ptr<IAudioDecoder>& decoder)
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

	void CAudioDecoder::remove(const StringView name)
	{
		m_decoders.remove_if([name](const std::unique_ptr<IAudioDecoder>& decoder)
			{
				return decoder->name() == name;
			});
	}

	const Array<std::unique_ptr<IAudioDecoder>>& CAudioDecoder::enumDecoder() const noexcept
	{
		return m_decoders;
	}

	Array<std::unique_ptr<IAudioDecoder>>::const_iterator CAudioDecoder::findDecoder(const AudioFormat audioFormat) const
	{
		if (audioFormat == AudioFormat::Unknown)
		{
			return m_decoders.end();
		}

		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
		{
			if ((*it)->audioFormat() == audioFormat)
			{
				return it;
			}
		}

		return m_decoders.end();
	}

	Array<std::unique_ptr<IAudioDecoder>>::const_iterator CAudioDecoder::findDecoder(const IReader& reader, const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return m_decoders.end();
		}

		if (not reader.supportsLookahead())
		{
			return m_decoders.end();
		}

		uint8 header[48] = {};
		constexpr int64 MinimumAudioHeaderSize = 16;

		if (reader.lookahead(header, sizeof(header)) < MinimumAudioHeaderSize)
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

	Array<std::unique_ptr<IAudioDecoder>>::const_iterator CAudioDecoder::findDecoder(const StringView encoderName) const
	{
		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
		{
			if ((*it)->name() == encoderName)
			{
				return it;
			}
		}

		return m_decoders.end();
	}
}
