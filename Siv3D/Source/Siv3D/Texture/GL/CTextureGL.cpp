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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CTexture_GL.hpp"
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	CTexture_GL::~CTexture_GL()
	{
		m_textures.destroy();
	}
	
	bool CTexture_GL::init()
	{
		const auto nullTexture = std::make_shared<Texture_GL>(Texture_GL::Null{});
		
		if (!nullTexture->isInitialized())
		{
			return false;
		}
		
		m_textures.setNullData(nullTexture);
		
		return true;
	}
	
	Texture::IDType CTexture_GL::createFromBackBuffer()
	{
		return Texture::NullHandleID;
	}
	
	Texture::IDType CTexture_GL::create(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return Texture::NullHandleID;
		}
		
		const auto texture = std::make_shared<Texture_GL>(image, desc);
		
		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}
		
		return m_textures.add(texture);
	}

	Texture::IDType CTexture_GL::create(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		if (!image)
		{
			return Texture::NullHandleID;
		}
		
		const auto texture = std::make_shared<Texture_GL>(image, mipmaps, desc);
		
		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}
		
		return m_textures.add(texture);
	}

	Texture::IDType CTexture_GL::createRT(const Size&, const uint32)
	{
		return Texture::NullHandleID;
	}
	
	void CTexture_GL::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}
	
	Size CTexture_GL::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}
	
	
	void CTexture_GL::setPS(const uint32 slot, const Texture::IDType handleID)
	{
		::glActiveTexture(GL_TEXTURE0 + slot);
		::glBindTexture(GL_TEXTURE_2D, m_textures[handleID]->getTexture());
	}
}

# endif
