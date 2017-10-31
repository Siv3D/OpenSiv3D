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

# include <crtdbg.h>
# include <future>
# include <Siv3D/Windows.hpp>
# include "Siv3DEngine.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		static void ShowException(const DWORD)
		{

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
				ShowException(ex->ExceptionRecord->ExceptionCode);
			}
		}
	}
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	using namespace s3d;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	::OutputDebugStringW(L"Siv3D for Windows\n");

	Siv3DEngine engine;

	// Running main thread
	{
		const std::future<void> f = std::async(std::launch::async, s3d::detail::MainThread);

		for (bool done = false; !done;)
		{
			done = f._Is_ready();

			::Sleep(1);
		}
	}

	return 0;
}

# endif
