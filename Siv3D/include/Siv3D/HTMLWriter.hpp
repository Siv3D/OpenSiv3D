//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
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

		class CHTMLWriter;

		std::shared_ptr<CHTMLWriter> pImpl;

	public:

		static String DefaultStyle()
		{
			return String(
UR"(body{
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

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HTMLWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~HTMLWriter();

		HTMLWriter(const FilePath& path, const String& title = U"Untitled", const StringView styleSheet = DefaultStyle())
			: HTMLWriter()
		{
			open(path, title, styleSheet);
		}

		bool open(const FilePath& path, const String& title = U"Untitled", const StringView styleSheet = DefaultStyle());

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const
		{
			return isOpened();
		}

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
