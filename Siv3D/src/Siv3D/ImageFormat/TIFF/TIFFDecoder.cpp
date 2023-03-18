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

# include <Siv3D/ImageFormat/TIFFDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libtiff/tiffio.h>
# else
#	include <tiffio.h>
# endif

namespace s3d
{
	namespace detail
	{
		struct TiffTagEntry
		{
			uint8 tag[2];
			uint8 type[2];
			uint8 count[4];
			uint8 offset[4];
		};

		class TiffStream
		{
		public:

			explicit TiffStream(IReader& reader)
				: m_handle(this)
				, m_streamLength(reader.size())
				, m_pReader(&reader)
			{
				m_tiff = TIFFClientOpen("",
					"r",
					m_handle,
					read,
					write,
					seek,
					close,
					size,
					map,
					unmap);
			}

			~TiffStream()
			{
				if (m_tiff)
				{
					TIFFClose(m_tiff);
				}
			}

			TIFF* getHandle() const
			{
				return m_tiff;
			}

		private:

			TIFF* m_tiff = nullptr;

			thandle_t m_handle = nullptr;

			int64 m_streamLength = 0;

			IReader* m_pReader = nullptr;

			static tsize_t read(thandle_t fd, tdata_t buf, tsize_t size)
			{
				TiffStream* ts = static_cast<TiffStream*>(fd);

				if (IReader* reader = ts->m_pReader)
				{
					const int64 remain = reader->size() - reader->getPos();
					const int64 actual = remain < size ? remain : size;
					return reader->read(buf, actual);
				}
				else
				{
					return 0;
				}
			}

			static tsize_t write(thandle_t, tdata_t, tsize_t)
			{
				return 0;
			}

			static toff_t seek(thandle_t fd, toff_t offset, int origin)
			{
				TiffStream* ts = static_cast<TiffStream*>(fd);

				if (IReader* reader = ts->m_pReader)
				{
					const int64 start = (origin == std::ios::beg) ? 0 :
						(origin == std::ios::cur) ? reader->getPos() : reader->size();

					if (reader->setPos(start + offset))
					{
						return reader->getPos();
					}
					else
					{
						return toff_t(-1);
					}
				}
				else
				{
					return toff_t(-1);
				}
			}

			static toff_t size(thandle_t fd)
			{
				const TiffStream* ts = static_cast<TiffStream*>(fd);

				return ts->m_streamLength;
			}

			static int close(thandle_t fd)
			{
				TiffStream* ts = static_cast<TiffStream*>(fd);

				ts->m_streamLength = 0;

				if (ts->m_pReader)
				{
					ts->m_pReader = nullptr;
					return 0;
				}
				else
				{
					return -1;
				}
			}

			static int map(thandle_t, tdata_t*, toff_t*)
			{
				return 0;
			}

			static void unmap(thandle_t, void*, toff_t)
			{
				return;
			}
		};
	}

	StringView TIFFDecoder::name() const
	{
		return U"TIFF"_sv;
	}

	ImageFormat TIFFDecoder::imageFormat() const noexcept
	{
		return ImageFormat::TIFF;
	}

	bool TIFFDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 TIFF_SIGN0[] = { 0x49, 0x49, 0x2A, 0x00 };
		static constexpr uint8 TIFF_SIGN1[] = { 0x4D, 0x4D, 0x00, 0x2A };

		return (std::memcmp(bytes, TIFF_SIGN0, sizeof(TIFF_SIGN0)) == 0)
			|| (std::memcmp(bytes, TIFF_SIGN1, sizeof(TIFF_SIGN1)) == 0);
	}

	const Array<String>& TIFFDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"tif", U"tiff" };

		return extensions;
	}

	Optional<ImageInfo> TIFFDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> TIFFDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		uint16 byteOrder;

		if (not reader.lookahead(byteOrder))
		{
			return none;
		}

		const bool intel = (byteOrder == 0x4949u);

		uint8 num_tags[2];

		if (reader.lookahead(&num_tags, 8, sizeof(num_tags)) != sizeof(num_tags))
		{
			return none;
		}

		uint32 tagCount = intel ?
			(num_tags[1] << 8) + num_tags[0] :
			(num_tags[0] << 8) + num_tags[1];

		int width = 0, height = 0;

		for (uint32 i = 0; i < tagCount; ++i)
		{
			detail::TiffTagEntry entry;

			if (reader.lookahead(&entry, 10 + i * sizeof(entry), sizeof(entry)) != sizeof(entry))
			{
				return none;
			}

			const uint16 tag = intel ?
				(entry.tag[1] << 8) + entry.tag[0] :
				(entry.tag[0] << 8) + entry.tag[1];

			if (tag == 256)
			{
				width = intel ?
					(entry.offset[3] << 24) + (entry.offset[2] << 16) + (entry.offset[1] << 8) + (entry.offset[0]) :
					(entry.offset[2] << 24) + (entry.offset[3] << 16) + (entry.offset[0] << 8) + (entry.offset[1]);
			}
			else if (tag == 257)
			{
				height = intel ?
					(entry.offset[3] << 24) + (entry.offset[2] << 16) + (entry.offset[1] << 8) + (entry.offset[0]) :
					(entry.offset[2] << 24) + (entry.offset[3] << 16) + (entry.offset[0] << 8) + (entry.offset[1]);
			}
		}

		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8A8;
		const Size size{ width, height };

		return ImageInfo{ size, ImageFormat::GIF, pixelFormat, false };
	}

	Image TIFFDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image TIFFDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"TIFFDecoder::decode()");

		detail::TiffStream tiffStream{ reader };

		TIFF* tiff = tiffStream.getHandle();

		if (not tiff)
		{
			return{};
		}

		uint32 width = 0, height = 0, type = 0, samplesPerSample = 0;
		TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width);
		TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height);
		TIFFGetField(tiff, TIFFTAG_PLANARCONFIG, &type);
		TIFFGetField(tiff, TIFFTAG_SAMPLESPERPIXEL, &samplesPerSample);

		//if ((not InRange<int32>(width, 1, Image::MaxWidth))
		//	|| (not InRange<int32>(height, 1, Image::MaxHeight)))
		//{
		//	return{};
		//}

		if ((width == 0) || (height == 0))
		{
			return{};
		}

		Image image(width, height);
		const size_t scanlineSize = TIFFScanlineSize(tiff);

		//LOG_TEST(width, L"x", height, L" sl:", scanlineSize, L" type:", type, L" samplesPerSample:", samplesPerSample);

		Color* pDst = image[0];

		if (type == 1)
		{
			uint8* const buf = static_cast<uint8*>(_TIFFmalloc(scanlineSize));

			if (samplesPerSample == 3)
			{
				for (uint32 y = 0; y < height; ++y)
				{
					TIFFReadScanline(tiff, buf, y);

					const uint8* pixel = buf;

					for (uint32 x = 0; x < width; ++x)
					{
						const uint32 r = *pixel++;
						const uint32 g = *pixel++;
						const uint32 b = *pixel++;
						(pDst++)->set(r, g, b);
					}
				}
			}
			else if (samplesPerSample == 4)
			{
				for (uint32 y = 0; y < height; ++y)
				{
					TIFFReadScanline(tiff, buf, y);

					const uint8* pixel = buf;

					for (uint32 x = 0; x < width; ++x)
					{
						const uint32 r = *pixel++;
						const uint32 g = *pixel++;
						const uint32 b = *pixel++;
						const uint32 a = *pixel++;
						(pDst++)->set(r, g, b, a);
					}
				}
			}

			_TIFFfree(buf);
		}
		else if (type == 2)
		{
			if (samplesPerSample == 3)
			{
				uint8* const bufR = static_cast<uint8*>(_TIFFmalloc(scanlineSize * 3));
				uint8* const bufG = bufR + scanlineSize;
				uint8* const bufB = bufR + scanlineSize * 2;

				for (uint32 y = 0; y < height; ++y)
				{
					TIFFReadScanline(tiff, bufR, y, 0);
					TIFFReadScanline(tiff, bufG, y, 1);
					TIFFReadScanline(tiff, bufB, y, 2);

					for (uint32 x = 0; x < width; ++x)
					{
						(pDst++)->set(bufR[x], bufG[x], bufB[x]);
					}
				}

				_TIFFfree(bufR);
			}
			else if (samplesPerSample == 4)
			{
				uint8* const bufR = static_cast<uint8*>(_TIFFmalloc(scanlineSize * 4));
				uint8* const bufG = bufR + scanlineSize;
				uint8* const bufB = bufR + scanlineSize * 2;
				uint8* const bufA = bufR + scanlineSize * 3;

				for (uint32 y = 0; y < height; ++y)
				{
					TIFFReadScanline(tiff, bufR, y, 0);
					TIFFReadScanline(tiff, bufG, y, 1);
					TIFFReadScanline(tiff, bufB, y, 2);
					TIFFReadScanline(tiff, bufA, y, 3);

					for (uint32 x = 0; x < width; ++x)
					{
						(pDst++)->set(bufR[x], bufG[x], bufB[x], bufA[x]);
					}
				}

				_TIFFfree(bufR);
			}
		}

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
