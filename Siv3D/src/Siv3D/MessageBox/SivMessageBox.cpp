//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/Window.hpp>

namespace s3d
{
	namespace System
	{
		MessageBoxResult MessageBoxOK(const StringView text, const MessageBoxStyle style)
		{
			return MessageBoxOK(Window::GetTitle(), text, style);
		}

		MessageBoxResult MessageBoxOKCancel(const StringView text, const MessageBoxStyle style)
		{
			return MessageBoxOKCancel(Window::GetTitle(), text, style);
		}

		MessageBoxResult MessageBoxYesNo(const StringView text, const MessageBoxStyle style)
		{
			return MessageBoxYesNo(Window::GetTitle(), text, style);
		}
	}
}
