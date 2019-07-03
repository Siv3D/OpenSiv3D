//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include "GLSpriteBatch.hpp"

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
	
	GLSpriteBatch::GLSpriteBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1)
	{
	
	}
	
	GLSpriteBatch::~GLSpriteBatch()
	{
		if (m_indexBuffer)
		{
			::glDeleteBuffers(1, &m_indexBuffer);
			m_indexBuffer = 0;
		}
		
		if (m_vertexBuffer)
		{
			::glDeleteBuffers(1, &m_vertexBuffer);
			m_vertexBuffer = 0;
		}
		
		if (m_vao)
		{
			::glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;
		}
	}
	
	bool GLSpriteBatch::init()
	{
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);
		
		::glGenVertexArrays(1, &m_vao);
		
		::glBindVertexArray(m_vao);
		{
			::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * VertexBufferSize, nullptr, GL_DYNAMIC_DRAW);
			
			::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, (GLubyte*)0);
			::glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (GLubyte*)8);
			::glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (GLubyte*)16);
			
			::glEnableVertexAttribArray(0);
			::glEnableVertexAttribArray(1);
			::glEnableVertexAttribArray(2);
			
			::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * IndexBufferSize, nullptr, GL_DYNAMIC_DRAW);
		}
		::glBindVertexArray(0);

		return true;
	}
	
	std::tuple<Vertex2D*, IndexType*, IndexType> GLSpriteBatch::getBuffer(const uint16 vertexSize, const uint32 indexSize, GLRenderer2DCommand& command)
	{
		// VB
		if (const uint32 vertexArrayWritePosTarget = m_vertexArrayWritePos + vertexSize;
			m_vertexArray.size() < vertexArrayWritePosTarget)
		{
			if (MaxVertexArraySize < vertexArrayWritePosTarget)
			{
				return{ nullptr, 0, 0 };
			}
			
			const size_t newVertexArraySize = detail::CalculateNewArraySize(m_vertexArray.size(), vertexArrayWritePosTarget);
			LOG_DEBUG(U"ℹ️ Resized GLSpriteBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
			m_vertexArray.resize(newVertexArraySize);
		}
		
		// IB
		if (const uint32 indexArrayWritePosTarget = m_indexArrayWritePos + indexSize;
			m_indexArray.size() < indexArrayWritePosTarget)
		{
			if (MaxIndexArraySize < indexArrayWritePosTarget)
			{
				return{ nullptr, 0, 0 };
			}
			
			const size_t newIndexArraySize = detail::CalculateNewArraySize(m_indexArray.size(), indexArrayWritePosTarget);
			LOG_DEBUG(U"ℹ️ Resized GLSpriteBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
			m_indexArray.resize(newIndexArraySize);
		}
		
		if (const auto& lastbatch = m_batches.back();
			(VertexBufferSize < (lastbatch.vertexPos + vertexSize) || IndexBufferSize < (lastbatch.indexPos + indexSize)))
		{
			command.pushUpdateBuffers(static_cast<uint32>(m_batches.size()));
			m_batches.emplace_back();
		}
		
		auto& lastbatch = m_batches.back();
		const std::tuple<Vertex2D*, IndexType*, IndexType> result{
			m_vertexArray.data() + m_vertexArrayWritePos
			, m_indexArray.data() + m_indexArrayWritePos
			, lastbatch.vertexPos };
		
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
		
		lastbatch.vertexPos	+= vertexSize;
		lastbatch.indexPos	+= indexSize;
		
		return result;
	}
	
	size_t GLSpriteBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}
	
	void GLSpriteBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();
		
		m_vertexArrayWritePos	= 0;
		m_indexArrayWritePos	= 0;
	}
	
	/*
	void GLSpriteBatch::setBuffers()
	{
		
	}
	 */
	
	BatchInfo GLSpriteBatch::updateBuffers(const size_t batchIndex)
	{
		assert(batchIndex < m_batches.size());
		
		size_t vertexArrayReadPos	= 0;
		size_t indexArrayReadPos	= 0;
		
		for (size_t i = 0; i < batchIndex; ++i)
		{
			vertexArrayReadPos	+= m_batches[i].vertexPos;
			indexArrayReadPos	+= m_batches[i].indexPos;
		}
		
		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		
		BatchInfo batchInfo;
		const auto& currentBatch = m_batches[batchIndex];
		
		// VB
		if (const uint16 vertexSize = currentBatch.vertexPos)
		{
			const Vertex2D* pSrc = m_vertexArray.data() + vertexArrayReadPos;
			
			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				m_vertexBufferWritePos = 0;
				::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * VertexBufferSize, nullptr, GL_DYNAMIC_DRAW);
			}
			
			void* pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * vertexSize,
											GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			std::memcpy(pDst, pSrc, sizeof(Vertex2D) * vertexSize);
			::glUnmapBuffer(GL_ARRAY_BUFFER);
			
			batchInfo.baseVertexLocation = m_vertexBufferWritePos;
			m_vertexBufferWritePos += vertexSize;
		}
		
		// IB
		if (const uint32 indexSize = currentBatch.indexPos)
		{
			const IndexType* pSrc	= m_indexArray.data() + indexArrayReadPos;
			
			if (IndexBufferSize < (m_indexBufferWritePos + indexSize))
			{
				m_indexBufferWritePos = 0;
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * IndexBufferSize, nullptr, GL_DYNAMIC_DRAW);
			}
			
			void* pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * m_indexBufferWritePos, sizeof(IndexType) * indexSize,
											GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			std::memcpy(pDst, pSrc, sizeof(IndexType) * indexSize);
			::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			
			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += indexSize;
		}
		
		return batchInfo;
	}
}
