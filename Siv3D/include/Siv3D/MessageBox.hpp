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
# include "Window.hpp"

namespace s3d
{
	enum class MessageBoxStyle
	{
		Default,

		Info,

		Warning,

		Error,

		Question,
	};

	enum class MessageBoxButtons
	{
		/// <summary>
		/// [OK]
		/// </summary>
		OK,

		/// <summary>
		/// [OK] [キャンセル]
		/// </summary>
		OKCancel,

		/// <summary>
		/// [はい] [いいえ]
		/// </summary>
		YesNo,
	};

	enum class MessageBoxSelection
	{
		OK,

		Cancel,

		Yes,

		No,

		None
	};

	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons = MessageBoxButtons::OK);

		inline MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxButtons buttons = MessageBoxButtons::OK)
		{
			return ShowMessageBox(title, text, MessageBoxStyle::Default, buttons);
		}

		inline MessageBoxSelection ShowMessageBox(const String& text, MessageBoxStyle style, MessageBoxButtons buttons = MessageBoxButtons::OK)
		{
			return ShowMessageBox(Window::GetState().title, text, style, buttons);
		}

		inline MessageBoxSelection ShowMessageBox(const String& text, MessageBoxButtons buttons = MessageBoxButtons::OK)
		{
			return ShowMessageBox(text, MessageBoxStyle::Default, buttons);
		}
	}
}
