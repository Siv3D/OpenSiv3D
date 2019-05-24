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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/DLL.hpp>
# include <ShellScalingApi.h>
# include "HighDPI.hpp"

namespace s3d
{
	// 高 DPI ディスプレイで、フルスクリーン使用時に High DPI Aware を有効にしないと、
	// Windows の互換性マネージャーによって
	// HKEY_CURRENT_USER/Software/Microsoft/Windows NT/CurrentVersion/AppCompatFlags/Layers
	// に高 DPI が既定の設定として登録されてしまう。
	void SetHighDPIAwareness(const bool aware)
	{
		LOG_TRACE(U"SetHighDPIAwareness(aware = {})"_fmt(aware));

		if (HMODULE user32 = DLL::LoadSystemLibrary(L"user32.dll"))
		{
			decltype(SetThreadDpiAwarenessContext)* p_SetThreadDpiAwarenessContext = DLL::GetFunctionNoThrow(user32, "SetThreadDpiAwarenessContext");

			if (p_SetThreadDpiAwarenessContext)
			{
				p_SetThreadDpiAwarenessContext(aware ? DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 : DPI_AWARENESS_CONTEXT_UNAWARE);
				::FreeLibrary(user32);
				return;
			}

			::FreeLibrary(user32);
		}

		if (HINSTANCE shcore = DLL::LoadSystemLibrary(L"shcore.dll"))
		{
			decltype(SetProcessDpiAwareness)* p_SetProcessDpiAwareness = DLL::GetFunctionNoThrow(shcore, "SetProcessDpiAwareness");

			if (p_SetProcessDpiAwareness)
			{
				p_SetProcessDpiAwareness(aware ? PROCESS_PER_MONITOR_DPI_AWARE : PROCESS_DPI_UNAWARE);
				::FreeLibrary(shcore);
				return;
			}

			::FreeLibrary(shcore);
		}

		if (aware)
		{
			::SetProcessDPIAware();
		}
	}
}
