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

# include <Siv3D/ImageFormat/PPMDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr bool IsWhiteSpace(const uint8 ch) noexcept
		{
			return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
		}

		//valueを表現できる最小のバイト数
		static uint32 RequiredBytes(uint32 value)
		{
			uint32 i = 1;
			while ((1u << (i * 8u)) - 1u < value)
			{
				++i;
			}
			return i;
		};

		static void SkipComment(IReader& reader)
		{
			uint8 c;
			if (0 == reader.lookahead(&c, 1) || c != '#')
			{
				return;
			}

			while (1 == reader.read(&c, 1))
			{
				if (c == '\n')
				{
					if (reader.lookahead(&c, 1) == 0 || c != '#')
					{
						return;
					}
				}
			}
		}

		static bool SkipWhiteSpaces(s3d::IReader& reader)
		{
			uint8 c;
			if (0 == reader.lookahead(&c, 1) || !IsWhiteSpace(c))
			{
				return false;
			}

			while (1 == reader.read(&c, 1))
			{
				if (not IsWhiteSpace(c))
				{
					//空白以外の文字を読んだら一つ戻って帰る
					reader.setPos(reader.getPos() - 1);
					return true;
				}
			}

			//終端にたどり着いた
			return true;
		}

		//数字 ホワイトスペース を読む
		static uint32 ReadNum(IReader& reader)
		{
			uint32 num = 0;

			uint8 c;
			while (1 == reader.read(&c, 1))
			{
				if (IsWhiteSpace(c))
				{
					SkipWhiteSpaces(reader);
					break;
				}

				num = (num * 10) + (c - '0');
			}

			return num;
		}

		static Size ReadSize(IReader& reader)
		{
			SkipComment(reader);

			bool expectHeight = false;

			Size size(0, 0);

			uint8 c;
			while (1 == reader.read(&c, 1))
			{
				//読み込み終了
				if (expectHeight && IsWhiteSpace(c))
				{
					SkipWhiteSpaces(reader);
					break;
				}

				if (IsWhiteSpace(c))
				{
					//Whitespaceは連続する可能性がある
					SkipWhiteSpaces(reader);
					expectHeight = true;
					continue;
				}

				if (not expectHeight)
				{
					size.x = size.x * 10 + (c - '0');
				}
				else
				{
					size.y = size.y * 10 + (c - '0');
				}
			}

			return size;
		}

		static Image ReadP1(IReader& reader, const Size& size)
		{
			Image image(size);

			Size pos(0, 0);
			uint8 c;
			for (; 1 == reader.read(&c, 1);)
			{
				const uint8 bit = c - '0';
				if (c == '\n')
				{
					++pos.y;
					pos.x = 0;
					continue;
				}
				if (c == ' ')
				{
					continue;
				}

				image[pos] = bit == 0 ? Palette::Black : Palette::White;

				++pos.x;
			}

			return image;
		}

		static Image ReadP2(IReader& reader, const Size& size)
		{
			const uint32 maxValue = ReadNum(reader);

			Image image(size);

			Size pos(0, 0);
			uint8 c;
			uint32 color = 0u;

			while (1 == reader.read(&c, 1))
			{
				const uint8 bit = c - '0';
				if (c == '\n')
				{
					image[pos] = ColorF(static_cast<double>(color) / maxValue);
					++pos.y;
					pos.x = 0;
					color = 0;
					continue;
				}
				if (c == ' ')
				{
					image[pos] = ColorF(static_cast<double>(color) / maxValue);
					++pos.x;
					color = 0;
					continue;
				}

				color = color * 10 + bit;
			}

			return image;
		}

		static Image ReadP3(IReader& reader, const Size& size)
		{
			const uint32 maxValue = ReadNum(reader);

			Image image(size);

			uint8* data = image.dataAsUint8();
			const auto currentIndex = [&]() {return data - image.dataAsUint8(); };

			Size pos(0, 0);
			uint8 c;
			uint32 color = 0u;
			while (1 == reader.read(&c, 1))
			{
				const uint8 bit = c - '0';
				if (c == '\n')
				{
					*data = Color::ToUint8(static_cast<double>(color) / maxValue);
					color = 0;
					++data;
					if (currentIndex() % 4 == 3)
					{
						*data = 255u;
						++data;
						++pos.y;
						pos.x = 0;
					}

					continue;
				}
				if (c == ' ')
				{
					*data = Color::ToUint8(static_cast<double>(color) / maxValue);
					++data;
					color = 0;
					if (currentIndex() % 4 == 3)
					{
						*data = 255u;
						++data;
						++pos.x;
					}

					continue;
				}

				color = color * 10 + bit;
			}

			return image;
		}

		static Image ReadP4(IReader& reader, const Size& size)
		{
			Image image(size);

			const uint8 reminder = (image.width() % 8 == 0 ? 0 : 1);
			const uint32 bytesOfRow = static_cast<uint32>(image.width()) / 8 + reminder;

			Color* data = image.data();

			Size pos(0, 0);
			uint8 c;
			while (pos.y < image.height())
			{
				for (uint32 byte = 0; byte < bytesOfRow && 1 == reader.read(&c, 1); ++byte)
				{
					for (uint8 bit = 7; pos.x < image.width(); --bit)
					{
						const int currentBits = byte * 8 + (7u - bit);
						const uint8 flag = 1u << bit;

						if (image.width() <= currentBits)
						{
							break;
						}

						*data = (c & flag) != 0 ? Palette::White : Palette::Black;
						++data;
						++pos.x;

						//forの条件で bit>=0 とする代わり(unsignedなので)
						if (bit == 0u)
						{
							break;
						}
					}
				}

				++pos.y;
				pos.x = 0;
			}

			return image;
		}

		static Image ReadP5(IReader& reader, const Size& size)
		{
			const uint32 maxValue = ReadNum(reader);

			const uint32 byteSizeOfPixel = RequiredBytes(maxValue);

			if (byteSizeOfPixel != 1)
			{
				//LOG_ERROR(L"PNM形式では輝度の最大値は255までしか扱えません");
				return Image();
			}

			const int64 pixelDataBytes = size.x * size.y * byteSizeOfPixel;

			reader.setPos(reader.size() - pixelDataBytes);

			Image image(size);

			uint8* data = image.dataAsUint8();

			Size pos(0, 0);
			uint8 c;
			while (pos.y < image.height())
			{
				for (pos.x = 0; pos.x < image.width(); ++pos.x)
				{
					if (1 != reader.read(&c, 1))
					{
						return Image();
					}

					data[0] = data[1] = data[2] = Color::ToUint8(static_cast<double>(c) / maxValue);
					data[3] = 255u;
					data += 4;
				}

				++pos.y;
			}

			return image;
		}

		static Image ReadP6(IReader& reader, const Size& size)
		{
			const uint32 maxValue = ReadNum(reader);

			const uint32 byteSizeOfColor = RequiredBytes(maxValue);

			if (byteSizeOfColor != 1)
			{
				//LOG_ERROR(L"PNM形式では輝度の最大値は255までしか扱えません");
				return Image();
			}

			const int64 pixelDataBytes = size.x * size.y * byteSizeOfColor * 3;

			reader.setPos(reader.size() - pixelDataBytes);

			Image image(size);

			Color* data = image.data();

			Size pos(0, 0);
			uint8 cr, cg, cb;
			while (pos.y < image.height())
			{
				for (pos.x = 0; pos.x < image.width(); ++pos.x)
				{
					if (1 != reader.read(&cr, 1) || 1 != reader.read(&cg, 1) || 1 != reader.read(&cb, 1))
					{
						//LOG_ERROR(L"データ形式が不正です");
						return Image();
					}

					*data = ColorF(static_cast<double>(cr) / maxValue, static_cast<double>(cg) / maxValue, static_cast<double>(cb) / maxValue);
					++data;
				}

				++pos.y;
			}

			return image;
		}
	}

	//-----------------------------------------------
	//	Author (OpenSiv3D 実装会)
	//	- Kenta Masuda
	//-----------------------------------------------

	StringView PPMDecoder::name() const
	{
		return U"PPM"_sv;
	}

	ImageFormat PPMDecoder::imageFormat() const noexcept
	{
		return ImageFormat::PPM;
	}

	bool PPMDecoder::isHeader(const uint8(&)[16]) const
	{
		return false;
	}

	const Array<String>& PPMDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"ppm", U"pgm", U"pbm", U"pnm" };

		return extensions;
	}

	Optional<ImageInfo> PPMDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> PPMDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		bool inComment = false;
		bool expectHeight = false;

		Size size{ 0, 0 };

		uint8 c;
		
		// 最初の 3 バイトが種類 + 改行
		for (int64 offset = 3; (1 == reader.lookahead(&c, offset, 1)); ++offset)
		{
			if (inComment)
			{
				inComment = (c != '\n');
				continue;
			}
			
			if (c == '#')
			{
				inComment = true;
			}

			if ((c == ' ') || (c == '\t'))
			{
				expectHeight = true;
				continue;
			}

			// 読み込み終了
			if (expectHeight && (c == '\n'))
			{
				break;
			}

			if (not expectHeight)
			{
				size.x = (size.x * 10 + (c - '0'));
			}
			else
			{
				size.y = (size.y * 10 + (c - '0'));
			}
		}
		
		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8;

		return ImageInfo{ size, ImageFormat::PPM, pixelFormat, false };
	}

	Image PPMDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image PPMDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"PPMDecoder::decode()");

		uint8 type1, type2;

		if ((not reader.read(type1))
			|| (not reader.read(type2)))
		{
			return{};
		}

		const uint16 type = ((static_cast<uint16>(type1) << 8) + type2);

		// Line Feed
		{
			char linefeed[2];
			reader.lookahead(linefeed);
			
			if (linefeed[1] == 0x0a) // CRLF
			{
				reader.skip(2);
			}
			else // others
			{
				reader.skip(1);
			}
		}

		Image image;
		const Size size = detail::ReadSize(reader);

		switch (type)
		{
		case 0x5031: // P1 Portable bitmap ASCII
			image = detail::ReadP1(reader, size);
			break;
		case 0x5032: // P2 Portable graymap ASCII
			image = detail::ReadP2(reader, size);
			break;
		case 0x5033: // P3 Portable pixmap ASCII
			image = detail::ReadP3(reader, size);
			break;
		case 0x5034: // P4 Portable bitmap Binary
			image = detail::ReadP4(reader, size);
			break;
		case 0x5035: // P5 Portable graymap Binary
			image = detail::ReadP5(reader, size);
			break;
		case 0x5036: // P6 Portable pixmap Binary
			image = detail::ReadP6(reader, size);
			break;
		default:
			return{};
		}

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			size.x, size.y));

		return image;
	}
}
