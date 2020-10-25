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

# include "Vertex2DBatch_Metal.hpp"

namespace s3d
{
	void Vertex2DBatch_Metal::init(id<MTLDevice> device)
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
	}

	void Vertex2DBatch_Metal::begin()
	{
		assert(!m_isActive);
		
		dispatch_semaphore_wait(m_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);
		++m_currentBufferIndex %= MaxInflightBuffers;
		m_currentVertexBufferWritePos = 0;
		m_currentIndexBufferWritePos = 0;
		
		m_isActive = true;
	}

	void Vertex2DBatch_Metal::end()
	{
		assert(m_isActive);

		m_isActive = false;
	}

	id<MTLBuffer> Vertex2DBatch_Metal::getCurrentVertexBuffer() const
	{
		return m_vertexBuffers[m_currentBufferIndex];
	}

	id<MTLBuffer> Vertex2DBatch_Metal::getCurrentIndexBuffer() const
	{
		return m_indexBuffers[m_currentBufferIndex];
	}

	dispatch_semaphore_t Vertex2DBatch_Metal::getSemaphore() const
	{
		return m_frameBoundarySemaphore;
	}

	std::tuple<Vertex2D*, Vertex2DBatch_Metal::IndexType*, Vertex2DBatch_Metal::IndexType> Vertex2DBatch_Metal::requestBuffer(const uint16 vertexSize, const uint32 indexSize, Renderer2DCommand_Metal& command)
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
		const auto indexOffset = m_currentVertexBufferWritePos;

		m_currentVertexBufferWritePos += vertexSize;
		m_currentIndexBufferWritePos += indexSize;

		return{ pVertex, pIndex, indexOffset };
	}
}
