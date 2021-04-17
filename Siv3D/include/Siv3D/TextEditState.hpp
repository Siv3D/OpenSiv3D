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
# include "Stopwatch.hpp"
# include "String.hpp"

namespace s3d
{
	struct TextEditState
	{
		String text;

		size_t cursorPos = 0;

		bool active = false;

		Stopwatch leftPressStopwatch, rightPressStopwatch, cursorStopwatch;

		SIV3D_NODISCARD_CXX20
		TextEditState() = default;

		SIV3D_NODISCARD_CXX20
		explicit TextEditState(const String& defaultText);
		
		SIV3D_NODISCARD_CXX20
		explicit TextEditState(String&& defaultText) noexcept;
		
		void clear() noexcept;
	};
}

# include "detail/TextEditState.ipp"
