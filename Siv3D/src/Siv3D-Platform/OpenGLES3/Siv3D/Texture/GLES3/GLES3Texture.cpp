//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GLES3Texture.hpp"

namespace s3d
{
	GLES3Texture::GLES3Texture(const Image& image, const TextureDesc desc)
	{
		constexpr TextureFormat format = TextureFormat::R8G8B8A8_Unorm;

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), image.width(), image.height(), 0,
						   format.GLFormat(), format.GLType(), image.data());
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}
		
		m_size			= image.size();
		m_format		= format;
		m_textureDesc	= desc;
		m_type			= TextureType::Default;
		m_initialized	= true;
	}
	
	GLES3Texture::GLES3Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		constexpr TextureFormat format = TextureFormat::R8G8B8A8_Unorm;

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), image.width(), image.height(), 0,
						   format.GLFormat(), format.GLType(), image.data());
			
			for (uint32 i = 0; i < mipmaps.size(); ++i)
			{
				const Image& mipmap = mipmaps[i];
				
				::glTexImage2D(GL_TEXTURE_2D, (i + 1), format.GLInternalFormat(), mipmap.width(), mipmap.height(), 0,
							   format.GLFormat(), format.GLType(), mipmap.data());
			}
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmaps.size()));
		}
		
		m_size			= image.size();
		m_format		= format;
		m_textureDesc	= desc;
		m_type			= TextureType::Default;
		m_initialized	= true;
	}

	GLES3Texture::~GLES3Texture()
	{
		// [resolved フレームバッファ] を破棄
		if (m_resolvedFrameBuffer)
		{
			::glDeleteFramebuffers(1, &m_resolvedFrameBuffer);
			m_resolvedFrameBuffer = 0;
		}

		// [マルチサンプルテクスチャ] を破棄
		if (m_multiSampledTexture)
		{
			::glDeleteTextures(1, &m_multiSampledTexture);
			m_multiSampledTexture = 0;
		}

		// [フレームバッファ] を破棄
		if (m_frameBuffer)
		{
			::glDeleteFramebuffers(1, &m_frameBuffer);
			m_frameBuffer = 0;
		}

		// [メインテクスチャ] を破棄
		if (m_texture)
		{
			::glDeleteTextures(1, &m_texture);
			m_texture = 0;
		}
	}

	bool GLES3Texture::isInitialized() const noexcept
	{
		return m_initialized;
	}

	GLuint GLES3Texture::getTexture() const noexcept
	{
		return m_texture;
	}

	GLuint GLES3Texture::getFrameBuffer() const noexcept
	{
		return m_frameBuffer;
	}

	Size GLES3Texture::getSize() const noexcept
	{
		return m_size;
	}

	TextureDesc GLES3Texture::getDesc() const noexcept
	{
		return m_textureDesc;
	}

	TextureFormat GLES3Texture::getFormat() const noexcept
	{
		return m_format;
	}
}
