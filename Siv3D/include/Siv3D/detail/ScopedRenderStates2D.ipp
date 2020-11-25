//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);
	}

	inline ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState)
		: m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
	}

	inline ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState)
		: m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics2D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	inline ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos)
	{
		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo s{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };

			m_oldSamplerStateInfos.push_back(s);

			Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}

	inline ScopedRenderStates2D::ScopedRenderStates2D(ScopedRenderStates2D&& other) noexcept
	{
		m_oldBlendState			= other.m_oldBlendState;
		m_oldRasterizerState	= other.m_oldRasterizerState;
		m_oldSamplerStateInfos	= std::move(other.m_oldSamplerStateInfos);
		other.clear();
	}

	inline ScopedRenderStates2D::~ScopedRenderStates2D()
	{
		m_oldBlendState.then(Graphics2D::Internal::SetBlendState);

		m_oldRasterizerState.then(Graphics2D::Internal::SetRasterizerState);

		for (const auto& oldSamplerStateInfo : m_oldSamplerStateInfos)
		{
			Graphics2D::Internal::SetSamplerState(oldSamplerStateInfo.shaderStage, oldSamplerStateInfo.slot, oldSamplerStateInfo.state);;
		}
	}

	//inline ScopedRenderStates2D& ScopedRenderStates2D::operator =(ScopedRenderStates2D&& other) noexcept
	//{
	//	if ((not m_oldBlendState) && other.m_oldBlendState)
	//	{
	//		m_oldBlendState = other.m_oldBlendState;
	//	}

	//	if ((not m_oldRasterizerState) && other.m_oldRasterizerState)
	//	{
	//		m_oldRasterizerState = other.m_oldRasterizerState;
	//	}
	//}

	inline void ScopedRenderStates2D::clear() noexcept
	{
		m_oldBlendState.reset();
		m_oldRasterizerState.reset();
		m_oldSamplerStateInfos.clear();
	}
}
