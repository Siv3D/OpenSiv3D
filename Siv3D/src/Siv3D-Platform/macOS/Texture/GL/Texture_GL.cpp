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
		constexpr TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			
			for (uint32 i = 0; i < 5; ++i)
			{
				const Image mipmap(16 >> i, 16 >> i, Palette::Yellow);
				::glTexImage2D(GL_TEXTURE_2D, i, prop.GLInternalFormat, mipmap.width(), mipmap.height(), 0,
							   prop.GLFormat, prop.GLType, mipmap.data());
			}
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		}
		
		m_size = Size(16, 16);
		m_format = format;
		m_textureDesc = TextureDesc::Mipped;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const TextureDesc desc)
	{
		constexpr TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, image.width(), image.height(), 0,
						   prop.GLFormat, prop.GLType, image.data());
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}
		
		m_size = image.size();
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		constexpr TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, image.width(), image.height(), 0,
						   prop.GLFormat, prop.GLType, image.data());
			
			for (uint32 i = 0; i < mipmaps.size(); ++i)
			{
				const Image& mipmap = mipmaps[i];
				
				::glTexImage2D(GL_TEXTURE_2D, (i + 1), prop.GLInternalFormat, mipmap.width(), mipmap.height(), 0,
							   prop.GLFormat, prop.GLType, mipmap.data());
			}
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmaps.size()));
		}
		
		m_size = image.size();
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Normal;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(Dynamic, const Size& size, const void* pData, const uint32, const TextureFormat format, const TextureDesc desc)
	{
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			if (format == TextureFormat::R8G8B8A8_Unorm
				|| format == TextureFormat::R8G8B8A8_Unorm_SRGB)
			{
				::glGenTextures(1, &m_texture);
				::glBindTexture(GL_TEXTURE_2D, m_texture);
				::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, size.x, size.y, 0,
							   prop.GLFormat, prop.GLType, pData);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
			else
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in DynamicTexture"_fmt(ToString(format)));
				return;
			}
		}
		
		m_size = size;
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Dynamic;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(Render, const Size& size, const TextureFormat format, const TextureDesc desc)
	{
		// サイズをチェック
		if (!InRange(size.x, 1, Image::MaxWidth) || !InRange(size.y, 1, Image::MaxHeight))
		{
			return;
		}
		
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			if (format == TextureFormat::R8G8B8A8_Unorm
				|| format == TextureFormat::R8G8B8A8_Unorm_SRGB
				|| format == TextureFormat::R16G16_Float
				|| format == TextureFormat::R32_Float
				|| format == TextureFormat::R10G10B10A2_Unorm
				|| format == TextureFormat::R11G11B10_UFloat
				|| format == TextureFormat::R16G16B16A16_Float
				|| format == TextureFormat::R32G32_Float
				|| format == TextureFormat::R32G32B32A32_Float)
			{
				::glGenTextures(1, &m_texture);
				::glBindTexture(GL_TEXTURE_2D, m_texture);
				::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, size.x, size.y, 0,
							   prop.GLFormat, prop.GLType, nullptr);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
			else
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture"_fmt(ToString(format)));
				return;
			}
		}
		
		// [メインテクスチャ・フレームバッファ] を作成
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
	
	Texture_GL::Texture_GL(Render, const Image& image, const TextureFormat format, const TextureDesc desc)
	{
		const auto& prop = GetTextureFormatProperty(format);
		
		// [メインテクスチャ] を作成
		{
			if (format == TextureFormat::R8G8B8A8_Unorm
				|| format == TextureFormat::R8G8B8A8_Unorm_SRGB)
			{
				::glGenTextures(1, &m_texture);
				::glBindTexture(GL_TEXTURE_2D, m_texture);
				::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, image.width(), image.height(), 0,
							   prop.GLFormat, prop.GLType, image.data());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
			else
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture (init with Image)"_fmt(ToString(format)));
				return;
			}
		}
		
		// [メインテクスチャ・フレームバッファ] を作成
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
		
		m_size = image.size();
		m_format = format;
		m_textureDesc = desc;
		m_type = TextureType::Render;
		m_initialized = true;
	}
	
	Texture_GL::Texture_GL(MSRender, const Size& size, const TextureFormat format, const TextureDesc desc)
	{
		// サイズをチェック
		if (!InRange(size.x, 1, Image::MaxWidth) || !InRange(size.y, 1, Image::MaxHeight))
		{
			return;
		}
		
		const auto& prop = GetTextureFormatProperty(format);
		
		// [マルチサンプル・テクスチャ] を作成
		{
			if (format == TextureFormat::R8G8B8A8_Unorm
				|| format == TextureFormat::R8G8B8A8_Unorm_SRGB
				|| format == TextureFormat::R16G16_Float
				|| format == TextureFormat::R32_Float
				|| format == TextureFormat::R10G10B10A2_Unorm
				|| format == TextureFormat::R11G11B10_UFloat
				|| format == TextureFormat::R16G16B16A16_Float
				|| format == TextureFormat::R32G32_Float
				|| format == TextureFormat::R32G32B32A32_Float)
			{
				::glGenTextures(1, &m_multiSampledTexture);
				::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTexture);
				::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, prop.GLInternalFormat, size.x, size.y, GL_FALSE);
				//::glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
			}
			else
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in MSRenderTexture"_fmt(ToString(format)));
				return;
			}
		}
		
		// [フレームバッファ] を作成
		{
			::glGenFramebuffers(1, &m_frameBuffer);
			::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTexture, 0);
			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in MSRenderTexture"_fmt(ToString(format)));
				return;
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		// [メインテクスチャ] を作成
		{
			if (format == TextureFormat::R8G8B8A8_Unorm
				|| format == TextureFormat::R8G8B8A8_Unorm_SRGB
				|| format == TextureFormat::R16G16_Float
				|| format == TextureFormat::R32_Float
				|| format == TextureFormat::R10G10B10A2_Unorm
				|| format == TextureFormat::R11G11B10_UFloat
				|| format == TextureFormat::R16G16B16A16_Float
				|| format == TextureFormat::R32G32_Float
				|| format == TextureFormat::R32G32B32A32_Float)
			{
				::glGenTextures(1, &m_texture);
				::glBindTexture(GL_TEXTURE_2D, m_texture);
				::glTexImage2D(GL_TEXTURE_2D, 0, prop.GLInternalFormat, size.x, size.y, 0,
							   prop.GLFormat, prop.GLType, nullptr);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
			else
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture"_fmt(ToString(format)));
				return;
			}
		}
		
		// [resolved フレームバッファ] を作成
		{
			::glGenFramebuffers(1, &m_resolvedFrameBuffer);
			::glBindFramebuffer(GL_FRAMEBUFFER, m_resolvedFrameBuffer);
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
		m_type = TextureType::MSRender;
		m_initialized = true;
	}
	
	Texture_GL::~Texture_GL()
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
		if (m_type != TextureType::Render
			&& m_type != TextureType::MSRender)
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

		//::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void Texture_GL::readRT(Image& image)
	{
		if (m_type != TextureType::Render
			&& m_type != TextureType::MSRender)
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
		
		::glBindFramebuffer(GL_FRAMEBUFFER, (m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer);
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void Texture_GL::resolveMSRT()
	{
		if (m_type != TextureType::MSRender)
		{
			return;
		}
		
		::glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);
		::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolvedFrameBuffer);
		::glBlitFramebuffer(0, 0, m_size.x, m_size.y, 0, 0, m_size.x, m_size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		
		::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		::glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
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
