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

# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "AudioFormat_WAVE.hpp"

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

	# define WAVE_FORMAT_IEEE_FLOAT 0x0003

	namespace detail
	{
		static constexpr uint8 RIFF_SIGN[] = { 'R', 'I', 'F', 'F' };
		static constexpr uint8 WAVE_SIGN[] = { 'W', 'A', 'V', 'E' };
		static constexpr uint8 FMT_CHUNK[] = { 'f', 'm', 't', ' ' };
		static constexpr uint8 DATA_CHUNK[] = { 'd', 'a', 't', 'a' };

		template <size_t Size>
		inline bool MemEqual(const uint8(&s1)[Size], const uint8(&s2)[Size])
		{
			return std::memcmp(s1, s2, Size) == 0;
		}
	}

	AudioFormat AudioFormat_WAVE::format() const
	{
		return AudioFormat::WAVE;
	}

	const Array<String>& AudioFormat_WAVE::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"wav" };

		return extensions;
	}

	bool AudioFormat_WAVE::isHeader(const uint8(&bytes)[16], const IReader&) const
	{
		static constexpr uint8 signature[] = { 0x52, 0x49, 0x46, 0x46 };

		return std::memcmp(bytes, signature, sizeof(signature)) == 0;
	}

	Wave AudioFormat_WAVE::decodeFromFile(const FilePath& path) const
	{
		BinaryReader reader(path);

		return decode(reader);
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

		Wave wave(num_samples, Arg::samplingRate = formatHeader.samplerate);

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

	bool AudioFormat_WAVE::encode(const Wave& wave, IWriter& writer, const WAVEFormat format) const
	{
		if (!wave || !writer.isOpen())
		{
			return false;
		}

		const uint16 bitsWidth = format == WAVEFormat::Stereo8U ? 1
			: format == WAVEFormat::Stereo16S ? 2 : 4;
		const uint16 channels = 2;
		const uint32 sampleRate = wave.samplingRate();
		const size_t waveSize = wave.size() * channels * bitsWidth;

		const uint32 headerSize = sizeof(RiffHeader) + sizeof(ChunkHeader) + sizeof(FormatHeader) + sizeof(ChunkHeader);

		const RiffHeader riffHeader
		{
			{ 'R', 'I', 'F', 'F' },
			static_cast<uint32>(waveSize + headerSize - 8),
			{ 'W', 'A', 'V', 'E' },
		};

		const ChunkHeader chunkHeader1
		{
			{ 'f', 'm', 't', ' ' },
			sizeof(FormatHeader),
		};

		const FormatHeader formatHeader
		{
			uint16((format == WAVEFormat::Stereo32F) ? WAVE_FORMAT_IEEE_FLOAT : 1),
			channels,
			sampleRate,
			sampleRate * bitsWidth * channels,
			uint16(bitsWidth * channels),
			uint16(bitsWidth * 8),
		};

		const ChunkHeader chunkHeader2
		{
			{ 'd', 'a', 't', 'a' },
			static_cast<uint32>(waveSize),
		};

		writer.write(&riffHeader, sizeof(riffHeader));
		writer.write(&chunkHeader1, sizeof(chunkHeader1));
		writer.write(&formatHeader, sizeof(formatHeader));
		writer.write(&chunkHeader2, sizeof(chunkHeader2));

		if (format == WAVEFormat::Stereo8U)
		{
			size_t samplesToWrite = wave.size();

			const uint32 bufferSize = 16384;
			Array<WS8bit> buffer(bufferSize);

			const WaveSample* pSrc = &wave[0];

			for (;;)
			{
				WS8bit* pDst = buffer.data();

				if (samplesToWrite > bufferSize)
				{
					for (uint32 i = 0; i < bufferSize; ++i)
					{
						pDst->left = static_cast<uint8>((pSrc->left + 1.0f) * 127.999f);
						pDst->right = static_cast<uint8>((pSrc->right + 1.0f) * 127.999f);
						++pDst;
						++pSrc;
					}

					writer.write(buffer.data(), bufferSize * sizeof(WS8bit));

					samplesToWrite -= bufferSize;
				}
				else
				{
					for (uint32 i = 0; i < samplesToWrite; ++i)
					{
						pDst->left = static_cast<uint8>((pSrc->left + 1.0f) * 127.999f);
						pDst->right = static_cast<uint8>((pSrc->right + 1.0f) * 127.999f);
						++pDst;
						++pSrc;
					}

					writer.write(buffer.data(), samplesToWrite * sizeof(WS8bit));

					break;
				}
			}
		}
		else if (format == WAVEFormat::Stereo16S)
		{
			size_t samplesToWrite = wave.size();

			const uint32 bufferCount = 16384;
			Array<WaveSampleS16> buffer(bufferCount);

			const WaveSample* pSrc = &wave[0];

			for (;;)
			{
				WaveSampleS16* pDst = buffer.data();

				if (samplesToWrite > bufferCount)
				{
					for (uint32 i = 0; i < bufferCount; ++i)
					{
						pDst->left = static_cast<int16>(pSrc->left * 32767.0f);
						pDst->right = static_cast<int16>(pSrc->right * 32767.0f);
						++pDst;
						++pSrc;
					}

					writer.write(buffer.data(), bufferCount * sizeof(WaveSampleS16));

					samplesToWrite -= bufferCount;
				}
				else
				{
					for (uint32 i = 0; i < samplesToWrite; ++i)
					{
						pDst->left = static_cast<int16>(pSrc->left * 32767.0f);
						pDst->right = static_cast<int16>(pSrc->right * 32767.0f);
						++pDst;
						++pSrc;
					}

					writer.write(buffer.data(), samplesToWrite * sizeof(WaveSampleS16));

					break;
				}
			}
		}
		else
		{
			writer.write(wave.data(), waveSize);
		}

		return true;
	}
}
