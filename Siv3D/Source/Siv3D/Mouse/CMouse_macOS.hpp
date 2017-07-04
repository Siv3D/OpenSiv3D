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
# if defined(SIV3D_TARGET_MACOS)

# include <mutex>
# include "IMouse.hpp"
# include <Siv3D/PointVector.hpp>
# include "../Window/IWindow.hpp"

namespace s3d
{
	enum class MouseButtonState
	{
		Released,
		
		Pressed,
		
		Tapped,
	};
	
	class CMouse_macOS : public ISiv3DMouse
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		std::array<InputState, MouseButtonCount> m_states;
		
		std::mutex m_scrollMutex;
		
		std::mutex m_buttonMutex;
		
		Vec2 m_scrollInternal{ 0.0, 0.0 };

		Vec2 m_scroll{ 0.0, 0.0 };
		
		std::array<MouseButtonState, MouseButtonCount> m_buttonsInternal;
		
		static void OnScroll(WindowHandle, double h, double v);
		
		static void OnMouseButtonUpdated(WindowHandle, int button, int action, int mods);
		
	public:

		CMouse_macOS();

		~CMouse_macOS() override;

		bool init() override;

		void update() override;
		
		bool down(uint32 index) const override;
		
		bool pressed(uint32 index) const override;
		
		bool up(uint32 index) const override;

		MillisecondsF pressedDuration(uint32 index) const override;
		
		const Vec2& wheel() const override;
		
		void onScroll(double v, double h) override;
		
		void onMouseButtonUpdated(int32 index, bool pressed) override;
	};
}

# endif
