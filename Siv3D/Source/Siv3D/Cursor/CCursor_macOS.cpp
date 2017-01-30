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
# if defined(SIV3D_TARGET_MACOS)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CCursor_macOS.hpp"

namespace s3d
{
	CCursor_macOS::CCursor_macOS()
	{

	}

	CCursor_macOS::~CCursor_macOS()
	{

	}

	bool CCursor_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		update();

		m_previousScreenPos = m_screenPos;
		m_previousClientPos = m_screenPos;
		m_screenDelta.set(0, 0);
		m_clientDelta.set(0, 0);

		return true;
	}

	void CCursor_macOS::update()
	{

		m_previousScreenPos = m_screenPos;


		m_previousClientPos = m_clientPos;
	}

	const Point& CCursor_macOS::previousScreenPos() const
	{
		return m_previousScreenPos;
	}

	const Point& CCursor_macOS::screenPos() const
	{
		return m_screenPos;
	}

	const Point& CCursor_macOS::screenDelta() const
	{
		return m_screenDelta;
	}

	const Point& CCursor_macOS::previousClientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_macOS::clientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_macOS::clientDelta() const
	{
		return m_clientDelta;
	}
}

# endif
