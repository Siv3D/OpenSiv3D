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

# include <Siv3D/AudioFormat/OpusDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/ogg/ogg.h>
#	include <ThirdParty-prebuilt/opus/opus.h>
#	include <ThirdParty-prebuilt/opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# else
#	include <ogg/ogg.h>
#	include <opus/opus.h>
#	include <opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# endif

namespace s3d
{
	StringView OpusDecoder::name() const
	{
		return U"Opus"_sv;
	}

	bool OpusDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 OGG_SIGN[] = { 0x4f, 0x67, 0x67 };
		static constexpr uint8 OPUS_SIGN[] = { 'O', 'p', 'u', 's' };
		const bool isOgg = (std::memcmp(bytes, OGG_SIGN, sizeof(OGG_SIGN)) == 0);

		if (not isOgg)
		{
			return false;
		}

		if (std::search(std::begin(bytes), std::end(bytes), std::begin(OPUS_SIGN), std::end(OPUS_SIGN))
			!= std::end(bytes))
		{
			return true;
		}

		return false;
	}

	const Array<String>& OpusDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"opus" };

		return extensions;
	}

	AudioFormat OpusDecoder::audioFormat() const noexcept
	{
		return AudioFormat::Opus;
	}

	Wave OpusDecoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave OpusDecoder::decode(IReader& reader, [[maybe_unused]] const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		Array<uint8> data(reader.size());
		reader.read(data.data(), data.size());

		int err;
		OggOpusFile* of = ::op_open_memory(data.data(), data.size(), &err);

		if (not of)
		{
			return{};
		}

		const OpusHead* head = ::op_head(of, 0);
		const uint32 num_channels = head->channel_count;
		LOG_TRACE(U"OpusDecoder::decode(): num_channels == {}"_fmt(num_channels));

		if ((num_channels != 1) && (num_channels != 2))
		{
			return{};
		}

		const size_t total = ::op_pcm_total(of, -1);
		Wave wave(total);

		if (num_channels == 1)
		{
			constexpr size_t BufferCount = 16384;
			Array<float> buffer(BufferCount);
			WaveSample* pDst = wave.data();

			for (;;)
			{
				const int32 result = ::op_read_float(of, buffer.data(), BufferCount, nullptr);

				if (0 < result)
				{
					for (int32 i = 0; i < result; ++i)
					{
						*pDst++ = buffer[i];
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			WaveSample* pDst = wave.data();
			int32 write_size = 0;

			for (;;)
			{
				const int32 result = ::op_read_float(of, &pDst->left,
					static_cast<int32>((wave.samples() * 2) - write_size), nullptr);

				if (0 < result)
				{
					write_size += (result * 2);
					pDst += result;
				}
				else
				{
					break;
				}
			}
		}

		wave.setSampleRate(head->input_sample_rate);

		::op_free(of);

		return wave;
	}
}
