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

# include <string>

# define __STDC_CONSTANT_MACROS
extern "C"
{
# include <libavformat/avformat.h>
# include <libavcodec/avcodec.h>
# include <libavutil/avutil.h>
# include <libswresample/swresample.h>
}

// https://ffmpeg.org/pipermail/libav-user/2013-January/003458.html
#undef av_err2str
#define av_err2str(errnum) av_make_error_string((char*)__builtin_alloca(AV_ERROR_MAX_STRING_SIZE), AV_ERROR_MAX_STRING_SIZE, errnum)

# include <Siv3D/EngineLog.hpp>

# include "AudioFormat_AAC.hpp"

namespace s3d
{
	namespace detail
	{
		class AACDecoder
		{
		private:
			AVFormatContext* m_format_context = nullptr;
			AVCodecContext* m_codec_context = nullptr;
			AVFrame* m_frame = nullptr;
			AVPacket* m_packet = nullptr;
			struct SwrContext* m_swr_context = nullptr;
			uint8_t* m_out_buf = nullptr;

			AVStream* m_audio_stream = nullptr;
			int m_audio_stream_idx = 0;
			AVCodec* m_codec = nullptr;
			int m_out_count = 0;
			int m_out_sample_rate = 0;
			int64_t m_duration = 0;
			size_t m_wave_idx = 0;

			FilePath m_path;
			
			void setSample(Wave& wave, float* buf, size_t idx, size_t count)
			{
				WaveSample sample;
				for (size_t i = 0; i < count; ++i)
				{
					sample.set(buf[0], buf[1]);

					if (idx < wave.size())
						wave[idx] = sample;
					else
						wave.push_back(sample);

					buf += 2;
					idx++;
				}
			}

			bool decode_by_avcodec(Wave& wave, bool do_flush)
			{
				int ret;

				ret = avcodec_send_packet(m_codec_context, (do_flush ? nullptr : m_packet));
				if (ret < 0)
				{
					LOG_FAIL(U"AACDecoder: load() failed (avcodec_send_packet()) ({})"_fmt(m_path));
					return false;
				}

				while (avcodec_receive_frame(m_codec_context, m_frame) == 0)
				{
					ret = swr_convert(m_swr_context, &m_out_buf, m_out_count,
							(const uint8_t**)(m_frame->data), m_frame->nb_samples);
					if (ret < 0)
					{
						LOG_FAIL(U"AACDecoder: load() failed (avcodec_receive_frame()) ({})"_fmt(m_path));
						return false;
					}

					setSample(wave, (float*)m_out_buf, m_wave_idx, ret);
					m_wave_idx += ret;
				}

				return true;
			}

		public:
			~AACDecoder()
			{
				if (m_out_buf != nullptr)
					av_free(m_out_buf);
				if (m_swr_context != nullptr)
					swr_free(&m_swr_context);
				if (m_frame != nullptr)
					av_frame_free(&m_frame);
				if (m_packet != nullptr)
					av_packet_free(&m_packet);
				if (m_codec_context != nullptr)
					avcodec_free_context(&m_codec_context);
				if (m_format_context != nullptr)
					avformat_close_input(&m_format_context);
			}
			
			bool init(const FilePath& path)
			{
				const std::string pathUTF8 = path.toUTF8();
				const char* path_char = pathUTF8.c_str();

				m_path = path;

				// open file.
				if (avformat_open_input(&m_format_context, path_char, nullptr, nullptr) != 0)
				{
					LOG_DEBUG(U"AACDecoder: avformat_open_input() failed ({}})"_fmt(m_path));
					return false;
				}

				if (avformat_find_stream_info(m_format_context, nullptr) < 0)
				{
					LOG_DEBUG(U"AACDecoder: avformat_find_stream_info() failed ({})"_fmt(m_path));
					return false;
				}

				// search audio stream
				for (size_t i = 0; i < m_format_context->nb_streams; ++i)
				{
					if (m_format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
					{
						m_audio_stream = m_format_context->streams[i];
						m_audio_stream_idx = i;
						break;
					}
				}
				if (m_audio_stream == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: There are no audio stream ({})"_fmt(m_path));
					return false;
				}
				m_duration = m_audio_stream->duration;

				// setup codec.
				m_codec = avcodec_find_decoder(m_audio_stream->codecpar->codec_id);
				if (m_codec == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: avcodec_find_decoder() failed ({})"_fmt(m_path));
					return false;
				}
				m_codec_context = avcodec_alloc_context3(m_codec);
				if (m_codec_context == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: avcodec_alloc_context3() failed ({})"_fmt(m_path));
					return false;
				}
				if (avcodec_parameters_to_context(m_codec_context, m_audio_stream->codecpar) < 0)
				{
					LOG_DEBUG(U"AACDecoder: avcodec_parameters_to_context() failed ({})"_fmt(m_path));
					return false;
				}
				if (avcodec_open2(m_codec_context, m_codec, nullptr) != 0)
				{
					LOG_DEBUG(U"AACDecoder: avcodec_open2() failed ({})"_fmt(m_path));
					return false;
				}

				// allocate packet
				m_packet = (AVPacket*)av_malloc(sizeof(AVPacket));
				if (m_packet == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: av_malloc() failed (packet) ({})"_fmt(m_path));
					return false;
				}
				av_init_packet(m_packet);

				// allocate frame
				m_frame = av_frame_alloc();
				if (m_frame == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: av_frame_alloc() failed ({})"_fmt(m_path));
					return false;
				}

				// initialize swr context
				int64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
				int out_nb_samples = m_codec_context->frame_size;
				AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_FLT;
				m_out_sample_rate = m_codec_context->sample_rate;
				m_swr_context = swr_alloc_set_opts(m_swr_context,
						out_channel_layout, out_sample_fmt, m_out_sample_rate,
						av_get_default_channel_layout(m_codec_context->channels),
						m_codec_context->sample_fmt, m_codec_context->sample_rate, 0, nullptr);
				if (m_swr_context == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: swr_alloc() failed ({})"_fmt(m_path));
					return false;
				}
				int averr = swr_init(m_swr_context);
				if (swr_is_initialized(m_swr_context) == 0)
				{
					LOG_DEBUG(U"AACDecoder: swr_init() failed (AVERROR: {}) ({})"_fmt(Unicode::Widen(av_err2str(averr)), m_path));
					return false;
				}

				// allocate output buffer
				int out_nb_channels = av_get_channel_layout_nb_channels(out_channel_layout);
				int buf_size = av_samples_get_buffer_size(nullptr,
						out_nb_channels, out_nb_samples, out_sample_fmt, 0);
				m_out_buf = (uint8_t*)av_malloc(buf_size);
				if (m_out_buf == nullptr)
				{
					LOG_DEBUG(U"AACDecoder: av_malloc() failed (m_out_buf) ({})"_fmt(m_path));
					return false;
				}

				m_out_count = buf_size / out_nb_channels;

				return true;
			}

			Wave load()
			{
				Wave wave(m_duration, Arg::samplingRate = static_cast<uint32>(m_out_sample_rate));

				while (0 <= av_read_frame(m_format_context, m_packet))
				{
					if (m_packet->stream_index == m_audio_stream_idx)
					{
						if(!decode_by_avcodec(wave, false))
							return Wave();
					}
					av_packet_unref(m_packet);
				}

				// flush decoder
				if(!decode_by_avcodec(wave, true))
					return Wave();

				wave.resize(m_wave_idx);
				return wave;
			}
		};
	}

	AudioFormat_AAC::AudioFormat_AAC()
	{

	}

	AudioFormat_AAC::~AudioFormat_AAC()
	{

	}

	AudioFormat AudioFormat_AAC::format() const
	{
		return AudioFormat::AAC;
	}

	const Array<String>& AudioFormat_AAC::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	bool AudioFormat_AAC::isHeader(const uint8(&bytes)[16], const IReader&) const
	{
		// M4V MPEG-4 video/QuickTime file
		static constexpr uint8 M4V_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32 };

		// M4A Apple Lossless Audio Codec file
		static constexpr uint8 M4A_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x4D, 0x34, 0x41, 0x20 };

		// MP4 ftypisom
		static constexpr uint8 MP4ISOM_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D };

		return (::memcmp(bytes + 4, M4V_SIGNx, sizeof(M4V_SIGNx)) == 0
				|| ::memcmp(bytes + 4, M4A_SIGNx, sizeof(M4A_SIGNx)) == 0
				|| ::memcmp(bytes + 4, MP4ISOM_SIGNx, sizeof(MP4ISOM_SIGNx)) == 0);
	}

	Wave AudioFormat_AAC::decodeFromFile(const FilePath& path) const
	{
		detail::AACDecoder decoder;

		if (!decoder.init(path))
		{
			LOG_FAIL(U"AACDecoder: init() failed.\n");
			return Wave();
		}

		return decoder.load();
	}

	Wave AudioFormat_AAC::decode(IReader&) const
	{
		// not supported
		return Wave();
	}
}
