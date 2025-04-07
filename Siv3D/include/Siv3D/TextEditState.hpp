﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Stopwatch.hpp"
# include "String.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct TextEditState
	{
		String text;

		size_t cursorPos = 0;

		bool active = false;

		bool textChanged = false;

		bool tabKey = false;

		bool enterKey = false;

		Stopwatch leftPressStopwatch, rightPressStopwatch, cursorStopwatch;

	# if SIV3D_PLATFORM(WEB)

		size_t lastCursorPos = 0;

	# endif

		SIV3D_NODISCARD_CXX20
		TextEditState() = default;

		SIV3D_NODISCARD_CXX20
		explicit TextEditState(const String& defaultText);
		
		SIV3D_NODISCARD_CXX20
		explicit TextEditState(String&& defaultText) noexcept;
		
		void clear() noexcept;

		void resetStopwatches() noexcept;
	};
}

# include "detail/TextEditState.ipp"
