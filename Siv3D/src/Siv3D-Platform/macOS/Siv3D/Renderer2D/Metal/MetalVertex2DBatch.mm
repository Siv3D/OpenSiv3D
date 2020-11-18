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
			m_viBuffers[i].vertexBuffer = [device newBufferWithLength:(sizeof(Vertex2D) * VertexBufferSize)
															  options:MTLResourceStorageModeShared];
			
			m_viBuffers[i].indexBuffer = [device newBufferWithLength:(sizeof(IndexType) * IndexBufferSize)
															 options:MTLResourceStorageModeShared];
		}
		
		return true;
	}

	void MetalVertex2DBatch::begin()
	{
		assert(!m_isActive);
		
		dispatch_semaphore_wait(m_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);
		++m_currentVIBufferIndex %= MaxInflightBuffers;
		
		m_viBuffers[m_currentVIBufferIndex].resetWritePos();
		
		m_isActive = true;
	}

	void MetalVertex2DBatch::end()
	{
		assert(m_isActive);

		m_isActive = false;
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentVertexBuffer() const
	{
		return m_viBuffers[m_currentVIBufferIndex].vertexBuffer;
	}

	id<MTLBuffer> MetalVertex2DBatch::getCurrentIndexBuffer() const
	{
		return m_viBuffers[m_currentVIBufferIndex].indexBuffer;
	}

	dispatch_semaphore_t MetalVertex2DBatch::getSemaphore() const
	{
		return m_frameBoundarySemaphore;
	}

	Vertex2DBufferPointer MetalVertex2DBatch::requestBuffer(const uint16 vertexSize, const uint32 indexSize, MetalRenderer2DCommandManager& commandManager)
	{
		auto& currentVIBuffer = m_viBuffers[m_currentVIBufferIndex];
		
		if (((currentVIBuffer.vertexBufferWritePos + vertexSize) > VertexBufferSize)
			|| ((currentVIBuffer.indexBufferWritePos + indexSize) > IndexBufferSize))
		{
			return{ nullptr, nullptr, 0 };
		}
		
		Vertex2D* const pVertex = static_cast<Vertex2D*>(currentVIBuffer.vertexBuffer.contents)
		+ currentVIBuffer.vertexBufferWritePos;
		IndexType* const pIndex = static_cast<IndexType*>(currentVIBuffer.indexBuffer.contents)
		+ currentVIBuffer.indexBufferWritePos;
		const Vertex2D::IndexType indexOffset = static_cast<Vertex2D::IndexType>(currentVIBuffer.vertexBufferWritePos);

		currentVIBuffer.vertexBufferWritePos += vertexSize;
		currentVIBuffer.indexBufferWritePos += indexSize;

		return{ pVertex, pIndex, indexOffset };
	}
}
