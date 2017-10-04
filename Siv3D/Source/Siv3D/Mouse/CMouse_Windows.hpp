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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <array>
# include <mutex>
# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef WIN32_LEAN_AND_MEAN
#	define  WIN32_LEAN_AND_MEAN
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
# include "IMouse.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	class CMouse_Windows : public ISiv3DMouse
	{
	private:

		HWND m_hWnd = nullptr;

		std::array<InputState, MouseButtonCount> m_states;

		std::mutex m_scrollMutex;

		std::mutex m_touchMutex;

		Vec2 m_scrollInternal{ 0.0, 0.0 };

		Vec2 m_scroll{ 0.0, 0.0 };

		bool m_touchAvailable = false;

		Optional<DWORD> m_currentPrimaryTouchID;

		Optional<Point> m_primaryTouchPos; // Screen

	public:

		CMouse_Windows();

		~CMouse_Windows() override;

		bool init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		MillisecondsF pressedDuration(uint32 index) const override;
		
		const Vec2& wheel() const override;
		
		void onScroll(double v, double h) override;
		
		void onMouseButtonUpdated(int32, bool) override {}

		void onTouchInput(const Array<TOUCHINPUT>& touchInputs);

		Optional<Point> getPrimaryTouchPos();
	};
}

# endif
