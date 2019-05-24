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
// s3d::HTMLWriter is originally created by Kenta Masuda (HAMSTRO)
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Grid.hpp"
# include "Color.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	class HTMLWriter
	{
	private:

		class HTMLWriterDetail;

		std::shared_ptr<HTMLWriterDetail> pImpl;

	public:

		static String DefaultStyle();

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HTMLWriter();

		HTMLWriter(const FilePath& path, const String& title = U"Untitled", StringView styleSheet = DefaultStyle());

		/// <summary>
		/// デストラクタ
		/// </summary>
		~HTMLWriter();

		bool open(const FilePath& path, const String& title = U"Untitled", StringView styleSheet = DefaultStyle());

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const;

		void writeRaw(StringView view);

		void writeParagraph(StringView view, const Color& color = Palette::Black);

		void writeHeader(StringView view, int32 level = 1);

		void writeList(const Array<String>& items);

		void writeOrderedList(const Array<String>& items);

		void writeTable(const Grid<String>& items, bool hasHeader = false);

		void writeLine(int32 thickness = 2, const Color& color = Color(223, 226, 229));

		void writeImage(const Image& image, const Optional<Size>& size = unspecified);

		void writeImage(const FilePath& url, const Optional<Size>& size = unspecified);

		[[nodiscard]] const FilePath& path() const;
	};
}
