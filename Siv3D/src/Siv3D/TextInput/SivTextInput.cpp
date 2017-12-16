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

# include "../Siv3DEngine.hpp"
# include "ITextInput.hpp"
# include <Siv3D/TextInput.hpp>

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

	namespace win::TextInput
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
	}

# endif
}
