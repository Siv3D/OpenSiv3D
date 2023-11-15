//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GL4Texture.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>

namespace s3d
{
	GL4Texture::GL4Texture(const Image& image, const TextureDesc desc)
		: m_hasMipMap{ detail::HasMipMap(desc) }
	{
		const TextureFormat format = 
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm;

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), image.width(), image.height(), 0,
						   format.GLFormat(), format.GLType(), image.data());

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(image.width(), image.height());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
		}
		
		m_size			= image.size();
		m_format		= format;
		m_textureDesc	= desc;
		m_type			= TextureType::Default;
		m_initialized	= true;
	}
	
	GL4Texture::GL4Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		: m_hasMipMap{ true }
	{
		const TextureFormat format =
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm;

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
		m_type			= TextureType::Dynamic;
		m_initialized	= true;
	}

	GL4Texture::GL4Texture(Dynamic, const Size& size, const void* pData, const uint32, const TextureFormat& format, const TextureDesc desc)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Dynamic }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), size.x, size.y, 0,
				format.GLFormat(), format.GLType(), pData);

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(size.x, size.y);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(Render, const Size& size, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if (format == TextureFormat::Unknown)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), size.x, size.y, 0,
				format.GLFormat(), format.GLType(), nullptr);

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(size.x, size.y);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(Render, const Image& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if ((format != TextureFormat::R8G8B8A8_Unorm)
			&& (format != TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Image&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), image.width(), image.height(), 0,
				format.GLFormat(), format.GLType(), image.data());

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(image.width(), image.height());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(Render, const Grid<float>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if (format != TextureFormat::R32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<float>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(),
				static_cast<GLint>(image.width()), static_cast<GLint>(image.height()), 0,
				format.GLFormat(), format.GLType(), image.data());

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(image.width(), image.height());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(Render, const Grid<Float2>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if (format != TextureFormat::R32G32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<Float2>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(),
				static_cast<GLint>(image.width()), static_cast<GLint>(image.height()), 0,
				format.GLFormat(), format.GLType(), image.data());

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(image.width(), image.height());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(Render, const Grid<Float4>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if (format != TextureFormat::R32G32B32A32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<Float4>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(),
				static_cast<GLint>(image.width()), static_cast<GLint>(image.height()), 0,
				format.GLFormat(), format.GLType(), image.data());

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(image.width(), image.height());
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::GL4Texture(MSRender, const Size& size, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::MSRender }
		, m_hasMipMap{ detail::HasMipMap(desc) }
	{
		if (format == TextureFormat::Unknown)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in MSRenderTexture"_fmt(format.name()));
			return;
		}

		// [マルチサンプル・テクスチャ] を作成
		{
			::glGenTextures(1, &m_multiSampledTexture);
			::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTexture);
			::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, format.GLInternalFormat(), size.x, size.y, GL_FALSE);
			//::glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
		}

		// [フレームバッファ] を作成
		{
			::glGenFramebuffers(1, &m_frameBuffer);
			::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTexture, 0);
			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LOG_FAIL(U"TextureFormat `{}` is not supported in MSRenderTexture"_fmt(format.name()));
				return;
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		// [メインテクスチャ] を作成
		{
			::glGenTextures(1, &m_texture);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, format.GLInternalFormat(), size.x, size.y, 0,
				format.GLFormat(), format.GLType(), nullptr);

			if (m_hasMipMap)
			{
				const size_t mipmapCount = ImageProcessing::CalculateMipCount(size.x, size.y);
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mipmapCount - 1));
				::glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
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

		if (hasDepth)
		{
			if (not initDepthBuffer())
			{
				return;
			}
		}

		m_initialized = true;
	}

	GL4Texture::~GL4Texture()
	{
		// [デプステクスチャ] を破棄
		if (m_depthTexture)
		{
			::glDeleteTextures(1, &m_depthTexture);
			m_depthTexture = 0;
		}

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

	bool GL4Texture::isInitialized() const noexcept
	{
		return m_initialized;
	}

	GLuint GL4Texture::getTexture() const noexcept
	{
		return m_texture;
	}

	GLuint GL4Texture::getFrameBuffer() const noexcept
	{
		return m_frameBuffer;
	}

	Size GL4Texture::getSize() const noexcept
	{
		return m_size;
	}

	TextureDesc GL4Texture::getDesc() const noexcept
	{
		return m_textureDesc;
	}

	TextureFormat GL4Texture::getFormat() const noexcept
	{
		return m_format;
	}

	bool GL4Texture::hasDepth() const noexcept
	{
		return m_hasDepth;
	}

	bool GL4Texture::fill(const ColorF& color, bool)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}

		const Array<Byte> data = GenerateInitialColorBuffer(m_size, color, m_format);

		if (not data)
		{
			return false;
		}

		::glBindTexture(GL_TEXTURE_2D, m_texture);

		::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), data.data());

		return true;
	}

	bool GL4Texture::fillRegion(const ColorF& color, const Rect& rect)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}

		if ((m_size.x < (rect.x + rect.w))
			|| (m_size.y < (rect.y + rect.h)))
		{
			return false;
		}

		const Array<Byte> data = GenerateInitialColorBuffer(rect.size, color, m_format);

		::glBindTexture(GL_TEXTURE_2D, m_texture);

		::glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.w, rect.h, m_format.GLFormat(), m_format.GLType(), data.data());

		return true;
	}

	bool GL4Texture::fill(const void* src, [[maybe_unused]] const uint32 stride, [[maybe_unused]] const bool wait)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}

		if ((m_format == TextureFormat::R8G8B8A8_Unorm)
			|| (m_format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			::glBindTexture(GL_TEXTURE_2D, m_texture);

			::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, src);
		
			return true;
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(m_format.name()));
			return false;
		}
	}

	bool GL4Texture::fillRegion(const void* src, const uint32 stride, const Rect& rect, [[maybe_unused]] const bool wait)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}

		if ((m_format == TextureFormat::R8G8B8A8_Unorm)
			|| (m_format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			Array<uint32> newData(rect.w * rect.h);

			if (not newData)
			{
				return true;
			}

			uint32* pDst = newData.data();

			for (int32 y = rect.y; y < rect.y + rect.h; ++y)
			{
				const uint32* line = static_cast<const uint32*>(src) + (stride / sizeof(uint32)) * y;

				for (int32 x = rect.x; x < rect.x + rect.w; ++x)
				{
					*pDst++ = line[x];
				}
			}

			::glBindTexture(GL_TEXTURE_2D, m_texture);

			::glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.w, rect.h, GL_RGBA, GL_UNSIGNED_BYTE, newData.data());
		
			return true;
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(m_format.name()));
			return false;
		}
	}

	void GL4Texture::clearRT(const ColorF& color)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		Float4 clearColor;

		if (m_format.isSRGB())
		{
			clearColor = color.applySRGBCurve().toFloat4();
		}
		else
		{
			clearColor = color.toFloat4();
		}

		::glClearColor(
			clearColor.x,
			clearColor.y,
			clearColor.z,
			clearColor.w);

		if (m_hasDepth)
		{
			auto p = static_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer));
			p->getDepthStencilState().set(DepthStencilState::Default3D);

			::glClearDepth(0.0);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else
		{
			::glClear(GL_COLOR_BUFFER_BIT);
		}

		//::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL4Texture::generateMips()
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender)
			&& (m_type != TextureType::Dynamic))
		{
			return;
		}

		if (not m_hasMipMap)
		{
			return;
		}

		::glBindTexture(GL_TEXTURE_2D, m_texture);
		::glGenerateMipmap(GL_TEXTURE_2D);
	}

	void GL4Texture::readRT(Image& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if ((m_format != TextureFormat::R8G8B8A8_Unorm)
			&& (m_format != TextureFormat::R8G8B8A8_Unorm_SRGB)) // RGBA8 形式以外なら失敗
		{
			LOG_FAIL(U"GL4Texture::readRT(): Image is not supported in this format");
			return;
		}

		image.resize(m_size);

		::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL4Texture::readRT(Grid<float>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32_Float) // R32F 形式以外なら失敗
		{
			LOG_FAIL(U"GL4Texture::readRT(): Grid<float> is not supported in this format");
			return;
		}

		image.resize(m_size);

		::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL4Texture::readRT(Grid<Float2>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32G32_Float) // RG32F 形式以外なら失敗
		{
			LOG_FAIL(U"GL4Texture::readRT(): Grid<Float2> is not supported in this format");
			return;
		}

		image.resize(m_size);

		::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL4Texture::readRT(Grid<Float4>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32G32B32A32_Float) // RGBA32F 形式以外なら失敗
		{
			LOG_FAIL(U"GL4Texture::readRT(): Grid<Float4> is not supported in this format");
			return;
		}

		image.resize(m_size);

		::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL4Texture::resolveMSRT()
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

	bool GL4Texture::initDepthBuffer()
	{
		assert(not m_hasDepth);
		assert(not m_depthTexture);
		assert((m_type == TextureType::Render) || (m_type == TextureType::MSRender));

		// [デプステクスチャ] を作成
		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		if (m_type == TextureType::Render)
		{
			::glGenTextures(1, &m_depthTexture);
			::glBindTexture(GL_TEXTURE_2D, m_depthTexture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x, m_size.y, 0,
				GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LOG_FAIL(U"glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE");
				return false;
			}
		}
		else
		{
			::glGenTextures(1, &m_depthTexture);
			::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_depthTexture);
			::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT32, m_size.x, m_size.y, GL_FALSE);
			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_depthTexture, 0);
		
			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LOG_FAIL(U"glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE");
				return false;
			}
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_hasDepth = true;

		return true;
	}
}
