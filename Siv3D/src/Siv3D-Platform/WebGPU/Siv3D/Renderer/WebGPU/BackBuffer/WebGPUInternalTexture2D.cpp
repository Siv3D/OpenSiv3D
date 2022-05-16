//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "WebGPUInternalTexture2D.hpp"

namespace s3d
{
	WebGPUInternalTexture2D::~WebGPUInternalTexture2D()
	{
		if (m_texture)
		{
			m_texture.Release();
		}
	}

	bool WebGPUInternalTexture2D::isEmpty() const noexcept
	{
		return m_size.isZero();
	}

	WebGPUInternalTexture2D::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	const Size& WebGPUInternalTexture2D::size() const noexcept
	{
		return m_size;
	}

	wgpu::TextureView WebGPUInternalTexture2D::getTextureView() const noexcept
	{
		return m_texture.CreateView();
	}

	WebGPURenderTargetState WebGPUInternalTexture2D::getRenderTargetState() const noexcept
	{
		return WebGPURenderTargetState
		{
			.renderTargetFormat = FromEnum(wgpu::TextureFormat::RGBA8Unorm),
			.hasDepth = false,
			.sampleCount = 1
		};
	}

	std::unique_ptr<WebGPUInternalTexture2D> WebGPUInternalTexture2D::CreateRenderTargetTexture2D(const wgpu::Device& device, Size size, const uint32 sampleCount)
	{
		assert(sampleCount != 0);

		auto p = std::make_unique<WebGPUInternalTexture2D>();

		wgpu::Texture texture = nullptr;
		
		wgpu::TextureDescriptor desc
		{
			.usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::TextureBinding,
			.dimension = wgpu::TextureDimension::e2D,
			.size = 
			{
				.width = static_cast<uint32_t>(size.x),
				.height = static_cast<uint32_t>(size.y),
				.depthOrArrayLayers = 1
			},
			.format = wgpu::TextureFormat::RGBA8Unorm,
			.mipLevelCount = 1,
			.sampleCount = 1 // sampleCount
		};

		texture = device.CreateTexture(&desc);

		if (not texture)
		{
			return nullptr;
		}

		p->m_texture		= texture;
		p->m_size			= size;

		return p;
	}
}
