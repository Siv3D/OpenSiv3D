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

# include <Siv3D/Common.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Mouse/CMouse.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"
# include <windowsx.h>

namespace s3d
{
	namespace detail
	{
		static void RegisterRawInput(HWND hWnd)
		{
			const RAWINPUTDEVICE rid =
			{
				.usUsagePage	= 0x01, // HID_USAGE_PAGE_GENERIC;
				.usUsage		= 0x02, // HID_USAGE_GENERIC_MOUSE;
				.dwFlags		= RIDEV_INPUTSINK,
				.hwndTarget		= hWnd,
			};

			LOG_TRACE(U"RegisterRawInputDevices()");
			if (!::RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
			{
				LOG_FAIL(U"❌ RegisterRawInputDevices() failed");
			}
		}

		static Point GetCursorClientPos(HWND hWnd)
		{
			POINT screenPos;
			::GetCursorPos(&screenPos);
			POINT clientPos = screenPos;
			::ScreenToClient(hWnd, &clientPos);
			return{ clientPos.x, clientPos.y };
		}
	}

	CCursor::CCursor()
		: m_clientPosBuffer{ { Time::GetMicrosec(), Point{ 0, 0 } } }
		, m_systemCursors{}
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");

		m_customCursors.clear();
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		//detail::RegisterRawInput(m_hWnd);

		{
			const Point lastClientPos = detail::GetCursorClientPos(m_hWnd);
			std::lock_guard lock{ m_clientPosBufferMutex };
			m_clientPosBuffer.emplace_back(Time::GetMicrosec(), lastClientPos);
		
			POINT screenPos;
			if (const auto touchPos = static_cast<CMouse*>(SIV3D_ENGINE(Mouse))->getPrimaryTouchPos())
			{
				screenPos.x = touchPos->x;
				screenPos.y = touchPos->y;
			}
			else
			{
				::GetCursorPos(&screenPos);
			}

			const double scaling = SIV3D_ENGINE(Window)->getState().scaling;
			const Vec2 clientPos = m_transformAllInv.transformPoint(lastClientPos / scaling);

			m_state.update(lastClientPos, clientPos, Point(screenPos.x, screenPos.y));
		}


		m_systemCursors[FromEnum(CursorStyle::Arrow)]			= ::LoadCursorW(nullptr, IDC_ARROW);
		m_systemCursors[FromEnum(CursorStyle::IBeam)]			= ::LoadCursorW(nullptr, IDC_IBEAM);
		m_systemCursors[FromEnum(CursorStyle::Cross)]			= ::LoadCursorW(nullptr, IDC_CROSS);
		m_systemCursors[FromEnum(CursorStyle::Hand)]			= ::LoadCursorW(nullptr, IDC_HAND);
		m_systemCursors[FromEnum(CursorStyle::NotAllowed)]		= ::LoadCursorW(nullptr, IDC_NO);
		m_systemCursors[FromEnum(CursorStyle::ResizeUpDown)]	= ::LoadCursorW(nullptr, IDC_SIZENS);
		m_systemCursors[FromEnum(CursorStyle::ResizeLeftRight)]	= ::LoadCursorW(nullptr, IDC_SIZEWE);
		m_systemCursors[FromEnum(CursorStyle::ResizeNWSE)]		= ::LoadCursorW(nullptr, IDC_SIZENWSE);
		m_systemCursors[FromEnum(CursorStyle::ResizeNESW)]		= ::LoadCursorW(nullptr, IDC_SIZENESW);
		m_systemCursors[FromEnum(CursorStyle::ResizeAll)]		= ::LoadCursorW(nullptr, IDC_SIZEALL);
		m_systemCursors[FromEnum(CursorStyle::Hidden)]			= nullptr;

		m_currentCursor		= m_systemCursors[FromEnum(CursorStyle::Arrow)];
		m_defaultCursor		= m_currentCursor;
		m_requestedCursor	= m_defaultCursor;
	}

	bool CCursor::update()
	{
		if (m_clippedToWindow)
		{
			confineCursor();
		}

		// [Siv3D ToDo] バッファを活用する
		{
			const uint64 time = Time::GetMicrosec();
	
			std::lock_guard lock{ m_clientPosBufferMutex };

			auto it = m_clientPosBuffer.begin();

			for (; it != (m_clientPosBuffer.end() - 1); ++it)
			{
				const uint64 elapsed = (time - it->first);

				if (elapsed < 1'000'000)
				{
					break;
				}
			}

			m_clientPosBuffer.erase(m_clientPosBuffer.begin(), it);
		}

		{
			auto [s, viewRect]	= SIV3D_ENGINE(Renderer)->getLetterboxComposition();
			m_transformScreen	= Mat3x2::Scale(s).translated(viewRect.pos);
			m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
			m_transformAllInv	= m_transformAll.inverse();
		}

		{
			POINT screenPos;
			if (const auto touchPos = static_cast<CMouse*>(SIV3D_ENGINE(Mouse))->getPrimaryTouchPos())
			{
				screenPos.x = touchPos->x;
				screenPos.y = touchPos->y;
			}
			else
			{
				::GetCursorPos(&screenPos);
			}
			
			Point lastClientRawPos;
			{
				POINT clientPos = screenPos;
				::ScreenToClient(m_hWnd, &clientPos);
				lastClientRawPos.set(clientPos.x, clientPos.y);
			}

			const double scaling = SIV3D_ENGINE(Window)->getState().scaling;
			const Vec2 clientPos = m_transformAllInv.transformPoint(lastClientRawPos);

			m_state.update(lastClientRawPos, clientPos, Point(screenPos.x, screenPos.y));
		}

		if (m_currentCursor != m_requestedCursor)
		{
			m_currentCursor = m_requestedCursor;
			::SetCursor(m_currentCursor);
		}
		else if (m_requestedCursor == nullptr)
		{
			// カーソルを必ず非表示にするための workaround
			::SetCursor(nullptr);
		}

		m_requestedCursor = m_defaultCursor;

		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}

	void CCursor::setPos(const Point pos)
	{
		const Vec2 rawPos = m_transformAll.transformPoint(pos);

		POINT point{ static_cast<int32>(rawPos.x), static_cast<int32>(rawPos.y) };
		::ClientToScreen(m_hWnd, &point);
		::SetCursorPos(point.x, point.y);

		update();
	}

	const Mat3x2& CCursor::getLocalTransform() const noexcept
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor::getCameraTransform() const noexcept
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor::getScreenTransform() const noexcept
	{
		return m_transformScreen;
	}

	void CCursor::setLocalTransform(const Mat3x2& matrix)
	{
		if (m_transformLocal == matrix)
		{
			return;
		}

		m_transformLocal	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	void CCursor::setCameraTransform(const Mat3x2& matrix)
	{
		if (m_transformCamera == matrix)
		{
			return;
		}

		m_transformCamera	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	void CCursor::setScreenTransform(const Mat3x2& matrix)
	{
		if (m_transformScreen == matrix)
		{
			return;
		}

		m_transformScreen	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	bool CCursor::isClippedToWindow() const noexcept
	{
		return m_clippedToWindow;
	}

	void CCursor::clipToWindow(const bool clip)
	{
		if (clip == m_clippedToWindow)
		{
			return;
		}

		m_clippedToWindow = clip;

		if (m_clippedToWindow)
		{
			confineCursor();
		}
		else
		{
			::ClipCursor(nullptr);
		}
	}

	void CCursor::requestStyle(const CursorStyle style)
	{
		m_requestedCursor = m_systemCursors[FromEnum(style)];
	}

	void CCursor::setDefaultStyle(const CursorStyle style)
	{
		m_defaultCursor = m_systemCursors[FromEnum(style)];
	}

	bool CCursor::registerCursor(const StringView name, const Image& image, const Point hotSpot)
	{
		if (m_customCursors.contains(name))
		{
			return false;
		}

		const BITMAPV5HEADER bi
		{
			.bV5Size		= sizeof(bi),
			.bV5Width		= image.width(),
			.bV5Height		= -image.height(),
			.bV5Planes		= 1,
			.bV5BitCount	= 32,
			.bV5Compression	= BI_BITFIELDS,
			.bV5RedMask		= 0x00FF0000,
			.bV5GreenMask	= 0x0000FF00,
			.bV5BlueMask	= 0x000000FF,
			.bV5AlphaMask	= 0xFF000000,
		};

		const HDC hdc = ::GetDC(nullptr);
		void* pData;
		HBITMAP hBitmap = ::CreateDIBSection(hdc, reinterpret_cast<const BITMAPINFO*>(&bi), DIB_RGB_COLORS, &pData, nullptr, 0);
		ScopeGuard sgBitmap = [&hBitmap]() { ::DeleteObject(hBitmap); };

		::ReleaseDC(nullptr, hdc);

		if (!hBitmap)
		{
			return false;
		}

		HBITMAP hMask = ::CreateBitmap(image.width(), image.height(), 1, 1, nullptr);
		ScopeGuard sgMask = [&hMask]() { ::DeleteObject(hMask); };

		if (!hMask)
		{
			return false;
		}

		{
			uint8* pDst = static_cast<uint8*>(pData);
			const Color* pSrc = image.data();

			for (size_t i = 0; i < image.num_pixels(); ++i)
			{
				pDst[0] = pSrc->b;
				pDst[1] = pSrc->g;
				pDst[2] = pSrc->r;
				pDst[3] = pSrc->a;

				pDst += 4;
				++pSrc;
			}
		}

		ICONINFO ii =
		{
			.fIcon		= FALSE, // Cursor
			.xHotspot	= Max<DWORD>(0, hotSpot.x),
			.yHotspot	= Max<DWORD>(0, hotSpot.y),
			.hbmMask	= hMask,
			.hbmColor	= hBitmap,
		};

		if (HICON hIcon = ::CreateIconIndirect(&ii))
		{
			m_customCursors.emplace(name, unique_resource{ hIcon, CursorDeleter });
			return true;
		}
		else
		{
			return false;
		}
	}

	void CCursor::requestStyle(const StringView name)
	{
		if (auto it = m_customCursors.find(name);
			it != m_customCursors.end())
		{
			m_requestedCursor = it->second.get();
		}
	}

	void CCursor::setCapture(const bool captured) noexcept
	{
		m_captured = captured;
	}

	bool CCursor::isCaptured() const noexcept
	{
		return m_captured;
	}

	void CCursor::handleMessage(const UINT message, const WPARAM, const LPARAM lParam)
	{
		Point newPosRaw;

		if (message == WM_MOUSEMOVE)
		{
			newPosRaw.set(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}
		//else if (message == WM_INPUT)
		//{
		//	RAWINPUT raw;
		//	UINT rawSize = sizeof(raw);

		//	if (UINT resultData = ::GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, &raw, &rawSize, sizeof(RAWINPUTHEADER)); 
		//		resultData == UINT(-1))
		//	{
		//		return;
		//	}

		//	if (raw.header.dwType != RIM_TYPEMOUSE)
		//	{
		//		return;
		//	}

		//	newPosRaw = detail::GetCursorClientPos(m_hWnd);
		//}
		else
		{
			return;
		}

		{
			std::lock_guard lock{ m_clientPosBufferMutex };

			if (m_clientPosBuffer.back().second != newPosRaw)
			{
				m_clientPosBuffer.emplace_back(Time::GetMicrosec(), newPosRaw);
			}
		}
	}

	void CCursor::onSetCursor()
	{
		::SetCursor(m_currentCursor);
	}

	void CCursor::confineCursor()
	{
		RECT clientRect;
		::GetClientRect(m_hWnd, &clientRect);

		POINT leftTop{ clientRect.left, clientRect.top };
		::ClientToScreen(m_hWnd, &leftTop);

		RECT clipRect{ leftTop.x, leftTop.y,
			leftTop.x + Max<int32>(clientRect.right - 1, 0),
			leftTop.y + Max<int32>(clientRect.bottom - 1, 0) };
		::ClipCursor(&clipRect);
	}
}
