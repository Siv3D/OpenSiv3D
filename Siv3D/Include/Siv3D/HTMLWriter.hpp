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
# include "TextWriter.hpp"
# include "Grid.hpp"
# include "Unspecified.hpp"
# include "Color.hpp"

namespace s3d
{
	class HTMLWriter
	{
	private:

		TextWriter m_writer;

		String m_title;

		String m_style;

		void writeEscapedElement(const String& escaped, const String& tag)
		{
			writeEscapedElement(escaped, tag, tag);
		}

		void writeEscapedElement(const String& escaped, const String& beginTag, const String& endTag)
		{
			if (!isOpened())
			{
				return;
			}

			m_writer.writeln(L"<" + beginTag + L">" + escaped + L"</" + endTag + L">");
		}

		void writeEscapedElement(const String& escaped, const String& tag, const Array<std::pair<String, String>>& styles)
		{
			const String beginTag = styles.map([](const std::pair<String, String>& keyValue) {return keyValue.first + L":" + keyValue.second + L";"; }).join(L" ", tag + L" style=\"", L"\"");

			if (escaped.isEmpty())
			{
				writeRaw(L"<" + beginTag + L">");
			}
			else
			{
				writeEscapedElement(escaped, beginTag, tag);
			}
		}

		void beginHTML()
		{
			//<html>のlangは指定しない
			m_writer.writeln(L"<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\" />");
			writeEscapedElement(m_title.xml_escaped(), L"title");
			writeEscapedElement(m_style, L"style");
			m_writer.writeln(L"</head>\n<body>");
		}

		void endHTML()
		{
			m_writer.writeln(L"</body>\n</html>");
		}

		static String HTMLEscape(const String& str)
		{
			String new_string;

			new_string.reserve(str.length());

			for (const auto v : str)
			{
				switch (v)
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
					new_string.push_back(v);
					break;
				}
			}

			return new_string;
		}

		static String GetRGBCode(const Color& color)
		{
			return L"#" +
				ToHex(color.r).lpad(2, L'0') +
				ToHex(color.g).lpad(2, L'0') +
				ToHex(color.b).lpad(2, L'0');
		}

		static String DefaultStyle()
		{
			return String(LR"(
				body{
					margin:0 5%;
				}
				table{
					border-collapse: collapse;
				}
				tr:nth-child(even){
					background:#f6f8fa;
				}
				th,td{
					padding:10px;
					border: 1px solid #dfe2e5;
				}
				)").remove(L"\t");
		}

	public:

		HTMLWriter() = default;

		HTMLWriter(const FilePath& path, const String& title = L"Untitled", const String& styleSheet = DefaultStyle())
			: m_writer(path)
			, m_title(title)
			, m_style(styleSheet)
		{
			beginHTML();
		}

		~HTMLWriter()
		{
			close();
		}

		void open(const FilePath& path, const String& title = L"Untitled", const String& styleSheet = DefaultStyle())
		{
			if (isOpened())
			{
				close();
			}

			m_writer = TextWriter(path);
			m_title = title;
			m_style = styleSheet;

			beginHTML();
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

		void writeRaw(const String& str)
		{
			if (!isOpened())
			{
				return;
			}

			m_writer.writeln(str);
		}

		void writeParagraph(const String& str, const Color& color = Palette::Black)
		{
			writeEscapedElement(HTMLEscape(str), L"p", { { L"color", GetRGBCode(color) } });
		}

		void writeHeader(const String& str, int32 level = 1)
		{
			writeEscapedElement(HTMLEscape(str), Format(L'h', Clamp(level, 1, 6)));
		}

		void writeList(const Array<String>& items)
		{
			writeRaw(L"<ul>");

			for (const auto& item : items)
			{
				writeEscapedElement(HTMLEscape(item), L"li");
			}

			writeRaw(L"</ul>");
		}

		void writeOrderedList(const Array<String>& items)
		{
			writeRaw(L"<ol>");

			for (const auto& item : items)
			{
				writeEscapedElement(HTMLEscape(item), L"li");
			}

			writeRaw(L"</ol>");
		}

		void writeTable(const Grid<String>& items)
		{
			writeRaw(L"<table>");

			if (items.isEmpty())
			{
				writeRaw(L"</table>");
				return;
			}

			writeRaw(L"<tr>");
			for (size_t x = 0; x < items.width(); ++x)
			{
				writeEscapedElement(HTMLEscape(items[0][x]), L"th");
			}
			writeRaw(L"</tr>");

			for (size_t y = 1; y < items.height(); ++y)
			{
				writeRaw(L"<tr>");

				for (size_t x = 0; x < items.width(); ++x)
				{
					writeEscapedElement(HTMLEscape(items[y][x]), L"td");
				}

				writeRaw(L"</tr>");
			}

			writeRaw(L"</table>");
		}

		void writeLine()
		{
			writeRaw(L"<hr>");
		}

		void writeLine(int32 thickness)
		{
			writeEscapedElement(L"", L"hr", { { L"height", Format(thickness, L"px") } });
		}

		void writeLine(int32 thickness, const Color& color)
		{
			writeEscapedElement(L"", L"hr", { { L"height", Format(thickness, L"px") },{ L"background-color", GetRGBCode(color) } });
		}

		void writeImage(const Image& image, const Optional<Size>& size = unspecified)
		{
		}
	};
}
