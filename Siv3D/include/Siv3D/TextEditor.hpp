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
			const Vec2& initialPos,
			const ColorF& textColor,
			const ColorF& editingTextColor);

	public:

		TextEditor();

		void update(const Font& font,
			const Font& fontCabdidate,
			const Vec2& initialPos,
			const ColorF& textColor = ColorF(0.0),
			const ColorF& editingTextColor = ColorF(0.5));

		void setActive(bool active) noexcept;

		bool isActive() const noexcept;

		bool isLocked() const noexcept;
	};
}
