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

# include "WebGPUTexture.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>

namespace s3d
{
	WebGPUTexture::WebGPUTexture(wgpu::Device* device, const Image& image, const TextureDesc desc)
	{
		const TextureFormat format = 
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm;

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.stride(),
				.rowsPerImage = static_cast<uint32>(image.height())
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}
		
		m_size			= image.size();
		m_format		= format;
		m_textureDesc	= desc;
		m_type			= TextureType::Default;
		m_initialized	= true;
	}
	
	WebGPUTexture::WebGPUTexture(wgpu::Device* device, const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		const TextureFormat format =
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm;

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst,
				.mipLevelCount = mipmaps.size()
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.stride(),
				.rowsPerImage = static_cast<uint32>(image.height())
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}

		for (uint32 i = 0; i < mipmaps.size(); ++i)
		{
			const Image& mipmap = mipmaps[i];
			
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture,
				.mipLevel = i
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = mipmap.stride(),
				.rowsPerImage = static_cast<uint32>(mipmap.height())
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(mipmap.width()),
				.height = static_cast<uint32_t>(mipmap.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				mipmap.data(), mipmap.size_bytes(), 
				&layout, &size);
		}
		
		m_size			= image.size();
		m_format		= format;
		m_textureDesc	= desc;
		m_type			= TextureType::Dynamic;
		m_initialized	= true;
	}

	WebGPUTexture::WebGPUTexture(Dynamic, wgpu::Device* device, const Size& size, const void* pData, const uint32, const TextureFormat& format, const TextureDesc desc)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Dynamic }
	{
		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(size.x),
					.height = static_cast<uint32_t>(size.y),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = static_cast<uint32_t>(size.x * format.pixelSize()),
				.rowsPerImage =  static_cast<uint32_t>(size.y)
			};

			wgpu::Extent3D textureSize
			{
				.width =  static_cast<uint32_t>(size.x),
				.height =  static_cast<uint32_t>(size.y),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				pData, static_cast<uint32_t>(size.x * size.y * format.pixelSize()), 
				&layout, &textureSize);
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(Render, wgpu::Device* device, const Size& size, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
	{
		if (format == TextureFormat::Unknown)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(size.x),
					.height = static_cast<uint32_t>(size.y),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(Render, wgpu::Device* device, const Image& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
	{
		if ((format != TextureFormat::R8G8B8A8_Unorm)
			&& (format != TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Image&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.stride(),
				.rowsPerImage = static_cast<uint32>(image.height())
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(Render, wgpu::Device* device, const Grid<float>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
	{
		if (format != TextureFormat::R32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<float>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.width() * sizeof(float),
				.rowsPerImage = image.height()
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(Render, wgpu::Device* device, const Grid<Float2>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
	{
		if (format != TextureFormat::R32G32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<Float2>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.width() * sizeof(Float2),
				.rowsPerImage = image.height()
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(Render, wgpu::Device* device, const Grid<Float4>& image, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ image.size() }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::Render }
	{
		if (format != TextureFormat::R32G32B32A32_Float)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in RenderTexture(const Grid<Float4>&)"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(image.width()),
					.height = static_cast<uint32_t>(image.height()),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = image.width() * sizeof(Float4),
				.rowsPerImage = image.height()
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(image.width()),
				.height = static_cast<uint32_t>(image.height()),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				image.data(), image.size_bytes(), 
				&layout, &size);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::WebGPUTexture(MSRender, wgpu::Device* device, const Size& size, const TextureFormat& format, const TextureDesc desc, const HasDepth hasDepth)
		: m_size{ size }
		, m_format{ format }
		, m_textureDesc{ desc }
		, m_type{ TextureType::MSRender }
	{
		if (format == TextureFormat::Unknown)
		{
			LOG_FAIL(U"TextureFormat `{}` is not supported in MSRenderTexture"_fmt(format.name()));
			return;
		}

		// [メインテクスチャ] を作成
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(size.x),
					.height = static_cast<uint32_t>(size.y),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst,
				.sampleCount = 4
			};

			m_multiSampledTexture = device->CreateTexture(&desc);
		}

		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(size.x),
					.height = static_cast<uint32_t>(size.y),
					.depthOrArrayLayers = 1
				},
				.format = ToEnum<wgpu::TextureFormat>(format.WGPUFormat()),
				.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::Sampled | wgpu::TextureUsage::CopyDst
			};

			m_texture = device->CreateTexture(&desc);
		}

		if (hasDepth)
		{
			if (not initDepthBuffer(device))
			{
				return;
			}
		}

		m_initialized = true;
	}

	WebGPUTexture::~WebGPUTexture()
	{
	}

	bool WebGPUTexture::isInitialized() const noexcept
	{
		return m_initialized;
	}

	wgpu::Texture WebGPUTexture::getTexture() const noexcept
	{
		return m_texture;
	}

	Size WebGPUTexture::getSize() const noexcept
	{
		return m_size;
	}

	TextureDesc WebGPUTexture::getDesc() const noexcept
	{
		return m_textureDesc;
	}

	TextureFormat WebGPUTexture::getFormat() const noexcept
	{
		return m_format;
	}

	bool WebGPUTexture::hasDepth() const noexcept
	{
		return m_hasDepth;
	}

	bool WebGPUTexture::fill(wgpu::Device* device, const ColorF& color, bool)
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

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture
			};

			wgpu::TextureDataLayout layout 
			{
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(m_size.x),
				.height = static_cast<uint32_t>(m_size.y),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				data.data(), data.size_bytes(), 
				&layout, &size);
		}

		return true;
	}

	bool WebGPUTexture::fillRegion(wgpu::Device* device, const ColorF& color, const Rect& rect)
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

		{
			wgpu::ImageCopyTexture copyOperationDesc
			{
				.texture = m_texture,
				.origin = 
				{
					.x = static_cast<uint32_t>(rect.x),
					.y = static_cast<uint32_t>(rect.y),
				}
			};

			wgpu::TextureDataLayout layout 
			{
				.bytesPerRow = static_cast<uint32>(rect.w) * m_format.pixelSize(),
				.rowsPerImage = static_cast<uint32>(rect.h)
			};

			wgpu::Extent3D size
			{
				.width = static_cast<uint32_t>(rect.w),
				.height = static_cast<uint32_t>(rect.h),
				.depthOrArrayLayers = 1
			};

			device->GetQueue().WriteTexture(
				&copyOperationDesc, 
				data.data(), data.size_bytes(), 
				&layout, &size);
		}

		return true;
	}

	bool WebGPUTexture::fill(wgpu::Device* device, const void* src, [[maybe_unused]] const uint32 stride, [[maybe_unused]] const bool wait)
	{
		if (m_type != TextureType::Dynamic)
		{
			return false;
		}

		if ((m_format == TextureFormat::R8G8B8A8_Unorm)
			|| (m_format == TextureFormat::R8G8B8A8_Unorm_SRGB))
		{
			{
				wgpu::ImageCopyTexture copyOperationDesc
				{
					.texture = m_texture
				};

				wgpu::TextureDataLayout layout 
				{
					.bytesPerRow = static_cast<uint32_t>(m_size.x) * m_format.pixelSize(),
					.rowsPerImage = static_cast<uint32_t>(m_size.y)
				};

				wgpu::Extent3D size
				{
					.width = static_cast<uint32_t>(m_size.x),
					.height = static_cast<uint32_t>(m_size.y),
					.depthOrArrayLayers = 1
				};

				device->GetQueue().WriteTexture(
					&copyOperationDesc, 
					src, m_size.x * m_size.y * m_format.pixelSize(), 
					&layout, &size);
			}
		
			return true;
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(m_format.name()));
			return false;
		}
	}

	bool WebGPUTexture::fillRegion(wgpu::Device* device, const void* src, const uint32 stride, const Rect& rect, [[maybe_unused]] const bool wait)
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

			{
				wgpu::ImageCopyTexture copyOperationDesc
				{
					.texture = m_texture,
					.origin = 
					{
						.x = static_cast<uint32_t>(rect.x),
						.y = static_cast<uint32_t>(rect.y),
					}
				};

				wgpu::TextureDataLayout layout 
				{
					.bytesPerRow = static_cast<uint32>(rect.w) * m_format.pixelSize(),
					.rowsPerImage = static_cast<uint32>(rect.h)
				};

				wgpu::Extent3D size
				{
					.width = static_cast<uint32_t>(rect.w),
					.height = static_cast<uint32_t>(rect.h),
					.depthOrArrayLayers = 1
				};

				device->GetQueue().WriteTexture(
					&copyOperationDesc, 
					newData.data(), newData.size_bytes(), 
					&layout, &size);
			}
		
			return true;
		}
		else
		{
			LOG_FAIL(U"DynamicTexture image fill for {0} is not yet implemented"_fmt(m_format.name()));
			return false;
		}
	}

	void WebGPUTexture::clearRT(const ColorF& color)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		// ::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		// Float4 clearColor = color.toFloat4();

		// ::glClearColor(
		// 	clearColor.x,
		// 	clearColor.y,
		// 	clearColor.z,
		// 	clearColor.w);

		// if (m_hasDepth)
		// {
		// 	if (auto p = dynamic_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer)))
		// 	{
		// 		p->getDepthStencilState().set(DepthStencilState::Default3D);
		// 	}

		// 	::glClearDepth(0.0);
		// 	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// }
		// else
		// {
		// 	::glClear(GL_COLOR_BUFFER_BIT);
		// }

		//::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGPUTexture::readRT(Image& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if ((m_format != TextureFormat::R8G8B8A8_Unorm)
			&& (m_format != TextureFormat::R8G8B8A8_Unorm_SRGB)) // RGBA8 形式以外なら失敗
		{
			LOG_FAIL(U"WebGPUTexture::readRT(): Image is not supported in this format");
			return;
		}

		image.resize(m_size);

		// ::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		// {
		// 	::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		// }
		// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGPUTexture::readRT(Grid<float>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32_Float) // R32F 形式以外なら失敗
		{
			LOG_FAIL(U"WebGPUTexture::readRT(): Grid<float> is not supported in this format");
			return;
		}

		image.resize(m_size);

		// ::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		// {
		// 	::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		// }
		// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGPUTexture::readRT(Grid<Float2>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32G32_Float) // RG32F 形式以外なら失敗
		{
			LOG_FAIL(U"WebGPUTexture::readRT(): Grid<Float2> is not supported in this format");
			return;
		}

		image.resize(m_size);

		// ::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		// {
		// 	::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		// }
		// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGPUTexture::readRT(Grid<Float4>& image)
	{
		if ((m_type != TextureType::Render)
			&& (m_type != TextureType::MSRender))
		{
			return;
		}

		if (m_format != TextureFormat::R32G32B32A32_Float) // RGBA32F 形式以外なら失敗
		{
			LOG_FAIL(U"WebGPUTexture::readRT(): Grid<Float4> is not supported in this format");
			return;
		}

		image.resize(m_size);

		// ::glBindFramebuffer(GL_FRAMEBUFFER, ((m_type == TextureType::MSRender) ? m_resolvedFrameBuffer : m_frameBuffer));
		// {
		// 	::glReadPixels(0, 0, m_size.x, m_size.y, m_format.GLFormat(), m_format.GLType(), image.data());
		// }
		// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGPUTexture::resolveMSRT()
	{
		if (m_type != TextureType::MSRender)
		{
			return;
		}

		// ::glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);
		// ::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolvedFrameBuffer);
		// ::glBlitFramebuffer(0, 0, m_size.x, m_size.y, 0, 0, m_size.x, m_size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		// ::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		// ::glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	bool WebGPUTexture::initDepthBuffer(wgpu::Device* device)
	{
		assert(not m_hasDepth);
		assert(not m_depthTexture);
		assert((m_type == TextureType::Render) || (m_type == TextureType::MSRender));

		// [デプステクスチャ] を作成
		if (m_type == TextureType::Render)
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(m_size.x),
					.height = static_cast<uint32_t>(m_size.y),
					.depthOrArrayLayers = 1
				},
				.format = wgpu::TextureFormat::Depth32Float,
				.usage = wgpu::TextureUsage::RenderAttachment
			};

			m_texture = device->CreateTexture(&desc);
		}
		else
		{
			wgpu::TextureDescriptor desc 
			{
				.size = 
				{
					.width = static_cast<uint32_t>(m_size.x),
					.height = static_cast<uint32_t>(m_size.y),
					.depthOrArrayLayers = 1
				},
				.format = wgpu::TextureFormat::Depth32Float,
				.usage = wgpu::TextureUsage::RenderAttachment,
				.sampleCount = 4
			};

			m_texture = device->CreateTexture(&desc);
		}
		
		m_hasDepth = true;

		return true;
	}
}
