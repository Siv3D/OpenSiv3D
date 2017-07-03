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
# include <Siv3D/HTMLWriter.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	class HTMLWriter::CHTMLWriter
	{
	private:

		TextWriter m_textWriter;

	public:

		CHTMLWriter();

		~CHTMLWriter();

		bool open(const FilePath& path, const String& title, const StringView styleSheet);

		void close();

		bool isOpened() const;

		void writeRaw(StringView view);

		void writeElementRaw(StringView content, const String& tag);

		void writeElementRaw(StringView content, const String& startTag, const String& endTag);

		void writeElementRaw(StringView content, const String& tag, const Array<std::pair<String, String>>& styles);
		
		const FilePath& path() const;
	};
}
