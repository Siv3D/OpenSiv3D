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

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/UserAction/IUSerAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Cursor/CCursor.hpp>
# include <Siv3D/Mouse/CMouse.hpp>
# include <Siv3D/Keyboard/CKeyboard.hpp>
# include <Siv3D/Gamepad/CGamepad.hpp>
# include <Siv3D/System/CSystem.hpp>
# include <Siv3D/TextInput/CTextInput.hpp>
# include <Siv3D/DragDrop/CDragDrop.hpp>
# include "WindowProc.hpp"
# include "CWindow.hpp"
# include <Dbt.h>

namespace s3d
{
	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT message, const WPARAM wParam, LPARAM lParam)
	{
		// エンジンコンポーネントにアクセスできるか
		const bool engineActive = (SIV3D_ENGINE(Addon) != nullptr);

		if (engineActive)
		{
			if (auto textinput = static_cast<CTextInput*>(SIV3D_ENGINE(TextInput)))
			{
				if (textinput->process(message, wParam, &lParam))
				{
					return 0;
				}
			}

			if (auto dragDrop = static_cast<CDragDrop*>(SIV3D_ENGINE(DragDrop)))
			{
				dragDrop->process();
			}
		}

		switch (message)
		{
		case WM_CLOSE:
			{
				LOG_TRACE(U"WM_CLOSE");

				if (engineActive)
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::CloseButtonClicked);
				}

				return 0; // WM_DESTROY を発生させない
			}
		case WM_SETFOCUS:
			{
				LOG_VERBOSE(U"WM_SETFOCUS");

				if (engineActive)
				{
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onFocus(true);
				}

				break;
			}
		case WM_SYSKEYDOWN:
			{
				if (engineActive)
				{
					if ((wParam == VK_RETURN) && (lParam & (1 << 29))) // Alt + Enter
					{
						static_cast<CWindow*>(SIV3D_ENGINE(Window))->requestToggleFullscreen();
						return 0;
					}
				}

				break;
			}
		case WM_SYSKEYUP:
			{
				break;
			}
		case WM_KILLFOCUS:
			{
				LOG_VERBOSE(U"WM_KILLFOCUS");

				if (engineActive)
				{
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onFocus(false);
				}

				break;
			}
		case WM_KEYDOWN:
			{
				LOG_VERBOSE(U"WM_KEYDOWN");

				if (engineActive)
				{
					const bool repeatFlag = ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT);

					if (not repeatFlag)
					{
						static_cast<CKeyboard*>(SIV3D_ENGINE(Keyboard))->onKeyEvent(static_cast<uint8>(wParam), true, false);
					}
				}

				break;
			}
		case WM_KEYUP:
			{
				if (engineActive)
				{
					static_cast<CKeyboard*>(SIV3D_ENGINE(Keyboard))->onKeyEvent(static_cast<uint8>(wParam), false, true);
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

				if (engineActive)
				{
					const uint32 newDPI = HIWORD(wParam);
					const RECT rect = *reinterpret_cast<const RECT*>(lParam);
					const Point pos(rect.left, rect.top);

					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onDPIChange(newDPI, pos);

					return true;
				}
			}
		case WM_SIZE:
			{
				LOG_TRACE(U"WM_SIZE");

				if (engineActive)
				{
					auto pCWindow = static_cast<CWindow*>(SIV3D_ENGINE(Window));
					pCWindow->onBoundsUpdate();

					const bool minimized = (wParam == SIZE_MINIMIZED);
					const bool maximized = (wParam == SIZE_MAXIMIZED)
						|| (pCWindow->getState().maximized && (wParam != SIZE_RESTORED));
					pCWindow->onResize(minimized, maximized);

					const Size frameBufferSize(LOWORD(lParam), HIWORD(lParam));
					pCWindow->onFrameBufferResize(frameBufferSize);
				}

				return 0;
			}
		case WM_MOVE:
			{
				LOG_VERBOSE(U"WM_MOVE");

				if (engineActive)
				{
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onBoundsUpdate();
				}

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
				LOG_VERBOSE(U"WM_CHAR");

				if (engineActive)
				{
					if (auto p = SIV3D_ENGINE(TextInput))
					{
						p->pushChar(static_cast<uint32>(wParam));
					}
				}

				return 0;
			}
		case WM_UNICHAR:
			{
				LOG_VERBOSE(U"WM_UNICHAR");

				if (wParam == UNICODE_NOCHAR)
				{
					return true;
				}

				if (engineActive)
				{
					if (auto p = SIV3D_ENGINE(TextInput))
					{
						p->pushChar(static_cast<uint32>(wParam));
					}
				}

				return 0;
			}
		case WM_DEVICECHANGE:
			{
				LOG_VERBOSE(U"WM_DEVICECHANGE {:#X}"_fmt(wParam));

				if (engineActive)
				{
					if (wParam == DBT_DEVICEARRIVAL)
					{
						LOG_TRACE(U"WM_DEVICECHANGE (DBT_DEVICEARRIVAL)");

						if (CSystem* system = static_cast<CSystem*>(SIV3D_ENGINE(System)))
						{
							system->onDeviceChange();
						}

						const DEV_BROADCAST_HDR* dbh = reinterpret_cast<DEV_BROADCAST_HDR*>(lParam);

						if (dbh && (dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE))
						{
							static_cast<CGamepad*>(SIV3D_ENGINE(Gamepad))->detectJoystickConnection();
						}
					}
					else if (wParam == DBT_DEVICEREMOVECOMPLETE)
					{
						LOG_TRACE(U"WM_DEVICECHANGE (DBT_DEVICEREMOVECOMPLETE)");

						if (CSystem* system = static_cast<CSystem*>(SIV3D_ENGINE(System)))
						{
							system->onDeviceChange();
						}

						const DEV_BROADCAST_HDR* dbh = reinterpret_cast<DEV_BROADCAST_HDR*>(lParam);

						if (dbh && (dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE))
						{
							static_cast<CGamepad*>(SIV3D_ENGINE(Gamepad))->detectJoystickDisconnection();
						}
					}
				}

				break;
			}
		case WM_ERASEBKGND:
			{
				return true;
			}
		case WM_GETMINMAXINFO:
			{
				//LOG_VERBOSE(U"WM_GETMINMAXINFO");

				if (engineActive)
				{
					LPMINMAXINFO pMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onMinMaxInfo(pMinMaxInfo);
				}

				break;
			}
		case WM_ENTERSIZEMOVE:
			{
				LOG_TRACE(U"WM_ENTERSIZEMOVE");

				if (engineActive)
				{
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onEnterSizeMove();
				}

				break;
			}
		case WM_EXITSIZEMOVE:
			{
				LOG_TRACE(U"WM_EXITSIZEMOVE");

				if (engineActive)
				{
					static_cast<CWindow*>(SIV3D_ENGINE(Window))->onExitSizeMove();
				}

				break;
			}
		case WM_MOUSEMOVE:
			{
				if (engineActive)
				{
					if (auto p = static_cast<CCursor*>(SIV3D_ENGINE(Cursor)))
					{
						p->handleMessage(message, wParam, lParam);
					}
				}
				
				break;
			}
		case WM_SETCURSOR:
			{
				if (engineActive)
				{
					if (const uint32 hitTest = (lParam & 0xFFFF);
						(hitTest == HTCLIENT))
					{
						if (auto p = static_cast<CCursor*>(SIV3D_ENGINE(Cursor)))
						{
							p->onSetCursor();
						}

						return 1;
					}
				}

				break;
			}
		case WM_MOUSEWHEEL:
			{
				if (engineActive)
				{
					SIV3D_ENGINE(Mouse)->onScroll(0, static_cast<short>(HIWORD(wParam)) / -double(WHEEL_DELTA));
				}

				return 0;
			}
		case WM_MOUSEHWHEEL:
			{
				if (engineActive)
				{
					SIV3D_ENGINE(Mouse)->onScroll(static_cast<short>(HIWORD(wParam)) / double(WHEEL_DELTA), 0);
				}

				return 0;
			}
		case WM_TOUCH:
			{
				if (engineActive)
				{
					if (const size_t num_inputs = LOWORD(wParam))
					{
						Array<TOUCHINPUT> touchInputs(num_inputs);

						if (::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(lParam),
							static_cast<uint32>(touchInputs.size()), touchInputs.data(),
							sizeof(TOUCHINPUT)))
						{
							if (auto pMouse = static_cast<CMouse*>(SIV3D_ENGINE(Mouse)))
							{
								pMouse->onTouchInput(touchInputs);
							}

							::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(lParam));

							return 0;
						}
					}
				}

				break;
			}
		}

		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}
}
