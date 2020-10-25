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

# include "MetalSamplerState.hpp"

namespace s3d
{
	namespace detail
	{
	/*
		static constexpr D3D11_FILTER filterTable[8] =
		{
			D3D11_FILTER_MIN_MAG_MIP_POINT,
			D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
			D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
			D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		};
*/
		static constexpr MTLSamplerAddressMode AddressModeTable[4] =
		{
			MTLSamplerAddressModeRepeat,
			MTLSamplerAddressModeMirrorRepeat,
			MTLSamplerAddressModeClampToEdge,
			MTLSamplerAddressModeClampToBorderColor,
		};
	
		constexpr MTLSamplerBorderColor ToBorderColor(const Float4 color)
		{
			if (color == Float4(0, 0, 0, 1))
			{
				return MTLSamplerBorderColorOpaqueBlack;
			}
			else if (color == Float4(1, 1, 1, 1))
			{
				return MTLSamplerBorderColorOpaqueWhite;
			}
			else
			{
				return MTLSamplerBorderColorTransparentBlack;
			}
		}
	}

	MetalSamplerState::MetalSamplerState(id<MTLDevice> device)
		: m_device(device)
	{
		//m_currentVSStates.fill(NullState);
		//m_currentPSStates.fill(NullState);
	}
/*
	void MetalSamplerState::setVS(const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentVSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_context->VSSetSamplers(slot, 1, it->second.GetAddressOf());

		m_currentVSStates[slot] = state;
	}

	void MetalSamplerState::setPS(const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentPSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_context->PSSetSamplers(slot, 1, it->second.GetAddressOf());

		m_currentPSStates[slot] = state;
	}
*/
	void MetalSamplerState::setPS(id<MTLRenderCommandEncoder> renderCommandEncoder, const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		//if (state == m_currentPSStates[slot])
		//{
		//	return;
		//}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return;
			}
		}

		[renderCommandEncoder setFragmentSamplerState:it->second atIndex:slot];
	}

	MetalSamplerState::StateList::iterator MetalSamplerState::create(const SamplerState& state)
	{
		id<MTLSamplerState> samplerState = nil;
		
		@autoreleasepool {
			MTLSamplerDescriptor* samplerDesc = [MTLSamplerDescriptor new];
			{
				samplerDesc.minFilter = static_cast<MTLSamplerMinMagFilter>(state.min);
				samplerDesc.magFilter = static_cast<MTLSamplerMinMagFilter>(state.mag);
				samplerDesc.mipFilter = static_cast<MTLSamplerMipFilter>(FromEnum(state.mip) + 1);
				samplerDesc.maxAnisotropy = state.maxAnisotropy;
				samplerDesc.rAddressMode = detail::AddressModeTable[FromEnum(state.addressU)];
				samplerDesc.sAddressMode = detail::AddressModeTable[FromEnum(state.addressV)];
				samplerDesc.tAddressMode = detail::AddressModeTable[FromEnum(state.addressW)];
				samplerDesc.borderColor = detail::ToBorderColor(state.borderColor);
			}
			
			samplerState = [m_device newSamplerStateWithDescriptor:samplerDesc];
		}

		if (samplerState == nil)
		{
			return m_states.end();
		}

		if (m_states.size() >= 1024)
		{
			m_states.clear();
		}

		return m_states.emplace(state, samplerState).first;
	}
}
