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

	void Wave::swapLR() noexcept
	{
		for (auto& sample : m_data)
		{
			sample.swapChannel();
		}
	}

	void Wave::removeSilenceFromBeginning()
	{
		size_t count = 0;

		for (auto it = m_data.begin(); it != m_data.end(); ++it)
		{
			if (it->left || it->right)
			{
				break;
			}

			++count;
		}

		if (2 <= count)
		{
			m_data.pop_front_N(count - 1);
		}
	}

	void Wave::removeSilenceFromEnd()
	{
		size_t count = 0;

		for (auto it = m_data.rbegin(); it != m_data.rend(); ++it)
		{
			if (it->left || it->right)
			{
				break;
			}

			++count;
		}

		if (2 <= count)
		{
			m_data.pop_back_N(count - 1);
		}
	}

	void Wave::fadeIn(size_t samples) noexcept
	{
		if (not m_data)
		{
			return;
		}

		samples = Min(samples, m_data.size());

		const float delta = (1.0f / samples);
		WaveSample* pDst = m_data.data();

		for (size_t i = 0; i < samples; ++i)
		{
			*pDst++ *= (delta * i);
		}
	}

	void Wave::fadeOut(size_t samples) noexcept
	{
		if (not m_data)
		{
			return;
		}

		samples = Min(samples, m_data.size());

		const float delta = (1.0f / samples);
		WaveSample* pDst = &m_data.back();

		for (size_t i = 0; i < samples; ++i)
		{
			*pDst-- *= (delta * i);
		}
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
