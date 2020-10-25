﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/UserAction/IUSerAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Cursor/CCursor.hpp>
# include "WindowProc.hpp"
# include "CWindow.hpp"

namespace s3d
{
	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
			{
				LOG_TRACE(U"WM_CLOSE");

				SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::CloseButtonClicked);

				return 0; // WM_DESTROY を発生させない
			}
		case WM_SETFOCUS:
			{
				LOG_TRACE(U"WM_SETFOCUS");

				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onFocus(true);
				
				break;
			}
		case WM_KILLFOCUS:
			{
				LOG_TRACE(U"WM_KILLFOCUS");

				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onFocus(false);

				break;
			}
		case WM_KEYDOWN:
			{
				LOG_TRACE(U"WM_KEYDOWN");

				if (wParam == VK_ESCAPE) // Escape key
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
				}
				else if ((VK_BACK <= wParam) || (wParam == VK_CANCEL)) // Key
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown);
				}
				else if ((VK_LBUTTON <= wParam) && (wParam <= VK_XBUTTON2)) // Mouse button
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::MouseButtonDown);
				}

				break;
			}
		case WM_SYSCOMMAND:
			{
				LOG_VERBOSE(U"WM_SYSCOMMAND");

				switch (wParam & 0xffF0)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				case SC_KEYMENU:
					return 0;
				}

				break;
			}
		case WM_DISPLAYCHANGE:
			{
				LOG_TRACE(U"WM_DISPLAYCHANGE");
				
				return true;
			}
		case WM_DPICHANGED:
			{
				LOG_TRACE(U"WM_DPICHANGED");

				const uint32 newDPI = HIWORD(wParam);
				const RECT rect = *reinterpret_cast<const RECT*>(lParam);
				const Point pos(rect.left, rect.top);
				
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onDPIChange(newDPI, pos);

				return true;
			}
		case WM_SIZE:
			{
				LOG_TRACE(U"WM_SIZE");

				auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window));
				pCWindow->onBoundsUpdate();

				const bool minimized = (wParam == SIZE_MINIMIZED);
				const bool maximized = (wParam == SIZE_MAXIMIZED)
					|| (pCWindow->getState().maximized && (wParam != SIZE_RESTORED));
				pCWindow->onResize(minimized, maximized);

				const Size frameBufferSize(LOWORD(lParam), HIWORD(lParam));
				pCWindow->onFrameBufferResize(frameBufferSize);

				return 0;
			}
		case WM_MOVE:
			{
				LOG_VERBOSE(U"WM_MOVE");

				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onBoundsUpdate();

				return 0;
			}
		case WM_DESTROY:
			{
				LOG_TRACE(U"WM_DESTROY");

				::PostQuitMessage(0);

				return 0;
			}
		case WM_DEVICECHANGE:
			{
				LOG_TRACE(U"WM_DEVICECHANGE");

				/*
				if (CSystem* system = dynamic_cast<CSystem*>(Siv3DEngine::Get<ISiv3DSystem>()))
				{
					system->onDeviceChange();
				}
				*/

				break;
			}
        case WM_ERASEBKGND:
			{
				return true;
			}
		case WM_GETMINMAXINFO:
			{
				//LOG_VERBOSE(U"WM_GETMINMAXINFO");

				LPMINMAXINFO pMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onMinMaxInfo(pMinMaxInfo);

				break;
			}
		case WM_ENTERSIZEMOVE:
			{
				LOG_TRACE(U"WM_ENTERSIZEMOVE");
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onEnterSizeMove();

				break;
			}
		case WM_EXITSIZEMOVE:
			{
				LOG_TRACE(U"WM_EXITSIZEMOVE");
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onExitSizeMove();

				break;
			}
		case WM_INPUT:
		case WM_MOUSEMOVE:
			{
				if (auto p = dynamic_cast<CCursor*>(SIV3D_ENGINE(Cursor)))
				{
					p->handleMessage(message, wParam, lParam);
				}
				
				break;
			}
		case WM_SETCURSOR:
			{
				if (const uint32 hitTest = (lParam & 0xFFFF);
					(hitTest == HTCLIENT))
				{

					if (auto p = dynamic_cast<CCursor*>(SIV3D_ENGINE(Cursor)))
					{
						p->onSetCursor();
					}

					return 1;
				}

				break;
			}
		}

		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}
}
