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
# include "GL4Vertex2DBatch.hpp"

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

	GL4Vertex2DBatch::GL4Vertex2DBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1)
	{

	}

	GL4Vertex2DBatch::~GL4Vertex2DBatch()
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

	bool GL4Vertex2DBatch::init()
	{
		::glGenVertexArrays(1, &m_vao);
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);

		::glBindVertexArray(m_vao);
		{
			{
				::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				::glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex2D) * VertexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			{
				::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)0);	// Vertex2D::pos
				::glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)8);	// Vertex2D::tex
				::glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)16);	// Vertex2D::color

				::glEnableVertexAttribArray(0);
				::glEnableVertexAttribArray(1);
				::glEnableVertexAttribArray(2);
			}

			{
				::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(Vertex2D::IndexType) * IndexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}
		}
		::glBindVertexArray(0);

		return true;
	}

	Vertex2DBufferPointer GL4Vertex2DBatch::requestBuffer(const uint16 vertexSize, const uint32 indexSize, GL4Renderer2DCommandManager& commandManager)
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
			LOG_TRACE(U"ℹ️ Resized GL4Vertex2DBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
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
			LOG_TRACE(U"ℹ️ Resized GL4Vertex2DBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
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

	size_t GL4Vertex2DBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}

	void GL4Vertex2DBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();

		m_vertexArrayWritePos = 0;
		m_indexArrayWritePos = 0;
	}

	void GL4Vertex2DBatch::setBuffers()
	{
		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	}

	BatchInfo2D GL4Vertex2DBatch::updateBuffers(const size_t batchIndex)
	{
		assert(batchIndex < m_batches.size());

		size_t vertexArrayReadPos = 0;
		size_t indexArrayReadPos = 0;

		for (size_t i = 0; i < batchIndex; ++i)
		{
			vertexArrayReadPos += m_batches[i].vertexPos;
			indexArrayReadPos += m_batches[i].indexPos;
		}

		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		BatchInfo2D batchInfo;
		const auto& currentBatch = m_batches[batchIndex];

		// VB
		if (const uint16 vertexSize = currentBatch.vertexPos)
		{
			const Vertex2D* pSrc = &m_vertexArray[vertexArrayReadPos];

			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				m_vertexBufferWritePos = 0;
				::glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex2D) * VertexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			void* const pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * vertexSize,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			{
				std::memcpy(pDst, pSrc, sizeof(Vertex2D) * vertexSize);
			}
			::glUnmapBuffer(GL_ARRAY_BUFFER);

			batchInfo.baseVertexLocation = m_vertexBufferWritePos;
			m_vertexBufferWritePos += vertexSize;
		}

		// IB
		if (const uint32 indexSize = currentBatch.indexPos)
		{
			const Vertex2D::IndexType* pSrc = &m_indexArray[indexArrayReadPos];

			if (IndexBufferSize < (m_indexBufferWritePos + indexSize))
			{
				m_indexBufferWritePos = 0;
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(Vertex2D::IndexType) * IndexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			void* const pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex2D::IndexType) * m_indexBufferWritePos, sizeof(Vertex2D::IndexType) * indexSize,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			{
				std::memcpy(pDst, pSrc, (sizeof(Vertex2D::IndexType) * indexSize));
			}
			::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += indexSize;
		}

		return batchInfo;
	}

	void GL4Vertex2DBatch::advanceArrayWritePos(const uint16 vertexSize, const uint32 indexSize) noexcept
	{
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
	}
}
