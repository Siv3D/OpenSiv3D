//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "GLRasterizerState.hpp"

namespace s3d
{
	GLRasterizerState::GLRasterizerState()
	{
		::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		::glDisable(GL_CULL_FACE);
						
		::glDisable(GL_SCISSOR_TEST);
						
		::glDisable(GL_POLYGON_OFFSET_LINE);
		::glDisable(GL_POLYGON_OFFSET_FILL);
	}
	
	void GLRasterizerState::set(const RasterizerState& state)
	{
		if (state == m_currentState)
		{
			return;
		}
		
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
				
				// CullMode::Front = GL_BACK, CullMode::Back = GL_FRONT
				::glCullFace(state.cullMode == CullMode::Front ? GL_BACK : GL_FRONT);
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
		
		m_currentState = state;
	}
}
