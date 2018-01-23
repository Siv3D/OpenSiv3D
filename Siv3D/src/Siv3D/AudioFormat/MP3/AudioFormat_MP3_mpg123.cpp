//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "AudioFormat_MP3_mpg123.hpp"
# include "../../Siv3DEngine.hpp"
# include "../../Codec/ICodec.hpp"
# include "../../EngineUtility.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>

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

	AudioFormat_MP3::AudioFormat_MP3()
	{
	# if defined(SIV3D_TARGET_MACOS)

		const FilePath libPath = Resource(U"engine/lib/mpg123/libmpg123.0.dylib");	

	# else

		const FilePath libPath = Resource(U"engine/lib/mpg123/libmpg123.so");

	# endif

		m_mpg123 = dlopen(libPath.narrow().c_str(), RTLD_LOCAL | RTLD_LAZY);

		if (!m_mpg123)
		{
			LOG_FAIL(U"❌ AudioFormat_MP3: Failed to load \"{0}\""_fmt(libPath));
			
			return;
		}

		p_mpg123_init = FunctionPointer(m_mpg123, "mpg123_init");
		p_mpg123_new = FunctionPointer(m_mpg123, "mpg123_new");
		p_mpg123_delete = FunctionPointer(m_mpg123, "mpg123_delete");
		p_mpg123_exit = FunctionPointer(m_mpg123, "mpg123_exit");
		p_mpg123_param = FunctionPointer(m_mpg123, "mpg123_param");
		p_mpg123_rates = FunctionPointer(m_mpg123, "mpg123_rates");
		p_mpg123_format = FunctionPointer(m_mpg123, "mpg123_format");
		p_mpg123_open_feed = FunctionPointer(m_mpg123, "mpg123_open_feed");
		p_mpg123_feed = FunctionPointer(m_mpg123, "mpg123_feed");
		p_mpg123_decode_frame = FunctionPointer(m_mpg123, "mpg123_decode_frame");
		p_mpg123_getformat = FunctionPointer(m_mpg123, "mpg123_getformat");
		p_mpg123_scan = FunctionPointer(m_mpg123, "mpg123_scan");
		p_mpg123_length = FunctionPointer(m_mpg123, "mpg123_length");
		p_mpg123_open = FunctionPointer(m_mpg123, "mpg123_open");
		p_mpg123_open_handle = FunctionPointer(m_mpg123, "mpg123_open_handle");
		p_mpg123_replace_reader_handle = FunctionPointer(m_mpg123, "mpg123_replace_reader_handle");
		p_mpg123_close = FunctionPointer(m_mpg123, "mpg123_close");
		p_mpg123_info = FunctionPointer(m_mpg123, "mpg123_info");

		if (!(p_mpg123_init && p_mpg123_new && p_mpg123_delete && p_mpg123_exit && p_mpg123_param
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
	}

	AudioFormat_MP3::~AudioFormat_MP3()
	{
		if (m_mpg123)
		{
			dlclose(m_mpg123);
		}
	}

	AudioFormat AudioFormat_MP3::format() const
	{
		return AudioFormat::MP3;
	}

	const Array<String>& AudioFormat_MP3::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"mp3" };

		return extensions;
	}

	bool AudioFormat_MP3::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 MPEG1_SIGN[] = { 0xFF, 0xFB };
		static constexpr uint8 MP3_SIGN[] = { 0x49, 0x44, 0x33 };

		return ::memcmp(bytes, MPEG1_SIGN, sizeof(MPEG1_SIGN))
			|| ::memcmp(bytes, MP3_SIGN, sizeof(MP3_SIGN));
	}

	Wave AudioFormat_MP3::decodeFromFile(const FilePath& path) const
	{
		BinaryReader reader(path);

		return decode(reader);
	}

	Wave AudioFormat_MP3::decode(IReader& reader) const
	{
		if (!m_libmpg123Available)
		{
			return Wave();
		}

		mpg123_handle* m = p_mpg123_new(nullptr, nullptr);

		if (!m)
		{
			return Wave();
		}

		p_mpg123_param(m, MPG123_RESYNC_LIMIT, -1, 0);

		if (p_mpg123_param(m, MPG123_FLAGS, MPG123_GAPLESS | MPG123_QUIET, 0) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return Wave();
		}

		if (p_mpg123_param(m, MPG123_INDEX_SIZE, -1, 0) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return Wave();
		}

		const long *rates = nullptr;

		size_t nrates = 0;

		p_mpg123_rates(&rates, &nrates);

		for (size_t i = 0; i < nrates; ++i)
		{
			if (p_mpg123_format(m, rates[i], MPG123_MONO | MPG123_STEREO, MPG123_ENC_16) != MPG123_OK)
			{
				p_mpg123_delete(m);
				return Wave();
			}
		}

		if (p_mpg123_replace_reader_handle(m, detail::Read_Callback, detail::Seek_Callback, detail::Cleanup_Callback) != MPG123_OK)
		{
			p_mpg123_close(m);
			p_mpg123_delete(m);
			return Wave();
		}

		if (!reader.isOpened())
		{
			return Wave();
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
			return Wave();
		}

		const long sSize = p_mpg123_length(m);

		p_mpg123_close(m);

		if (sSize <= 0)
		{
			p_mpg123_delete(m);
			return Wave();
		}

		if (p_mpg123_open_feed(m) != MPG123_OK)
		{
			p_mpg123_delete(m);
			return Wave();
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
					wave.setSamplingRate(static_cast<uint32>(rate));
				}

				if (outc + bytes > (wave.size() * sizeof(WaveSampleS16)))
				{
					return Wave();
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

# endif
