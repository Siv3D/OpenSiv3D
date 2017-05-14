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

# include "Texture_GL.hpp"

namespace s3d
{
	Texture_GL::Texture_GL(Null)
	{
		const Image image(16, 16, Palette::Yellow);
		
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		for (uint32 i = 0; i < 4; ++i)
		{
			const Image mipmap(8 >> i, 8 >> i, Palette::Yellow);
			
			::glTexImage2D(GL_TEXTURE_2D, (i + 1), GL_RGBA, mipmap.width(), mipmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap.data());
		}
		
		m_size = image.size();
		
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const TextureDesc desc)
	{
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		
		m_size = image.size();
		
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		for (uint32 i = 0; i < mipmaps.size(); ++i)
		{
			const Image& mipmap = mipmaps[i];
			
			::glTexImage2D(GL_TEXTURE_2D, (i + 1), GL_RGBA, mipmap.width(), mipmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap.data());
		}
		
		m_size = image.size();
		
		m_initialized = true;
	}
	
	Texture_GL::~Texture_GL()
	{
		if (m_texture)
		{
			::glDeleteTextures(1, &m_texture);
		}
	}
}

# endif
