//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/HTMLWriter.hpp>
# include <Siv3D/Base64.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include "CHTMLWriter.hpp"

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
				case L'\n':
					new_string.append(S3DSTR("<br>"), 4);
					break;
				case L'\r':
					break;
				case L'\"':
					new_string.append(S3DSTR("&quot;"), 6);
					break;
				case L'&':
					new_string.append(S3DSTR("&amp;"), 5);
					break;
				case L'\'':
					new_string.append(S3DSTR("&apos;"), 6);
					break;
				case L'<':
					new_string.append(S3DSTR("&lt;"), 4);
					break;
				case L'>':
					new_string.append(S3DSTR("&gt;"), 4);
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
			return S3DSTR("#") + color.toHex();
		}
	}

	HTMLWriter::HTMLWriter()
		: pImpl(std::make_shared<CHTMLWriter>())
	{

	}

	HTMLWriter::~HTMLWriter()
	{

	}

	bool HTMLWriter::open(const FilePath& path, const String& title, const StringView styleSheet)
	{
		return pImpl->open(path, title, styleSheet);
	}

	void HTMLWriter::close()
	{
		pImpl->close();
	}

	bool HTMLWriter::isOpened() const
	{
		return pImpl->isOpened();
	}

	void HTMLWriter::writeRaw(const StringView view)
	{
		pImpl->writeRaw(view);
	}

	void HTMLWriter::writeParagraph(const StringView view, const Color& color)
	{
		pImpl->writeElementRaw(detail::HTMLEscape(view), S3DSTR("p"), { { S3DSTR("color"), detail::GetColorCode(color) } });
	}

	void HTMLWriter::writeHeader(const StringView view, int32 level)
	{
		pImpl->writeElementRaw(detail::HTMLEscape(view), Format(L'h', Clamp(level, 1, 6)));
	}

	void HTMLWriter::writeList(const Array<String>& items)
	{
		pImpl->writeRaw(S3DSTR("<ul>\n"));
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), S3DSTR("li"));
			}
		}
		pImpl->writeRaw(S3DSTR("</ul>\n"));
	}

	void HTMLWriter::writeOrderedList(const Array<String>& items)
	{
		pImpl->writeRaw(S3DSTR("<ol>\n"));
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), S3DSTR("li"));
			}
		}
		pImpl->writeRaw(S3DSTR("</ol>\n"));
	}

	void HTMLWriter::writeTable(const Grid<String>& items, const bool hasHeader)
	{
		pImpl->writeRaw(S3DSTR("<table>\n"));
		{
			if (items.isEmpty())
			{
				return pImpl->writeRaw(S3DSTR("</table>\n"));
			}

			if (hasHeader)
			{
				pImpl->writeRaw(S3DSTR("<tr>\n"));
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[0][x]), S3DSTR("th"));
					}
				}
				pImpl->writeRaw(S3DSTR("</tr>\n"));
			}

			for (size_t y = hasHeader; y < items.height(); ++y)
			{
				pImpl->writeRaw(S3DSTR("<tr>\n"));
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[y][x]), S3DSTR("td"));
					}
				}
				pImpl->writeRaw(S3DSTR("</tr>\n"));
			}
		}
		pImpl->writeRaw(S3DSTR("</table>\n"));
	}

	void HTMLWriter::writeLine(int32 thickness, const Color& color)
	{
		pImpl->writeRaw(Format(S3DSTR("<hr style=\"height:"), thickness, S3DSTR("px; background-color:"), detail::GetColorCode(color), S3DSTR("; border: 0;\">\n")));
	}

	void HTMLWriter::writeImage(const Image& image, const Optional<Size>& size)
	{
		pImpl->writeRaw(S3DSTR("<img src=\"data:image/png;base64,"));

		pImpl->writeRaw(Base64::Encode(image.encode(ImageFormat::PNG).getView()));

		const Size s = size.value_or(image.size());

		pImpl->writeRaw(S3DSTR("\" width=\"") + Format(s.x) + S3DSTR("\" height=\"") + Format(s.y) + S3DSTR("\">\n"));
	}

	void HTMLWriter::writeImage(const FilePath& url, const Optional<Size>& size)
	{
		pImpl->writeRaw(S3DSTR("<img src=\"") + url);

		if (size)
		{
			pImpl->writeRaw(S3DSTR("\" width=\"") + Format(size->x) + S3DSTR("\" height=\"") + Format(size->y) + S3DSTR("\">\n"));
		}
		else
		{
			pImpl->writeRaw(S3DSTR("\">\n"));
		}
	}

	const FilePath& HTMLWriter::path() const
	{
		return pImpl->path();
	}
}
