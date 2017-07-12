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

# include "AudioFormat_WAVE.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
# pragma pack (push, 1)

	struct RiffHeader
	{
		uint8 riff[4];
		uint32 fileSizeWithoutHead8;
		uint8 type[4];
	};

	struct ChunkHeader
	{
		uint8 chunkID[4];
		uint32 chunkSize;
	};

	struct FormatHeader
	{
		uint16 formatID;
		uint16 channels;
		uint32 samplerate;
		uint32 bytePerSec;
		uint16 blockAlign;
		uint16 bitsWidth;
	};

	struct WS8bit
	{
		uint8 left;
		uint8 right;
	};

	struct WaveSmaple24S_Mono
	{
		uint8 mono[3];
	};

	struct WaveSmaple24S_Stereo
	{
		uint8 left[3];
		uint8 right[3];
	};

# pragma pack ( pop )

	namespace detail
	{
		static constexpr uint8 RIFF_SIGN[] = { 'R', 'I', 'F', 'F' };
		static constexpr uint8 WAVE_SIGN[] = { 'W', 'A', 'V', 'E' };
		static constexpr uint8 FMT_CHUNK[] = { 'f', 'm', 't', ' ' };
		static constexpr uint8 DATA_CHUNK[] = { 'd', 'a', 't', 'a' };

		template <size_t Size>
		inline bool MemEqual(const uint8(&s1)[Size], const uint8(&s2)[Size])
		{
			return ::memcmp(s1, s2, Size) == 0;
		}
	}

	AudioFormat AudioFormat_WAVE::format() const
	{
		return AudioFormat::WAVE;
	}

	const Array<String>& AudioFormat_WAVE::possibleExtexsions() const
	{
		static const Array<String> extensions = { S3DSTR("wav") };

		return extensions;
	}

	bool AudioFormat_WAVE::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature[] = { 0x42, 0x4d };

		return ::memcmp(bytes, signature, sizeof(signature)) == 0;
	}

	Wave AudioFormat_WAVE::decode(IReader& reader) const
	{
		RiffHeader riffHeader;

		if (!reader.read(riffHeader))
		{
			return Wave();
		}

		if (!detail::MemEqual(riffHeader.riff, detail::RIFF_SIGN) || !detail::MemEqual(riffHeader.type, detail::WAVE_SIGN))
		{
			return Wave();
		}

		ChunkHeader chunkHeader;

		for (;;)
		{
			if (!reader.read(chunkHeader))
			{
				return Wave();
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

		if (!reader.read(formatHeader))
		{
			return Wave();
		}

		if (chunkHeader.chunkSize > sizeof(formatHeader))
		{
			reader.skip(chunkHeader.chunkSize - sizeof(formatHeader));
		}

		for (;;)
		{
			if (!reader.read(chunkHeader))
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

		Wave wave(num_samples, formatHeader.samplerate);

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
			return Wave();
		}

		return wave;
	}
}
