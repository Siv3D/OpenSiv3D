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

		void clear()
		{
			m_oldBlendState.reset();
		}

	public:

		RenderStateBlock2D() = default;

		RenderStateBlock2D(const BlendState& blendState)
			: m_oldBlendState(Graphics2D::GetBlendState())
		{
			Graphics2D::SetBlendState(blendState);
		}

		RenderStateBlock2D(RenderStateBlock2D&& block)
		{
			m_oldBlendState = block.m_oldBlendState;

			block.clear();
		}

		~RenderStateBlock2D()
		{
			m_oldBlendState.then(Graphics2D::SetBlendState);
		}

		RenderStateBlock2D& operator =(RenderStateBlock2D&& block)
		{
			if (!m_oldBlendState && block.m_oldBlendState)
			{
				m_oldBlendState = block.m_oldBlendState;
			}

			block.clear();

			return *this;
		}
	};
}
