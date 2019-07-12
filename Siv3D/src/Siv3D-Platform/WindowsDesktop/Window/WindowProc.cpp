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

# include <Siv3DEngine.hpp>
# include <System/ISystem.hpp>
# include <Mouse/IMouse.hpp>
# include <Cursor/ICursor.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/EngineLog.hpp>
# include <TextInput/CTextInput.hpp>
# include <System/CSystem.hpp>
# include <Mouse/CMouse.hpp>
# include "CWindow.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr Rect ToRect(const RECT& rect)
		{
			return Rect(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
		}
	}

	LRESULT CALLBACK CWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (auto textinput = dynamic_cast<CTextInput*>(Siv3DEngine::Get<ISiv3DTextInput>()))
		{
			if (textinput->process(message, wParam, &lParam))
			{
				return 0;
			}
		}

		switch (message)
		{
		case WM_CLOSE:
			{
				LOG_TRACE(U"WM_CLOSE");

				Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::CloseButtonClicked);
				return 0; // WM_DESTROY を発生させない
			}
		case WM_KILLFOCUS:
			{
				Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::WindowDeactivated);
				break;
			}
		case WM_KEYDOWN:
			{
				if (wParam == VK_ESCAPE) // Escape key
				{
					Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
				}
				else if ((VK_BACK <= wParam) || (wParam == VK_CANCEL)) // Key
				{
					Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::AnyKeyDown);
				}
				else if ((VK_LBUTTON <= wParam) && (wParam <= VK_XBUTTON2)) // Mouse button
				{
					Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::MouseButtonDown);
				}

				break;
			}
		case WM_SYSKEYDOWN:
			{
				if ((wParam == VK_RETURN) && (lParam & (1 << 29))) // Alt + Enter
				{
					Siv3DEngine::Get<ISiv3DWindow>()->requestToggleFullscreen();
					return 0;
				}

				break;
			}
		case WM_SYSKEYUP:
			{
				Siv3DEngine::Get<ISiv3DCursor>()->onAltPressed();
				break;
			}
		case WM_MOUSEWHEEL:
			{
				Siv3DEngine::Get<ISiv3DMouse>()->onScroll(static_cast<short>(HIWORD(wParam)) / -double(WHEEL_DELTA), 0);
				return 0;
			}
		case WM_MOUSEHWHEEL:
			{
				Siv3DEngine::Get<ISiv3DMouse>()->onScroll(0, static_cast<short>(HIWORD(wParam)) / double(WHEEL_DELTA));
				return 0;
			}
		case WM_MOUSEMOVE:
			{
				Siv3DEngine::Get<ISiv3DCursor>()->onMouseMove(LOWORD(lParam), HIWORD(lParam));
				break;
			}
		case WM_PAINT:
			{
				LOG_TRACE(U"WM_PAINT");
				::ValidateRect(hWnd, nullptr);
				return 1;
			}
		case WM_GETMINMAXINFO:
			{
				const WindowState state = Siv3DEngine::Get<ISiv3DWindow>()->getWindowState();
				LPMINMAXINFO pMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);
				pMinMaxInfo->ptMinTrackSize.x = state.minimumSize.x + (state.frameSize.x * 2);
				pMinMaxInfo->ptMinTrackSize.y = state.minimumSize.y + (state.frameSize.y * 2) + +state.titleBarHeight;
				break;
			}
		case WM_SYSCOMMAND:
			{
				switch (wParam & 0xffF0)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				}

				break;
			}
		case WM_DISPLAYCHANGE:
			{
				LOG_TRACE(U"WM_DISPLAYCHANGE");

				return 1;
			}
		case WM_SIZE:
			{
				LOG_TRACE(U"WM_SIZE");

				RECT windowRect = {};
				::GetWindowRect(hWnd, &windowRect);
				Siv3DEngine::Get<ISiv3DWindow>()->updateWindowBounds(detail::ToRect(windowRect));

				RECT clientRect = {};
				::GetClientRect(hWnd, &clientRect);
				Siv3DEngine::Get<ISiv3DWindow>()->requestBackBufferResizing(
					Size(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top),
					(wParam == SIZE_MINIMIZED),
					(wParam == SIZE_MAXIMIZED));

				return 0;
			}
		case WM_MOVE:
			{
				RECT windowRect = {};
				::GetWindowRect(hWnd, &windowRect);
				Siv3DEngine::Get<ISiv3DWindow>()->updateWindowBounds(detail::ToRect(windowRect));

				//const int32 xPos = static_cast<int32>((short)LOWORD(lParam));
				//const int32 yPos = static_cast<int32>((short)HIWORD(lParam));
				//pApp->onWindowMoved(xPos, yPos);

				return 0;
			}
		case WM_DESTROY:
			{
				LOG_TRACE(U"WM_DESTROY");

				::PostQuitMessage(0);
				return 0;
			}
		case WM_CHAR:
			{
				LOG_TRACE(U"WM_CHAR");

				Siv3DEngine::Get<ISiv3DTextInput>()->pushChar(static_cast<uint32>(wParam));
				return 0;
			}
		case WM_UNICHAR:
			{
				LOG_TRACE(U"WM_UNICHAR");

				if (wParam == UNICODE_NOCHAR)
				{
					return true;
				}

				Siv3DEngine::Get<ISiv3DTextInput>()->pushChar(static_cast<uint32>(wParam));
				return 0;
			}
		case WM_DEVICECHANGE:
			{
				LOG_TRACE(U"WM_DEVICECHANGE");

				if (CSystem* system = dynamic_cast<CSystem*>(Siv3DEngine::Get<ISiv3DSystem>()))
				{
					system->onDeviceChange();
				}

				break;
			}
		case WM_TOUCH:
			{
				if (const size_t num_inputs = LOWORD(wParam))
				{
					Array<TOUCHINPUT> touchInputs(num_inputs);

					if (::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(lParam),
						static_cast<uint32>(touchInputs.size()), touchInputs.data(),
						sizeof(TOUCHINPUT)))
					{
						if (auto pMouse = dynamic_cast<CMouse*>(Siv3DEngine::Get<ISiv3DMouse>()))
						{
							pMouse->onTouchInput(touchInputs);
						}

						::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(lParam));

						return 0;
					}
				}

				break;
			}
		}

		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}
}
