//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <crtdbg.h>
# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include "Siv3DEngine.hpp"
# include "Logger/ILogger.hpp"
# include "System/ISystem.hpp"
# include "Window/IWindow.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		namespace init
		{
			void SetModulePath();
		}

		static void MainThread()
		{
			PEXCEPTION_POINTERS ex = nullptr;

			__try
			{
				Main();
			}
			__except (ex = GetExceptionInformation(), EXCEPTION_EXECUTE_HANDLER)
			{

			}
		}

		enum class MessageResult
		{
			Quit,

			Dispatched,

			NoMessage,
		};

		static MessageResult HandleMessage()
		{
			MSG message;

			if (::PeekMessageW(&message, 0, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					return MessageResult::Quit;
				}
				else
				{
					::TranslateMessage(&message);

					::DispatchMessageW(&message);
				}

				return MessageResult::Dispatched;
			}

			return MessageResult::NoMessage;
		}

		static void CloseWindow()
		{
			Siv3DEngine::GetWindow()->destroy();

			for (int wait = 0; wait < 16; ++wait)
			{
				if (HandleMessage() == MessageResult::Quit)
				{
					break;
				}
			}
		}
	}
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	using namespace s3d;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	detail::init::SetModulePath();
	{
		int nArgs = 0;

		LPWSTR* szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);

		if (nArgs >= 2 && FileSystem::Exists(szArglist[1]))
		{
			::SetCurrentDirectoryW(FileSystem::ParentPath(FileSystem::ModulePath()).c_str());
		}

		::LocalFree(szArglist);
	}

	::OutputDebugStringW(L"Siv3D for Windows\n");

	Siv3DEngine engine;

	if (!Siv3DEngine::GetSystem()->init())
	{
		return false;
	}

	const std::future<void> f = std::async(std::launch::async, detail::MainThread);

	for (;;)
	{
		bool quit = f._Is_ready();

		for (int32 i = 0; !quit && i < 100; ++i)
		{
			const auto result = detail::HandleMessage();

			if (result == detail::MessageResult::Quit)
			{
				quit = true;
			}
			else if (result == detail::MessageResult::NoMessage)
			{
				break;
			}
		}

		if (quit)
		{
			break;
		}

		::Sleep(1);
	}

	detail::CloseWindow();

	return 0;
}

# endif
