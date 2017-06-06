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
			return CharacterSet::FromUTF32(Siv3DEngine::GetTextInput()->getChars());
		}

		size_t UpdateText(String& text, size_t cursorPos, const TextInputMode mode)
		{
			const std::u32string chars = Siv3DEngine::GetTextInput()->getChars();

			if (chars.empty())
			{
				return cursorPos;
			}

		# if defined(SIV3D_TARGET_WINDOWS)

			const bool allowEnter = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowEnter);
			const bool allowTab = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowTab);
			const bool allowBackSpace = static_cast<uint32>(mode) & static_cast<uint32>(TextInputMode::AllowBackSpace);

			std::u32string textU32 = text.toUTF32();

			if (textU32.size() < cursorPos)
			{
				cursorPos = textU32.size();
			}

			for (auto const ch : chars)
			{
				if (ch == S3DCHAR('\r'))
				{
					if (allowEnter)
					{
						textU32.insert(textU32.begin() + cursorPos, S3DCHAR('\n'));
						++cursorPos;
					}
				}
				else if (ch == S3DCHAR('\b'))
				{
					if (allowBackSpace && 0 < cursorPos)
					{
						textU32.erase(textU32.begin() + cursorPos - 1);
						--cursorPos;
					}
				}
				else if (ch == S3DCHAR('\t'))
				{
					if (allowTab)
					{
						textU32.insert(textU32.begin() + cursorPos, S3DCHAR('\t'));
						++cursorPos;
					}
				}
				else if (!IsControl(ch))
				{
					textU32.insert(textU32.begin() + cursorPos, ch);
					++cursorPos;
				}
			}

			text = CharacterSet::FromUTF32(textU32);

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			if (text.size() < cursorPos)
			{
				cursorPos = text.size();
			}

			for (auto const ch : chars)
			{
				if (ch == S3DCHAR('\r'))
				{
					text.insert(text.begin() + cursorPos, S3DCHAR('\n'));
					++cursorPos;
				}
				else if (ch == S3DCHAR('\b'))
				{
					if (0 < cursorPos)
					{
						text.erase(text.begin() + cursorPos - 1);
						--cursorPos;
					}
				}
				else if (!IsControl(ch) || ch == S3DCHAR('\t'))
				{
					text.insert(text.begin() + cursorPos, ch);
					++cursorPos;
				}
			}
		
		# endif

			return cursorPos;
		}
		
		String GetMarkedText()
		{
			return Siv3DEngine::GetTextInput()->getMarkedText();
		}
	}
}
