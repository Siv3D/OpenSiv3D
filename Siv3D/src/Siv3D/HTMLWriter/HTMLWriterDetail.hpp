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

# pragma once
# include <Siv3D/HTMLWriter.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	class HTMLWriter::HTMLWriterDetail
	{
	public:

		HTMLWriterDetail();

		~HTMLWriterDetail();

		bool open(FilePathView path, StringView title, StringView styleSheet);

		void close();

		bool isOpen() const;

		void writeRaw(StringView view);

		void writeElementRaw(StringView content, StringView tag);

		void writeElementRaw(StringView content, StringView startTag, StringView endTag);

		void writeElementRaw(StringView content, StringView tag, const Array<std::pair<String, String>>& styles);

		const FilePath& path() const;

	private:

		TextWriter m_textWriter;
	};
}
