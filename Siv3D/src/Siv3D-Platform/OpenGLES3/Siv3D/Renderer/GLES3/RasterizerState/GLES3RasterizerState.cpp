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

# include <Siv3D/EngineLog.hpp>
# include "GLES3RasterizerState.hpp"

namespace s3d
{
	GLES3RasterizerState::GLES3RasterizerState()
	{
		// ::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		::glDisable(GL_CULL_FACE);

		::glDisable(GL_SCISSOR_TEST);

		// ::glDisable(GL_POLYGON_OFFSET_LINE);
		::glDisable(GL_POLYGON_OFFSET_FILL);
	}

	void GLES3RasterizerState::set(const RasterizerState& state)
	{
		if (state == m_currentState)
		{
			return;
		}

		if (state.fillMode != m_currentState.fillMode)
		{
			LOG_ERROR(U"WireFrame rendendering is not supported because WebGL2 is lacking of glPolygonMode.");
			// ::glPolygonMode(GL_FRONT_AND_BACK, state.fillMode == FillMode::Solid ? GL_FILL : GL_LINE);
		}

		if (state.cullMode != m_currentState.cullMode)
		{
			if (state.cullMode == CullMode::Off)
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
				// ::glEnable(GL_POLYGON_OFFSET_LINE);
				::glEnable(GL_POLYGON_OFFSET_FILL);
				::glPolygonOffset(0, state.depthBias);
			}
			else
			{
				// ::glDisable(GL_POLYGON_OFFSET_LINE);
				::glDisable(GL_POLYGON_OFFSET_FILL);
			}
		}

		m_currentState = state;
	}
}
