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

# include "../Siv3DEngine.hpp"
# include "ITextInput.hpp"
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/Indexed.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace TextInput
	{
		String GetRawInput()
		{
			return Siv3DEngine::GetTextInput()->getChars();
		}
		
		size_t UpdateText(String& text, size_t cursorPos, const TextInputMode mode)
		{
			const String chars = Siv3DEngine::GetTextInput()->getChars();
			
			if (chars.empty())
			{
				return cursorPos;
			}
			
			const bool allowEnter = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowEnter);
			const bool allowTab = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowTab);
			const bool allowBackSpace = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowBackSpace);
			const bool allowDelete = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowDelete);

			if (text.size() < cursorPos)
			{
				cursorPos = text.size();
			}
			
			for (auto const ch : chars)
			{
				if (ch == U'\r')
				{
					if (allowEnter)
					{
						text.insert(text.begin() + cursorPos, U'\n');
						++cursorPos;
					}
				}
				else if (ch == U'\b')
				{
					if (allowBackSpace && 0 < cursorPos)
					{
						text.erase(text.begin() + cursorPos - 1);
						--cursorPos;
					}
				}
				else if (ch == U'\t')
				{
					if (allowTab)
					{
						text.insert(text.begin() + cursorPos, U'\t');
						++cursorPos;
					}
				}
				else if (ch == char32(0x7F))
				{
					if (allowDelete && cursorPos < text.size())
					{
						text.erase(text.begin() + cursorPos);
					}
				}
				else if (!IsControl(ch))
				{
					text.insert(text.begin() + cursorPos, ch);
					++cursorPos;
				}
			}

			return cursorPos;
		}
		
		String GetEditingText()
		{
			return Siv3DEngine::GetTextInput()->getEditingText();
		}
	}

# if defined(SIV3D_TARGET_WINDOWS)

	namespace Windows::TextInput
	{
		void DisableIME()
		{
			Siv3DEngine::GetTextInput()->enableIME(false);
		}

		const Array<String>& GetCandidates()
		{
			return Siv3DEngine::GetTextInput()->getCandidates();
		}

		std::pair<int32, int32> GetCursorIndex()
		{
			return Siv3DEngine::GetTextInput()->getCursorIndex();
		}

		void DrawCandidateWindow(const Font& font,
			const Vec2& basePos,
			const ColorF& boxColor,
			const ColorF& selectedBackgroundColor,
			const ColorF& frameColor,
			const ColorF& textColor)
		{
			const double candidatesMargin = 4.0;
			const String editingText = s3d::TextInput::GetEditingText();
			const auto[editingCursorIndex, editingTargetlength] = GetCursorIndex();
			const bool hasEditingTarget = (editingTargetlength > 0);
			const String editingTargetText = editingText.substr(editingCursorIndex, editingTargetlength);
			const auto cadidates = GetCandidates();
			const double candidateItemHeight = font.height() + candidatesMargin;

			double boxWidth = 0.0;

			for (const auto& canditate : cadidates)
			{
				boxWidth = Max<double>(boxWidth, font(canditate).region().w);
			}

			const double leftOffset = hasEditingTarget ? font(U"1  ").region().w : 0.0;
			const Vec2 boxPos(Clamp(basePos.x - leftOffset, 7.0, s3d::Window::Width() - boxWidth - leftOffset - 12.0), basePos.y);

			boxWidth += leftOffset + 5;

			if (cadidates)
			{
				RectF(boxPos, boxWidth, candidateItemHeight * cadidates.size()).stretched(5, 0)
					.draw(boxColor).drawFrame(1, 0, frameColor);
			}

			for (auto[i, text] : Indexed(cadidates))
			{
				bool selected = false;

				if (editingTargetText == text)
				{
					selected = true;

					RectF(boxPos.x, boxPos.y + i * candidateItemHeight, boxWidth, candidateItemHeight)
						.stretched(5, 0).draw(selectedBackgroundColor);
				}

				if (text)
				{
					const Vec2 posNumber(boxPos.x, boxPos.y + i * candidateItemHeight + (candidatesMargin) / 2);
					const Vec2 posLabel(posNumber.x + leftOffset, posNumber.y);

					if (hasEditingTarget)
					{
						font(i + 1).draw(posNumber, textColor);
					}

					font(text).draw(posLabel, textColor);
				}
			}
		}
	}

# endif
}
