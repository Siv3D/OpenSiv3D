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
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/HashTable.hpp>
# import <Metal/Metal.h>

namespace s3d
{
	class MetalRasterizerState
	{
	private:

		RasterizerState m_currentState = RasterizerState{ FillMode::Solid, CullMode::Off, false, false, 0 };

	public:

		MetalRasterizerState();

		void set(id<MTLRenderCommandEncoder> renderCommandEncoder, const RasterizerState& state);
	};
}
