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

namespace s3d
{
	/// <summary>
	/// アプリケーションを終了させるためのユーザアクション
	/// User Actions for Application Termination
	/// </summary>
	/// <remarks>
	/// System::SetTerminationTriggers(), System::GetTerminationTriggers(), System::GetUserActions() で使われる定数
	/// Constants used for System::SetTerminationTriggers(), System::GetTerminationTriggers(), and System::GetUserActions()
	/// </remarks>
	namespace UserAction
	{
		enum Flag : uint32
		{
			/// <summary>
			/// ユーザーがアプリケーションウィドウの閉じるボタンを押した。
			/// The user has clicked the close button of the application window.
			/// </summary>
			CloseButtonClicked	= 0b000001u,

			/// <summary>
			/// ユーザーがエスケープキーを押した
			/// The user has pressed the escape key.
			/// </summary>
			EscapeKeyDown		= 0b000010u,

			/// <summary>
			/// ユーザーがウィンドウを非アクティブにした
			/// The application window has been deactivated.
			/// </summary>
			WindowDeactivated	= 0b000100u,

			/// <summary>
			/// ユーザーが何らかのキーを押した
			/// The user has pressed a key.
			/// </summary>
			AnyKeyDown			= 0b001000u,

			/// <summary>
			/// ユーザーが何らかのマウスのボタンを押した
			/// The user has pressed a mouse button.
			/// </summary>
			MouseButtonDown		= 0b010000u,

			/// <summary>
			/// ユーザーが何らかのキーかマウスのボタンを押した
			/// The user has pressed a key or a mouse button.
			/// </summary>
			AnyKeyOrMouseDown	= (AnyKeyDown | MouseButtonDown),

			/// <summary>
			/// デフォルト設定 (CloseButtonClicked | EscapeKeyDown)
			/// Default (CloseButtonClicked | EscapeKeyDown)
			/// </summary>
			Default				= (CloseButtonClicked | EscapeKeyDown),

			/// <summary>
			/// 設定しない
			/// None
			/// </summary>
			/// <remarks>
			/// このフラグを単独で使用した場合、メインループを終了するために System::Exit() を明示的に呼ぶ必要があります。
			/// When this flag is set exclusively, you must explicitly call System::Exit() to exit the main loop.
			/// </remarks>
			None				= 0u,
		};

		static constexpr uint32 ExitFlag = 0x10000000u;
	};
}
