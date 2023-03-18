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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include "WebGPULine3DBatch.hpp"

namespace s3d
{
	namespace detail
	{
		static size_t CalculateNewArraySize(const size_t current, const size_t target) noexcept
		{
			size_t newArraySize = current * 2;

			while (newArraySize < target)
			{
				newArraySize *= 2;
			}

			return newArraySize;
		}
	}

	WebGPULine3DBatch::WebGPULine3DBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1) {}

	WebGPULine3DBatch::~WebGPULine3DBatch()
	{
	}

	bool WebGPULine3DBatch::init(const wgpu::Device& device)
	{
		{
			wgpu::BufferDescriptor indexBufferDescripter
			{
				.size = sizeof(VertexLine3D::IndexType) * IndexBufferSize,
				.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
			};

			m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
		}

		{
			wgpu::BufferDescriptor vertexBufferDescripter
			{
				.size = sizeof(VertexLine3D) * VertexBufferSize,
				.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
			};

			m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
		}

		return true;
	}

	VertexLine3DBufferPointer WebGPULine3DBatch::requestBuffer(const VertexLine3D::IndexType vertexSize, const uint32 indexSize, WebGPURenderer3DCommandManager& commandManager)
	{
		// VB
		if (const uint32 vertexArrayWritePosTarget = m_vertexArrayWritePos + vertexSize;
			m_vertexArray.size() < vertexArrayWritePosTarget) SIV3D_UNLIKELY
		{
			if (MaxVertexArraySize < vertexArrayWritePosTarget) SIV3D_UNLIKELY
			{
				return{ nullptr, 0, 0 };
			}

			const size_t newVertexArraySize = detail::CalculateNewArraySize(m_vertexArray.size(), vertexArrayWritePosTarget);
			LOG_TRACE(U"ℹ️ Resized WebGPULine3DBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
			m_vertexArray.resize(newVertexArraySize);
		}

		// IB
		if (const uint32 indexArrayWritePosTarget = m_indexArrayWritePos + indexSize;
			m_indexArray.size() < indexArrayWritePosTarget) SIV3D_UNLIKELY
		{
			if (MaxIndexArraySize < indexArrayWritePosTarget) SIV3D_UNLIKELY
			{
				return{ nullptr, 0, 0 };
			}

			const size_t newIndexArraySize = detail::CalculateNewArraySize(m_indexArray.size(), indexArrayWritePosTarget);
			LOG_TRACE(U"ℹ️ Resized WebGPULine3DBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
			m_indexArray.resize(newIndexArraySize);
		}

		if (const auto& lastbatch = m_batches.back();
			(VertexBufferSize < (lastbatch.vertexPos + vertexSize) || IndexBufferSize < (lastbatch.indexPos + indexSize)))
		{
			commandManager.pushUpdateLine3DBuffers(static_cast<uint32>(m_batches.size()));
			m_batches.emplace_back();
		}

		auto& lastbatch = m_batches.back();
		VertexLine3D* const pVertex = (m_vertexArray.data() + m_vertexArrayWritePos);
		VertexLine3D::IndexType* const pIndex = (m_indexArray.data() + m_indexArrayWritePos);
		const auto indexOffset = lastbatch.vertexPos;

		advanceArrayWritePos(vertexSize, indexSize);
		lastbatch.advance(vertexSize, indexSize);

		return{ pVertex, pIndex, indexOffset };
	}

	size_t WebGPULine3DBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}

	bool WebGPULine3DBatch::isEmpty() const noexcept
	{
		return (m_vertexArrayWritePos == 0);
	}

	void WebGPULine3DBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();

		m_vertexArrayWritePos = 0;
		m_indexArrayWritePos = 0;

		m_vertexBufferWritePos = 0;
	}

	void WebGPULine3DBatch::setBuffers(const wgpu::RenderPassEncoder& pass)
	{
		// ::glBindVertexArray(m_vao);
		// ::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		pass.SetVertexBuffer(0, m_vertexBuffer, 0, sizeof(VertexLine3D) * VertexBufferSize);
		pass.SetIndexBuffer(m_indexBuffer, wgpu::IndexFormat::Uint32, 0, sizeof(VertexLine3D::IndexType) * IndexBufferSize);
	}

	BatchInfoLine3D WebGPULine3DBatch::updateBuffers(const wgpu::Device& device, const size_t batchIndex)
	{
		assert(batchIndex < m_batches.size());

		size_t vertexArrayReadPos = 0;
		size_t indexArrayReadPos = 0;

		for (size_t i = 0; i < batchIndex; ++i)
		{
			vertexArrayReadPos += m_batches[i].vertexPos;
			indexArrayReadPos += m_batches[i].indexPos;
		}

		BatchInfoLine3D batchInfo;
		const auto& currentBatch = m_batches[batchIndex];

		// VB
		if (const VertexLine3D::IndexType vertexSize = currentBatch.vertexPos)
		{
			const VertexLine3D* pSrc = &m_vertexArray[vertexArrayReadPos];

			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				m_vertexBufferWritePos = 0;

				wgpu::BufferDescriptor vertexBufferDescripter
				{
					.size = sizeof(VertexLine3D) * VertexBufferSize,
					.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
				};
				
				m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
			}

			device.GetQueue().WriteBuffer(m_vertexBuffer, sizeof(VertexLine3D) * m_vertexBufferWritePos, pSrc, sizeof(VertexLine3D) * vertexSize);

			batchInfo.baseVertexLocation = m_vertexBufferWritePos;
			m_vertexBufferWritePos += vertexSize;
		}

		// IB
		if (const uint32 indexSize = currentBatch.indexPos)
		{
			const VertexLine3D::IndexType* pSrc = &m_indexArray[indexArrayReadPos];

			if (IndexBufferSize < (m_indexBufferWritePos + indexSize))
			{
				m_indexBufferWritePos = 0;

				wgpu::BufferDescriptor indexBufferDescripter
				{
					.size = sizeof(VertexLine3D::IndexType) * IndexBufferSize,
					.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
				};

				m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
			}

			device.GetQueue().WriteBuffer(m_indexBuffer, sizeof(VertexLine3D::IndexType) * m_indexBufferWritePos, pSrc, sizeof(VertexLine3D::IndexType) * indexSize);

			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += indexSize;
		}

		return batchInfo;
	}

	void WebGPULine3DBatch::advanceArrayWritePos(const VertexLine3D::IndexType vertexSize, const uint32 indexSize) noexcept
	{
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
	}
}
