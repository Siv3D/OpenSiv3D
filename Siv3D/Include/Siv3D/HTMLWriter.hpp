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

# pragma once
# include "Fwd.hpp"
# include "TextWriter.hpp"
# include "Grid.hpp"
# include "Unspecified.hpp"
# include "Color.hpp"
# include "Image.hpp"

namespace s3d
{
	class HTMLWriter
	{
	private:

		TextWriter m_writer;

		void writeElementRaw(const StringView content, const String& tag)
		{
			writeElementRaw(content, tag, tag);
		}

		void writeElementRaw(const StringView content, const String& startTag, const String& endTag)
		{
			if (!isOpened())
			{
				return;
			}

			m_writer.writeln(L"<" + startTag + L">");

			m_writer.writeln(content);

			m_writer.writeln(L"</" + endTag + L">");
		}

		void writeElementRaw(const StringView content, const String& tag, const Array<std::pair<String, String>>& styles)
		{
			const String startTag =
				styles.map([](const std::pair<String, String>& keyValue) {
					return keyValue.first + L":" + keyValue.second + L";";
				}).join(L" ", tag + L" style=\"", L"\"");

			if (content.isEmpty())
			{
				writeRaw(L"<" + startTag + L">");
			}
			else
			{
				writeElementRaw(content, startTag, tag);
			}
		}

		void beginHTML(const String& title, const StringView style)
		{
			m_writer.writeln(L"<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\" />");
			
			writeElementRaw(title.xml_escaped(), L"title");
			
			writeElementRaw(style, L"style");
			
			m_writer.writeln(L"</head>\n<body>");
		}

		void endHTML()
		{
			m_writer.writeln(L"</body>\n</html>");
		}

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

		static String DefaultStyle()
		{
			return String(
LR"(body{
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

	public:

		HTMLWriter() = default;

		HTMLWriter(const FilePath& path, const String& title = L"Untitled", const StringView styleSheet = DefaultStyle())
		{
			open(path, title, styleSheet);
		}

		~HTMLWriter()
		{
			close();
		}

		bool open(const FilePath& path, const String& title = L"Untitled", const StringView styleSheet = DefaultStyle())
		{
			if (isOpened())
			{
				close();
			}

			if (!m_writer.open(path))
			{
				return false;
			}

			beginHTML(title, styleSheet);

			return true;
		}

		void close()
		{
			if (!isOpened())
			{
				return;
			}

			endHTML();

			m_writer.close();
		}

		bool isOpened() const
		{
			return m_writer.isOpened();
		}

		explicit operator bool() const
		{
			return isOpened();
		}

		void writeRaw(const StringView view)
		{
			if (!isOpened())
			{
				return;
			}

			m_writer.write(view);
		}

		void writeParagraph(const StringView view, const Color& color = Palette::Black)
		{
			writeElementRaw(HTMLEscape(view), L"p", { { L"color", GetColorCode(color) } });
		}

		void writeHeader(const StringView view, int32 level = 1)
		{
			writeElementRaw(HTMLEscape(view), Format(L'h', Clamp(level, 1, 6)));
		}

		void writeList(const Array<String>& items)
		{
			writeRaw(L"<ul>\n");
			{
				for (const auto& item : items)
				{
					writeElementRaw(HTMLEscape(item), L"li");
				}
			}
			writeRaw(L"</ul>\n");
		}

		void writeOrderedList(const Array<String>& items)
		{
			writeRaw(L"<ol>\n");
			{
				for (const auto& item : items)
				{
					writeElementRaw(HTMLEscape(item), L"li");
				}
			}
			writeRaw(L"</ol>\n");
		}

		void writeTable(const Grid<String>& items, const bool hasHeader = false)
		{
			writeRaw(L"<table>\n");
			{
				if (items.isEmpty())
				{
					return writeRaw(L"</table>\n");
				}

				if (hasHeader)
				{
					writeRaw(L"<tr>\n");
					{
						for (size_t x = 0; x < items.width(); ++x)
						{
							writeElementRaw(HTMLEscape(items[0][x]), L"th");
						}
					}
					writeRaw(L"</tr>\n");
				}

				for (size_t y = hasHeader; y < items.height(); ++y)
				{
					writeRaw(L"<tr>\n");
					{
						for (size_t x = 0; x < items.width(); ++x)
						{
							writeElementRaw(HTMLEscape(items[y][x]), L"td");
						}
					}
					writeRaw(L"</tr>\n");
				}
			}
			writeRaw(L"</table>\n");
		}

		void writeLine(int32 thickness = 2, const Color& color = Color(223, 226, 229))
		{
			writeRaw(Format(L"<hr style=\"height:", thickness, L"px; background-color:", GetColorCode(color), L"; border: 0;\">\n"));
		}

		void writeImage(const Image& image, const Optional<Size>& size = unspecified)
		{
			writeRaw(L"<img src=\"data:image/png;base64,");

			writeRaw(Base64::Encode(image.encode(ImageFormat::PNG).getView()));

			const Size s = size.value_or(image.size());

			writeRaw(L"\" width=\"" + Format(s.x) + L"\" height=\"" + Format(s.y) + L"\">\n");
		}

		void writeImage(const FilePath& url, const Optional<Size>& size = unspecified)
		{
			writeRaw(L"<img src=\"" + url);

			if (size)
			{
				writeRaw(L"\" width=\"" + Format(size->x) + L"\" height=\"" + Format(size->y) + L"\">\n");
			}
			else
			{
				writeRaw(L"\">\n");
			}			
		}

		const FilePath& path() const
		{
			return m_writer.path();
		}
	};
}
