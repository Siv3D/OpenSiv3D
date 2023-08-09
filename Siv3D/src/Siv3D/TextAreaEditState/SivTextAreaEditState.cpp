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

# include <Siv3D/TextAreaEditState.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	constexpr size_t TextAreaTabSize = 12;

	TextAreaEditState::TextAreaEditState(const String& defaultText)
		: text{ defaultText }
		, cursorPos{ defaultText.size() }
	{
		rebuildGlyphs();
	}

	TextAreaEditState::TextAreaEditState(String&& defaultText) noexcept
		: text{ std::move(defaultText) }
		, cursorPos{ text.size() }
	{
		rebuildGlyphs();
	}

	void TextAreaEditState::clear() noexcept
	{
		text.clear();
		cursorPos = 0;
		scrollY = 0.0;
		glyphs.clear();
		resetStopwatches();
	}

	void TextAreaEditState::resetStopwatches() noexcept
	{
		leftPressStopwatch.reset();
		rightPressStopwatch.reset();
		cursorStopwatch.restart();
		upPressStopwatch.reset();
		downPressStopwatch.reset();
	}

	void TextAreaEditState::rebuildGlyphs()
	{
		const Font& font = SimpleGUI::GetFont();
		const double spaceWidth = font.spaceWidth();

		glyphs = font.getGlyphs(text);

		for (auto& glyph : glyphs)
		{
			if (glyph.codePoint == U'\t')
			{
				glyph.xAdvance = (spaceWidth * TextAreaTabSize);
			}
			else if (IsControl(glyph.codePoint))
			{
				glyph.xAdvance = 0;
			}
		}
	}
}
