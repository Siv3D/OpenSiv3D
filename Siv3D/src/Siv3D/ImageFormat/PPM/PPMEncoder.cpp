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

# include <Siv3D/ImageFormat/PPMEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	//-----------------------------------------------
	//	Author (OpenSiv3D 実装会)
	//	- Kenta Masuda
	//-----------------------------------------------

	namespace detail
	{
		static void WriteNumber(IWriter& writer, const uint8 n)
		{
			const std::string s = std::to_string(n);
			writer.write(s.data(), s.size());
		}

		static void WriteNumber(IWriter& writer, const int32 n)
		{
			const std::string s = std::to_string(n);
			writer.write(s.data(), s.size());
		}

		static bool WriteP1(const Image& image, IWriter& writer)
		{
			writer.write("P1\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
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

		static bool WriteP2(const Image& image, IWriter& writer)
		{
			writer.write("P2\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
			writer.write('\n');
			writer.write("255\n", 4);

			for (int y = 0; y < image.height(); ++y)
			{
				for (int x = 0; x + 1 < image.width(); ++x)
				{
					WriteNumber(writer, image[y][x].grayscale0_255());
					writer.write(' ');
				}

				if (1 <= image.width())
				{
					WriteNumber(writer, image[y][image.width() - 1].grayscale0_255());
					writer.write('\n');
				}
			}

			return true;
		}

		static bool WriteP3(const Image& image, IWriter& writer)
		{
			writer.write("P3\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
			writer.write('\n');
			writer.write("255\n", 4);

			for (int y = 0; y < image.height(); ++y)
			{
				for (int x = 0; x + 1 < image.width(); ++x)
				{
					const Color& c = image[y][x];
					WriteNumber(writer, c.r);
					writer.write(' ');
					WriteNumber(writer, c.g);
					writer.write(' ');
					WriteNumber(writer, c.b);
					writer.write(' ');
				}

				if (1 <= image.width())
				{
					const Color& c = image[y][image.width() - 1];
					WriteNumber(writer, c.r);
					writer.write(' ');
					WriteNumber(writer, c.g);
					writer.write(' ');
					WriteNumber(writer, c.b);
					writer.write('\n');
				}
			}

			return true;
		}

		static bool WriteP4(const Image& image, IWriter& writer)
		{
			writer.write("P4\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
			writer.write('\n');

			const auto binarize = [&](const Color& c)->bool {return 128000 <= 299 * c.r + 587 * c.g + 114 * c.b; };

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

				if (x < image.width())
				{
					uint8 c = 0;
					for (uint8 i = 128; x < image.width(); ++x, i >>= 1)
					{
						c += binarize(image[y][x]) ? i : 0;
					}

					writer.write(c);
				}
			}

			return true;
		}

		static bool WriteP5(const Image& image, IWriter& writer)
		{
			writer.write("P5\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
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

		static bool WriteP6(const Image& image, IWriter& writer)
		{
			writer.write("P6\n", 3);
			WriteNumber(writer, image.width());
			writer.write(' ');
			WriteNumber(writer, image.height());
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
	}

	StringView PPMEncoder::name() const
	{
		return U"PPM"_sv;
	}

	ImageFormat PPMEncoder::imageFormat() const noexcept
	{
		return ImageFormat::PPM;
	}

	const Array<String>& PPMEncoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"ppm", U"pgm", U"pbm", U"pnm" };

		return extensions;
	}

	bool PPMEncoder::save(const Image& image, const FilePathView path) const
	{
		return save(image, path, DefaultFormat);
	}

	bool PPMEncoder::save(const Image& image, const FilePathView path, const PPMType format) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer, format);
	}

	bool PPMEncoder::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, DefaultFormat);
	}

	bool PPMEncoder::encode(const Image& image, IWriter& writer, PPMType format) const
	{
		if (not writer.isOpen())
		{
			return false;
		}

		switch (format)
		{
		case PPMType::P1: // P1 Portable bitmap ASCII
			return detail::WriteP1(image, writer);
		case PPMType::P2: // P2 Portable graymap ASCII
			return detail::WriteP2(image, writer);
		case PPMType::P3: // P3 Portable pixmap ASCII
			return detail::WriteP3(image, writer);
		case PPMType::P4: // P4 Portable bitmap Binary
			return detail::WriteP4(image, writer);
		case PPMType::P5: // P5 Portable graymap Binary
			return detail::WriteP5(image, writer);
		case PPMType::P6: // P6 Portable pixmap Binary
			return detail::WriteP6(image, writer);
		default:
			return false;
		}
	}

	Blob PPMEncoder::encode(const Image& image) const
	{
		return encode(image, DefaultFormat);
	}

	Blob PPMEncoder::encode(const Image& image, PPMType format) const
	{
		MemoryWriter writer;
		
		if (not encode(image, writer, format))
		{
			return{};
		}

		return writer.retrieve();
	}
}
