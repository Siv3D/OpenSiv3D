//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Wave.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/AudioEncoder.hpp>
# include <Siv3D/Dialog.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioFormat/WAVEEncoder.hpp>
# include <Siv3D/AudioFormat/OggVorbisEncoder.hpp>

namespace s3d
{
	Wave::Wave(const FilePathView path, const AudioFormat format)
	{
		*this = AudioDecoder::Decode(path, format);
	}

	Wave::Wave(IReader&& reader, const AudioFormat format)
	{
		*this = AudioDecoder::Decode(reader, format);
	}

	bool Wave::save(const FilePathView path, const AudioFormat format) const
	{
		return AudioEncoder::Save(*this, format, path);
	}

	Blob Wave::encode(const AudioFormat format) const
	{
		return AudioEncoder::Encode(*this, format);
	}

	bool Wave::saveWithDialog() const
	{
		if (isEmpty())
		{
			LOG_FAIL(U"Wave::saveWithDialog(): Wave is empty");
			return false;
		}

		if (const auto path = Dialog::SaveWave())
		{
			return save(*path);
		}
		else
		{
			return false;
		}
	}

	bool Wave::saveWAVE(const FilePathView path, const WAVEFormat format) const
	{
		return WAVEEncoder{}.save(*this, path, format);
	}

	Blob Wave::encodeWAVE(const WAVEFormat format) const
	{
		return WAVEEncoder{}.encode(*this, format);
	}

	bool Wave::saveOggVorbis(const FilePathView path, const int32 quality, const AudioLoopTiming& loopTiming) const
	{
		return OggVorbisEncoder{}.save(*this, path, quality, loopTiming);
	}

	Blob Wave::encodeOggVorbis(const int32 quality, const AudioLoopTiming& loopTiming) const
	{
		return OggVorbisEncoder{}.encode(*this, quality, loopTiming);
	}
}
