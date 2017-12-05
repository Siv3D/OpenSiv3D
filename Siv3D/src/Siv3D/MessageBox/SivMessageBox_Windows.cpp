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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/ConcurrentTask.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr int32 messageBoxStyleFlags[5] =
		{
			0,
			MB_ICONINFORMATION,
			MB_ICONWARNING,
			MB_ICONERROR,
			MB_ICONQUESTION,
		};

		static constexpr int32 messageBoxButtonFlags[5] =
		{
			MB_OK,
			MB_OKCANCEL,
			MB_YESNO,
		};
	}

	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			if (Window::GetState().fullScreen)
			{
				return MessageBoxSelection::None;
			}

			const int32 flag = detail::messageBoxStyleFlags[static_cast<int32>(style)]
							 | detail::messageBoxButtonFlags[static_cast<int32>(buttons)];

			const int32 result = CreateConcurrentTask([&, flag]()
			{
				return ::MessageBoxW(nullptr, text.toWstr().c_str(), title.toWstr().c_str(), flag);
			}).get();

			switch (result)
			{
			case IDOK:
				return MessageBoxSelection::OK;
			case IDCANCEL:
				return MessageBoxSelection::Cancel;
			case IDYES:
				return MessageBoxSelection::Yes;
			case IDNO:
				return MessageBoxSelection::No;
			default:
				return MessageBoxSelection::None;
			}
		}
	}
}

# endif
