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

# include <Siv3D/Windows.hpp>
# include <Siv3D/System.hpp>
# include "../Siv3DEngine.hpp"
# include "../System/ISystem.hpp"
# include "CWindow_Windows.hpp"

namespace s3d
{
	namespace detail
	{
		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_CLOSE:
			{
				Siv3DEngine::GetSystem()->reportEvent(WindowEvent::CloseButton);

				return 0; // WM_DESTROY を発生させない
			}
			case WM_KILLFOCUS:
			{
				Siv3DEngine::GetSystem()->reportEvent(WindowEvent::Unfocus);

				break;
			}
			case WM_DESTROY:
			{
				::PostQuitMessage(0);

				return 0;
			}
			case WM_SIZING:
			{
				if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
				{
					window->requestResize();
				}

				break;
			}
			case WM_SIZE:
			{
				if (wParam == SIZE_RESTORED)
				{
					if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
					{
						window->requestResize();
					}

					return 0;
				}
				else if (wParam == SIZE_MINIMIZED)
				{
					break;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
					{
						window->requestResize();
					}

					return 0;
				}

				break;
			}
			case WM_KEYDOWN:
			{
				if (wParam == VK_ESCAPE)
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey | WindowEvent::EscapeKey);
				}
				else if (VK_BACK <= wParam) // マウス以外のキー入力
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey);
				}

				break;
			}
			case WM_MOUSEWHEEL:
			{
				//Siv3DEngine::GetMouse()->onScroll(static_cast<short>(HIWORD(wParam)) / -double(WHEEL_DELTA), 0);

				return 0;
			}
			case WM_MOUSEHWHEEL:
			{
				//Siv3DEngine::GetMouse()->onScroll(0, static_cast<short>(HIWORD(wParam)) / double(WHEEL_DELTA));

				return 0;
			}
			case WM_CHAR:
			{
				//Siv3DEngine::GetTextInput()->pushChar(static_cast<uint32>(wParam));

				return 0;
			}
			case WM_UNICHAR:
			{
				if (wParam == UNICODE_NOCHAR)
				{
					return true;
				}

				//Siv3DEngine::GetTextInput()->pushChar(static_cast<uint32>(wParam));

				return 0;
			}
			case WM_TOUCH:
			{
				//if (const size_t num_inputs = LOWORD(wParam))
				//{
				//	Array<TOUCHINPUT> touchInputs(num_inputs);

				//	if (::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(lParam),
				//		static_cast<uint32>(touchInputs.size()), touchInputs.data(),
				//		sizeof(TOUCHINPUT)))
				//	{
				//		if (auto pMouse = dynamic_cast<CMouse_Windows*>(Siv3DEngine::GetMouse()))
				//		{
				//			pMouse->onTouchInput(touchInputs);
				//		}

				//		::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(lParam));

				//		return 0;
				//	}
				//}

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
			}

			return ::DefWindowProcW(hWnd, message, wParam, lParam);
		}
	}
}

# endif
