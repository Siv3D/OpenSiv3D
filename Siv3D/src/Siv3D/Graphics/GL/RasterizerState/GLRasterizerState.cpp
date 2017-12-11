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
# include "GLRasterizerState.hpp"

namespace s3d
{
	//namespace detail
	//{
	//	static constexpr uint32 blendOpTable[6] =
	//	{
	//		0,
	//		GL_FUNC_ADD,
	//		GL_FUNC_SUBTRACT,
	//		GL_FUNC_REVERSE_SUBTRACT,
	//		GL_MIN,
	//		GL_MAX
	//	};

	//	static constexpr uint32 blendTable[20] =
	//	{
	//		0,
	//		GL_ZERO,
	//		GL_ONE,
	//		GL_SRC_COLOR,
	//		GL_ONE_MINUS_SRC_COLOR,
	//		GL_SRC_ALPHA,
	//		GL_ONE_MINUS_SRC_ALPHA,
	//		GL_DST_ALPHA,
	//		GL_ONE_MINUS_DST_ALPHA,
	//		GL_DST_COLOR,
	//		GL_ONE_MINUS_DST_COLOR,
	//		GL_SRC_ALPHA_SATURATE,
	//		0,
	//		0,
	//		GL_CONSTANT_COLOR,
	//		GL_ONE_MINUS_CONSTANT_COLOR,
	//		GL_SRC1_COLOR,
	//		GL_ONE_MINUS_SRC1_COLOR,
	//		GL_SRC1_ALPHA,
	//		GL_ONE_MINUS_SRC1_ALPHA,
	//	};
	//}
	
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
		
		m_currentState = state;
	}
}

# endif
