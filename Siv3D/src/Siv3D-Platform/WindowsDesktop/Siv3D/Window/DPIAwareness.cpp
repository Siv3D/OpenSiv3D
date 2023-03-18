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

# include <Siv3D/Windows/Windows.hpp>
# include <ShellScalingApi.h> // for SetProcessDpiAwareness()
# include <Siv3D/DLL.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d::detail
{
	void SetDPIAwareness(HMODULE user32)
	{
		LOG_SCOPED_TRACE(U"SetDPIAwareness()");

		// Windows 10 1703-
		{
			decltype(SetProcessDpiAwarenessContext)* p_SetProcessDpiAwarenessContext = DLL::GetFunctionNoThrow(user32, "SetProcessDpiAwarenessContext");

			if (p_SetProcessDpiAwarenessContext)
			{
				LOG_VERBOSE(U"SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)");
				p_SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
				return;
			}
		}

		// Windows 10 1607-
		{
			decltype(SetThreadDpiAwarenessContext)* p_SetThreadDpiAwarenessContext = DLL::GetFunctionNoThrow(user32, "SetThreadDpiAwarenessContext");

			if (p_SetThreadDpiAwarenessContext)
			{
				LOG_VERBOSE(U"SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)");
				p_SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
				
				LOG_VERBOSE(U"SetProcessDPIAware()");
				::SetProcessDPIAware();
				return;
			}
		}

		// Windows 8.1-
		if (LibraryHandle shcore = DLL::LoadSystemLibraryNoThrow(L"shcore.dll"))
		{
			decltype(SetProcessDpiAwareness)* p_SetProcessDpiAwareness = DLL::GetFunctionNoThrow(shcore, "SetProcessDpiAwareness");

			if (p_SetProcessDpiAwareness)
			{
				LOG_VERBOSE(U"SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE)");
				p_SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
				::FreeLibrary(shcore);
				return;
			}

			DLL::Unload(shcore);
		}

		// Windows Vista-
		LOG_VERBOSE(U"SetProcessDPIAware()");
		::SetProcessDPIAware();
	}
}
