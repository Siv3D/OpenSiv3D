//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GLES3DepthStencilState.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr GLenum GLFuncs[] =
		{
			0, GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL,
			GL_GEQUAL, GL_ALWAYS
		};

		[[nodiscard]]
		inline constexpr GLenum ToGLFunc(const DepthFunc func) noexcept
		{
			return GLFuncs[FromEnum(func)];
		}
	}

	GLES3DepthStencilState::GLES3DepthStencilState()
	{
		::glDisable(GL_DEPTH_TEST);

		::glDisable(GL_STENCIL_TEST);

		::glDepthMask(GL_FALSE);

		::glDepthFunc(GL_ALWAYS);
	}

	void GLES3DepthStencilState::set(const DepthStencilState& state)
	{
		if (state == m_currentState)
		{
			return;
		}

		if (state.depthEnable != m_currentState.depthEnable)
		{
			if (state.depthEnable)
			{
				::glEnable(GL_DEPTH_TEST);
			}
			else
			{
				::glDisable(GL_DEPTH_TEST);
			}
		}

		if (state.depthWriteEnable != m_currentState.depthWriteEnable)
		{
			if (state.depthWriteEnable)
			{
				::glDepthMask(GL_TRUE);
			}
			else
			{
				::glDepthMask(GL_FALSE);
			}
		}

		if (state.depthFunc != m_currentState.depthFunc)
		{
			::glDepthFunc(detail::ToGLFunc(state.depthFunc));
		}

		m_currentState = state;
	}
}
