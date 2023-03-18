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

# include <Siv3D/AudioFormat/OggVorbisDecoder.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Parse.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/vorbis/vorbisenc.h>
#	include <ThirdParty-prebuilt/vorbis/vorbisfile.h>
# else
#	include <vorbis/vorbisenc.h>
#	include <vorbis/vorbisfile.h>
# endif

namespace s3d
{
	namespace detail
	{
		static size_t ReadOgg_Callback(void* dst, size_t size1, size_t size2, void* data)
		{
			IReader* reader = static_cast<IReader*>(data);

			size_t len = size1 * size2;

			if (reader->getPos() + static_cast<int64>(len) > reader->size())
			{
				len = static_cast<size_t>(reader->size() - reader->getPos());
			}

			reader->read(dst, len);

			return len;
		}

		static int SeekOgg_Callback(void* data, ogg_int64_t to, int type)
		{
			IReader* reader = static_cast<IReader*>(data);

			switch (type)
			{
			case SEEK_CUR:
				reader->setPos(reader->getPos() + to);
				break;
			case SEEK_END:
				reader->setPos(reader->size() - to);
				break;
			case SEEK_SET:
				reader->setPos(to);
				break;
			default:
				return -1;
			}

			if (reader->getPos() < 0)
			{
				reader->setPos(0);

				return -1;
			}

			if (reader->getPos() > reader->size())
			{
				reader->setPos(reader->size());

				return -1;
			}

			return 0;
		}

		static int CloseOgg_Callback(void*)
		{
			return 0;
		}

		static long TellOgg_Callback(void* data)
		{
			IReader* reader = static_cast<IReader*>(data);

			return static_cast<long>(reader->getPos());
		}
	}

	StringView OggVorbisDecoder::name() const
	{
		return U"OggVorbis"_sv;
	}

	bool OggVorbisDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 OGG_SIGN[] = { 0x4f, 0x67, 0x67 };
		//static constexpr uint8 VORBIS_SIGN[] = { 'v', 'o', 'r', 'v', 'i', 's' };
		static constexpr uint8 OPUS_SIGN[] = { 'O', 'p', 'u', 's' };
		const bool isOgg = (std::memcmp(bytes, OGG_SIGN, sizeof(OGG_SIGN)) == 0);

		if (not isOgg)
		{
			return false;
		}

		if (std::search(std::begin(bytes), std::end(bytes), std::begin(OPUS_SIGN), std::end(OPUS_SIGN))
			!= std::end(bytes))
		{
			return false;
		}

		return true;
	}

	const Array<String>& OggVorbisDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"ogg" };

		return extensions;
	}

	AudioFormat OggVorbisDecoder::audioFormat() const noexcept
	{
		return AudioFormat::OggVorbis;
	}

	Wave OggVorbisDecoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave OggVorbisDecoder::decode(IReader& reader, [[maybe_unused]] const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		ov_callbacks callbacks;
		callbacks.read_func = detail::ReadOgg_Callback;
		callbacks.seek_func = detail::SeekOgg_Callback;
		callbacks.close_func = detail::CloseOgg_Callback;
		callbacks.tell_func = detail::TellOgg_Callback;

		OggVorbis_File vf;

		if (::ov_open_callbacks(&reader, &vf, nullptr, -1, callbacks) != 0)
		{
			return{};
		}

		vorbis_info* vi = ::ov_info(&vf, -1);

		if (not vi)
		{
			::ov_clear(&vf);
			return{};
		}

		const uint32 samples = (::ov_pcm_total(&vf, -1)) & 0xffFFffFF;

		if (samples == 0)
		{
			return{};
		}

		const int32 channels = vi->channels;

		if (channels != 1 && channels != 2)
		{
			::ov_clear(&vf);
			return{};
		}

		Wave wave(samples, Arg::sampleRate = (vi->rate ? static_cast<uint32>(vi->rate) : Wave::DefaultSampleRate));
		constexpr int32 BufferSize = 4096;
		std::array<char, BufferSize> buffer;
		WaveSample* pDst = wave.data();
		int current_sec = 0;

		if (channels == 1)
		{
			for (;;)
			{
				const long bytes_read = ::ov_read(&vf, buffer.data(), BufferSize, 0, 2, 1, &current_sec);
				const long samples_read = (bytes_read / 2);

				if (bytes_read == 0)
				{
					break;
				}
				else if (bytes_read < 0)
				{
					::ov_clear(&vf);
					return{};
				}

				const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(buffer.data()));

				for (int32 i = 0; i < samples_read; ++i)
				{
					*pDst++ = WaveSampleS16(*pSrc++).asWaveSample();
				}
			}
		}
		else // channels == 2
		{
			for (;;)
			{
				const long bytes_read = ::ov_read(&vf, buffer.data(), BufferSize, 0, 2, 1, &current_sec);
				const long samples_read = (bytes_read / 4);

				if (bytes_read == 0)
				{
					break;
				}
				else if (bytes_read < 0)
				{
					::ov_clear(&vf);
					return{};
				}

				const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(buffer.data()));

				for (int32 i = 0; i < samples_read; ++i)
				{
					const int16 left = *pSrc++;
					const int16 right = *pSrc++;
					*pDst++ = WaveSample::FromInt16(left, right);
				}
			}
		}

		::ov_clear(&vf);

		return wave;
	}

	AudioLoopTiming OggVorbisDecoder::getLoopInfo(const FilePathView path) const
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return{};
		}

		return getLoopInfo(reader);
	}

	AudioLoopTiming OggVorbisDecoder::getLoopInfo(IReader& reader) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		ov_callbacks callbacks;
		callbacks.read_func = detail::ReadOgg_Callback;
		callbacks.seek_func = detail::SeekOgg_Callback;
		callbacks.close_func = detail::CloseOgg_Callback;
		callbacks.tell_func = detail::TellOgg_Callback;

		OggVorbis_File vf;

		if (::ov_open_callbacks(&reader, &vf, nullptr, -1, callbacks) != 0)
		{
			return{};
		}

		vorbis_info* vi = ::ov_info(&vf, -1);

		if (not vi)
		{
			::ov_clear(&vf);

			return{};
		}

		uint64 loopstart = 0, looplength = 0;
		char** ptr = vf.vc->user_comments;

		while (*ptr)
		{
			const Array<String> tag = Unicode::WidenAscii(*ptr).split(L'=');

			if (tag.size() == 2)
			{
				if (tag[0] == U"LOOPSTART")
				{
					loopstart = ParseOr<uint64>(tag[1], 0);
				}
				else if (tag[0] == U"LOOPLENGTH")
				{
					looplength = ParseOr<uint64>(tag[1], 0);
				}
			}

			++ptr;
		}

		::ov_clear(&vf);

		if (looplength == 0)
		{
			return{};
		}

		return{ loopstart, (loopstart + looplength) };
	}
}
