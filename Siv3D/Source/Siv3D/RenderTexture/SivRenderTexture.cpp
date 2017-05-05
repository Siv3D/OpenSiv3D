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

# include <Siv3D/RenderTexture.hpp>
# include "../Siv3DEngine.hpp"
# include "../Texture/ITexture.hpp"

namespace s3d
{
	RenderTexture::RenderTexture(BackBuffer)
		: Texture(BackBuffer{})
	{

	}

	RenderTexture::RenderTexture()
		: Texture()
	{

	}

	RenderTexture::RenderTexture(const Size& size, uint32 multisampleCount)
		: Texture(Texture::Render{}, size, multisampleCount)
	{
	
	}

	void RenderTexture::clear(const ColorF& color)
	{
		Siv3DEngine::GetTexture()->clearRT(m_handle->getID(), color);
	}

	void RenderTexture::beginResize()
	{
		Siv3DEngine::GetTexture()->beginResize(m_handle->getID());
	}

	bool RenderTexture::endResize(const Size& size, const uint32 multisampleCount)
	{
		return Siv3DEngine::GetTexture()->endResizeRT(m_handle->getID(), size, multisampleCount);
	}
}
