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
# include "Optional.hpp"
# include "Graphics2D.hpp"

namespace s3d
{
	class RenderStateBlock2D
	{
	private:

		Optional<BlendState> m_oldBlendState;

		Optional<RasterizerState> m_oldRasterizerState;

		void clear()
		{
			m_oldBlendState.reset();

			m_oldRasterizerState.reset();
		}

	public:

		RenderStateBlock2D() = default;

		explicit RenderStateBlock2D(const BlendState& blendState)
			: m_oldBlendState(Graphics2D::GetBlendState())
		{
			Graphics2D::SetBlendState(blendState);
		}

		explicit RenderStateBlock2D(const RasterizerState& rasterizerState)
			: m_oldRasterizerState(Graphics2D::GetRasterizerState())
		{
			Graphics2D::SetRasterizerState(rasterizerState);
		}

		RenderStateBlock2D(const BlendState& blendState, const RasterizerState& rasterizerState)
			: m_oldBlendState(Graphics2D::GetBlendState())
			, m_oldRasterizerState(Graphics2D::GetRasterizerState())
		{
			Graphics2D::SetBlendState(blendState);

			Graphics2D::SetRasterizerState(rasterizerState);
		}

		RenderStateBlock2D(const RasterizerState& rasterizerState, const BlendState& blendState)
			: RenderStateBlock2D(blendState, rasterizerState) {}

		RenderStateBlock2D(RenderStateBlock2D&& block)
		{
			m_oldBlendState = block.m_oldBlendState;

			m_oldRasterizerState = block.m_oldRasterizerState;

			block.clear();
		}

		~RenderStateBlock2D()
		{
			m_oldBlendState.then(Graphics2D::SetBlendState);

			m_oldRasterizerState.then(Graphics2D::SetRasterizerState);
		}

		RenderStateBlock2D& operator =(RenderStateBlock2D&& block)
		{
			if (!m_oldBlendState && block.m_oldBlendState)
			{
				m_oldBlendState = block.m_oldBlendState;
			}

			if (!m_oldRasterizerState && block.m_oldRasterizerState)
			{
				m_oldRasterizerState = block.m_oldRasterizerState;
			}

			block.clear();

			return *this;
		}
	};
}
