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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../../Siv3DEngine.hpp"
# include "CTexture_D3D11.hpp"
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class BackBufferTexture : public RenderTexture
	{
	public:

		BackBufferTexture()
			: RenderTexture(BackBuffer{}) {}

		bool endResize()
		{
			return Siv3DEngine::GetTexture()->endResizeBackBuffer(m_handle->id());
		}
	};
}

# endif
