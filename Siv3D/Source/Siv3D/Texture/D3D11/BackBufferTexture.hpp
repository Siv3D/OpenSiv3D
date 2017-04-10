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

# include "CTextureD3D11.hpp"
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class BackBufferTexture : public Texture
	{
	public:

		BackBufferTexture()
			: Texture(BackBuffer{}) {}

		void beginResize(CTextureD3D11* texture)
		{
			texture->beginResize(m_handle->getID());
		}

		bool endResize(CTextureD3D11* texture)
		{
			return texture->endResizeBackBuffer(m_handle->getID());
		}
	};
}

# endif
