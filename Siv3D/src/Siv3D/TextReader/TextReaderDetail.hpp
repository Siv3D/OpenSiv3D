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

# pragma once
# include <Siv3D/TextReader.hpp>

namespace s3d
{
	class TextReader::TextReaderDetail
	{
	private:

		std::unique_ptr<IReader> m_reader;

		struct Info
		{
			FilePath fullPath;
			TextEncoding encoding = TextEncoding::Default;
			bool isOpen = false;
		} m_info;

		[[nodiscard]]
		bool readByte(uint8& c);

		[[nodiscard]]
		bool readTwoBytes(uint16& c);

		[[nodiscard]]
		bool readUTF8(char32& c);

		[[nodiscard]]
		bool readUTF16LE(char32& c);

		[[nodiscard]]
		bool readUTF16BE(char32& c);

		[[nodiscard]]
		bool readCodePoint(char32& codePoint);

	public:

		TextReaderDetail();

		~TextReaderDetail();

		[[nodiscard]]
		bool open(FilePathView path, const Optional<TextEncoding>& encoding);

		[[nodiscard]]
		bool open(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		Optional<char32> readChar();

		[[nodiscard]]
		Optional<String> readLine();

		[[nodiscard]]
		Array<String> readLines();

		[[nodiscard]]
		String readAll();

		[[nodiscard]]
		bool readChar(char32& ch);

		[[nodiscard]]
		bool readLine(String& line);

		bool readLines(Array<String>& lines);

		bool readAll(String& s);

		[[nodiscard]]
		TextEncoding encoding() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}
