//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// @brief アプリケーションを終了させるためのユーザアクションを表します。 | User Actions for Application Termination
	/// @remark System::SetTerminationTriggers(), System::GetTerminationTriggers(), System::GetUserActions() で使われる定数
	/// @remark | 演算子で複数の値を組み合わせることができます。
	/// @remark Constants used for System::SetTerminationTriggers(), System::GetTerminationTriggers(), and System::GetUserActions()
	namespace UserAction
	{
		enum Flag : uint32
		{
			/// @brief アプリケーションウィドウの閉じるボタンを押す操作です。 | The user has clicked the close button of the application window.
			CloseButtonClicked = 0b000001u,

			/// @brief エスケープキーを押す操作です。 | The user has pressed the escape key.
			EscapeKeyDown = 0b000010u,

			/// @brief ウィンドウを非アクティブにする操作です。 | The application window has been deactivated.
			WindowDeactivated = 0b000100u,

			/// @brief 何らかのキーを押す操作です。 | The user has pressed a key.
			AnyKeyDown = 0b001000u,

			/// @brief 何らかのマウスのボタンを押す操作です。 | The user has pressed a mouse button.
			MouseButtonDown = 0b010000u,

			/// @brief 何らかのキー、または何らかのマウスのボタンを押す操作です。 | The user has pressed a key or a mouse button.
			AnyKeyOrMouseDown = (AnyKeyDown | MouseButtonDown),

			/// @brief アプリケーションウィドウの閉じるボタンを押すか、エスケープキーを押す操作です。
			Default = (CloseButtonClicked | EscapeKeyDown),

			/// @brief アプリケーションを終了させるためのユーザアクションを設定しないことを示します。 | None.
			/// @remark System::SetTerminationTriggers() にこの定数のみを渡した場合、メインループから抜けるには break や return を使うか、System::Exit() を呼ぶ必要があります。
			/// @remark When this flag is set exclusively, you must explicitly call System::Exit() to exit the main loop.
			NoAction = 0u,
		};
	};
}
