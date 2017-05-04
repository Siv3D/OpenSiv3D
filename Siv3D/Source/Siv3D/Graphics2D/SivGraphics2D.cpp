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

# include <Siv3D/Graphics2D.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace Graphics2D
	{
		void SetBlendState(const BlendState& blendState)
		{
			Siv3DEngine::GetRenderer2D()->setBlendState(blendState);
		}

		BlendState GetBlendState()
		{
			return Siv3DEngine::GetRenderer2D()->getBlendState();
		}
	}
}
