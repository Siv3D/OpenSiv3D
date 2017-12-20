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
# include "Fwd.hpp"
# include "String.hpp"
# include "TextInput.hpp"
# include "Stopwatch.hpp"
# include "Color.hpp"

namespace s3d
{
	class TextEditor
	{
	private:

		String m_text;

		size_t m_cursorIndex = 0;

		Stopwatch m_leftPressStopwatch, m_rightPressStopwatch, m_cursorStopwatch;

		bool m_locked = false;
	
		bool m_active = true;
	
		void drawCursor(const Vec2& pos, double fontHeight, const ColorF& textColor) const;

		void drawText(const Font& font,
			const Font& fontCabdidate,
			const RectF& rect,
			const ColorF& textColor,
			const ColorF& editingTextColor);

	public:

		TextEditor(bool active = false);

		void update(const Font& font,
			const Font& fontCabdidate,
			const RectF& rect,
			const ColorF& textColor = ColorF(0.0),
			const ColorF& editingTextColor = ColorF(0.5),
			TextInputMode mode = TextInputMode::Default);

		void setActive(bool active) noexcept;

		bool isActive() const noexcept;

		bool isLocked() const noexcept;
	};
}
