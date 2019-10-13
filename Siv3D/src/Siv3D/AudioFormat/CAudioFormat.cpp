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

# include <AudioFormat/WAVE/AudioFormat_WAVE.hpp>
# include <AudioFormat/MP3/AudioFormat_MP3.hpp>
# include <AudioFormat/AAC/AudioFormat_AAC.hpp>
# include <AudioFormat/OggVorbis/AudioFormat_OggVorbis.hpp>
# include <Siv3D/IReader.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/WritableMemoryMapping.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CAudioFormat.hpp"

namespace s3d
{
	namespace detail
	{
		class TemporaryFile
		{
		private:

			FilePath m_path;

		public:

			TemporaryFile(const IReader& reader)
				: m_path(FileSystem::UniqueFilePath())
			{
				WritableMemoryMapping file(m_path);

				const size_t size = static_cast<size_t>(reader.size());

				file.map(0, size);

				reader.lookahead(file.data(), size);

				file.unmap();
			}

			~TemporaryFile()
			{
				FileSystem::Remove(m_path);
			}

			const FilePath& path() const
			{
				return m_path;
			}
		};
	}

	CAudioFormat::CAudioFormat()
	{

	}

	CAudioFormat::~CAudioFormat()
	{
		LOG_TRACE(U"CAudioFormat::~CAudioFormat()");
	}

	void CAudioFormat::init()
	{
		LOG_TRACE(U"CAudioFormat::init()");

		m_audioFormats.push_back(std::make_unique<AudioFormat_WAVE>());
		m_audioFormats.push_back(std::make_unique<AudioFormat_MP3>());
		m_audioFormats.push_back(std::make_unique<AudioFormat_AAC>());
		m_audioFormats.push_back(std::make_unique<AudioFormat_OggVorbis>());

		LOG_INFO(U"ℹ️ CAudioFormat initialized");
	}

	AudioFormat CAudioFormat::getFormatFromReader(const IReader& reader, const FilePath& pathHint) const
	{
		const auto it = findFormat(reader, pathHint);

		if (it == m_audioFormats.end())
		{
			return AudioFormat::Unknown;
		}

		return (*it)->format();
	}

	AudioFormat CAudioFormat::getFormatFromFilePath(const FilePath& path) const
	{
		if (!path.isEmpty())
		{
			const String extension = FileSystem::Extension(path);

			for (const auto& audioFormat : m_audioFormats)
			{
				if (audioFormat->possibleExtexsions().includes(extension))
				{
					return audioFormat->format();
				}
			}
		}

		return AudioFormat::Unknown;
	}

	Wave CAudioFormat::load(const FilePath& path) const
	{
		BinaryReader reader(path);

		const auto it = findFormat(reader, path);

		if (it == m_audioFormats.end())
		{
			return Wave();
		}
		
	# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

		if ((*it)->format() == AudioFormat::AAC)
		{
			reader.close();

			return (*it)->decodeFromFile(path);
		}

	# endif

		return (*it)->decode(reader);
	}

	Wave CAudioFormat::decode(IReader&& reader, AudioFormat format) const
	{
		if (format == AudioFormat::Unknown)
		{
			format = getFormatFromReader(reader, String());
		}

		const auto it = findFormat(format);

		if (it == m_audioFormats.end())
		{
			return Wave();
		}

	# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

		if ((*it)->format() == AudioFormat::AAC)
		{
			detail::TemporaryFile tmp(reader);
			
			return (*it)->decodeFromFile(tmp.path());
		}

	# endif

		return (*it)->decode(reader);
	}

	bool CAudioFormat::encodeWAVE(IWriter& writer, const Wave& wave, const WAVEFormat format) const
	{
		const auto p = findFormat(AudioFormat::WAVE);

		if (p == m_audioFormats.end())
		{
			return false;
		}

		if (const AudioFormat_WAVE* wav = dynamic_cast<AudioFormat_WAVE*>(p->get()))
		{
			return wav->encode(wave, writer, format);
		}

		return false;
	}

	bool CAudioFormat::encodeOggVorbis(IWriter& writer, const Wave& wave, const int32 quality) const
	{
		const auto p = findFormat(AudioFormat::OggVorbis);

		if (p == m_audioFormats.end())
		{
			return false;
		}

		if (const AudioFormat_OggVorbis * wav = dynamic_cast<AudioFormat_OggVorbis*>(p->get()))
		{
			return wav->encode(wave, quality, writer);
		}

		return false;
	}

	Array<std::unique_ptr<IAudioFormat>>::const_iterator CAudioFormat::findFormat(const AudioFormat format) const
	{
		for (auto it = m_audioFormats.begin(); it != m_audioFormats.end(); ++it)
		{
			if ((*it)->format() == format)
			{
				return it;
			}
		}

		return m_audioFormats.end();
	}

	Array<std::unique_ptr<IAudioFormat>>::const_iterator CAudioFormat::findFormat(const IReader& reader, const FilePath& pathHint) const
	{
		if (!reader.isOpened())
		{
			return m_audioFormats.end();
		}

		if (!reader.supportsLookahead())
		{
			return m_audioFormats.end();
		}

		uint8 header[16] = {};

		if (!reader.lookahead(header))
		{
			return m_audioFormats.end();
		}

		for (auto it = m_audioFormats.begin(); it != m_audioFormats.end(); ++it)
		{
			if ((*it)->isHeader(header, reader))
			{
				return it;
			}
		}

		if (!pathHint.isEmpty())
		{
			const String extension = FileSystem::Extension(pathHint);

			for (auto it = m_audioFormats.begin(); it != m_audioFormats.end(); ++it)
			{
				if ((*it)->possibleExtexsions().includes(extension))
				{
					return it;
				}
			}
		}

		return m_audioFormats.end();
	}
}
