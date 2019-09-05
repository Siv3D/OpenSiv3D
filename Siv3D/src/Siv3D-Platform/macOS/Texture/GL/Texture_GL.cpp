//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include "Texture_GL.hpp"

namespace s3d
{
	Texture_GL::Texture_GL(Null)
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			
			for (uint32 i = 0; i < 5; ++i)
			{
				const Image mipmap(16 >> i, 16 >> i, Palette::Yellow);
				::glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, mipmap.width(), mipmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap.data());
			}
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		}
		
		m_size = Size(16, 16);
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_textureDesc = TextureDesc::Mipped;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const TextureDesc desc)
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}
		
		m_size = image.size();
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_textureDesc = desc;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
			
			for (uint32 i = 0; i < mipmaps.size(); ++i)
			{
				const Image& mipmap = mipmaps[i];
				
				::glTexImage2D(GL_TEXTURE_2D, (i + 1), GL_RGBA, mipmap.width(), mipmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap.data());
			}
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmaps.size()));
		}
		
		m_size = image.size();
		m_format = TextureFormat::R8G8B8A8_Unorm;
		m_textureDesc = desc;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Dynamic&, const Size& size, const void* pData, const uint32, const TextureFormat format, const TextureDesc desc)
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}
		
		m_size = size;
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Dynamic;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Render&, const Size& size, const TextureFormat format, const TextureDesc desc)
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}

		// [フレームバッファ] を作成
		{
			::glGenFramebuffers(1, &m_frameBuffer);
			::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				return;
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		m_size = size;
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Render;
		m_initialized = true;
	}
	
	Texture_GL::~Texture_GL()
	{
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
	
	bool Texture_GL::isInitialized() const noexcept
	{
		return m_initialized;
	}
	
	GLuint Texture_GL::getTexture() const noexcept
	{
		return m_texture;
	}
	
	GLuint Texture_GL::getFrameBuffer() const noexcept
	{
		return m_frameBuffer;
	}
	
	Size Texture_GL::getSize() const noexcept
	{
		return m_size;
	}
	
	TextureDesc Texture_GL::getDesc() const noexcept
	{
		return m_textureDesc;
	}
	
	TextureFormat Texture_GL::getFormat() const noexcept
	{
		return m_format;
	}
	
	void Texture_GL::clearRT(const ColorF& color)
	{
		if (m_type != TextureType::Render)
		{
			return;
		}
		
		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		::glClearColor(
					   static_cast<float>(color.r),
					   static_cast<float>(color.g),
					   static_cast<float>(color.b),
					   static_cast<float>(color.a));
		::glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Texture_GL::readRT(Image& image)
	{
		if (m_type != TextureType::Render)
		{
			return;
		}
		
		if (const auto prop = GetTextureFormatProperty(m_format);
			(prop.num_channels != 4) || (prop.pixelSize != 4)) // RGBA 形式以外なら失敗
		{
			LOG_FAIL(U"Texture_D3D11::readRT(): This format is not supported");
			return;
		}
		
		image.resize(m_size);
		
		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	bool Texture_GL::fill(const ColorF& color, bool)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}
		
		Image image(m_size, color);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		return true;
	}
	
	bool Texture_GL::fillRegion(const ColorF& color, const Rect& rect)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}
		
		if ((rect.x + rect.w) > m_size.x || (rect.y + rect.h) > m_size.y)
		{
			return false;
		}
		
		Image image(rect.size, color);
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.w, rect.h, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		return true;
	}
	
	bool Texture_GL::fill(const void* src, [[maybe_unused]] const uint32 stride, [[maybe_unused]] const bool wait)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, src);
		
		return true;
	}
	
	bool Texture_GL::fillRegion(const void* src, const uint32 stride, const Rect& rect, [[maybe_unused]] const bool wait)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}
		
		Array<uint32> newData(rect.w * rect.h);
		
		if (newData.isEmpty())
		{
			return true;
		}
		
		uint32* pDst = newData.data();

		for (int32 y = rect.y; y < rect.y + rect.h; ++y)
		{
			const uint32* line = static_cast<const uint32*>(src) + (stride/sizeof(uint32)) * y;
			
			for (int32 x = rect.x; x < rect.x + rect.w; ++x)
			{
				*pDst++ = line[x];
			}
		}
		
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		
		::glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.w, rect.h, GL_RGBA, GL_UNSIGNED_BYTE, newData.data());
		
		return true;
	}
}
