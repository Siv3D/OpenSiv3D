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

# include <Siv3D/SimpleTable.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	SimpleTable::Style SimpleTable::Style::Default()
	{
		return{};
	}

	SimpleTable::SimpleTable(const size_t columns, const Style& style)
		: SimpleTable{ Array<double>(columns, Style::DefaultCellHeight), style } {}

	SimpleTable::SimpleTable(const Array<double>& minColumnWidths, const Style& style)
		: m_style{ style }
		, m_grid(minColumnWidths.size(), 0)
		, m_minColumnWidths(minColumnWidths)
		, m_columnWidths(minColumnWidths)
		, m_columnAccumulatedWidths(m_columnWidths, m_style.borderThickness) {}

	const Grid<SimpleTable::Item>& SimpleTable::items() const noexcept
	{
		return m_grid;
	}

	const SimpleTable::Item& SimpleTable::getItem(const size_t y, const size_t x) const
	{
		if ((m_grid.width() <= x) || (m_grid.height() <= y))
		{
			throw Error{ U"TableRenderer::getItem(): Invalid index ({}, {})"_fmt(x, y) };
		}

		return m_grid[y][x];
	}

	const SimpleTable::Item& SimpleTable::getItem(const Point& index) const
	{
		if ((static_cast<int32>(m_grid.width()) <= index.x)
			|| (static_cast<int32>(m_grid.height()) <= index.y))
		{
			throw Error{ U"TableRenderer::getItem(): Invalid index ({})"_fmt(index) };
		}

		return m_grid[index];
	}

	const SimpleTable::Style& SimpleTable::style() const noexcept
	{
		return m_style;
	}

	size_t SimpleTable::rows() const noexcept
	{
		return m_grid.height();
	}

	size_t SimpleTable::columns() const noexcept
	{
		return m_grid.width();
	}

	bool SimpleTable::isEmpty() const noexcept
	{
		return m_grid.isEmpty();
	}

	SimpleTable::operator bool() const noexcept
	{
		return (not m_grid.isEmpty());
	}

	SimpleTable& SimpleTable::push_back_row()
	{
		return push_back_row(Array<String>(m_grid.width()));
	}

	SimpleTable& SimpleTable::push_back_row(const Array<int32>& textAlignments)
	{
		return push_back_row(Array<String>(m_grid.width()), textAlignments);
	}

	SimpleTable& SimpleTable::push_back_row(const Array<String>& texts)
	{
		Array<int32> textAlignments(m_grid.width(), DefaultAlignment);

		if (0 < m_grid.height())
		{
			const size_t y = (m_grid.height() - 1);

			for (size_t x = 0; x < m_grid.width(); ++x)
			{
				textAlignments[x] = m_grid[y][x].textAlignment;
			}
		}

		return push_back_row(texts, textAlignments);
	}

	SimpleTable& SimpleTable::push_back_row(const Array<String>& texts, const Array<int32>& textAlignments)
	{
		if (m_grid.width() != texts.size())
		{
			throw Error{ U"TableRenderer::push_back_row(): Invalid number of texts ({})"_fmt(texts.size()) };
		}

		if (m_grid.width() != textAlignments.size())
		{
			throw Error{ U"TableRenderer::push_back_row(): Invalid number of textAlignments ({})"_fmt(textAlignments.size()) };
		}

		m_grid.push_back_row({});

		for (size_t x = 0; x < texts.size(); ++x)
		{
			setText((m_grid.height() - 1), x, texts[x]);
			setTextAlignment((m_grid.height() - 1), x, textAlignments[x]);
		}

		return *this;
	}

	void SimpleTable::pop_back_row()
	{
		if (m_grid.isEmpty())
		{
			return;
		}

		m_grid.pop_back_row();

		if (not m_style.variableWidth)
		{
			return;
		}

		for (size_t x = 0; x < m_grid.width(); ++x)
		{
			int32 newMaxTextWidth = 0;

			for (size_t y = 0; y < m_grid.height(); ++y)
			{
				newMaxTextWidth = Max(newMaxTextWidth, m_grid[y][x].textWidth);
			}

			m_columnWidths[x] = Max(m_minColumnWidths[x], (newMaxTextWidth + m_style.textPaddingLR * 2));
		}

		m_columnAccumulatedWidths.rebuild(m_columnWidths, m_style.borderThickness);
	}

	void SimpleTable::clear()
	{
		m_grid.resize(m_minColumnWidths.size(), 0);

		m_columnWidths = m_minColumnWidths;

		m_columnAccumulatedWidths = AccumulatedWidths(m_columnWidths, m_style.borderThickness);
	}

	SimpleTable& SimpleTable::setText(const size_t y, const size_t x, const String& text)
	{
		if ((m_grid.width() <= x) || (m_grid.height() <= y))
		{
			throw Error{ U"TableRenderer::set(): Invalid index ({}, {})"_fmt(x, y) };
		}

		auto& item = m_grid[y][x];

		{
			if (item.text == text)
			{
				return *this;
			}

			item.text = text;
		}

		{
			const int32 oldTextWidth = item.textWidth;
			const int32 newTextWidth = static_cast<int32>(Math::Ceil(m_style.font(text).region(m_style.fontSize).w));

			if (oldTextWidth == newTextWidth)
			{
				return *this;
			}

			item.textWidth = newTextWidth;
		}

		if (not m_style.variableWidth)
		{
			return *this;
		}

		{
			const double oldColumnWidth = m_columnWidths[x];

			int32 newMaxTextWidth = 0;

			for (size_t yy = 0; yy < m_grid.height(); ++yy)
			{
				newMaxTextWidth = Max(newMaxTextWidth, m_grid[yy][x].textWidth);
			}

			m_columnWidths[x] = Max(m_minColumnWidths[x], (newMaxTextWidth + m_style.textPaddingLR * 2));

			if (oldColumnWidth == m_columnWidths[x])
			{
				return *this;
			}

			m_columnAccumulatedWidths.rebuild(m_columnWidths, m_style.borderThickness);
		}

		return *this;
	}

	SimpleTable& SimpleTable::setText(const Point& index, const String& text)
	{
		return setText(index.y, index.x, text);
	}

	SimpleTable& SimpleTable::setText(const size_t y, const Array<String>& texts)
	{
		if (m_grid.width() != texts.size())
		{
			throw Error{ U"TableRenderer::setText(): Invalid number of texts ({})"_fmt(texts.size()) };
		}

		for (size_t x = 0; x < texts.size(); ++x)
		{
			setText(y, x, texts[x]);
		}

		return *this;
	}

	SimpleTable& SimpleTable::setTextAlignment(const size_t y, const size_t x, const int32 textAlignment)
	{
		if ((m_grid.width() <= x) || (m_grid.height() <= y))
		{
			throw Error{ U"TableRenderer::setTextAlignment(): Invalid index ({}, {})"_fmt(x, y) };
		}

		m_grid[y][x].textAlignment = static_cast<int8>(textAlignment);

		return *this;
	}

	SimpleTable& SimpleTable::setTextAlignment(const Point& index, const int32 textAlignment)
	{
		return setTextAlignment(index.y, index.x, textAlignment);
	}

	SimpleTable& SimpleTable::setRowTextAlignment(const size_t y, const int32 textAlignment)
	{
		if (m_grid.height() <= y)
		{
			throw Error{ U"TableRenderer::setRowTextAlignment(): Invalid index ({})"_fmt(y) };
		}

		for (size_t x = 0; x < m_grid.width(); ++x)
		{
			setTextAlignment(y, x, textAlignment);
		}

		return *this;
	}

	SimpleTable& SimpleTable::setBackgroundColor(const size_t y, const size_t x, const Optional<ColorF>& color)
	{
		if ((m_grid.width() <= x) || (m_grid.height() <= y))
		{
			throw Error{ U"TableRenderer::setBackgroundColor(): Invalid index ({}, {})"_fmt(x, y) };
		}

		m_grid[y][x].backgroundColor = color;

		return *this;
	}

	SimpleTable& SimpleTable::setBackgroundColor(const Point& index, const Optional<ColorF>& color)
	{
		return setBackgroundColor(index.y, index.x, color);
	}

	SimpleTable& SimpleTable::setRowBackgroundColor(const size_t y, const Optional<ColorF>& color)
	{
		if (m_grid.height() <= y)
		{
			throw Error{ U"TableRenderer::setRowBackgroundColor(): Invalid index ({})"_fmt(y) };
		}

		for (size_t x = 0; x < m_grid.width(); ++x)
		{
			m_grid[y][x].backgroundColor = color;
		}

		return *this;
	}

	SimpleTable& SimpleTable::setTextColor(const size_t y, const size_t x, const Optional<ColorF>& color)
	{
		if ((m_grid.width() <= x) || (m_grid.height() <= y))
		{
			throw Error{ U"TableRenderer::setTextColor(): Invalid index ({}, {})"_fmt(x, y) };
		}

		m_grid[y][x].textColor = color;

		return *this;
	}

	SimpleTable& SimpleTable::setTextColor(const Point& index, const Optional<ColorF>& color)
	{
		return setTextColor(index.y, index.x, color);
	}

	SimpleTable& SimpleTable::setRowTextColor(const size_t y, const Optional<ColorF>& color)
	{
		if (m_grid.height() <= y)
		{
			throw Error{ U"TableRenderer::setRowTextColor(): Invalid index ({})"_fmt(y) };
		}

		for (size_t x = 0; x < m_grid.width(); ++x)
		{
			setTextColor(y, x, color);
		}

		return *this;
	}

	SizeF SimpleTable::size() const noexcept
	{
		return{ width(), height() };
	}

	double SimpleTable::width() const noexcept
	{
		if (m_grid.isEmpty())
		{
			return 0.0;
		}

		return m_columnAccumulatedWidths.back();
	}

	double SimpleTable::height() const noexcept
	{
		if (m_grid.isEmpty())
		{
			return 0.0;
		}

		return ((m_grid.height() * m_style.cellHeight) + (m_grid.height() * m_style.borderThickness) + m_style.borderThickness);
	}

	RectF SimpleTable::region(const Vec2& tablePos) const noexcept
	{
		return{ tablePos, width(), height() };
	}

	RectF SimpleTable::rowRegion(const Vec2& tablePos, const size_t y) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return RectF::Empty();
		}

		const double xPos = tablePos.x;
		const double yPos = (tablePos.y + (m_style.cellHeight * y) + (m_style.borderThickness * (y + 1)));

		return{ xPos, yPos, width(), m_style.cellHeight };
	}

	RectF SimpleTable::columnRegion(const Vec2& tablePos, const size_t x) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return RectF::Empty();
		}

		const double xPos = (tablePos.x + m_columnAccumulatedWidths[x]);
		const double yPos = tablePos.y;
		const double cellWidth = (m_columnAccumulatedWidths.getWidth(x) - m_style.borderThickness);

		return{ xPos, yPos, cellWidth, height() };
	}

	RectF SimpleTable::cellRegion(const Vec2& tablePos, const size_t y, const size_t x) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return RectF::Empty();
		}

		const double xPos = (tablePos.x + m_columnAccumulatedWidths[x]);
		const double yPos = (tablePos.y + (m_style.cellHeight * y) + (m_style.borderThickness * (y + 1)));
		const double cellWidth = (m_columnAccumulatedWidths.getWidth(x) - m_style.borderThickness);

		return{ xPos, yPos, cellWidth, m_style.cellHeight };
	}

	RectF SimpleTable::cellRegion(const Vec2& tablePos, const Point& index) const noexcept
	{
		return cellRegion(tablePos, index.y, index.x);
	}

	Optional<int32> SimpleTable::rowIndex(const Vec2& tablePos, const Vec2& pos) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return none;
		}

		const RectF region{ this->region(tablePos) };

		if (not region.intersects(pos))
		{
			return none;
		}

		const double y = (pos.y - tablePos.y - m_style.borderThickness / 2);

		return Clamp(static_cast<int32>(y / (m_style.cellHeight + m_style.borderThickness)), 0, static_cast<int32>(m_grid.height() - 1));
	}

	Optional<int32> SimpleTable::columnIndex(const Vec2& tablePos, const Vec2& pos) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return none;
		}

		const RectF region{ this->region(tablePos) };

		if (not region.intersects(pos))
		{
			return none;
		}

		const double x = (pos.x - tablePos.x + m_style.borderThickness / 2);
		const int64 xi = (std::lower_bound(m_columnAccumulatedWidths.values.begin(), m_columnAccumulatedWidths.values.end(), x) - m_columnAccumulatedWidths.values.begin());

		return Clamp(static_cast<int32>(xi - 1), 0, static_cast<int32>(m_grid.width() - 1));
	}

	Optional<Point> SimpleTable::cellIndex(const Vec2& tablePos, const Vec2& pos) const noexcept
	{
		if (m_grid.isEmpty())
		{
			return none;
		}

		const RectF region{ this->region(tablePos) };

		if (not region.intersects(pos))
		{
			return none;
		}

		const double x = (pos.x - tablePos.x + m_style.borderThickness / 2);
		const double y = (pos.y - tablePos.y - m_style.borderThickness / 2);
		const int64 xi = (std::lower_bound(m_columnAccumulatedWidths.values.begin(), m_columnAccumulatedWidths.values.end(), x) - m_columnAccumulatedWidths.values.begin());

		const int32 column = Clamp(static_cast<int32>(xi - 1), 0, static_cast<int32>(m_grid.width() - 1));
		const int32 row = Clamp(static_cast<int32>(y / (m_style.cellHeight + m_style.borderThickness)), 0, static_cast<int32>(m_grid.height() - 1));

		return Point{ column, row };
	}

	void SimpleTable::draw(const Vec2& tablePos) const
	{
		if (m_grid.isEmpty())
		{
			return;
		}

		const RectF region{ this->region(tablePos) };

		if (m_style.backgroundColor)
		{
			region.draw(*m_style.backgroundColor);
		}

		for (size_t y = 0; y < m_grid.height(); ++y)
		{
			const double yPos = (tablePos.y + (m_style.cellHeight * y) + (m_style.borderThickness * (y + 1)));

			for (size_t x = 0; x < m_grid.width(); ++x)
			{
				const auto& item = m_grid[y][x];

				if (not item.backgroundColor)
				{
					continue;
				}

				const double xPos = (tablePos.x + m_columnAccumulatedWidths[x]);
				const double cellWidth = (m_columnAccumulatedWidths.getWidth(x) - m_style.borderThickness);
				const RectF cell{ xPos, yPos, cellWidth, m_style.cellHeight };
				cell.draw(*item.backgroundColor);
			}
		}

		if (m_style.hoveredRow || m_style.hoveredCell)
		{
			if (const auto activeCell = cellIndex(tablePos, Cursor::PosF()))
			{
				if (m_style.hoveredRow)
				{
					if (const auto color = m_style.hoveredRow(*activeCell))
					{
						rowRegion(tablePos, activeCell->y).draw(*color);
					}
				}

				if (m_style.hoveredCell)
				{
					if (const auto color = m_style.hoveredCell(*activeCell))
					{
						cellRegion(tablePos, *activeCell).draw(*color);
					}
				}
			}
		}

		if (m_style.hasHorizontalBorder)
		{
			for (size_t y = 1; y < m_grid.height(); ++y)
			{
				RectF{ tablePos + Vec2{ 0, ((m_style.cellHeight + m_style.borderThickness) * y) }, region.w, m_style.borderThickness }.draw(m_style.borderColor);
			}
		}

		if (m_style.hasOuterBorder)
		{
			for (size_t y : { size_t{ 0 }, m_grid.height() })
			{
				RectF{ tablePos + Vec2{ 0, ((m_style.cellHeight + m_style.borderThickness) * y) }, region.w, m_style.borderThickness }.draw(m_style.borderColor);
			}
		}

		if (m_style.hasVerticalBorder)
		{
			for (size_t x = 1; x < m_grid.width(); ++x)
			{
				RectF{ tablePos + Vec2{ (m_columnAccumulatedWidths[x] - m_style.borderThickness), 0 }, m_style.borderThickness, region.h }.draw(m_style.borderColor);
			}
		}

		if (m_style.hasOuterBorder)
		{
			for (size_t x : { size_t{ 0 }, m_grid.width() })
			{
				RectF{ tablePos + Vec2{ (m_columnAccumulatedWidths[x] - m_style.borderThickness), 0 }, m_style.borderThickness, region.h }.draw(m_style.borderColor);
			}
		}

		// 列ヘッダのセルを描画
		const bool hasColumnHeader = (m_style.columnHeaderFont || m_style.columnHeaderFontSize);

		if (hasColumnHeader)
		{
			const Font& font = ((m_style.columnHeaderFont) ? *m_style.columnHeaderFont : m_style.font);
			const double fontSize = ((m_style.columnHeaderFontSize) ? *m_style.columnHeaderFontSize : m_style.fontSize);
			const double yPos = (tablePos.y + m_style.borderThickness);

			for (size_t x = 0; x < m_grid.width(); ++x)
			{
				drawItem(0, x, tablePos, yPos, font, fontSize);
			}
		}

		// 行ヘッダのセルを描画
		const bool hasRowHeader = (m_style.rowHeaderFont || m_style.rowHeaderFontSize);

		if (hasRowHeader)
		{
			const Font& font = ((m_style.rowHeaderFont) ? *m_style.rowHeaderFont : m_style.font);
			const double fontSize = ((m_style.rowHeaderFontSize) ? *m_style.rowHeaderFontSize : m_style.fontSize);

			for (size_t y = 0; y < m_grid.height(); ++y)
			{
				const double yPos = (tablePos.y + (m_style.cellHeight * y) + (m_style.borderThickness * (y + 1)));

				drawItem(y, 0, tablePos, yPos, font, fontSize);
			}
		}

		// それ以外のセルを描画
		for (size_t y = hasColumnHeader; y < m_grid.height(); ++y)
		{
			const Font& font = m_style.font;
			const double fontSize = m_style.fontSize;
			const double yPos = (tablePos.y + (m_style.cellHeight * y) + (m_style.borderThickness * (y + 1)));

			for (size_t x = hasRowHeader; x < m_grid.width(); ++x)
			{
				drawItem(y, x, tablePos, yPos, font, fontSize);
			}
		}
	}

	void SimpleTable::drawItem(const size_t y, const size_t x, const Vec2& tablePos, const double yPos, const Font& font, const double fontSize) const
	{
		const auto& item = m_grid[y][x];
		const double xPos = (tablePos.x + m_columnAccumulatedWidths[x]);
		const double cellWidth = (m_columnAccumulatedWidths.getWidth(x) - m_style.borderThickness);
		const RectF cell{ xPos, yPos, cellWidth, m_style.cellHeight };
		const auto drawableText = font(item.text);
		const ColorF textColor = (item.textColor ? ColorF{ *item.textColor } : m_style.textColor);

		if (item.textAlignment < 0)
		{
			drawableText.draw(fontSize, Arg::leftCenter = (cell.leftCenter().movedBy(m_style.textPaddingLR, 0)), textColor);
		}
		else if (0 < item.textAlignment)
		{
			drawableText.draw(fontSize, Arg::rightCenter = (cell.rightCenter().movedBy(-m_style.textPaddingLR, 0)), textColor);
		}
		else
		{
			drawableText.drawAt(fontSize, cell.center().movedBy(0, 0), textColor);
		}
	}

	SimpleTable::AccumulatedWidths::AccumulatedWidths(const Array<double>& columnWidths, const double borderThickness)
	{
		rebuild(columnWidths, borderThickness);
	}

	void SimpleTable::AccumulatedWidths::rebuild(const Array<double>& columnWidths, const double borderThickness)
	{
		values.resize(columnWidths.size() + 1);

		values[0] = borderThickness;

		for (size_t i = 0; i < columnWidths.size(); ++i)
		{
			values[i + 1] = (values[i] + columnWidths[i] + borderThickness);
		}
	}

	double SimpleTable::AccumulatedWidths::getWidth(const size_t index) const
	{
		return (values[index + 1] - values[index]);
	}

	double SimpleTable::AccumulatedWidths::operator [](const size_t index) const
	{
		return values[index];
	}

	double SimpleTable::AccumulatedWidths::back() const
	{
		return values.back();
	}
}
