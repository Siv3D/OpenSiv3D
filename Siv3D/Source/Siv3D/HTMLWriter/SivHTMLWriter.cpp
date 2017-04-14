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
					new_string.append(L"<br>", 4);
					break;
				case L'\r':
					break;
				case L'\"':
					new_string.append(L"&quot;", 6);
					break;
				case L'&':
					new_string.append(L"&amp;", 5);
					break;
				case L'\'':
					new_string.append(L"&apos;", 6);
					break;
				case L'<':
					new_string.append(L"&lt;", 4);
					break;
				case L'>':
					new_string.append(L"&gt;", 4);
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
			return L"#" + color.toHex();
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
		pImpl->writeElementRaw(detail::HTMLEscape(view), L"p", { { L"color", detail::GetColorCode(color) } });
	}

	void HTMLWriter::writeHeader(const StringView view, int32 level)
	{
		pImpl->writeElementRaw(detail::HTMLEscape(view), Format(L'h', Clamp(level, 1, 6)));
	}

	void HTMLWriter::writeList(const Array<String>& items)
	{
		pImpl->writeRaw(L"<ul>\n");
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), L"li");
			}
		}
		pImpl->writeRaw(L"</ul>\n");
	}

	void HTMLWriter::writeOrderedList(const Array<String>& items)
	{
		pImpl->writeRaw(L"<ol>\n");
		{
			for (const auto& item : items)
			{
				pImpl->writeElementRaw(detail::HTMLEscape(item), L"li");
			}
		}
		pImpl->writeRaw(L"</ol>\n");
	}

	void HTMLWriter::writeTable(const Grid<String>& items, const bool hasHeader)
	{
		pImpl->writeRaw(L"<table>\n");
		{
			if (items.isEmpty())
			{
				return pImpl->writeRaw(L"</table>\n");
			}

			if (hasHeader)
			{
				pImpl->writeRaw(L"<tr>\n");
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[0][x]), L"th");
					}
				}
				pImpl->writeRaw(L"</tr>\n");
			}

			for (size_t y = hasHeader; y < items.height(); ++y)
			{
				pImpl->writeRaw(L"<tr>\n");
				{
					for (size_t x = 0; x < items.width(); ++x)
					{
						pImpl->writeElementRaw(detail::HTMLEscape(items[y][x]), L"td");
					}
				}
				pImpl->writeRaw(L"</tr>\n");
			}
		}
		pImpl->writeRaw(L"</table>\n");
	}

	void HTMLWriter::writeLine(int32 thickness, const Color& color)
	{
		pImpl->writeRaw(Format(L"<hr style=\"height:", thickness, L"px; background-color:", detail::GetColorCode(color), L"; border: 0;\">\n"));
	}

	void HTMLWriter::writeImage(const Image& image, const Optional<Size>& size)
	{
		pImpl->writeRaw(L"<img src=\"data:image/png;base64,");

		pImpl->writeRaw(Base64::Encode(image.encode(ImageFormat::PNG).getView()));

		const Size s = size.value_or(image.size());

		pImpl->writeRaw(L"\" width=\"" + Format(s.x) + L"\" height=\"" + Format(s.y) + L"\">\n");
	}

	void HTMLWriter::writeImage(const FilePath& url, const Optional<Size>& size)
	{
		pImpl->writeRaw(L"<img src=\"" + url);

		if (size)
		{
			pImpl->writeRaw(L"\" width=\"" + Format(size->x) + L"\" height=\"" + Format(size->y) + L"\">\n");
		}
		else
		{
			pImpl->writeRaw(L"\">\n");
		}
	}

	const FilePath& HTMLWriter::path() const
	{
		return pImpl->path();
	}
}
