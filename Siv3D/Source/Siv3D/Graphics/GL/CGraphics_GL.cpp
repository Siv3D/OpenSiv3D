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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../../Siv3DEngine.hpp"
# include "CGraphics_GL.hpp"

namespace s3d
{
	CGraphics_GL::CGraphics_GL()
	{

	}

	CGraphics_GL::~CGraphics_GL()
	{

	}

	bool CGraphics_GL::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();
		
		return true;
	}
	
	void CGraphics_GL::setClearColor(const ColorF& color)
	{
		m_clearColor = color;
	}
	
	bool CGraphics_GL::present()
	{
		glfwSwapBuffers(m_glfwWindow);
		
		return true;
	}
	
	void CGraphics_GL::clear()
	{
		glClearColor(
					 static_cast<float>(m_clearColor.r),
					 static_cast<float>(m_clearColor.g),
					 static_cast<float>(m_clearColor.b),
					 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

# endif
