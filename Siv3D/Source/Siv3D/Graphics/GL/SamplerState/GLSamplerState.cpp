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

# include <GL/glew.h>
# include "../../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "GLSamplerState.hpp"

namespace s3d
{
	GLSamplerState::GLSamplerState()
	{
	
	}
	
	void GLSamplerState::set(const SamplerState& state)
	{
		if (state == m_currentState)
		{
			return;
		}
	
		/*
		
		if (state.fillMode != m_currentState.fillMode)
		{
			::glPolygonMode(GL_FRONT_AND_BACK, state.fillMode == FillMode::Solid ? GL_FILL : GL_LINE);
		}

		if (state.cullMode != m_currentState.cullMode)
		{
			if (state.cullMode == CullMode::None)
			{
				::glDisable(GL_CULL_FACE);
			}
			else
			{
				::glEnable(GL_CULL_FACE);
				
				::glFrontFace(GL_CW);
				
				::glCullFace(state.cullMode == CullMode::Front ? GL_FRONT : GL_BACK);
			}
		}
		
		if (state.scissorEnable != m_currentState.scissorEnable)
		{
			if (state.scissorEnable)
			{
				::glEnable(GL_SCISSOR_TEST);
			}
			else
			{
				::glDisable(GL_SCISSOR_TEST);
			}
		}
		
		if (state.depthBias != m_currentState.depthBias)
		{
			if (state.depthBias)
			{
				::glEnable(GL_POLYGON_OFFSET_LINE);
				::glEnable(GL_POLYGON_OFFSET_FILL);
				::glPolygonOffset(0, state.depthBias);
			}
			else
			{
				::glDisable(GL_POLYGON_OFFSET_LINE);
				::glDisable(GL_POLYGON_OFFSET_FILL);
			}
		}
		
		 */
		 
		m_currentState = state;
	}
}

# endif
