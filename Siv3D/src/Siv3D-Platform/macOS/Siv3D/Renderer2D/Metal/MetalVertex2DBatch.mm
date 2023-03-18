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

# include "MetalVertex2DBatch.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	bool MetalVertex2DBatch::init(id<MTLDevice> device)
	{
		m_device = device;
		
		for(size_t i = 0; i < MaxInflightBuffers; ++i)
		{
			auto& viBuffer = m_viBuffers[i].emplace_back();
			viBuffer.vertexBuffer = [m_device newBufferWithLength:(sizeof(Vertex2D) * VertexBufferSize)
														  options:MTLResourceStorageModeShared];
			viBuffer.indexBuffer = [m_device newBufferWithLength:(sizeof(IndexType) * IndexBufferSize)
														 options:MTLResourceStorageModeShared];
		}
		
		return true;
	}

	void MetalVertex2DBatch::begin()
	{
		assert(!m_isActive);
		
		dispatch_semaphore_wait(m_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);
		++m_currentVIBufferIndex %= MaxInflightBuffers;
		
		m_currentBatchIndex = 0;
		m_allVertexCount = 0;
		m_allIndexCount = 0;
		
		for (auto& viBuffer : m_viBuffers[m_currentVIBufferIndex])
		{
			viBuffer.resetWritePos();
		}
	
		m_isActive = true;
	}

	void MetalVertex2DBatch::end()
	{
		assert(m_isActive);

		m_isActive = false;
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentVertexBuffer(size_t index) const
	{
		return m_viBuffers[m_currentVIBufferIndex][index].vertexBuffer;
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentIndexBuffer(size_t index) const
	{
		return m_viBuffers[m_currentVIBufferIndex][index].indexBuffer;
	}

	dispatch_semaphore_t MetalVertex2DBatch::getSemaphore() const
	{
		return m_frameBoundarySemaphore;
	}

	Vertex2DBufferPointer MetalVertex2DBatch::requestBuffer(const uint16 vertexSize, const uint32 indexSize, MetalRenderer2DCommandManager& commandManager)
	{
		{
			auto& currentVIBuffer = m_viBuffers[m_currentVIBufferIndex][m_currentBatchIndex];
			
			// VB
			if (const uint32 allVertexCount = m_allVertexCount + vertexSize;
				MaxVertexCount < allVertexCount)
			{
				return{ nullptr, 0, 0 };
			}
			
			// IB
			if (const uint32 allIndexCount = m_allIndexCount + indexSize;
				MaxIndexCount < allIndexCount)
			{
				return{ nullptr, 0, 0 };
			}
			
			if ((VertexBufferSize < (currentVIBuffer.vertexBufferWritePos + vertexSize)
				 || IndexBufferSize < (currentVIBuffer.indexBufferWritePos + indexSize)))
			{
				++m_currentBatchIndex;
				commandManager.pushUpdateBuffers(static_cast<uint32>(m_currentBatchIndex));
				
				if (m_viBuffers[m_currentVIBufferIndex].size() < (m_currentBatchIndex + 1))
				{
					LOG_TRACE(U"m_viBuffers[{}] resized to {}"_fmt(m_currentVIBufferIndex, (m_viBuffers[m_currentVIBufferIndex].size() + 1)));
					
					auto& viBuffer = m_viBuffers[m_currentVIBufferIndex].emplace_back();
					viBuffer.vertexBuffer = [m_device newBufferWithLength:(sizeof(Vertex2D) * VertexBufferSize)
																  options:MTLResourceStorageModeShared];
					viBuffer.indexBuffer = [m_device newBufferWithLength:(sizeof(IndexType) * IndexBufferSize)
																 options:MTLResourceStorageModeShared];
				}
			}
		}
		
		auto& currentVIBuffer = m_viBuffers[m_currentVIBufferIndex][m_currentBatchIndex];
		Vertex2D* const pVertex = (static_cast<Vertex2D*>(currentVIBuffer.vertexBuffer.contents) + currentVIBuffer.vertexBufferWritePos);
		IndexType* const pIndex = (static_cast<IndexType*>(currentVIBuffer.indexBuffer.contents) + currentVIBuffer.indexBufferWritePos);
		const Vertex2D::IndexType indexOffset = static_cast<Vertex2D::IndexType>(currentVIBuffer.vertexBufferWritePos);

		currentVIBuffer.vertexBufferWritePos += vertexSize;
		currentVIBuffer.indexBufferWritePos += indexSize;
		m_allVertexCount += vertexSize;
		m_allIndexCount += indexSize;

		return{ pVertex, pIndex, indexOffset };
	}

	size_t MetalVertex2DBatch::num_batches() const noexcept
	{
		return (m_currentBatchIndex + 1);
	}

	BatchInfo2D MetalVertex2DBatch::updateBuffers(const size_t batchIndex)
	{
		assert(batchIndex < num_batches());
		
		const auto& currentVIBuffer = m_viBuffers[m_currentVIBufferIndex][batchIndex];
		
		return{ currentVIBuffer.indexBufferWritePos, 0, 0 };
	}
}
