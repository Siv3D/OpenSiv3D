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

# include <array>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d::detail
{
	void DisableTouchFeedbackVisualization(HWND hWND, HMODULE user32)
	{
		LOG_VERBOSE(U"DisableTouchFeedbackVisualization()");

		if (decltype(SetWindowFeedbackSetting) * pSetWindowFeedbackSetting = DLL::GetFunctionNoThrow(user32, "SetWindowFeedbackSetting"))
		{
			static constexpr std::array<FEEDBACK_TYPE, 11> feedbackTypes =
			{
				FEEDBACK_TOUCH_CONTACTVISUALIZATION,
				FEEDBACK_PEN_BARRELVISUALIZATION,
				FEEDBACK_PEN_TAP,
				FEEDBACK_PEN_DOUBLETAP,
				FEEDBACK_PEN_PRESSANDHOLD,
				FEEDBACK_PEN_RIGHTTAP,
				FEEDBACK_TOUCH_TAP,
				FEEDBACK_TOUCH_DOUBLETAP,
				FEEDBACK_TOUCH_PRESSANDHOLD,
				FEEDBACK_TOUCH_RIGHTTAP,
				FEEDBACK_GESTURE_PRESSANDTAP,
			};

			for (const auto& feedbackType : feedbackTypes)
			{
				BOOL val = FALSE;
				pSetWindowFeedbackSetting(hWND, feedbackType, 0, sizeof(BOOL), &val);
			}
		}
	}
}
