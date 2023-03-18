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

# include "HTMLWriterDetail.hpp"

namespace s3d
{
	HTMLWriter::HTMLWriterDetail::HTMLWriterDetail()
	{
		// do nothing
	}

	HTMLWriter::HTMLWriterDetail::~HTMLWriterDetail()
	{
		close();
	}

	bool HTMLWriter::HTMLWriterDetail::open(const FilePathView path, const StringView title, const StringView styleSheet)
	{
		if (m_textWriter.isOpen())
		{
			close();
		}

		if (not m_textWriter.open(path))
		{
			return false;
		}

		m_textWriter.writeln(U"<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\" />");

		writeElementRaw(String(title).xml_escaped(), U"title");

		writeElementRaw(styleSheet, U"style");

		m_textWriter.writeln(U"</head>\n<body>");

		return true;
	}

	void HTMLWriter::HTMLWriterDetail::close()
	{
		if (not m_textWriter)
		{
			return;
		}

		m_textWriter.writeln(U"</body>\n</html>");

		m_textWriter.close();
	}

	bool HTMLWriter::HTMLWriterDetail::isOpen() const
	{
		return m_textWriter.isOpen();
	}

	void HTMLWriter::HTMLWriterDetail::writeRaw(const StringView view)
	{
		if (not m_textWriter.isOpen())
		{
			return;
		}

		m_textWriter.write(view);
	}

	void HTMLWriter::HTMLWriterDetail::writeElementRaw(const StringView content, const StringView tag)
	{
		writeElementRaw(content, tag, tag);
	}

	void HTMLWriter::HTMLWriterDetail::writeElementRaw(const StringView content, const StringView startTag, const StringView endTag)
	{
		if (not m_textWriter)
		{
			return;
		}

		m_textWriter.write(U"<" + startTag + U">");

		m_textWriter.write(content);

		m_textWriter.write(U"</" + endTag + U">\n");
	}

	void HTMLWriter::HTMLWriterDetail::writeElementRaw(const StringView content, const StringView tag, const Array<std::pair<String, String>>& styles)
	{
		const String startTag =
			styles.map([](const std::pair<String, String>& keyValue) {
			return keyValue.first + U":" + keyValue.second + U";";
		}).join(U" ", tag + U" style=\"", U"\"");

		if (content.isEmpty())
		{
			writeRaw(U"<" + startTag + U">");
		}
		else
		{
			writeElementRaw(content, startTag, tag);
		}
	}

	const FilePath& HTMLWriter::HTMLWriterDetail::path() const
	{
		return m_textWriter.path();
	}
}
