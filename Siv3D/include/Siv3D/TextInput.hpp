//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Font.hpp"
# include "TextInputMode.hpp"

namespace s3d
{
	namespace TextInput
	{
		[[nodiscard]]
		String GetRawInput();

		[[nodiscard]]
		size_t UpdateText(String& text, size_t cursorPos, TextInputMode mode = TextInputMode::Default);

		void UpdateText(String& text, TextInputMode mode = TextInputMode::Default);

		[[nodiscard]]
		String GetEditingText();
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::TextInput
	{
		void DisableIME();

		[[nodiscard]]
		const Array<String>& GetCandidates();

		[[nodiscard]]
		std::pair<int32, int32> GetCursorIndex();

		void DrawCandidateWindow(const Font& font,
			const Vec2& basePos,
			const ColorF& boxColor = ColorF{ 1.0 },
			const ColorF& selectedBackgroundColor = ColorF{ 0.55, 0.85, 1.0 },
			const ColorF& frameColor = ColorF{ 0.75 },
			const ColorF& textColor = ColorF{ 0.0 });
	}

# endif
}
