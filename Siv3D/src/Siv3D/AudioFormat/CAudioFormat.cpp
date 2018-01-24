//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CAudioFormat.hpp"
# include "WAVE/AudioFormat_WAVE.hpp"
# include "MP3/AudioFormat_MP3_Windows.hpp"
# include "MP3/AudioFormat_MP3_mpg123.hpp"
# include "AAC/AudioFormat_AAC_Windows.hpp"
# include "AAC/AudioFormat_AAC_macOS.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/WritableMemoryMapping.hpp>
# include <Siv3D/Logger.hpp>

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

				const int64 size = reader.size();

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

	}

	bool CAudioFormat::init()
	{
		m_audioFormats.push_back(std::make_unique<AudioFormat_WAVE>());
		m_audioFormats.push_back(std::make_unique<AudioFormat_MP3>());

	# if defined(SIV3D_TARGET_WINDOWS) || defined(SIV3D_TARGET_MACOS)

		m_audioFormats.push_back(std::make_unique<AudioFormat_AAC>());

	# endif

		LOG_INFO(U"ℹ️ AudioFormat initialized");
		
		return true;
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
		
		if ((*it)->format() != AudioFormat::AAC)
		{
			return Wave();
		}

	# if defined(SIV3D_TARGET_MACOS)

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

	# if defined(SIV3D_TARGET_MACOS)

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
			if ((*it)->isHeader(header))
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
