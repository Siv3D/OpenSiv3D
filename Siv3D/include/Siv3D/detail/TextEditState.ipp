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

namespace s3d
{
	inline TextEditState::TextEditState(const String& defaultText)
		: text{ defaultText }
		, cursorPos{ defaultText.size() } {}

	inline TextEditState::TextEditState(String&& defaultText) noexcept
		: text{ std::move(defaultText) }
		, cursorPos{ text.size() } {}

	inline void TextEditState::clear() noexcept
	{
		text.clear();
		cursorPos = 0;
		leftPressStopwatch.reset();
		rightPressStopwatch.reset();
		cursorStopwatch.reset();
	}

	inline void TextEditState::resetStopwatches() noexcept
	{
		leftPressStopwatch.reset();
		rightPressStopwatch.reset();
		cursorStopwatch.restart();
	}
}
