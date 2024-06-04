//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <crtdbg.h>
# include <future>
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/CSystem.hpp>
# include <Siv3D/Window/CWindow.hpp>
# include <Siv3D/Script/IScript.hpp>

void Main();

//        [THREAD #0]                        [THREAD #1]
//                            
// WinMain() {                 
//   f = std::async(MainThread)       || MainThread() {
//   **LOCK**                         ||   Siv3DEngine engine;
//                                    ||   engine->System->init();
//                                    <=   **LOCK**
//   engine->Window->init();          ||
//   **LOCK**                         =>
//                                    ||   engine->System->init2();
//                                    <=
//   while (!f._Is_ready()) {         ||   Main() { while(System::Update()) {} } // User code
//     PumMessages();                 ||
//                                    ||   engine::~Siv3DEngine() {
//     if (g_callWindowDestroy) {     ||     ...
//       engine->Window->destroy();   ||     g_callWindowDestroy = true
//       g_callWindowDestroy = false; ||     |
//     }                              ||     wait until (g_callWindowDestroy == false)
//                                    ||     ...  
//     Sleep(1);                      ||   }
//   }                                || }  
// }

namespace s3d
{
	namespace
	{
		std::condition_variable g_cv;
		std::mutex g_mutex;
		int g_initStep = 0;
		bool g_hasError = false;

		// デバッグ実行時には、Visual Studio に例外の情報を渡す
		const bool g_isDebuggerPresent = IsDebuggerPresent();
	}

	std::atomic<bool> g_callWindowDestroy{ false };

	static void PumpMessages()
	{
		for (int32 i = 0; i < 100; ++i)
		{
			MSG message = {};

			if (::PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&message);
				::DispatchMessageW(&message);
			}
			else
			{
				return;
			}
		}
	}

	static void TryMain()
	{
		String errorMessage;

		try
		{
			LOG_TRACE(U"Main() ---");

			Main();

			LOG_TRACE(U"--- Main()");
		}
		catch (const Error& error)
		{
			errorMessage = Format(error);
		}
		catch (const fmt::format_error& error)
		{
			errorMessage = U"Error occured in _fmt : {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::runtime_error& error)
		{
			errorMessage = U"[std::runtime_error] {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::out_of_range& error)
		{
			errorMessage = U"[std::out_of_range] {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::exception& error)
		{
			errorMessage = U"[std::exception] {}"_fmt(Unicode::Widen(error.what()));
		}

		if (errorMessage)
		{
			//static_cast<void>(Window::SetFullscreen(false)); // メッセージボックスを表示するためにフルスクリーンモードを解除

			errorMessage += U"\n\nFor more information, [Debug] -> [Windows] -> [Exception Settings] -> Tick the C++ Exceptions checkbox under the [Break When Thrown] heading.";

			FreestandingMessageBox::ShowError(errorMessage);
		}

		SIV3D_ENGINE(Script)->shutdown();
	}

	[[nodiscard]]
	constexpr StringView ExceptionToString(const DWORD code) noexcept
	{
		switch (code)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			return U"EXCEPTION_ACCESS_VIOLATION"_sv;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			return U"EXCEPTION_ARRAY_BOUNDS_EXCEEDED"_sv;
		case EXCEPTION_BREAKPOINT:
			return U"EXCEPTION_BREAKPOINT"_sv;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			return U"EXCEPTION_DATATYPE_MISALIGNMENT"_sv;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			return U"EXCEPTION_FLT_DENORMAL_OPERAND"_sv;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			return U"EXCEPTION_FLT_DIVIDE_BY_ZERO"_sv;
		case EXCEPTION_FLT_INEXACT_RESULT:
			return U"EXCEPTION_FLT_INEXACT_RESULT"_sv;
		case EXCEPTION_FLT_INVALID_OPERATION:
			return U"EXCEPTION_FLT_INVALID_OPERATION"_sv;
		case EXCEPTION_FLT_OVERFLOW:
			return U"EXCEPTION_FLT_OVERFLOW"_sv;
		case EXCEPTION_FLT_STACK_CHECK:
			return U"EXCEPTION_FLT_STACK_CHECK"_sv;
		case EXCEPTION_FLT_UNDERFLOW:
			return U"EXCEPTION_FLT_UNDERFLOW"_sv;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			return U"EXCEPTION_ILLEGAL_INSTRUCTION"_sv;
		case EXCEPTION_IN_PAGE_ERROR:
			return U"EXCEPTION_IN_PAGE_ERROR"_sv;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			return U"EXCEPTION_INT_DIVIDE_BY_ZERO"_sv;
		case EXCEPTION_INT_OVERFLOW:
			return U"EXCEPTION_INT_OVERFLOW"_sv;
		case EXCEPTION_INVALID_DISPOSITION:
			return U"EXCEPTION_INVALID_DISPOSITION"_sv;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			return U"EXCEPTION_NONCONTINUABLE_EXCEPTION"_sv;
		case EXCEPTION_PRIV_INSTRUCTION:
			return U"EXCEPTION_PRIV_INSTRUCTION"_sv;
		case EXCEPTION_SINGLE_STEP:
			return U"EXCEPTION_SINGLE_STEP"_sv;
		case EXCEPTION_STACK_OVERFLOW:
			return U"EXCEPTION_STACK_OVERFLOW"_sv;
		default:
			return U"Unknown Exception"_sv;
		}
	}

	static int ShowException(const DWORD code, struct _EXCEPTION_POINTERS*)
	{
		LOG_ERROR(U"🛑 Application terminated due to an exception `{}`"_fmt(ExceptionToString(code)));

		Window::Minimize();

		FreestandingMessageBox::ShowError(U"Application terminated due to an exception `{}`"_fmt(ExceptionToString(code)));

		return EXCEPTION_EXECUTE_HANDLER;
	}

	static void MainSEH()
	{
		__try
		{
			TryMain();
		}
		__except (ShowException(GetExceptionCode(), GetExceptionInformation()))
		{

		}
	}

	static void MainThread()
	{
		Siv3DEngine engine;

		std::unique_lock ul(g_mutex); // (1)--

		try
		{
			SIV3D_ENGINE(System)->init();
		}
		catch (const Error& error)
		{
			::OutputDebugStringW(Format(error, U'\n').toWstr().c_str());
			FreestandingMessageBox::ShowError(Format(error));
			g_hasError = true;

			ul.unlock(); // --(1)
			g_cv.notify_one();
			return;
		}

		g_initStep = 1;

		ul.unlock(); // --(1)
		g_cv.notify_one();
		ul.lock();

		g_cv.wait(ul, []() { return ((g_initStep == 2) || g_hasError); }); // (3)--

		if (g_hasError)
		{
			ul.unlock();
			g_cv.notify_one();
			return;
		}

		try
		{
			static_cast<CSystem*>(SIV3D_ENGINE(System))->init2();
		}
		catch (const Error& error)
		{
			::OutputDebugStringW(Format(error, U'\n').toWstr().c_str());
			FreestandingMessageBox::ShowError(Format(error));
			g_hasError = true;
			ul.unlock(); // --(3)
			g_cv.notify_one();
			return;
		}

		g_initStep = 3;

		ul.unlock(); // --(3)
		g_cv.notify_one();

		// (4b)--

		MainSEH();
	}

	static void SetWorkingDirectory()
	{
		if (System::IsRunningInVisualStudio())
		{
			return;
		}

		if (const FilePath workingDirectory = FileSystem::ParentPath(FileSystem::ModulePath()))
		{
			FileSystem::ChangeCurrentDirectory(workingDirectory);
		}
	}

	namespace detail::init
	{
		void InitCommandLines(int argc, char** argv);
	}
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	using namespace s3d;

	if constexpr (SIV3D_BUILD(DEBUG))
	{
		if (g_isDebuggerPresent &&
			(g_engineOptions.debugHeap == EngineOption::DebugHeap::Yes))
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
	}

	detail::init::InitCommandLines(__argc, __argv);

	if (::OleInitialize(nullptr) >= 0)
	{
		::CoUninitialize();
		::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	SetWorkingDirectory();

	std::unique_lock ul(g_mutex); // (0)--

	const std::future<void> f = std::async(std::launch::async, MainThread);

	g_cv.wait(ul, [&]() { return ((g_initStep == 1) || g_hasError); }); // --(0) (2)--

	if (g_hasError)
	{
		return -1;
	}

	try
	{
		SIV3D_ENGINE(Window)->init();
	}
	catch (const Error& error)
	{
		::OutputDebugStringW(Format(error, U'\n').toWstr().c_str());
		g_hasError = true;
		return -1;
	}

	g_initStep = 2;

	ul.unlock(); // --(2)
	g_cv.notify_one();
	ul.lock();

	g_cv.wait(ul, []() { return ((g_initStep == 3) || g_hasError); }); // (4a)--

	if (g_hasError)
	{
		while (!f._Is_ready())
		{
			if (g_callWindowDestroy)
			{
				if (auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window)))
				{
					pCWindow->destroy();
				}
				
				g_callWindowDestroy = false;
			}

			::Sleep(1);
		}

		return -1;
	}

	while (f.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
	{
		PumpMessages();

		if (g_callWindowDestroy)
		{
			if (auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window)))
			{
				pCWindow->destroy();
			}

			g_callWindowDestroy = false;
		}

		::timeBeginPeriod(1);
		{
			::Sleep(1);
		}
		::timeEndPeriod(1);
	}

	::CoUninitialize();
	::OleUninitialize();

	return 0;
}
