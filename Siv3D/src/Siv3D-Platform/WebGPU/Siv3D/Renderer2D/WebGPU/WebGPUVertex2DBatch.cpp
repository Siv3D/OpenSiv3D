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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include "WebGPUVertex2DBatch.hpp"

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

	WebGPUVertex2DBatch::WebGPUVertex2DBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1)
	{

	}

	WebGPUVertex2DBatch::~WebGPUVertex2DBatch()
	{
	}

	bool WebGPUVertex2DBatch::init(const wgpu::Device& device)
	{
		{
			wgpu::BufferDescriptor indexBufferDescripter
			{
				.size = sizeof(Vertex2D::IndexType) * IndexBufferSize,
				.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
			};

			m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
		}

		{
			wgpu::BufferDescriptor vertexBufferDescripter
			{
				.size = sizeof(Vertex2D) * VertexBufferSize,
				.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
			};

			m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
		}

		return true;
	}

	Vertex2DBufferPointer WebGPUVertex2DBatch::requestBuffer(const uint16 vertexSize, const uint32 indexSize, WebGPURenderer2DCommandManager& commandManager)
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
			LOG_TRACE(U"ℹ️ Resized WebGPUVertex2DBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
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
			LOG_TRACE(U"ℹ️ Resized WebGPUVertex2DBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
			m_indexArray.resize(newIndexArraySize);
		}

		if (const auto& lastbatch = m_batches.back();
			(VertexBufferSize < (lastbatch.vertexPos + vertexSize) || IndexBufferSize < (lastbatch.indexPos + indexSize)))
		{
			commandManager.pushUpdateBuffers(static_cast<uint32>(m_batches.size()));
			m_batches.emplace_back();
		}

		auto& lastbatch = m_batches.back();
		Vertex2D* const pVertex = (m_vertexArray.data() + m_vertexArrayWritePos);
		Vertex2D::IndexType* const pIndex = (m_indexArray.data() + m_indexArrayWritePos);
		const auto indexOffset = lastbatch.vertexPos;

		advanceArrayWritePos(vertexSize, indexSize);
		lastbatch.advance(vertexSize, indexSize);

		return{ pVertex, pIndex, indexOffset };
	}

	size_t WebGPUVertex2DBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}

	void WebGPUVertex2DBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();

		m_vertexArrayWritePos = 0;
		m_indexArrayWritePos = 0;

		// m_vertexBufferWritePos = 0;
		// m_indexBufferWritePos = 0;
	}

	void WebGPUVertex2DBatch::setBuffers(const wgpu::RenderPassEncoder& pass)
	{
		// pass.SetVertexBuffer(0, m_vertexBuffer, sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * (VertexBufferSize - m_vertexBufferWritePos));
		// pass.SetIndexBuffer(m_indexBuffer, wgpu::IndexFormat::Uint16, sizeof(Vertex2D::IndexType) * m_indexBufferWritePos, sizeof(Vertex2D::IndexType) * (IndexBufferSize - m_indexBufferWritePos));

		pass.SetVertexBuffer(0, m_vertexBuffer, 0, sizeof(Vertex2D) * VertexBufferSize);
		pass.SetIndexBuffer(m_indexBuffer, wgpu::IndexFormat::Uint16, 0, sizeof(Vertex2D::IndexType) * IndexBufferSize);
	}

	BatchInfo2D WebGPUVertex2DBatch::updateBuffers(const wgpu::Device& device, const size_t batchIndex)
	{
		assert(batchIndex < m_batches.size());

		size_t vertexArrayReadPos = 0;
		size_t indexArrayReadPos = 0;

		for (size_t i = 0; i < batchIndex; ++i)
		{
			vertexArrayReadPos += m_batches[i].vertexPos;
			indexArrayReadPos += m_batches[i].indexPos;
		}

		BatchInfo2D batchInfo;
		const auto& currentBatch = m_batches[batchIndex];

		// VB
		if (const uint16 vertexSize = currentBatch.vertexPos)
		{
			const Vertex2D* pSrc = &m_vertexArray[vertexArrayReadPos];

			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				m_vertexBufferWritePos = 0;

				wgpu::BufferDescriptor vertexBufferDescripter
				{
					.size = sizeof(Vertex2D) * VertexBufferSize,
					.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
				};
				
				m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
			}

			device.GetQueue().WriteBuffer(m_vertexBuffer, sizeof(Vertex2D) * m_vertexBufferWritePos, pSrc, sizeof(Vertex2D) * vertexSize);

			// void* const pDst = m_vertexBuffer.GetMappedRange(sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * vertexSize);
			// {
			// 	std::memcpy(pDst, pSrc, sizeof(Vertex2D) * vertexSize);
			// }
			// m_vertexBuffer.Unmap();

			batchInfo.baseVertexLocation = m_vertexBufferWritePos;
			m_vertexBufferWritePos += vertexSize;
		}

		// IB
		if (const uint32 indexSize = currentBatch.indexPos)
		{
			const uint32 alignedIndexSize = (indexSize & 0xFFFFFFFE) + 2;
			const Vertex2D::IndexType* pSrc = &m_indexArray[indexArrayReadPos];

			if (IndexBufferSize < (m_indexBufferWritePos + indexSize))
			{
				m_indexBufferWritePos = 0;

				wgpu::BufferDescriptor indexBufferDescripter
				{
					.size = sizeof(Vertex2D::IndexType) * IndexBufferSize,
					.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
				};

				m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
			}

			device.GetQueue().WriteBuffer(m_indexBuffer, sizeof(Vertex2D::IndexType) * m_indexBufferWritePos, pSrc, sizeof(Vertex2D::IndexType) * alignedIndexSize);

			// void* const pDst = m_indexBuffer.GetMappedRange(sizeof(Vertex2D::IndexType) * m_indexBufferWritePos, sizeof(Vertex2D::IndexType) * indexSize);
			// {
			// 	std::memcpy(pDst, pSrc, (sizeof(Vertex2D::IndexType) * indexSize));
			// }
			// m_indexBuffer.Unmap();

			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += alignedIndexSize;
		}

		return batchInfo;
	}

	void WebGPUVertex2DBatch::advanceArrayWritePos(const uint16 vertexSize, const uint32 indexSize) noexcept
	{
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
	}
}
