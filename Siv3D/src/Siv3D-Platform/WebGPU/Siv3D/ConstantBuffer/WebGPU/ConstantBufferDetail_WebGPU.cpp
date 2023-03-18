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

# include "ConstantBufferDetail_WebGPU.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>

namespace s3d
{
	ConstantBufferDetail_WebGPU::ConstantBufferDetail_WebGPU(const size_t size)
	{
		m_bufferSize = size;

		if ((m_bufferSize & 0xFF) != 0)
		{
			m_bufferSize = (m_bufferSize & ~0xFF) + 0x100;
		}

		m_allocatedBufferSize = 16 * 1024; // 16KB
	}

	ConstantBufferDetail_WebGPU::~ConstantBufferDetail_WebGPU()
	{
	}

	bool ConstantBufferDetail_WebGPU::init() const
	{
		auto pRenderer = static_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer));
		m_device = *pRenderer->getDevice();

		if (not m_device)
		{
			return false;
		}

		wgpu::BufferDescriptor desc
		{
			.size = m_allocatedBufferSize,
			.usage = wgpu::BufferUsage::Uniform | wgpu::BufferUsage::CopyDst
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

		m_device.GetQueue().WriteBuffer(m_uniformBuffer, m_bufferOffsetWritePos, data, size);

		m_bufferOffset = m_bufferOffsetWritePos;
		m_bufferOffsetWritePos += m_bufferSize;

		if (m_bufferOffsetWritePos >= m_allocatedBufferSize)
		{
			m_bufferOffsetWritePos = 0;
		}

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

	wgpu::BindGroupEntry ConstantBufferDetail_WebGPU::getBindGroupEntry() const
	{
		if (not m_uniformBuffer)
		{
			init();
		}

		return wgpu::BindGroupEntry
		{
			.buffer = m_uniformBuffer,
			.size = m_bufferSize,
			.offset = m_bufferOffset
		};
	}
}
