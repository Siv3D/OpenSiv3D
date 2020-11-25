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

# include "MetalRasterizerState.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr MTLTriangleFillMode FillModeTable[4] =
		{
			MTLTriangleFillMode(0),
			MTLTriangleFillMode(0),
			MTLTriangleFillModeLines,
			MTLTriangleFillModeFill,
		};
	
		constexpr MTLCullMode CullModeTable[4] =
		{
			MTLCullMode(0),
			MTLCullModeNone,
			MTLCullModeFront,
			MTLCullModeBack,
		};
	}

	MetalRasterizerState::MetalRasterizerState()
	{
		
	}

	void MetalRasterizerState::set(id<MTLRenderCommandEncoder> renderCommandEncoder, const RasterizerState& state)
	{
		if (state.fillMode != m_currentState.fillMode)
		{
			[renderCommandEncoder setTriangleFillMode:detail::FillModeTable[static_cast<uint32>(state.fillMode)]];
		}
		
		if (state.cullMode != m_currentState.cullMode)
		{
			[renderCommandEncoder setCullMode:detail::CullModeTable[static_cast<uint32>(state.cullMode)]];
		}

		if (state.scissorEnable != m_currentState.scissorEnable)
		{
			// [Siv3D Todo]
		}
		
		if (state.antialiasedLine3D != m_currentState.antialiasedLine3D)
		{
			// [Siv3D Todo]
		}
		
		if (state.depthBias != m_currentState.depthBias)
		{
			// [Siv3D Todo]
		}
		
		m_currentState = state;
	}
}
