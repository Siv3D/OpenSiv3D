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
# include <libvorbis/vorbisfile.h>
# include <libvorbis/vorbisenc.h>
# include "AudioFormat_OggVorbis.hpp"

namespace s3d
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

	AudioFormat AudioFormat_OggVorbis::format() const
	{
		return AudioFormat::OggVorbis;
	}

	const Array<String>& AudioFormat_OggVorbis::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"ogg" };

		return extensions;
	}

	bool AudioFormat_OggVorbis::isHeader(const uint8(&bytes)[16], const IReader& reader) const
	{
		static constexpr uint8 OGG_SIGN[] = { 0x4f, 0x67, 0x67 };
		//static constexpr uint8 VORBIS_SIGN[] = { 'v', 'o', 'r', 'v', 'i', 's' };
		static constexpr uint8 OPUS_SIGN[] = { 'O', 'p', 'u', 's' };
		const bool isOgg = (std::memcmp(bytes, OGG_SIGN, sizeof(OGG_SIGN)) == 0);
		
		if (!isOgg)
		{
			return false;
		}
		
		uint8 hed2[48] = {};

		if (!reader.lookahead(hed2))
		{
			return false;
		}

		if (std::search(std::begin(hed2), std::end(hed2), std::begin(OPUS_SIGN), std::end(OPUS_SIGN))
			!= std::end(hed2))
		{
			return false;
		}

		return true;
	}

	Wave AudioFormat_OggVorbis::decodeFromFile(const FilePath& path) const
	{
		BinaryReader reader(path);

		return decode(reader);
	}

	Wave AudioFormat_OggVorbis::decode(IReader& reader) const
	{
		if (!reader.isOpen())
		{
			return Wave();
		}

			ov_callbacks callbacks;
			callbacks.read_func = ReadOgg_Callback;
			callbacks.seek_func = SeekOgg_Callback;
			callbacks.close_func = CloseOgg_Callback;
			callbacks.tell_func = TellOgg_Callback;

			OggVorbis_File vf;

			if (::ov_open_callbacks(&reader, &vf, nullptr, -1, callbacks) != 0)
			{
				return Wave();
			}

			vorbis_info* vi = ::ov_info(&vf, -1);

			if (!vi)
			{
				::ov_clear(&vf);		
				return Wave();
			}

			const uint32 samples = (::ov_pcm_total(&vf, -1)) & 0xffFFffFF;
			
			if (samples == 0)
			{
				return Wave();
			}
			
			const int32 channels = vi->channels;

			if (channels != 1 && channels != 2)
			{
				::ov_clear(&vf);
				return Wave();
			}
			
			Wave wave(samples, Arg::samplingRate = (vi->rate ? static_cast<uint32>(vi->rate) : Wave::DefaultSamplingRate));
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
						return Wave();
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
						return Wave();
					}

					const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(buffer.data()));

					for (int32 i = 0; i < samples_read; ++i)
					{
						const int16 left = *pSrc++;
						const int16 right = *pSrc++;
						*pDst++ = WaveSampleS16(left, right).asWaveSample();
					}
				}
			}

			::ov_clear(&vf);

			return wave;
	}

	bool AudioFormat_OggVorbis::encode(const Wave& wave, int32 quality, IWriter& writer) const
	{
		if (!wave || !writer.isOpen())
		{
			return false;
		}

		vorbis_info vi;

		::vorbis_info_init(&vi);

		if (::vorbis_encode_init_vbr(&vi, 2, wave.samplingRate(), quality == 0 ? -0.1f : 0.01f * quality) != 0)
		{
			return false;
		}

		vorbis_comment  vc;
		::vorbis_comment_init(&vc);
		::vorbis_comment_add_tag(&vc, "ENCODER", "Siv3D");

		//if (loop)
		//{
		//	::vorbis_comment_add_tag(&vc, "LOOPSTART", std::to_string(loop->loopBegin).c_str());
		//	::vorbis_comment_add_tag(&vc, "LOOPLENGTH", std::to_string(loop->loopLength).c_str());
		//}

		vorbis_dsp_state vd;
		::vorbis_analysis_init(&vd, &vi);

		vorbis_block  vb;
		::vorbis_block_init(&vd, &vb);

		ogg_stream_state os;
		::ogg_stream_init(&os, rand());

		ogg_packet header;
		ogg_packet header_comm;
		ogg_packet header_code;
		::vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
		::ogg_stream_packetin(&os, &header);
		::ogg_stream_packetin(&os, &header_comm);
		::ogg_stream_packetin(&os, &header_code);

		ogg_page og;
		ogg_packet op;

		for(;;)
		{
			const int result = ::ogg_stream_flush(&os, &og);

			if (result == 0)
			{
				break;
			}

			writer.write(og.header, og.header_len);
			writer.write(og.body, og.body_len);
		}

		const size_t READ = 4096;
		const WaveSample* pSrc = wave.data();
		size_t pos_read = 0;
		int eos = 0;

		while (!eos)
		{
			size_t samples_read = 0;

			if (pos_read + READ <= wave.lengthSample())
			{
				samples_read = READ / sizeof(WaveSample);
				pos_read += samples_read;
			}

			if (samples_read == 0)
			{
				::vorbis_analysis_wrote(&vd, 0);
			}
			else
			{
				float** buffer = ::vorbis_analysis_buffer(&vd, READ);

				for (size_t i = 0; i < samples_read; ++i)
				{
					buffer[0][i] = pSrc->left;
					buffer[1][i] = pSrc->right;
					++pSrc;
				}

				::vorbis_analysis_wrote(&vd, static_cast<int32>(samples_read));
			}

			while (::vorbis_analysis_blockout(&vd, &vb) == 1)
			{
				::vorbis_analysis(&vb, nullptr);
				::vorbis_bitrate_addblock(&vb);

				while (::vorbis_bitrate_flushpacket(&vd, &op))
				{
					::ogg_stream_packetin(&os, &op);

					while (!eos)
					{
						const int result = ::ogg_stream_pageout(&os, &og);

						if (result == 0)
						{
							break;
						}

						writer.write(og.header, og.header_len);
						writer.write(og.body, og.body_len);

						if (::ogg_page_eos(&og))
						{
							eos = 1;
						}
					}
				}
			}
		}

		::ogg_stream_clear(&os);
		::vorbis_block_clear(&vb);
		::vorbis_dsp_clear(&vd);
		::vorbis_comment_clear(&vc);
		::vorbis_info_clear(&vi);

		return true;
	}
}
