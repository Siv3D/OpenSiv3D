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

# include <Siv3D/AudioFormat/WAVEDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include "WAVEHeader.hpp"

namespace s3d
{
	StringView WAVEDecoder::name() const
	{
		return U"WAVE"_sv;
	}

	bool WAVEDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 signature[] = { 0x52, 0x49, 0x46, 0x46 };

		return (std::memcmp(bytes, signature, sizeof(signature)) == 0);
	}

	const Array<String>& WAVEDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"wav" };

		return extensions;
	}

	AudioFormat WAVEDecoder::audioFormat() const noexcept
	{
		return AudioFormat::WAVE;
	}

	Wave WAVEDecoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave WAVEDecoder::decode(IReader& reader, [[maybe_unused]] const FilePathView pathHint) const
	{
		RiffHeader riffHeader;

		if (not reader.read(riffHeader))
		{
			return{};
		}

		if ((not detail::MemEqual(riffHeader.riff, detail::RIFF_SIGN))
			|| (not detail::MemEqual(riffHeader.type, detail::WAVE_SIGN)))
		{
			return{};
		}

		ChunkHeader chunkHeader;

		for (;;)
		{
			if (not reader.read(chunkHeader))
			{
				return{};
			}

			if (detail::MemEqual(chunkHeader.chunkID, detail::FMT_CHUNK))
			{
				break;
			}
			else
			{
				reader.setPos(reader.getPos() + chunkHeader.chunkSize);
			}
		}

		FormatHeader formatHeader;

		if (not reader.read(formatHeader))
		{
			return Wave();
		}

		if (chunkHeader.chunkSize > sizeof(formatHeader))
		{
			reader.skip(chunkHeader.chunkSize - sizeof(formatHeader));
		}

		for (;;)
		{
			if (not reader.read(chunkHeader))
			{
				return Wave();
			}

			if (detail::MemEqual(chunkHeader.chunkID, detail::DATA_CHUNK))
			{
				break;
			}
			else
			{
				reader.setPos(reader.getPos() + chunkHeader.chunkSize);
			}
		}

		const uint32 size_bytes = chunkHeader.chunkSize;
		const size_t num_samples = size_bytes / (formatHeader.channels * (formatHeader.bitsWidth / 8));

		Wave wave(num_samples, Arg::sampleRate = formatHeader.samplerate);

		if (formatHeader.bitsWidth == 8 && formatHeader.channels == 1)
		{
			// PCM 8bit 1ch
			Array<uint8> samples(num_samples);

			reader.read(samples.data(), size_bytes);

			for (size_t i = 0; i < num_samples; ++i)
			{
				wave[i].set(samples[i] / 127.5f - 1.0f);
			}
		}
		else if (formatHeader.bitsWidth == 8 && formatHeader.channels == 2)
		{
			// PCM 8bit 2ch
			Array<WS8bit> samples(num_samples);

			reader.read(samples.data(), size_bytes);

			for (uint32 i = 0; i < num_samples; ++i)
			{
				wave[i].set(samples[i].left / 127.5f - 1.0f, samples[i].right / 127.5f - 1.0f);
			}
		}
		else if (formatHeader.bitsWidth == 16 && formatHeader.channels == 1)
		{
			// PCM 16bit 1ch
			Array<int16> samples(num_samples);

			reader.read(samples.data(), size_bytes);

			for (uint32 i = 0; i < num_samples; ++i)
			{
				wave[i].set(samples[i] / 32768.0f);
			}
		}
		else if (formatHeader.bitsWidth == 16 && formatHeader.channels == 2)
		{
			// PCM 16bit 2ch
			Array<WaveSampleS16> samples(num_samples);

			reader.read(samples.data(), size_bytes);

			for (uint32 i = 0; i < num_samples; ++i)
			{
				wave[i].set(samples[i].left / 32768.0f, samples[i].right / 32768.0f);
			}
		}
		else if (formatHeader.bitsWidth == 24 && formatHeader.channels == 1)
		{
			// PCM 24bit 1ch
			size_t samplesToRead = size_bytes / sizeof(WaveSmaple24S_Mono);

			const uint32 bufferSize = 16384;

			Array<WaveSmaple24S_Mono> buffer(bufferSize);

			WaveSample* pDst = &wave[0];

			for (;;)
			{
				WaveSmaple24S_Mono* pSrc = buffer.data();

				if (samplesToRead > bufferSize)
				{
					reader.read(pSrc, bufferSize * sizeof(WaveSmaple24S_Mono));

					for (uint32 i = 0; i < bufferSize; ++i)
					{
						const int32 s = ((pSrc->mono[2] << 24) | (pSrc->mono[1] << 16) | (pSrc->mono[0] << 8)) / 65536;
						pDst->set(s / 32768.0f);
						++pDst;
						++pSrc;
					}

					samplesToRead -= bufferSize;
				}
				else
				{
					reader.read(pSrc, samplesToRead * sizeof(WaveSmaple24S_Mono));

					for (uint32 i = 0; i < samplesToRead; ++i)
					{
						const int32 s = ((pSrc->mono[2] << 24) | (pSrc->mono[1] << 16) | (pSrc->mono[0] << 8)) / 65536;
						pDst->set(s / 32768.0f);
						++pDst;
						++pSrc;
					}

					break;
				}
			}
		}
		else if (formatHeader.bitsWidth == 24 && formatHeader.channels == 2)
		{
			// PCM 24bit 2ch
			size_t samplesToRead = size_bytes / sizeof(WaveSmaple24S_Stereo);

			const uint32 bufferSize = 16384;

			Array<WaveSmaple24S_Stereo> buffer(bufferSize);

			WaveSample* pDst = &wave[0];

			for (;;)
			{
				WaveSmaple24S_Stereo* pSrc = buffer.data();

				if (samplesToRead > bufferSize)
				{
					reader.read(pSrc, bufferSize * sizeof(WaveSmaple24S_Stereo));

					for (uint32 i = 0; i < bufferSize; ++i)
					{
						const int32 sL = ((pSrc->left[2] << 24) | (pSrc->left[1] << 16) | (pSrc->left[0] << 8)) / 65536;
						const int32 sR = ((pSrc->right[2] << 24) | (pSrc->right[1] << 16) | (pSrc->right[0] << 8)) / 65536;
						pDst->left = sL / 32768.0f;
						pDst->right = sR / 32768.0f;
						++pDst;
						++pSrc;
					}

					samplesToRead -= bufferSize;
				}
				else
				{
					reader.read(pSrc, samplesToRead * sizeof(WaveSmaple24S_Stereo));

					for (uint32 i = 0; i < samplesToRead; ++i)
					{
						const int32 sL = ((pSrc->left[2] << 24) | (pSrc->left[1] << 16) | (pSrc->left[0] << 8)) / 65536;
						const int32 sR = ((pSrc->right[2] << 24) | (pSrc->right[1] << 16) | (pSrc->right[0] << 8)) / 65536;
						pDst->left = sL / 32768.0f;
						pDst->right = sR / 32768.0f;
						++pDst;
						++pSrc;
					}

					break;
				}
			}
		}
		else if (formatHeader.formatID == 0x0003 && formatHeader.bitsWidth == 32 && formatHeader.channels == 1)
		{
			// PCM 32bit float 1ch
			Array<float> samples(num_samples);

			reader.read(samples.data(), size_bytes);

			for (uint32 i = 0; i < num_samples; ++i)
			{
				wave[i].set(samples[i]);
			}
		}
		else if (formatHeader.formatID == 0x0003 && formatHeader.bitsWidth == 32 && formatHeader.channels == 2)
		{
			// PCM 32bit float 2ch
			reader.read(wave.data(), size_bytes);
		}
		else
		{
			return{};
		}

		return wave;
	}
}
