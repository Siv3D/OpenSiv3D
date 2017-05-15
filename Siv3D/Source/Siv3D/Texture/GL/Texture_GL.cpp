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
# include <Siv3D/Logger.hpp>

namespace s3d
{
	Texture_GL::Texture_GL(Null)
	{
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);

		for (uint32 i = 0; i < 5; ++i)
		{
			const Image mipmap(16 >> i, 16 >> i, Palette::Yellow);
			
			::glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, mipmap.width(), mipmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap.data());
		}
		
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		
		m_size = Size(16, 16);
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_isDynamic = false;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const TextureDesc desc)
	{
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		
		m_size = image.size();
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_isDynamic = false;
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
		
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmaps.size());
		
		m_size = image.size();
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_isDynamic = false;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Size& size, const void* pData, const uint32 stride, const TextureFormat format)
	{
		::glGenTextures(1, &m_texture);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
		
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		
		m_size = size;
		m_format = format;
		m_isDynamic = true;
		m_initialized = true;
	}
	
	Texture_GL::~Texture_GL()
	{
		if (m_texture)
		{
			::glDeleteTextures(1, &m_texture);
		}
	}
	
	bool Texture_GL::fill(const ColorF& color, bool wait)
	{
		if (!m_isDynamic)
		{
			return false;
		}
		
		Image image(m_size, color);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

		return true;
	}
	
	bool Texture_GL::fill(const void* src, uint32 stride, bool wait)
	{
		if (!m_isDynamic)
		{
			return false;
		}
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, src);
		
		return true;
	}
}

# endif
