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

# include <Siv3D/ScopedRenderStates2D.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState)
		: m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState)
		: m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics2D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo)
	{
		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos)
	{
		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
		, m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics2D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics2D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo)
		: m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetRasterizerState(rasterizerState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}


	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ rasterizerState, samplerState } {}


	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ rasterizerState, samplerStateInfo } {}


	ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, samplerStateInfos } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ rasterizerState, samplerStateInfos } {}


	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
		, m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
		, m_oldSamplerStateInfos{ { ShaderStage::Pixel, 0, Graphics2D::GetSamplerState(ShaderStage::Pixel, 0) } }
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, samplerState);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
		, m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);

		const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
		m_oldSamplerStateInfos.push_back(old);
		Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos)
		: m_oldBlendState{ Graphics2D::GetBlendState() }
		, m_oldRasterizerState{ Graphics2D::GetRasterizerState() }
	{
		Graphics2D::Internal::SetBlendState(blendState);
		Graphics2D::Internal::SetRasterizerState(rasterizerState);

		for (const auto& samplerStateInfo : samplerStateInfos)
		{
			const SamplerStateInfo old{ samplerStateInfo.shaderStage, samplerStateInfo.slot, Graphics2D::GetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot) };
			m_oldSamplerStateInfos.push_back(old);
			Graphics2D::Internal::SetSamplerState(samplerStateInfo.shaderStage, samplerStateInfo.slot, samplerStateInfo.state);
		}
	}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfos } {}


	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfos } {}


	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerState } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfo } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const RasterizerState& rasterizerState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfos } {}

	ScopedRenderStates2D::ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const BlendState& blendState)
		: ScopedRenderStates2D{ blendState, rasterizerState, samplerStateInfos } {}


	ScopedRenderStates2D::ScopedRenderStates2D(ScopedRenderStates2D&& other) noexcept
	{
		m_oldBlendState = other.m_oldBlendState;
		m_oldRasterizerState = other.m_oldRasterizerState;
		m_oldSamplerStateInfos = std::move(other.m_oldSamplerStateInfos);
		other.clear();
	}

	ScopedRenderStates2D::~ScopedRenderStates2D()
	{
		m_oldBlendState.then(Graphics2D::Internal::SetBlendState);

		m_oldRasterizerState.then(Graphics2D::Internal::SetRasterizerState);

		for (const auto& oldSamplerStateInfo : m_oldSamplerStateInfos)
		{
			Graphics2D::Internal::SetSamplerState(oldSamplerStateInfo.shaderStage, oldSamplerStateInfo.slot, oldSamplerStateInfo.state);;
		}
	}

	//ScopedRenderStates2D& ScopedRenderStates2D::operator =(ScopedRenderStates2D&& other) noexcept
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

	void ScopedRenderStates2D::clear() noexcept
	{
		m_oldBlendState.reset();
		m_oldRasterizerState.reset();
		m_oldSamplerStateInfos.clear();
	}
}
