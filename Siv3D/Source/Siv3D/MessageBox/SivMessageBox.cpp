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

# include <Siv3D/MessageBox.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
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
			const int32 flag = detail::messageBoxStyleFlags[static_cast<int32>(style)]
							 | detail::messageBoxButtonFlags[static_cast<int32>(buttons)];

			const int32 result = CreateConcurrentTask([&, flag]()
			{
				return ::MessageBoxW(nullptr, text.c_str(), title.c_str(), flag);
			}).get();

			return MessageBoxSelection::None;
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS)

namespace s3d
{
	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons);
	}
}

# elif defined(SIV3D_TARGET_LINUX)

namespace s3d
{
	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons);
	}
}

# endif
