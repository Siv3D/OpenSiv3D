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

# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CAudioCodec.hpp"

extern "C"
{
# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libswresample/swresample.h>
}
// https://ffmpeg.org/pipermail/libav-user/2013-January/003458.html
#undef av_err2str
#define av_err2str(errnum) av_make_error_string((char*)__builtin_alloca(AV_ERROR_MAX_STRING_SIZE), AV_ERROR_MAX_STRING_SIZE, errnum)

namespace s3d
{
	namespace detail
	{
		static ssize_t Read_Callback(void* data, void* dst, size_t size)
		{
			IReader* reader = static_cast<IReader*>(data);
			
			if (reader->getPos() + static_cast<ssize_t>(size) > reader->size())
			{
				size = static_cast<size_t>(reader->size() - reader->getPos());
			}
			
			reader->read(dst, size);
			
			return size;
		}
		
		static off_t Seek_Callback(void* data, off_t to, int type)
		{
			IReader* reader = static_cast<IReader*>(data);
			
			switch (type)
			{
				case SEEK_CUR:
					reader->setPos(reader->getPos() + to);
					break;
				case SEEK_END:
					reader->setPos(reader->size() + to);
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
			
			return static_cast<off_t>(reader->getPos());
		}
		
		static void Cleanup_Callback(void*)
		{
			return;
		}
	}

	namespace detail
	{
		class AACDecoder
		{
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
					LOG_TRACE(U"AACDecoder: avformat_open_input() failed ({}})"_fmt(m_path));
					return false;
				}

				if (avformat_find_stream_info(m_format_context, nullptr) < 0)
				{
					LOG_TRACE(U"AACDecoder: avformat_find_stream_info() failed ({})"_fmt(m_path));
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
					LOG_TRACE(U"AACDecoder: There are no audio stream ({})"_fmt(m_path));
					return false;
				}
				m_duration = m_audio_stream->duration;

				// setup codec.
				m_codec = avcodec_find_decoder(m_audio_stream->codecpar->codec_id);
				if (m_codec == nullptr)
				{
					LOG_TRACE(U"AACDecoder: avcodec_find_decoder() failed ({})"_fmt(m_path));
					return false;
				}
				m_codec_context = avcodec_alloc_context3(m_codec);
				if (m_codec_context == nullptr)
				{
					LOG_TRACE(U"AACDecoder: avcodec_alloc_context3() failed ({})"_fmt(m_path));
					return false;
				}
				if (avcodec_parameters_to_context(m_codec_context, m_audio_stream->codecpar) < 0)
				{
					LOG_TRACE(U"AACDecoder: avcodec_parameters_to_context() failed ({})"_fmt(m_path));
					return false;
				}
				if (avcodec_open2(m_codec_context, m_codec, nullptr) != 0)
				{
					LOG_TRACE(U"AACDecoder: avcodec_open2() failed ({})"_fmt(m_path));
					return false;
				}

				// allocate packet
				m_packet = (AVPacket*)av_malloc(sizeof(AVPacket));
				if (m_packet == nullptr)
				{
					LOG_TRACE(U"AACDecoder: av_malloc() failed (packet) ({})"_fmt(m_path));
					return false;
				}
				av_init_packet(m_packet);

				// allocate frame
				m_frame = av_frame_alloc();
				if (m_frame == nullptr)
				{
					LOG_TRACE(U"AACDecoder: av_frame_alloc() failed ({})"_fmt(m_path));
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
					LOG_TRACE(U"AACDecoder: swr_alloc() failed ({})"_fmt(m_path));
					return false;
				}
				[[maybe_unused]] int averr = swr_init(m_swr_context);
				if (swr_is_initialized(m_swr_context) == 0)
				{
					LOG_TRACE(U"AACDecoder: swr_init() failed (AVERROR: {}) ({})"_fmt(Unicode::Widen(av_err2str(averr)), m_path));
					return false;
				}

				// allocate output buffer
				int out_nb_channels = av_get_channel_layout_nb_channels(out_channel_layout);
				int buf_size = av_samples_get_buffer_size(nullptr,
						out_nb_channels, out_nb_samples, out_sample_fmt, 0);
				m_out_buf = (uint8_t*)av_malloc(buf_size);
				if (m_out_buf == nullptr)
				{
					LOG_TRACE(U"AACDecoder: av_malloc() failed (m_out_buf) ({})"_fmt(m_path));
					return false;
				}

				m_out_count = buf_size / out_nb_channels;

				return true;
			}

			Wave load()
			{
				Wave wave(m_duration, Arg::sampleRate = static_cast<uint32>(m_out_sample_rate));

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

		private:

			AVFormatContext* m_format_context = nullptr;
			AVCodecContext* m_codec_context = nullptr;
			AVFrame* m_frame = nullptr;
			AVPacket* m_packet = nullptr;
			struct SwrContext* m_swr_context = nullptr;
			uint8_t* m_out_buf = nullptr;

			AVStream* m_audio_stream = nullptr;
			int m_audio_stream_idx = 0;
			const AVCodec* m_codec = nullptr;
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
		};
	}


	CAudioCodec::CAudioCodec()
	{
		// do nothing
	}

	CAudioCodec::~CAudioCodec()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::~CAudioCodec()");

		DLL::Unload(m_mpg123);
	}

	void CAudioCodec::init()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::init()");

		loadMPG123();
	}

	Wave CAudioCodec::decode(IReader& reader, AudioFormat audioFormat)
	{
		if (audioFormat == AudioFormat::MP3)
		{
			return decodeMP3(reader);
		}

		// do nothing
		return{};
	}

	bool CAudioCodec::encode(const Wave& , IWriter&, AudioFormat)
	{
		// do nothing
		return(false);
	}

	Wave CAudioCodec::decode(const FilePathView path, const AudioFormat audioFormat)
	{
		if (audioFormat == AudioFormat::AAC)
		{
			detail::AACDecoder decoder;

			if (not decoder.init(FilePath{ path }))
			{
				LOG_FAIL(U"AACDecoder: init() failed.\n");
				return{};
			}

			return decoder.load();
		}

		/*
		detail::AudioFileDecoder decoder;
		
		if (not decoder.init(FilePath{ path }))
		{
			return{};
		}
		
		return decoder.load();
		*/
		return{};
	}	

	void CAudioCodec::loadMPG123()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::loadMPG123()");

		m_mpg123 = DLL::Load(U"libmpg123.so");
		
		if (not m_mpg123)
		{
			LOG_FAIL(U"❌ Failed to load libmpg123.so");
			return;
		}
		
		p_mpg123_init = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_init");
		p_mpg123_new = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_new");
		p_mpg123_delete = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_delete");
		p_mpg123_exit = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_exit");
		p_mpg123_param = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_param");
		p_mpg123_rates = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_rates");
		p_mpg123_format = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_format");
		p_mpg123_open_feed = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open_feed");
		p_mpg123_feed = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_feed");
		p_mpg123_decode_frame = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_decode_frame");
		p_mpg123_getformat = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_getformat");
		p_mpg123_scan = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_scan");
		p_mpg123_length = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_length");
		p_mpg123_open = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open");
		p_mpg123_open_handle = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open_handle");
		p_mpg123_replace_reader_handle = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_replace_reader_handle");
		p_mpg123_close = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_close");
		p_mpg123_info = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_info");
		
		if (not(p_mpg123_init && p_mpg123_new && p_mpg123_delete && p_mpg123_exit && p_mpg123_param
			&& p_mpg123_rates && p_mpg123_format && p_mpg123_open_feed && p_mpg123_feed
			&& p_mpg123_decode_frame && p_mpg123_getformat && p_mpg123_scan && p_mpg123_length
			&& p_mpg123_open && p_mpg123_open_handle && p_mpg123_replace_reader_handle
			&& p_mpg123_info))
		{
			return;
		}
		
		if (p_mpg123_init() != MPG123_OK)
		{
			p_mpg123_exit = nullptr;		
			return;
		}
		
		m_libmpg123Available = true;
		LOG_INFO(U"libmpg123 is available");
	}

	Wave CAudioCodec::decodeMP3(IReader& reader)
	{
		if (not m_libmpg123Available)
		{
			return{};
		}
		
		if (not reader.isOpen())
		{
			return{};
		}
		
		mpg123_handle* m = p_mpg123_new(nullptr, nullptr);
		
		if (!m)
		{
			return{};
		}
		
		p_mpg123_param(m, MPG123_RESYNC_LIMIT, -1, 0);
		
		if (p_mpg123_param(m, MPG123_FLAGS, MPG123_GAPLESS | MPG123_QUIET, 0) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return{};
		}
		
		if (p_mpg123_param(m, MPG123_INDEX_SIZE, -1, 0) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return{};
		}
		
		const long *rates = nullptr;
		
		size_t nrates = 0;
		
		p_mpg123_rates(&rates, &nrates);
		
		for (size_t i = 0; i < nrates; ++i)
		{
			if (p_mpg123_format(m, rates[i], MPG123_MONO | MPG123_STEREO, MPG123_ENC_16) != MPG123_OK)
			{
				p_mpg123_delete(m);
				return{};
			}
		}
		
		if (p_mpg123_replace_reader_handle(m, detail::Read_Callback, detail::Seek_Callback, detail::Cleanup_Callback) != MPG123_OK)
		{
			p_mpg123_close(m);
			p_mpg123_delete(m);
			return{};
		}

		if (p_mpg123_open_handle(m, &reader) != MPG123_OK)
		{
			p_mpg123_close(m);
			p_mpg123_delete(m);
			return Wave();
		}
		
		if (p_mpg123_scan(m) != MPG123_OK)
		{
			p_mpg123_close(m);
			p_mpg123_delete(m);
			return{};
		}
		
		const long sSize = p_mpg123_length(m);
		
		p_mpg123_close(m);
		
		if (sSize <= 0)
		{
			p_mpg123_delete(m);
			return{};
		}
		
		if (p_mpg123_open_feed(m) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return{};
		}
		
		reader.setPos(0);
		
		Wave wave(sSize);
		
		size_t inc = 0;
		off_t num = 0;
		unsigned char* audio = nullptr;
		size_t bytes = 0;
		long rate = 44100;
		int channels = 0;
		int enc = 0;
		size_t outc = 0;
		
		const size_t buffersize = 16384 * 4;
		Array<uint8> m_buffer(buffersize);
		WaveSample* pDst = wave.data();
		
		for (;;)
		{
			const int len = static_cast<int>(reader.read(m_buffer.data(), buffersize));
			
			if (len <= 0)
			{
				break;
			}
			
			inc += len;
			
			int ret = p_mpg123_feed(m, m_buffer.data(), len);
			
			while (ret != MPG123_ERR && ret != MPG123_NEED_MORE)
			{
				ret = p_mpg123_decode_frame(m, &num, &audio, &bytes);
				
				if (ret == MPG123_NEW_FORMAT)
				{
					p_mpg123_getformat(m, &rate, &channels, &enc);
					wave.setSampleRate(static_cast<uint32>(rate));
				}
				
				if (outc + bytes > (wave.size() * sizeof(WaveSampleS16)))
				{
					return{};
				}
				
				if (channels == 1)
				{
					const size_t length = bytes / sizeof(int16);
					const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(audio));
					
					for (size_t i = 0; i < length; ++i)
					{
						(pDst++)->set(*pSrc++);
					}
				}
				else
				{
					const size_t length = bytes / sizeof(WaveSampleS16);
					const WaveSampleS16* pSrc = static_cast<const WaveSampleS16*>(static_cast<const void*>(audio));
					
					for (size_t i = 0; i < length; ++i)
					{
						pDst->set(pSrc->left / 32768.0f, pSrc->right / 32768.0f);
						++pDst;
						++pSrc;
					}
				}
				
				outc += bytes;
			}
			
			if (ret == MPG123_ERR)
			{
				break;
			}
		}
		
		p_mpg123_delete(m);
		
		if (outc < (wave.size() * sizeof(WaveSampleS16)))
		{
			WaveSample* pDst = wave.data() + (outc / sizeof(WaveSample));
			
			::memset(pDst, 0, wave.size_bytes() - outc);
		}
		
		return wave;
	}
}
