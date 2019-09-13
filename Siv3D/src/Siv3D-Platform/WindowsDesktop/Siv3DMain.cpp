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

# include <crtdbg.h>
# include <future>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <Siv3DEngine.hpp>
# include <Script/IScript.hpp>
# include <System/ISystem.hpp>

void Main();

namespace cv
{
	void DeleteInitializationMutex();
}

namespace s3d
{
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

	constexpr StringView ExceptionToString(const DWORD code)
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

		EngineMessageBox::ShowError(U"Application terminated due to an exception `{}`"_fmt(ExceptionToString(code)));

		return EXCEPTION_EXECUTE_HANDLER;
	}

	static void TryMain()
	{
		try
		{
			Main();
		}
		catch (const Error& error)
		{
			static_cast<void>(Window::SetFullscreen(false)); // メッセージボックスを表示するためにフルスクリーンモードを解除
			EngineMessageBox::ShowError(U"Error:\n{}"_fmt(error.what()));
			return;
		}
	}

	static void MainThread()
	{
		if (!Siv3DEngine::Get<ISiv3DScript>()->init())
		{
			return;
		}

		__try
		{
			TryMain();
		}
		__except (ShowException(GetExceptionCode(), GetExceptionInformation()))
		{

		}

		Siv3DEngine::Get<ISiv3DScript>()->shutdown();
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SIMPLE_LOG(U"WinMain");
	SIMPLE_LOG(U"Siv3D for Windows");

	using namespace s3d;
	ScopeGuard onExit = [](){ cv::DeleteInitializationMutex(); };

	Siv3DEngine engine;

	try
	{
		Siv3DEngine::Get<ISiv3DSystem>()->init();
	}
	catch (const EngineError& error)
	{
		const String text = U"EngineError: {}"_fmt(error.what());
		LOG_ERROR(text);
		EngineMessageBox::Show(text);
		return -1;
	}

	LOG_TRACE(U"MainThread");
	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");
	{
		const std::future<void> f = std::async(std::launch::async, MainThread);

		while (!f._Is_ready())
		{
			PumpMessages();

			::Sleep(1);
		}
	}
	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");
	
	return 0;
}
