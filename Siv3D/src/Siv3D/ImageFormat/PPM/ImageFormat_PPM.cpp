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
// s3d::ImageFormat_PPM is originally created by Kenta Masuda (HAMSTRO)
//-----------------------------------------------

# include <Siv3D/String.hpp>
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ByteArrayViewAdapter.hpp>
# include "ImageFormat_PPM.hpp"

namespace
{
	using namespace s3d;

	inline constexpr bool IsWhiteSpace(const uint8 ch) noexcept
	{
		return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
	}

	//valueを表現できる最小のバイト数
	uint32 requiredBytes(uint32 value)
	{
		uint32 i = 1;
		while ((1u << (i * 8u)) - 1u < value)
		{
			++i;
		}
		return i;
	};

	void skipComment(s3d::IReader& reader)
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

	bool skipWhiteSpaces(s3d::IReader& reader)
	{
		uint8 c;
		if (0 == reader.lookahead(&c, 1) || !IsWhiteSpace(c))
		{
			return false;
		}

		while (1 == reader.read(&c, 1))
		{
			if (!IsWhiteSpace(c))
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
	uint32 readNum(IReader& reader)
	{
		uint32 num = 0;

		uint8 c;
		while (1 == reader.read(&c, 1))
		{
			if (IsWhiteSpace(c))
			{
				skipWhiteSpaces(reader);
				break;
			}

			num = (num * 10) + (c - '0');
		}

		return num;
	}

	s3d::Size readSize(s3d::IReader& reader)
	{
		skipComment(reader);

		bool expectHeight = false;

		s3d::Size size(0, 0);

		s3d::uint8 c;
		while (1 == reader.read(&c, 1))
		{
			//読み込み終了
			if (expectHeight && IsWhiteSpace(c))
			{
				skipWhiteSpaces(reader);
				break;
			}

			if (IsWhiteSpace(c))
			{
				//Whitespaceは連続する可能性がある
				skipWhiteSpaces(reader);
				expectHeight = true;
				continue;
			}

			if (!expectHeight)
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
}

namespace s3d
{
	ImageFormat ImageFormat_PPM::format() const
	{
		return ImageFormat::PPM;
	}

	const Array<String>& ImageFormat_PPM::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"ppm", U"pgm", U"pbm", U"pnm" };

		return extensions;
	}

	bool ImageFormat_PPM::isHeader(const uint8(&)[16]) const
	{
		return false;
	}

	Size ImageFormat_PPM::getSize(const IReader& reader) const
	{
		bool inComment = false;
		bool expectHeight = false;

		Size size(0, 0);

		uint8 c;
		//最初の3バイトが種類＋改行
		for (int64 offset = 3; 1 == reader.lookahead(&c, offset, 1); ++offset)
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

			if (c == ' ' || c == '\t')
			{
				expectHeight = true;
				continue;
			}

			//読み込み終了
			if (expectHeight && c == '\n')
			{
				break;
			}

			if (!expectHeight)
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

	Image readP1(IReader& reader, const Size& size)
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

	Image readP2(IReader& reader, const Size& size)
	{
		const uint32 maxValue = readNum(reader);

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

	Image readP3(IReader& reader, const Size& size)
	{
		const uint32 maxValue = readNum(reader);

		Image image(size);

		uint8* data = image.dataAsUint8();
		const auto currentIndex = [&]() {return data - image.dataAsUint8(); };
		const auto toInteger = [&](double r)->uint8 {return r >= 1.0 ? 255 : r <= 0.0 ? 0 : static_cast<uint8>(r * 255.0 + 0.5); };

		Size pos(0, 0);
		uint8 c;
		uint32 color = 0u;
		while (1 == reader.read(&c, 1))
		{
			const uint8 bit = c - '0';
			if (c == '\n')
			{
				*data = toInteger(static_cast<double>(color) / maxValue);
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
				*data = toInteger(static_cast<double>(color) / maxValue);
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

	Image readP4(IReader& reader, const Size& size)
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

	Image readP5(IReader& reader, const Size& size)
	{
		const uint32 maxValue = readNum(reader);

		const uint32 byteSizeOfPixel = requiredBytes(maxValue);

		if (byteSizeOfPixel != 1)
		{
			//LOG_ERROR(L"PNM形式では輝度の最大値は255までしか扱えません");
			return Image();
		}

		Image image(size);

		uint8* data = image.dataAsUint8();
		const auto toInteger = [&](double r)->uint8 {return r >= 1.0 ? 255 : r <= 0.0 ? 0 : static_cast<uint8>(r * 255.0 + 0.5); };

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

				data[0] = data[1] = data[2] = toInteger(static_cast<double>(c) / maxValue);
				data[3] = 255u;
				data += 4;
			}

			++pos.y;
		}

		return image;
	}

	Image readP6(IReader& reader, const Size& size)
	{
		const uint32 maxValue = readNum(reader);

		const uint32 byteSizeOfPixel = requiredBytes(maxValue);

		if (byteSizeOfPixel != 1)
		{
			//LOG_ERROR(L"PNM形式では輝度の最大値は255までしか扱えません");
			return Image();
		}

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

	bool writeP1(const Image& image, IWriter& writer)
	{
		writer.write("P1\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');

		for (int y = 0; y < image.height(); ++y)
		{
			for (int x = 0; x + 1 < image.width(); ++x)
			{
				writer.write(image[y][x].grayscale0_255() < 128 ? '0' : '1');
				writer.write(' ');
			}

			if (1 <= image.width())
			{
				writer.write(image[y][image.width() - 1].grayscale0_255() < 128 ? '0' : '1');
				writer.write('\n');
			}
		}

		return true;
	}

	bool writeP2(const Image& image, IWriter& writer)
	{
		writer.write("P2\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');
		writer.write("255\n", 4);

		for (int y = 0; y < image.height(); ++y)
		{
			for (int x = 0; x + 1 < image.width(); ++x)
			{
				writer.write(std::to_string(image[y][x].grayscale0_255()));
				writer.write(' ');
			}

			if (1 <= image.width())
			{
				writer.write(std::to_string(image[y][image.width() - 1].grayscale0_255()));
				writer.write('\n');
			}
		}

		return true;
	}

	bool writeP3(const Image& image, IWriter& writer)
	{
		writer.write("P3\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');
		writer.write("255\n", 4);

		for (int y = 0; y < image.height(); ++y)
		{
			for (int x = 0; x + 1 < image.width(); ++x)
			{
				const Color& c = image[y][x];
				writer.write(std::to_string(c.r));
				writer.write(' ');
				writer.write(std::to_string(c.g));
				writer.write(' ');
				writer.write(std::to_string(c.b));
				writer.write(' ');
			}

			if (1 <= image.width())
			{
				const Color& c = image[y][image.width() - 1];
				writer.write(std::to_string(c.r));
				writer.write(' ');
				writer.write(std::to_string(c.g));
				writer.write(' ');
				writer.write(std::to_string(c.b));
				writer.write('\n');
			}
		}

		return true;
	}

	bool writeP4(const Image& image, IWriter& writer)
	{
		writer.write("P4\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');

		const auto binarize = [&](const Color& c)->bool {return 128000 <= 299*c.r + 587*c.g + 114*c.b; };

		for (int32 y = 0; y < image.height(); ++y)
		{
			int32 x = 0;
			for (; x + 7 < image.width(); x += 8)
			{
				const uint8 c =
					(binarize(image[y][x]) ? 128 : 0) +
					(binarize(image[y][x + 1]) ? 64 : 0) +
					(binarize(image[y][x + 2]) ? 32 : 0) +
					(binarize(image[y][x + 3]) ? 16 : 0) +
					(binarize(image[y][x + 4]) ? 8 : 0) +
					(binarize(image[y][x + 5]) ? 4 : 0) +
					(binarize(image[y][x + 6]) ? 2 : 0) +
					(binarize(image[y][x + 7]) ? 1 : 0);

				writer.write(c);
			}

			uint8 c = 0;
			for (uint8 i = 128; x < image.width(); ++x, i >>= 1)
			{
				c += binarize(image[y][x]) ? i : 0;
			}

			if (1 <= image.width())
			{
				writer.write(c);
			}
		}

		return true;
	}

	bool writeP5(const Image& image, IWriter& writer)
	{
		writer.write("P5\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');
		writer.write("255\n", 4);

		for (int y = 0; y < image.height(); ++y)
		{
			for (int x = 0; x + 1 < image.width(); ++x)
			{
				writer.write(image[y][x].grayscale0_255());
			}

			if (1 <= image.width())
			{
				writer.write(image[y][image.width() - 1].grayscale0_255());
			}
		}

		return true;
	}

	bool writeP6(const Image& image, IWriter& writer)
	{
		writer.write("P6\n", 3);
		writer.write(std::to_string(image.width()));
		writer.write(' ');
		writer.write(std::to_string(image.height()));
		writer.write('\n');
		writer.write("255\n", 4);

		for (int y = 0; y < image.height(); ++y)
		{
			for (int x = 0; x + 1 < image.width(); ++x)
			{
				const Color& c = image[y][x];
				writer.write(static_cast<uint8>(c.r));
				writer.write(static_cast<uint8>(c.g));
				writer.write(static_cast<uint8>(c.b));
			}

			if (1 <= image.width())
			{
				const Color& c = image[y][image.width() - 1];
				writer.write(static_cast<uint8>(c.r));
				writer.write(static_cast<uint8>(c.g));
				writer.write(static_cast<uint8>(c.b));
			}
		}

		return true;
	}

	Image ImageFormat_PPM::decode(IReader& reader) const
	{
		Image image;

		uint8 type1, type2;
		if (!reader.read(type1) || !reader.read(type2))
		{
			return image;
		}

		const uint16 type = (static_cast<uint16>(type1) << 8) + type2;

		//Line Feed
		reader.skip(1);

		const Size size = readSize(reader);

		switch (type)
		{
		case 0x5031://P1 Portable bitmap ASCII
			return readP1(reader, size);
		case 0x5032://P2 Portable graymap ASCII
			return readP2(reader, size);
		case 0x5033://P3 Portable pixmap ASCII
			return readP3(reader, size);
		case 0x5034://P4 Portable bitmap Binary
			return readP4(reader, size);
		case 0x5035://P5 Portable graymap Binary
			return readP5(reader, size);
		case 0x5036://P6 Portable pixmap Binary
			return readP6(reader, size);
		default:
			return image;
		}
	}

	bool ImageFormat_PPM::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, PPMType::P6);
	}

	bool ImageFormat_PPM::encode(const Image & image, IWriter & writer, PPMType format) const
	{
		if (!writer.isOpened())
		{
			return false;
		}

		switch (format)
		{
		case PPMType::P1://P1 Portable bitmap ASCII
			return writeP1(image, writer);
		case PPMType::P2://P2 Portable graymap ASCII
			return writeP2(image, writer);
		case PPMType::P3://P3 Portable pixmap ASCII
			return writeP3(image, writer);
		case PPMType::P4://P4 Portable bitmap Binary
			return writeP4(image, writer);
		case PPMType::P5://P5 Portable graymap Binary
			return writeP5(image, writer);
		case PPMType::P6://P6 Portable pixmap Binary
			return writeP6(image, writer);
		default:
			return false;
		}
	}

	bool ImageFormat_PPM::save(const Image& image, const FilePath& path) const
	{
		return save(image, path, PPMType::P6);
	}

	bool ImageFormat_PPM::save(const Image & image, const FilePath & path, PPMType format) const
	{
		BinaryWriter writer(path);

		return encode(image, writer, format);
	}
}
