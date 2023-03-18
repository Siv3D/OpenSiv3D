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

# include "MetalSamplerState.hpp"

namespace s3d
{
	namespace detail
	{
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

	id<MTLSamplerState> MetalSamplerState::get(const SamplerState& state)
	{
		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return nil;
			}
		}
		
		return it->second;
	}
}
