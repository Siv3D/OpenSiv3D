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

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Color.hpp"

namespace s3d
{
	enum class TextInputMode
	{
		DenyControl		= 0x00,

		AllowEnter		= 0x01,

		AllowTab		= 0x02,

		AllowBackSpace	= 0x04,

		AllowDelete		= 0x08,

		AllowEnterTab					= AllowEnter | AllowTab,

		AllowEnterBackSpace				= AllowEnter | AllowBackSpace,

		AllowEnterBackSpaceDelete		= AllowEnter | AllowBackSpace | AllowDelete,

		AllowTabBackSpace				= AllowTab | AllowBackSpace,

		AllowTabBackSpaceDelete			= AllowTab | AllowBackSpace | AllowDelete,

		AllowBackSpaceDelete			= AllowBackSpace | AllowDelete,

		AllowEnterTabBackSpace			= AllowEnter | AllowTab | AllowBackSpace,

		AllowEnterTabBackSpaceDelete	= AllowEnter | AllowTab | AllowBackSpace | AllowDelete,

		Default					= AllowEnterTabBackSpaceDelete,
	};

	namespace TextInput
	{
		[[nodiscard]] String GetRawInput();

		[[nodiscard]] size_t UpdateText(String& text, size_t cursorPos, TextInputMode mode = TextInputMode::Default);

		inline void UpdateText(String& text, TextInputMode mode = TextInputMode::Default)
		{
			(void)UpdateText(text, text.length(), mode);
		}
		
		[[nodiscard]] String GetEditingText();
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::TextInput
	{
		void DisableIME();

		[[nodiscard]] const Array<String>& GetCandidates();

		[[nodiscard]] std::pair<int32, int32> GetCursorIndex();

		void DrawCandidateWindow(const Font& font,
			const Vec2& basePos,
			const ColorF& boxColor = ColorF(1.0),
			const ColorF& selectedBackgroundColor = ColorF(0.55, 0.85, 1.0),
			const ColorF& frameColor = ColorF(0.75),
			const ColorF& textColor = ColorF(0.0));
	}

# endif
}
