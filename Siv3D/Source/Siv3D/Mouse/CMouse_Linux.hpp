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
# if defined(SIV3D_TARGET_LINUX)

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
		
	public:

		CMouse_Linux();

		~CMouse_Linux() override;

		bool init() override;

		void update() override;
		
		bool down(uint32 index) const override;
		
		bool pressed(uint32 index) const override;
		
		bool up(uint32 index) const override;

		MillisecondsF pressedDuration(uint32 index) const override;
	};
}

# endif
