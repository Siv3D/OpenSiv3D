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

# include "ConstantBufferDetail_WebGPU.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>

namespace s3d
{
	ConstantBufferDetail_WebGPU::ConstantBufferDetail_WebGPU(const size_t size)
		: m_bufferSize(size)
	{
	}

	ConstantBufferDetail_WebGPU::~ConstantBufferDetail_WebGPU()
	{
		if (m_uniformBuffer)
		{
			m_uniformBuffer.Release();
		}
	}

	bool ConstantBufferDetail_WebGPU::init() const
	{
		CRenderer_WebGPU* const pRenderer = dynamic_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer));

		m_device = *pRenderer->getDevice();

		if (not m_device)
		{
			return false;
		}

		wgpu::BufferDescriptor desc
		{
			.size = m_bufferSize,
			.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::Uniform
		};

		m_uniformBuffer = m_device.CreateBuffer(&desc);

		return true;
	}

	bool ConstantBufferDetail_WebGPU::update(const void* const data, const size_t size)
	{
		if (not m_uniformBuffer)
		{
			init();
		}

		assert(size <= m_bufferSize);

		m_device.GetQueue().WriteBuffer(m_uniformBuffer, 0, data, size);

		return true;
	}

	wgpu::Buffer ConstantBufferDetail_WebGPU::getHandle() const
	{
		if (not m_uniformBuffer)
		{
			init();
		}

		return m_uniformBuffer;
	}
}
