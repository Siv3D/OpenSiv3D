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

# include <Siv3D/BlendState.hpp>

namespace s3d
{
	BlendState::BlendState(const Predefined predefined)
	{
		static const BlendState predefinedStates[6] =
		{
			BlendState{ true },																// NonPremultiplied
			BlendState{ false },																// Opaque
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::Add },	// Additive
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::RevSubtract },	// Subtractive
			BlendState{ true, Blend::Zero,		Blend::SrcColor,	BlendOp::Add },	// Multiplicative
			BlendState{ true, Blend::DestColor,	Blend::SrcColor,	BlendOp::Add },	// Multiplicative2X
		};
		
		*this = predefinedStates[static_cast<size_t>(predefined)];
	}
}
