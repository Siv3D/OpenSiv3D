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

namespace s3d
{
	inline TextEditState::TextEditState(const String& defaultText)
		: text{ defaultText }
		, cursorPos{ defaultText.size() } {}

	inline TextEditState::TextEditState(String&& defaultText) noexcept
		: text{ std::move(defaultText) }
		, cursorPos{ defaultText.size() } {}

	inline void TextEditState::clear() noexcept
	{
		text.clear();
		cursorPos = 0;
		leftPressStopwatch.reset();
		rightPressStopwatch.reset();
		cursorStopwatch.reset();
	}
}
