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

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr int32 MessageBoxStyleFlags[5] =
		{
			0,
			MB_ICONINFORMATION,
			MB_ICONWARNING,
			MB_ICONERROR,
			MB_ICONQUESTION,
		};

		static MessageBoxResult ShowMessageBox(const StringView title, const StringView text, const MessageBoxStyle style, const int32 buttons)
		{
			if (Window::GetState().fullscreen)
			{
				return MessageBoxResult::Cancel;
			}

			const int32 flag = (MessageBoxStyleFlags[static_cast<int32>(style)] | buttons);

			const int32 result = Async([=]()
				{
					const HWND hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
					return ::MessageBoxW(hWnd, text.toWstr().c_str(), title.toWstr().c_str(), flag);
				}).get();

			switch (result)
			{
			case IDOK:
				return MessageBoxResult::OK;
			case IDCANCEL:
			default:
				return MessageBoxResult::Cancel;
			case IDYES:
				return MessageBoxResult::Yes;
			case IDNO:
				return MessageBoxResult::No;
			}
		}
	}

	namespace System
	{
		MessageBoxResult MessageBoxOK(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, MB_OK);
		}

		MessageBoxResult MessageBoxOKCancel(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, MB_OKCANCEL);
		}

		MessageBoxResult MessageBoxYesNo(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, MB_YESNO);
		}
	}
}
