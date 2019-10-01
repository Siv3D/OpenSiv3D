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

# include <Siv3D/ScopedRenderStates2D.hpp>

namespace s3d
{
	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState)
		: m_oldBlendState(Graphics2D::GetBlendState())
	{
		Graphics2D::Internal::SetBlendState(blendState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState)
		: m_oldRasterizerState(Graphics2D::GetRasterizerState())
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState)
		: m_oldSamplerState(Graphics2D::GetSamplerState())
	{
		Graphics2D::Internal::SetSamplerState(samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState)
		: m_oldBlendState(Graphics2D::GetBlendState())
		, m_oldRasterizerState(Graphics2D::GetRasterizerState())
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState)
		: m_oldBlendState(Graphics2D::GetBlendState())
		, m_oldSamplerState(Graphics2D::GetSamplerState())
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetSamplerState(samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D(blendState, rasterizerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldRasterizerState(Graphics2D::GetRasterizerState())
		, m_oldSamplerState(Graphics2D::GetSamplerState())
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
		Graphics2D::Internal::SetSamplerState(samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates2D(blendState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D(rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldBlendState(Graphics2D::GetBlendState())
		, m_oldRasterizerState(Graphics2D::GetRasterizerState())
		, m_oldSamplerState(Graphics2D::GetSamplerState())
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
		Graphics2D::Internal::SetSamplerState(samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D(blendState, rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState)
		: ScopedRenderStates2D(blendState, rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates2D(blendState, rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D(blendState, rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D(blendState, rasterizerState, samplerState) {}

	ScopedRenderStates2D::ScopedRenderStates2D(ScopedRenderStates2D&& block) noexcept
	{
		m_oldBlendState = block.m_oldBlendState;
		m_oldRasterizerState = block.m_oldRasterizerState;
		m_oldSamplerState = block.m_oldSamplerState;
		block.clear();
	}

	ScopedRenderStates2D::~ScopedRenderStates2D()
	{
		m_oldBlendState.then(Graphics2D::Internal::SetBlendState);

		m_oldRasterizerState.then(Graphics2D::Internal::SetRasterizerState);

		if (m_oldSamplerState)
		{
			Graphics2D::Internal::SetSamplerState(m_oldSamplerState.value());
		}
	}

	ScopedRenderStates2D& ScopedRenderStates2D::operator =(ScopedRenderStates2D&& block) noexcept
	{
		if (!m_oldBlendState && block.m_oldBlendState)
		{
			m_oldBlendState = block.m_oldBlendState;
		}

		if (!m_oldRasterizerState && block.m_oldRasterizerState)
		{
			m_oldRasterizerState = block.m_oldRasterizerState;
		}

		if (!m_oldSamplerState && block.m_oldSamplerState)
		{
			m_oldSamplerState = block.m_oldSamplerState;
		}

		block.clear();

		return *this;
	}

	void ScopedRenderStates2D::clear() noexcept
	{
		m_oldBlendState.reset();
		m_oldRasterizerState.reset();
		m_oldSamplerState.reset();
	}
}
