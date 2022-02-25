//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::HTMLWriter is originally created by Kenta Masuda (HAMSTRO)
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Grid.hpp"
# include "ColorHSV.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief HTML 文書の書き出し
	class HTMLWriter
	{
	public:

		static String DefaultStyle();

		SIV3D_NODISCARD_CXX20
		HTMLWriter();

		SIV3D_NODISCARD_CXX20
		HTMLWriter(FilePathView path, StringView title = U"Untitled", StringView styleSheet = DefaultStyle());

		~HTMLWriter();

		bool open(FilePathView path, StringView title = U"Untitled", StringView styleSheet = DefaultStyle());

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void writeRaw(StringView s);

		void writeParagraph(StringView s, const Color& color = Palette::Black);

		void writeHeader(StringView s, int32 level = 1);

		void writeList(const Array<String>& items);

		void writeOrderedList(const Array<String>& items);

		void writeTable(const Grid<String>& items, HasHeader hasHeader = HasHeader::No);

		void writeLine(int32 thickness = 2, const Color& color = Color(223, 226, 229));

		void writeImage(const Image& image, const Optional<Size>& size = unspecified);

		void writeImage(FilePathView url, const Optional<Size>& size = unspecified);

		[[nodiscard]]
		const FilePath& path() const;

	private:

		class HTMLWriterDetail;

		std::shared_ptr<HTMLWriterDetail> pImpl;
	};
}
