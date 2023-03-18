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

# include <Siv3D/AudioFormat/OggVorbisEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/Wave.hpp>
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
	StringView OggVorbisEncoder::name() const
	{
		return U"OggVorbis"_sv;
	}

	const Array<String>& OggVorbisEncoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"ogg" };

		return extensions;
	}

	bool OggVorbisEncoder::save(const Wave& wave, const FilePathView path) const
	{
		return save(wave, path, DefaultQuality);
	}

	bool OggVorbisEncoder::save(const Wave& wave, const FilePathView path, const int32 quality, const AudioLoopTiming& loopTiming) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(wave, writer, quality, loopTiming);
	}

	bool OggVorbisEncoder::encode(const Wave& wave, IWriter& writer) const
	{
		return encode(wave, writer, DefaultQuality);
	}

	bool OggVorbisEncoder::encode(const Wave& wave, IWriter& writer, const int32 quality, const AudioLoopTiming& loopTiming) const
	{
		if ((not wave) || (not writer.isOpen()))
		{
			return false;
		}

		vorbis_info vi;

		::vorbis_info_init(&vi);

		if (::vorbis_encode_init_vbr(&vi, 2, wave.sampleRate(), quality == 0 ? -0.1f : 0.01f * quality) != 0)
		{
			return false;
		}

		vorbis_comment  vc;
		::vorbis_comment_init(&vc);
		::vorbis_comment_add_tag(&vc, "ENCODER", "Siv3D");

		if (const int64 loopLength = (loopTiming.endPos - loopTiming.beginPos);
			0 < loopLength)
		{
			::vorbis_comment_add_tag(&vc, "LOOPSTART", std::to_string(loopTiming.beginPos).c_str());
			::vorbis_comment_add_tag(&vc, "LOOPLENGTH", std::to_string(loopLength).c_str());
		}

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

		for (;;)
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

	Blob OggVorbisEncoder::encode(const Wave& wave) const
	{
		return encode(wave, DefaultQuality);
	}

	Blob OggVorbisEncoder::encode(const Wave& wave, const int32 quality, const AudioLoopTiming& loopTiming) const
	{
		MemoryWriter writer;

		if (not encode(wave, writer, quality, loopTiming))
		{
			return{};
		}

		return writer.retrieve();
	}
}
