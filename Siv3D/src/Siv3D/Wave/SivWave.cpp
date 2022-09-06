//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Wave.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/AudioEncoder.hpp>
# include <Siv3D/Dialog.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/SoundFont/ISoundFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/AudioFormat/WAVEEncoder.hpp>
# include <Siv3D/AudioFormat/OggVorbisEncoder.hpp>

namespace s3d
{
	namespace detail
	{
		// https://stackoverflow.com/a/55112294
		inline constexpr size_t DeinterleaveIndex(const size_t i, const size_t length) noexcept
		{
			const size_t mid = (length - length / 2);

			if (i < mid)
			{
				return (i * 2);
			}

			return ((i - mid) * 2 + 1);
		}

		template <class Type>
		inline void Deinterleave(Type* arr, const size_t length) noexcept
		{
			if (length <= 1)
			{
				return;
			}

			for (size_t i = 1; i < length; ++i)
			{
				size_t k = DeinterleaveIndex(i, length);

				while (k < i)
				{
					k = DeinterleaveIndex(k, length);
				}

				std::swap(arr[i], arr[k]);
			}
		}
	}

	Wave::Wave(const FilePathView path, const AudioFormat format)
	{
		*this = AudioDecoder::Decode(path, format);
	}

	Wave::Wave(IReader&& reader, const AudioFormat format)
	{
		*this = AudioDecoder::Decode(reader, format);
	}

	Wave::Wave(const GMInstrument instrument, const uint8 key, const Duration& duration, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
		: Wave{ instrument, key, duration, SecondsF{ 1.0 }, velocity, sampleRate } {}

	Wave::Wave(const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		*this = SIV3D_ENGINE(SoundFont)->render(instrument, key, noteOn, noteOff, velocity, sampleRate);
	}

	Wave& Wave::swapLR() noexcept
	{
		for (auto& sample : m_data)
		{
			sample.swapChannel();
		}

		return *this;
	}

	Wave& Wave::removeSilenceFromBeginning()
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

		return *this;
	}

	Wave& Wave::removeSilenceFromEnd()
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

		return *this;
	}

	Wave& Wave::fadeIn(size_t samples) noexcept
	{
		if (not m_data)
		{
			return *this;
		}

		samples = Min(samples, m_data.size());

		const float delta = (1.0f / samples);
		WaveSample* pDst = m_data.data();

		for (size_t i = 0; i < samples; ++i)
		{
			*pDst++ *= (delta * i);
		}

		return *this;
	}

	Wave& Wave::fadeOut(size_t samples) noexcept
	{
		if (not m_data)
		{
			return *this;
		}

		samples = Min(samples, m_data.size());

		const float delta = (1.0f / samples);
		WaveSample* pDst = &m_data.back();

		for (size_t i = 0; i < samples; ++i)
		{
			*pDst-- *= (delta * i);
		}

		return *this;
	}

	void Wave::deinterleave() noexcept
	{
		detail::Deinterleave(&m_data[0].left, m_data.size() * 2);
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

	Wave& Wave::fill(const value_type& value)
	{
		m_data.fill(value);

		return *this;
	}

	Wave& Wave::append(const Array<value_type>& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	Wave& Wave::append(const Wave& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	Wave& Wave::remove_at(const size_t index)
	{
		m_data.remove_at(index);

		return *this;
	}

	Wave& Wave::reverse()
	{
		m_data.reverse();

		return *this;
	}

	Wave Wave::reversed() const
	{
		return Wave(rbegin(), rend());
	}

	Wave Wave::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return Wave(begin() + index, end());
	}

	Wave Wave::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return Wave(begin() + index, begin() + Min(index + length, size()));
	}
}
