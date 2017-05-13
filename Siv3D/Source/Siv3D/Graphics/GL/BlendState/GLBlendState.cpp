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
# include "GLBlendState.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr uint32 blendOpTable[6] =
		{
			0,
			GL_FUNC_ADD,
			GL_FUNC_SUBTRACT,
			GL_FUNC_REVERSE_SUBTRACT,
			GL_MIN,
			GL_MAX
		};

		static constexpr uint32 blendTable[20] =
		{
			0,
			GL_ZERO,
			GL_ONE,
			GL_SRC_COLOR,
			GL_ONE_MINUS_SRC_COLOR,
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA,
			GL_DST_ALPHA,
			GL_ONE_MINUS_DST_ALPHA,
			GL_DST_COLOR,
			GL_ONE_MINUS_DST_COLOR,
			GL_SRC_ALPHA_SATURATE,
			0,
			0,
			GL_CONSTANT_COLOR,
			GL_ONE_MINUS_CONSTANT_COLOR,
			GL_SRC1_COLOR,
			GL_ONE_MINUS_SRC1_COLOR,
			GL_SRC1_ALPHA,
			GL_ONE_MINUS_SRC1_ALPHA,
		};
	}
	
	GLBlendState::GLBlendState()
	{
		::glEnable(GL_BLEND);
		
		::glBlendEquationSeparate(detail::blendOpTable[static_cast<size_t>(m_currentState.op)],
								  detail::blendOpTable[static_cast<size_t>(m_currentState.opAlpha)]);
		
		::glBlendFuncSeparate(detail::blendTable[static_cast<size_t>(m_currentState.src)],
							  detail::blendTable[static_cast<size_t>(m_currentState.dst)],
							  detail::blendTable[static_cast<size_t>(m_currentState.srcAlpha)],
							  detail::blendTable[static_cast<size_t>(m_currentState.dstAlpha)]);
	}
	
	void GLBlendState::set(const BlendState& state)
	{
		if (state == m_currentState)
		{
			return;
		}

		if (state.enable != m_currentState.enable)
		{
			if (state.enable)
			{
				::glEnable(GL_BLEND);
			}
			else
			{
				::glDisable(GL_BLEND);
			}
		}
		
		if (state.op != m_currentState.op || state.opAlpha != m_currentState.opAlpha)
		{
			::glBlendEquationSeparate(detail::blendOpTable[static_cast<size_t>(state.op)],
									  detail::blendOpTable[static_cast<size_t>(state.opAlpha)]);
		}
		
		if (state.src != m_currentState.src || state.dst != m_currentState.dst
			|| state.srcAlpha != m_currentState.srcAlpha || state.dstAlpha != m_currentState.dstAlpha)
		{
			::glBlendFuncSeparate(detail::blendTable[static_cast<size_t>(state.src)],
								  detail::blendTable[static_cast<size_t>(state.dst)],
								  detail::blendTable[static_cast<size_t>(state.srcAlpha)],
								  detail::blendTable[static_cast<size_t>(state.dstAlpha)]);
		}
		
		m_currentState = state;
	}
}

# endif
