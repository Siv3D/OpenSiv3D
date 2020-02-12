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

# pragma once
# include <Siv3D/HTMLWriter.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	class HTMLWriter::HTMLWriterDetail
	{
	private:

		TextWriter m_textWriter;

	public:

		HTMLWriterDetail();

		~HTMLWriterDetail();

		bool open(FilePathView path, const String& title, const StringView styleSheet);

		void close();

		bool isOpen() const;

		void writeRaw(StringView view);

		void writeElementRaw(StringView content, const String& tag);

		void writeElementRaw(StringView content, const String& startTag, const String& endTag);

		void writeElementRaw(StringView content, const String& tag, const Array<std::pair<String, String>>& styles);
		
		const FilePath& path() const;
	};
}
