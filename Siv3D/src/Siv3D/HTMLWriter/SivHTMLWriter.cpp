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
// s3d::HTMLWriter is originally created by Kenta Masuda (HAMSTRO)
//-----------------------------------------------

# include <Siv3D/HTMLWriter.hpp>
# include <Siv3D/Base64.hpp>
# include <Siv3D/Image.hpp>
# include "HTMLWriterDetail.hpp"

namespace s3d
{
	namespace detail
	{
		static String HTMLEscape(const StringView view)
		{
			String new_string;

			new_string.reserve(view.length());

			for (const auto ch : view)
			{
				switch (ch)
				{
				case U'\n':
					new_string.append(U"<br>"_sv);
					break;
				case U'\r':
					break;
				case U'\"':
					new_string.append(U"&quot;"_sv);
					break;
				case U'&':
					new_string.append(U"&amp;"_sv);
					break;
				case U'\'':
					new_string.append(U"&apos;"_sv);
					break;
				case U'<':
					new_string.append(U"&lt;"_sv);
					break;
				case U'>':
					new_string.append(U"&gt;"_sv);
					break;
				default:
					new_string.push_back(ch);
					break;
				}
			}

			return new_string;
		}

		static String GetColorCode(const Color& color)
		{
			return U"#" + color.toHex();
		}
	}

	String HTMLWriter::DefaultStyle()
	{
		return String(
UR"(body{
  margin: 20px 40px;
}
table{
  border-collapse: collapse;
}
tr:nth-child(even){
  background: #f6f8fa;
}
th,td{
  padding: 10px;
  border: 1px solid #dfe2e5;
})");
	}

	HTMLWriter::HTMLWriter()
		: pImpl{ std::make_shared<HTMLWriterDetail>() } {}

	HTMLWriter::HTMLWriter(const FilePathView path, const StringView title, const StringView styleSheet)
		: HTMLWriter{}
	{
		open(path, title, styleSheet);
	}

	HTMLWriter::~HTMLWriter()
	{
		// do nothing
	}

	bool HTMLWriter::open(const FilePathView path, const StringView title, const StringView styleSheet)
	{
		return pImpl->open(path, title, styleSheet);
	}

	void HTMLWriter::close()
	{
		pImpl->close();
	}

	bool HTMLWriter::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	HTMLWriter::operator bool() const noexcept
	{
		return isOpen();
	}

	void HTMLWriter::writeRaw(const StringView view)
	{
		pImpl->writeRaw(view);
	}

	void HTMLWriter::writeParagraph(const StringView view, const Color& color)
	{
		pImpl->writeElementRaw(detail::HTMLEscape(view), U"p", { { U"color", detail::GetColorCode(color) } });
	}

	void HTMLWriter::writeHeader(const StringView view, int32 level)
	{
		pImpl->writeElementRaw(detail::HTMLEscape(view), Format(U'h', Clamp(level, 1, 6)));
	}

	void HTMLWriter::writeList(const Array<String>& items)
	{
		pImpl->writeRaw(U"<ul>\n");
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), U"li");
			}
		}
		pImpl->writeRaw(U"</ul>\n");
	}

	void HTMLWriter::writeOrderedList(const Array<String>& items)
	{
		pImpl->writeRaw(U"<ol>\n");
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), U"li");
			}
		}
		pImpl->writeRaw(U"</ol>\n");
	}

	void HTMLWriter::writeTable(const Grid<String>& items, const HasHeader hasHeader)
	{
		pImpl->writeRaw(U"<table>\n");
		{
			if (items.isEmpty())
			{
				return pImpl->writeRaw(U"</table>\n");
			}

			if (hasHeader)
			{
				pImpl->writeRaw(U"<tr>\n");
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[0][x]), U"th");
					}
				}
				pImpl->writeRaw(U"</tr>\n");
			}

			for (size_t y = hasHeader.getBool(); y < items.height(); ++y)
			{
				pImpl->writeRaw(U"<tr>\n");
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[y][x]), U"td");
					}
				}
				pImpl->writeRaw(U"</tr>\n");
			}
		}
		pImpl->writeRaw(U"</table>\n");
	}

	void HTMLWriter::writeLine(int32 thickness, const Color& color)
	{
		pImpl->writeRaw(Format(U"<hr style=\"height:", thickness, U"px; background-color:", detail::GetColorCode(color), U"; border: 0;\">\n"));
	}

	void HTMLWriter::writeImage(const Image& image, const Optional<Size>& size)
	{
		pImpl->writeRaw(U"<img src=\"data:image/png;base64,");

		const Blob blob = image.encode(ImageFormat::PNG);

		pImpl->writeRaw(Base64::Encode(blob.data(), blob.size()));

		const Size s = size.value_or(image.size());

		pImpl->writeRaw(U"\" width=\"" + Format(s.x) + U"\" height=\"" + Format(s.y) + U"\">\n");
	}

	void HTMLWriter::writeImage(const FilePathView url, const Optional<Size>& size)
	{
		pImpl->writeRaw(U"<img src=\"" + url);

		if (size)
		{
			pImpl->writeRaw(U"\" width=\"" + Format(size->x) + U"\" height=\"" + Format(size->y) + U"\">\n");
		}
		else
		{
			pImpl->writeRaw(U"\">\n");
		}
	}

	const FilePath& HTMLWriter::path() const
	{
		return pImpl->path();
	}
}
