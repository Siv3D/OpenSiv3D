//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "MetalVertex2DBatch.hpp"

namespace s3d
{
	bool MetalVertex2DBatch::init(id<MTLDevice> device)
	{
		for(size_t i = 0; i < MaxInflightBuffers; ++i)
		{
			m_vertexBuffers[i] = [device newBufferWithLength:(sizeof(Vertex2D) * VertexBufferSize)
													 options:MTLResourceStorageModeShared];
		}
		
		for(size_t i = 0; i < MaxInflightBuffers; ++i)
		{
			m_indexBuffers[i] = [device newBufferWithLength:(sizeof(IndexType) * IndexBufferSize)
													 options:MTLResourceStorageModeShared];
		}
		
		return true;
	}

	void MetalVertex2DBatch::begin()
	{
		assert(!m_isActive);
		
		dispatch_semaphore_wait(m_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);
		++m_currentBufferIndex %= MaxInflightBuffers;
		m_currentVertexBufferWritePos = 0;
		m_currentIndexBufferWritePos = 0;
		
		m_isActive = true;
	}

	void MetalVertex2DBatch::end()
	{
		assert(m_isActive);

		m_isActive = false;
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentVertexBuffer() const
	{
		return m_vertexBuffers[m_currentBufferIndex];
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentIndexBuffer() const
	{
		return m_indexBuffers[m_currentBufferIndex];
	}

	dispatch_semaphore_t MetalVertex2DBatch::getSemaphore() const
	{
		return m_frameBoundarySemaphore;
	}

	Vertex2DBufferPointer MetalVertex2DBatch::requestBuffer(const uint16 vertexSize, const uint32 indexSize, MetalRenderer2DCommandManager& commandManager)
	{
		if (((m_currentVertexBufferWritePos + vertexSize) > VertexBufferSize)
			|| ((m_currentIndexBufferWritePos + indexSize) > IndexBufferSize))
		{
			return{ nullptr, nullptr, 0 };
		}
		
		Vertex2D* const pVertex = static_cast<Vertex2D*>(m_vertexBuffers[m_currentBufferIndex].contents)
		+ m_currentVertexBufferWritePos;
		IndexType* const pIndex = static_cast<IndexType*>(m_indexBuffers[m_currentBufferIndex].contents)
		+ m_currentIndexBufferWritePos;
		const uint32 indexOffset = static_cast<uint32>(m_currentVertexBufferWritePos);

		m_currentVertexBufferWritePos += vertexSize;
		m_currentIndexBufferWritePos += indexSize;

		return{ pVertex, pIndex, indexOffset };
	}
}
