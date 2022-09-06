//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <sstream>
# include <Siv3D/QR.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/TextWriter.hpp>
# include <ThirdParty/qr-code-generator-library/qrcodegen.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Grid<bool> ToGrid(const qrcodegen::QrCode& qr)
		{
			const int32 size = qr.getSize();

			Grid<bool> grid(size, size);

			for (int32 y = 0; y < size; ++y)
			{
				for (int32 x = 0; x < size; ++x)
				{
					grid[y][x] = qr.getModule(x, y);
				}
			}

			return grid;
		}

		[[nodiscard]]
		inline constexpr qrcodegen::QrCode::Ecc ToEcc(const QRErrorCorrection ec)
		{
			return qrcodegen::QrCode::Ecc{ FromEnum(ec) };
		}

		static constexpr bool alnumTable[128] = {
			false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
			false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
			true, false, false, false, true, true, false, false, false, false, true, true, false, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false,
			false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false,
			false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
			false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
		};

		[[nodiscard]]
		inline constexpr bool IsAlnumQR(const char8 ch) noexcept
		{
			return (static_cast<uint8>(ch) < 128) && alnumTable[static_cast<uint8>(ch)];
		}

		static void FillCell(Color* pOrigin, const int32 cellSize, const size_t imageWidth)
		{
			Color* pLine = pOrigin;

			for (int32 y = 0; y < cellSize; ++y)
			{
				Color* pDst = pLine;

				for (int32 x = 0; x < cellSize; ++x)
				{
					(*pDst++).setRGB(0);
				}

				pLine += imageWidth;
			}
		}

		[[nodiscard]]
		std::string MakeSVGSource(const Grid<bool>& qr, const size_t borderCells)
		{
			std::ostringstream ss;
			ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			ss << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
			ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
			ss << (qr.width() + borderCells * 2) << " " << (qr.height() + borderCells * 2) << "\" stroke=\"none\">\n";
			ss << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
			ss << "\t<path d=\"";

			for (size_t y = 0; y < qr.height(); ++y)
			{
				for (size_t x = 0; x < qr.width(); ++x)
				{
					if (qr[y][x] == false)
					{
						continue;
					}

					if (x != 0 || y != 0)
					{
						ss << " ";
					}

					ss << "M" << (x + borderCells) << "," << (y + borderCells) << "h1v1h-1z";
				}
			}

			ss << "\" fill=\"#000000\"/>\n";
			ss << "</svg>\n";

			return ss.str();
		}
	}

	namespace QR
	{
		Grid<bool> EncodeNumber(const StringView s, const QRErrorCorrection ec, const int32 minVersion)
		{
			if (not std::all_of(s.begin(), s.end(), IsDigit))
			{
				return{};
			}

			try
			{
				const std::vector<qrcodegen::QrSegment> segs{ qrcodegen::QrSegment::makeNumeric(s.toUTF8().c_str()) };
				const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeSegments(segs, detail::ToEcc(ec), minVersion);
				return detail::ToGrid(qr);
			}
			catch (const std::exception&)
			{
				return{};
			}
		}

		Grid<bool> EncodeAlnum(const StringView s, const QRErrorCorrection ec, const int32 minVersion)
		{
			const std::string utf8 = s.toUTF8();

			if (not std::all_of(utf8.begin(), utf8.end(), detail::IsAlnumQR))
			{
				return{};
			}

			try
			{
				const std::vector<qrcodegen::QrSegment> segs{ qrcodegen::QrSegment::makeAlphanumeric(utf8.c_str()) };
				const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeSegments(segs, detail::ToEcc(ec), minVersion);
				return detail::ToGrid(qr);
			}
			catch (const std::exception&)
			{
				return{};
			}
		}

		Grid<bool> EncodeText(const StringView s, const QRErrorCorrection ec, const int32 minVersion)
		{
			try
			{
				const std::vector<qrcodegen::QrSegment> segs = qrcodegen::QrSegment::makeSegments(s.toUTF8().c_str());
				const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeSegments(segs, detail::ToEcc(ec), minVersion);
				return detail::ToGrid(qr);
			}
			catch (const std::exception&)
			{
				return{};
			}
		}

		Grid<bool> EncodeBinary(const void* data, const size_t size, const QRErrorCorrection ec, const int32 minVersion)
		{
			const std::vector<std::uint8_t> binary(static_cast<const std::uint8_t*>(data)
				, static_cast<const std::uint8_t*>(data) + size);

			try
			{
				const std::vector<qrcodegen::QrSegment> segs{ qrcodegen::QrSegment::makeBytes(binary) };
				const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeSegments(segs, detail::ToEcc(ec), minVersion);
				return detail::ToGrid(qr);
			}
			catch (const std::exception&)
			{
				return{};
			}
		}

		Image MakeImage(const Grid<bool>& qr, const int32 cellSize, const size_t borderCells)
		{
			const size_t cellWidth = (qr.width() + (borderCells * 2));
			const size_t cellHeight = (qr.height() + (borderCells * 2));
			const size_t imageWidth = (cellWidth * cellSize);
			const size_t imageHeight = (cellHeight * cellSize);

			if ((imageWidth > Image::MaxWidth)
				|| (imageHeight > Image::MaxHeight))
			{
				return{};
			}

			Image image(imageWidth, imageHeight, Color(255));

			for (size_t cx = 0; cx < cellWidth; ++cx)
			{
				if ((cx < borderCells) || ((qr.width() + borderCells) <= cx))
				{
					continue;
				}

				for (size_t cy = 0; cy < cellHeight; ++cy)
				{
					if ((cy < borderCells) || ((qr.height() + borderCells) <= cy))
					{
						continue;
					}

					if (qr[cy - borderCells][cx - borderCells])
					{
						detail::FillCell(&image[cy * cellSize][cx * cellSize], cellSize, imageWidth);
					}
				}
			}

			return image;
		}

		SVG MakeSVG(const Grid<bool>& qr, size_t borderCells)
		{
			if (not qr)
			{
				return{};
			}

			return SVG::Parse(detail::MakeSVGSource(qr, borderCells));
		}

		bool SaveSVG(const FilePathView path, const Grid<bool>& qr, const size_t borderCells)
		{
			if (not qr)
			{
				return false;
			}

			TextWriter writer{ path };

			if (not writer)
			{
				return false;
			}

			writer.writeUTF8(detail::MakeSVGSource(qr, borderCells));

			return true;
		}
	}
}
