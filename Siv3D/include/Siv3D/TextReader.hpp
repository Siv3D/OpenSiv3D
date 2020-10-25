//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "TextEncoding.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	/// @brief 読み込み用テキストファイル
	class TextReader
	{
	private:

		class TextReaderDetail;

		std::shared_ptr<TextReaderDetail> pImpl;

	public:

		SIV3D_NODISCARD_CXX20
		TextReader();

		SIV3D_NODISCARD_CXX20
		explicit TextReader(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit TextReader(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		SIV3D_NODISCARD_CXX20
		explicit TextReader(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool open(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool open(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		Optional<char32> readChar();

		[[nodiscard]]
		Optional<String> readLine();

		[[nodiscard]]
		Array<String> readLines();

		[[nodiscard]]
		String readAll();

		bool readChar(char32& ch);

		bool readLine(String& line);

		bool readLines(Array<String>& lines);

		bool readAll(String& s);

		[[nodiscard]]
		TextEncoding encoding() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}

# include "detail/TextReader.ipp"
