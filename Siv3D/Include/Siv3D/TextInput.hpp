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

namespace s3d
{
	enum class TextInputMode
	{
		DenyControl				= 0x00,

		AllowEnter				= 0x01,

		AllowTab				= 0x02,

		AllowBackSpace			= 0x04,

		AllowEnterTab			= AllowEnter | AllowTab,

		AllowEnterBackSpace		= AllowEnter | AllowBackSpace,

		AllowTabBackSpace		= AllowTab | AllowBackSpace,

		AllowEnterTabBackSpace	= AllowEnter | AllowTab | AllowBackSpace,

		Default					= AllowEnterTabBackSpace,
	};

	namespace TextInput
	{
		String GetRawInput();

		size_t UpdateText(String& text, size_t cursorPos, TextInputMode mode = TextInputMode::Default);

		inline void UpdateText(String& text, TextInputMode mode = TextInputMode::Default)
		{
			UpdateText(text, text.num_codePoints(), mode);
		}
		
		String GetMarkedText();
	}
}
