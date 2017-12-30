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
# include <Siv3D/String.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>
# include "Siv3DEngine.hpp"
# include "System/ISystem.hpp"
# include "Script/IScript.hpp"

void Main();

namespace s3d::detail
{
	namespace init
	{
		void SetModulePath();
	}

	static void ShowException(const DWORD _code)
	{
		const String code = (_code == EXCEPTION_ACCESS_VIOLATION) ? U"EXCEPTION_ACCESS_VIOLATION"
			: Format(U"0x", Pad(ToHex(_code), { 8, U'0' }));

		LOG_ERROR(U"🛑 Application terminated due to an exception. Exception code: {0}"_fmt(code));
	}

	static void MainThread()
	{
		PEXCEPTION_POINTERS ex = nullptr;

		if (!Siv3DEngine::GetScript()->init())
		{
			return;
		}

		__try
		{
			Main();
		}
		__except (ex = GetExceptionInformation(), EXCEPTION_EXECUTE_HANDLER)
		{
			ShowException(ex->ExceptionRecord->ExceptionCode);
		}

		Siv3DEngine::GetScript()->shutdown();
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
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	using namespace s3d;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	detail::init::SetModulePath();
	{
		int nArgs = 0;

		LPWSTR* szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);

		if (nArgs >= 2 && FileSystem::Exists(Unicode::FromWString(szArglist[1])))
		{
			::SetCurrentDirectoryW(FileSystem::ParentPath(FileSystem::ModulePath()).toWstr().c_str());
		}

		::LocalFree(szArglist);
	}

	::OutputDebugStringW(L"Siv3D for Windows\n");

	Siv3DEngine engine;

	if (!Siv3DEngine::GetSystem()->init())
	{
		LOG_ERROR(U"🛑 Application cannot start due to an initialization error");

		return false;
	}

	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");

	// Running main thread
	{
		const std::future<void> f = std::async(std::launch::async, s3d::detail::MainThread);

		for (bool done = false; !done;)
		{
			done = f._Is_ready();

			for (int32 i = 0; !done && i < 100; ++i)
			{
				const auto result = detail::HandleMessage();

				if (result == detail::MessageResult::Quit)
				{
					done = true;
				}
				else if (result == detail::MessageResult::NoMessage)
				{
					break;
				}
			}

			if (done)
			{
				break;
			}

			::Sleep(1);
		}
	}

	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");

	return 0;
}

# endif
