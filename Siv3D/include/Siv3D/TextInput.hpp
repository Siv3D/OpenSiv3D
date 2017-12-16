﻿//-----------------------------------------------
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
# include "Array.hpp"

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

		AllowEnterTabBackSpace			= AllowEnter | AllowTab | AllowBackSpace,

		AllowEnterTabBackSpaceDelete	= AllowEnter | AllowTab | AllowBackSpace | AllowDelete,

		Default					= AllowEnterTabBackSpaceDelete,
	};

	namespace TextInput
	{
		String GetRawInput();

		size_t UpdateText(String& text, size_t cursorPos, TextInputMode mode = TextInputMode::Default);

		inline void UpdateText(String& text, TextInputMode mode = TextInputMode::Default)
		{
			UpdateText(text, text.length(), mode);
		}
		
		String GetEditingText();
	}

# if defined(SIV3D_TARGET_WINDOWS)

	namespace win::TextInput
	{
		void DisableIME();

		const Array<String>& GetCandidates();

		std::pair<int32, int32> GetCursorIndex();
	}

# endif
}
