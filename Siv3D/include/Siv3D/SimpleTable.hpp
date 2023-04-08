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
# include "Common.hpp"
# include "Optional.hpp"
# include "Grid.hpp"
# include "ColorHSV.hpp"
# include "Font.hpp"
# include "SimpleGUI.hpp"

namespace s3d
{
	/// @brief テーブルデータ | Table data
	class SimpleTable
	{
	public:

		/// @brief セルの要素 | Cell elements
		struct Item
		{
			/// @brief テキスト | Text
			String text;

			/// @brief テキストの幅（ピクセル） | Text width (pixels)
			int32 textWidth = 0;

			/// @brief テキストの色 | Text color
			Optional<Color> textColor;

			/// @brief テキストアライメント（左: -1, 中央: 0, 右: 1） | Text alignment (left: -1, center: 0, right: 1)
			int8 textAlignment = 0;

			/// @brief セルの背景色 | Cell background color
			Optional<Color> backgroundColor;
		};

		/// @brief テーブルのスタイル | Table style
		struct Style
		{
			/// @brief セルの高さ  | Cell height
			double cellHeight = DefaultCellHeight;

			/// @brief 枠の太さ | Border thickness
			double borderThickness = DefaultBorderThickness;

			/// @brief 背景色 | Background color
			Optional<ColorF> backgroundColor = ColorF{ 1.0 };

			/// @brief テキストの色 | Text color
			ColorF textColor{ 0.11 };

			/// @brief 枠の色 | Border color
			ColorF borderColor{ 0.33 };

			/// @brief セル幅が動的に変化するか | Variable cell width
			bool variableWidth = false;

			/// @brief 水平方向の枠線があるか | Has horizontal border
			bool hasHorizontalBorder = true;

			/// @brief 垂直方向の枠線があるか | Has vertical border
			bool hasVerticalBorder = true;

			/// @brief 外周の枠線があるか | Has outer border
			bool hasOuterBorder = true;

			/// @brief テキストの左右のパディング | Text left and right padding
			double textPaddingLR = DefaultTextPaddingLR;

			/// @brief 使用するフォント | Font to use
			Font font = SimpleGUI::GetFont();

			/// @brief フォントサイズ | Font size
			double fontSize = DefaultFontSize;

			/// @brief 列のヘッダで使用するフォント | Font for column header
			Optional<Font> columnHeaderFont;

			/// @brief 列のヘッダのフォントサイズ  | Column header font size
			Optional<double> columnHeaderFontSize;

			/// @brief 行のヘッダで使用するフォント | Font for row header
			Optional<Font> rowHeaderFont;

			/// @brief 行のヘッダのフォントサイズ | Row header font size
			Optional<double> rowHeaderFontSize;

			/// @brief 行がマウスオーバーされているときの行の色 | Row color when hovered
			std::function<Optional<ColorF>(const Point& index)> hoveredRow;

			/// @brief セルがマウスオーバーされているときのセルの色 | Cell color when hovered
			std::function<Optional<ColorF>(const Point& index)> hoveredCell;

			static constexpr double DefaultCellHeight = 35.0;

			static constexpr double DefaultBorderThickness = 1.0;

			static constexpr double DefaultTextPaddingLR = 12.0;

			static constexpr double DefaultFontSize = 20.0;
			
			[[nodiscard]]
			static Style Default();
		};

		/// @brief 空のテーブルを作成します。 | Creates an empty table.
		SIV3D_NODISCARD_CXX20
		SimpleTable() = default;

		/// @brief 列数を指定して空のテーブルを作成します。 | Creates an empty table with specified number of columns.
		/// @param columns 列数 | Number of columns
		/// @param style スタイル | Style
		SIV3D_NODISCARD_CXX20
		explicit SimpleTable(size_t columns, const Style& style = Style::Default());

		/// @brief 列数と各列の最小幅を指定して空のテーブルを作成します。 | Creates an empty table with specified number of columns and minimum column widths.
		/// @param minColumnWidths 各列の最小幅（ピクセル） | Minimum width of each column (pixels)
		/// @param style スタイル | Style
		SIV3D_NODISCARD_CXX20
		explicit SimpleTable(const Array<double>& minColumnWidths, const Style& style = Style::Default());

		/// @brief テーブルのアイテムの二次元配列を返します。 | Returns a 2D array of table items.
		/// @return テーブルのアイテムの二次元配列 | 2D array of table items
		[[nodiscard]]
		const Grid<Item>& items() const noexcept;

		/// @brief テーブルの指定したセルのアイテムを返します。 | Returns the item in the specified cell of the table.
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @return 指定したセルのアイテム | Item in the specified cell
		[[nodiscard]]
		const Item& getItem(size_t y, size_t x) const;

		/// @brief テーブルの指定したセルのアイテムを返します。 | Returns the item in the specified cell of the table.
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @return 指定したセルのアイテム | Item in the specified cell
		[[nodiscard]]
		const Item& getItem(const Point& index) const;

		/// @brief テーブルのスタイルを返します。 | Returns the table style.
		/// @return テーブルのスタイル | Table style
		[[nodiscard]]
		const Style& style() const noexcept;

		/// @brief テーブルの行数を返します。 | Returns the number of rows in the table.
		/// @return テーブルの行数 | Number of rows
		[[nodiscard]]
		size_t rows() const noexcept;

		/// @brief テーブルの列数を返します。 | Returns the number of columns in the table.
		/// @return テーブルの列数 | Number of columns
		[[nodiscard]]
		size_t columns() const noexcept;

		/// @brief テーブルが空かどうかを返します。 | Returns whether the table is empty or not.
		/// @return テーブルが空の場合 true, それ以外の場合は false | true if the table is empty, false otherwise
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief テーブルが空でないかどうかを返します。 | Returns whether the table is not empty or not.
		/// @return テーブルが空でない場合 true, それ以外の場合は false | true if the table is not empty, false otherwise
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief テーブルの末尾に行を追加します。 | Adds a row to the end of the table.
		/// @return *this
		SimpleTable& push_back_row();

		/// @brief テーブルの末尾に行を追加します。 | Adds a row to the end of the table.
		/// @param textAlignments 各セルのテキストアライメント (左: -1, 中央: 0, 右: 1) | Text alignment of each cell (left: -1, center: 0, right: 1)
		/// @return *this
		SimpleTable& push_back_row(const Array<int32>& textAlignments);

		/// @brief テーブルの末尾に行を追加します。 | Adds a row to the end of the table.
		/// @param texts 各セルのテキスト | Text of each cell
		/// @return *this
		SimpleTable& push_back_row(const Array<String>& texts);

		/// @brief テーブルの末尾に行を追加します。 | Adds a row to the end of the table.
		/// @param texts 各セルのテキスト
		/// @param textAlignments 各セルのテキストアライメント (左: -1, 中央: 0, 右: 1)
		/// @return *this
		SimpleTable& push_back_row(const Array<String>& texts, const Array<int32>& textAlignments);

		/// @brief テーブルの末尾の行を削除します。 | Removes the last row of the table.
		/// @remark テーブルが空の場合は何もしません。 | Does nothing if the table is empty.
		void pop_back_row();

		/// @brief テーブルのアイテムをすべて削除します。 | Removes all items from the table.
		/// @remark 列数の情報は保持されます。 | The number of columns is retained.
		void clear();

		/// @brief 指定したセルのテキストを設定します。 | Sets the text of the specified cell.
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @param text テキスト | Text
		/// @return *this
		SimpleTable& setText(size_t y, size_t x, const String& text);

		/// @brief 指定したセルのテキストを設定します。 | Sets the text of the specified cell.
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @param text テキスト | Text
		/// @return *this
		SimpleTable& setText(const Point& index, const String& text);

		/// @brief 指定した行のテキストを設定します。 | Sets the text of the specified row.
		/// @param y 行 | Row
		/// @param texts 各列のテキスト | Text of each column
		/// @return *this
		SimpleTable& setText(size_t y, const Array<String>& texts);

		/// @brief 指定したセルのテキストアライメントを設定します。 | Sets the text alignment of the specified cell.
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @param textAlignment テキストアライメント (左: -1, 中央: 0, 右: 1) | Text alignment (left: -1, center: 0, right: 1)
		/// @return *this
		SimpleTable& setTextAlignment(size_t y, size_t x, int32 textAlignment);

		/// @brief 指定したセルのテキストアライメントを設定します。 | Sets the text alignment of the specified cell.
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @param textAlignment テキストアライメント (左: -1, 中央: 0, 右: 1) | Text alignment (left: -1, center: 0, right: 1)
		/// @return *this
		SimpleTable& setTextAlignment(const Point& index, int32 textAlignment);

		/// @brief 指定した行のテキストアライメントを設定します。 | Sets the text alignment of the specified row.
		/// @param y 行 | Row
		/// @param textAlignment テキストアライメント (左: -1, 中央: 0, 右: 1) | Text alignment (left: -1, center: 0, right: 1)
		/// @return *this
		SimpleTable& setRowTextAlignment(size_t y, int32 textAlignment);

		/// @brief 指定したセルの背景色を設定します。 | Sets the background color of the specified cell.
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setBackgroundColor(size_t y, size_t x, const Optional<ColorF>& color);

		/// @brief 指定したセルの背景色を設定します。 | Sets the background color of the specified cell.
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setBackgroundColor(const Point& index, const Optional<ColorF>& color);

		/// @brief 指定した行の背景色を設定します。 | Sets the background color of the specified row.
		/// @param y 行 | Row
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setRowBackgroundColor(size_t y, const Optional<ColorF>& color);

		/// @brief 指定したセルのテキスト色を設定します。 | Sets the text color of the specified cell.
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setTextColor(size_t y, size_t x, const Optional<ColorF>& color);

		/// @brief 指定したセルのテキスト色を設定します。 | Sets the text color of the specified cell.
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setTextColor(const Point& index, const Optional<ColorF>& color);

		/// @brief 指定した行のテキスト色を設定します。 | Sets the text color of the specified row.
		/// @param y 行 | Row
		/// @param color 色 | Color
		/// @return *this
		SimpleTable& setRowTextColor(size_t y, const Optional<ColorF>& color);

		/// @brief テーブルのサイズ（ピクセル）を返します。 | Returns the size of the table (pixels).
		/// @return テーブルのサイズ（ピクセル） | Size of the table (pixels)
		[[nodiscard]]
		SizeF size() const noexcept;

		/// @brief テーブルの幅（ピクセル）を返します。 | Returns the width of the table (pixels).
		/// @return テーブルの幅（ピクセル） | Width of the table (pixels)
		[[nodiscard]]
		double width() const noexcept;

		/// @brief テーブルの高さ（ピクセル）を返します。 | Returns the height of the table (pixels).
		/// @return テーブルの高さ（ピクセル） | Height of the table (pixels)
		[[nodiscard]]
		double height() const noexcept;

		/// @brief テーブルの領域を返します。 | Returns the region of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @return テーブルの領域 | Region of the table
		[[nodiscard]]
		RectF region(const Vec2& tablePos = Vec2{ 0, 0 }) const noexcept;

		/// @brief テーブルの指定した行の領域を返します。 | Returns the region of the specified row of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param y 行 | Row
		/// @return テーブルの指定した行の領域 | Region of the specified row of the table
		[[nodiscard]]
		RectF rowRegion(const Vec2& tablePos, size_t y) const noexcept;

		/// @brief テーブルの指定した列の領域を返します。 | Returns the region of the specified column of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param x 列 | Column
		/// @return テーブルの指定した列の領域 | Region of the specified column of the table
		[[nodiscard]]
		RectF columnRegion(const Vec2& tablePos, size_t x) const noexcept;

		/// @brief テーブルの指定したセルの領域を返します。 | Returns the region of the specified cell of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param y 行 | Row
		/// @param x 列 | Column
		/// @return テーブルの指定したセルの領域 | Region of the specified cell of the table
		[[nodiscard]]
		RectF cellRegion(const Vec2& tablePos, size_t y, size_t x) const noexcept;

		/// @brief テーブルの指定したセルの領域を返します。 | Returns the region of the specified cell of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param index セルのインデックス（列, 行） | Cell index (column, row)
		/// @return テーブルの指定したセルの領域 | Region of the specified cell of the table
		[[nodiscard]]
		RectF cellRegion(const Vec2& tablePos, const Point& index) const noexcept;

		/// @brief テーブルの指定した位置にある行のインデックスを返します。 | Returns the index of the row at the specified position of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param pos 位置（シーン座標） | Position (scene coordinates)
		/// @return テーブルの指定した位置にある行のインデックス。テーブル上にない場合は none | Index of the row at the specified position of the table. none if not on the table
		[[nodiscard]]
		Optional<int32> rowIndex(const Vec2& tablePos, const Vec2& pos) const noexcept;

		/// @brief テーブルの指定した位置にある列のインデックスを返します。 | Returns the index of the column at the specified position of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param pos 位置（シーン座標） | Position (scene coordinates)
		/// @return テーブルの指定した位置にある列のインデックス。テーブル上にない場合は none | Index of the column at the specified position of the table. none if not on the table
		[[nodiscard]]
		Optional<int32> columnIndex(const Vec2& tablePos, const Vec2& pos) const noexcept;

		/// @brief テーブルの指定した位置にあるセルのインデックスを返します。 | Returns the index of the cell at the specified position of the table.
		/// @param tablePos テーブルの位置 | Position of the table
		/// @param pos 位置（シーン座標） | Position (scene coordinates)
		/// @return テーブルの指定した位置にあるセルのインデックス。テーブル上にない場合は none | Index of the cell at the specified position of the table. none if not on the table
		[[nodiscard]]
		Optional<Point> cellIndex(const Vec2& tablePos, const Vec2& pos) const noexcept;

		/// @brief テーブルを描画します。 | Draws the table.
		/// @param tablePos テーブルの位置 | Position of the table
		void draw(const Vec2& tablePos = Vec2{ 0, 0 }) const;

	private:

		static constexpr int32 DefaultAlignment = -1;

		Style m_style;

		Grid<Item> m_grid;

		Array<double> m_minColumnWidths;

		Array<double> m_columnWidths;

		struct AccumulatedWidths
		{
			Array<double> values;

			SIV3D_NODISCARD_CXX20
			AccumulatedWidths() = default;

			SIV3D_NODISCARD_CXX20
			AccumulatedWidths(const Array<double>& columnWidths, double borderThickness);

			void rebuild(const Array<double>& columnWidths, double borderThickness);

			[[nodiscard]]
			double getWidth(size_t index) const;

			[[nodiscard]]
			double operator [](size_t index) const;

			[[nodiscard]]
			double back() const;

		} m_columnAccumulatedWidths;

		void drawItem(size_t y, size_t x, const Vec2& tablePos, double yPos, const Font& font, double fontSize) const;
	};
}
