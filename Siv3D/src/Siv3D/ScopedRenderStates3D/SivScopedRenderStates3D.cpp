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

# include <Siv3D/ScopedRenderStates3D.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState)
		: m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState)
		: m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo)
	{
		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos)
	{
		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState)
		: m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo)
		: m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ depthStencilState, samplerState } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ depthStencilState, samplerStateInfo } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ depthStencilState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfos } {}



	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerState& samplerState)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const SamplerState& samplerState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, depthStencilState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfos } {}



	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerState } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerState } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfo } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfo } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState, const BlendState& blendState)
		: ScopedRenderStates3D{ blendState, depthStencilState, samplerStateInfos } {}

	ScopedRenderStates3D::ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState)
		: ScopedRenderStates3D{ rasterizerState, depthStencilState, samplerStateInfos } {}


	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics3D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);
		Graphics3D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates3D::ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics3D::GetBlendState() }
		, m_oldRasterizerState{ Graphics3D::GetRasterizerState() }
		, m_oldDepthStencilState{ Graphics3D::GetDepthStencilState() }
	{
		Graphics3D::Internal::SetBlendState(blendState);
		Graphics3D::Internal::SetRasterizerState(rasterizerState);
		Graphics3D::Internal::SetDepthStencilState(depthStencilState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics3D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics3D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}



	ScopedRenderStates3D::ScopedRenderStates3D(ScopedRenderStates3D&& other) noexcept
	{
		m_oldBlendState = other.m_oldBlendState;
		m_oldRasterizerState = other.m_oldRasterizerState;
		m_oldDepthStencilState = other.m_oldDepthStencilState;
		m_oldSamplerStateInfos = std::move(other.m_oldSamplerStateInfos);
		other.clear();
	}

	ScopedRenderStates3D::~ScopedRenderStates3D()
	{
		m_oldBlendState.then(Graphics3D::Internal::SetBlendState);

		m_oldRasterizerState.then(Graphics3D::Internal::SetRasterizerState);

		m_oldDepthStencilState.then(Graphics3D::Internal::SetDepthStencilState);

		for (const auto& oldSamplerStateInfo : m_oldSamplerStateInfos)
		{
			Graphics3D::Internal::SetSamplerState(oldSamplerStateInfo.shaderStage, oldSamplerStateInfo.slot, oldSamplerStateInfo.state);;
		}
	}

	////ScopedRenderStates3D& ScopedRenderStates3D::operator =(ScopedRenderStates3D&& other) noexcept
	////{
	////	if ((not m_oldBlendState) && other.m_oldBlendState)
	////	{
	////		m_oldBlendState = other.m_oldBlendState;
	////	}

	////	if ((not m_oldRasterizerState) && other.m_oldRasterizerState)
	////	{
	////		m_oldRasterizerState = other.m_oldRasterizerState;
	////	}
	////}

	void ScopedRenderStates3D::clear() noexcept
	{
		m_oldBlendState.reset();
		m_oldRasterizerState.reset();
		m_oldDepthStencilState.reset();
		m_oldSamplerStateInfos.clear();
	}
}
