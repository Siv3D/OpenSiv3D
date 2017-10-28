//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CAudioFormat.hpp"
# include "WAVE/AudioFormat_WAVE.hpp"
# include "MP3/AudioFormat_MP3_Windows.hpp"
# include "MP3/AudioFormat_MP3_macOS.hpp"
# include "MP3/AudioFormat_MP3_Linux.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
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
				if (audioFormat->possibleExtexsions().include(extension))
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
				if ((*it)->possibleExtexsions().include(extension))
				{
					return it;
				}
			}
		}

		return m_audioFormats.end();
	}
}
