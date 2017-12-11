﻿//-----------------------------------------------
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
# if defined(SIV3D_TARGET_LINUX)

# include <mutex>
# include "IMouse.hpp"
# include <Siv3D/PointVector.hpp>
# include "../Window/IWindow.hpp"

namespace s3d
{
	class CMouse_Linux : public ISiv3DMouse
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		std::array<InputState, MouseButtonCount> m_states;

		std::mutex m_scrollMutex;

		Vec2 m_scrollInternal{ 0.0, 0.0 };

		Vec2 m_scroll{ 0.0, 0.0 };

		static void OnScroll(WindowHandle, double h, double v);
		
	public:

		CMouse_Linux();

		~CMouse_Linux() override;

		bool init() override;

		void update() override;
		
		bool down(uint32 index) const override;
		
		bool pressed(uint32 index) const override;
		
		bool up(uint32 index) const override;

		MillisecondsF pressedDuration(uint32 index) const override;

		const Vec2& wheel() const override;

		void onScroll(double v, double h) override;
		
		void onMouseButtonUpdated(int32, bool) override {}
	};
}

# endif
