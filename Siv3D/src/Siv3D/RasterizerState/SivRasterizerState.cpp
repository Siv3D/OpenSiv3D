//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/RasterizerState.hpp>

namespace s3d
{
	RasterizerState::RasterizerState(const Predefined predefined)
	{
		static const RasterizerState predefinedStates[14] =
		{
			RasterizerState{ FillMode::Solid,		CullMode::Back },	// SolidCullBack
			RasterizerState{ FillMode::Solid,		CullMode::Front },	// SolidCullFront
			RasterizerState{ FillMode::Solid,		CullMode::None },	// SolidCullNone
			RasterizerState{ FillMode::Wireframe,	CullMode::Back },	// WireframeCullBack
			RasterizerState{ FillMode::Wireframe,	CullMode::Front },	// WireframeCullFront
			RasterizerState{ FillMode::Wireframe,	CullMode::None },	// WireframeCullNone
			RasterizerState{ FillMode::Solid,		CullMode::None, false, true },	// AntialiasedLine3D
			RasterizerState{ FillMode::Solid,		CullMode::Back, true },			// SolidCullBackScissor
			RasterizerState{ FillMode::Solid,		CullMode::Front, true },		// SolidCullFrontScissor
			RasterizerState{ FillMode::Solid,		CullMode::None, true },			// SolidCullNoneScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Back, true },			// WireframeCullBackScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Front, true },		// WireframeCullFrontScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::None, true },			// WireframeCullNoneScissor
			RasterizerState{ FillMode::Solid,		CullMode::None, true, true },	// AntialiasedLine3DScissor
		};
		
		*this = predefinedStates[static_cast<size_t>(predefined)];
	}
}
