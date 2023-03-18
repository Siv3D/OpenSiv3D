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
# include "GLES3Line3DBatch.hpp"

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

	GLES3Line3DBatch::GLES3Line3DBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1) {}

	GLES3Line3DBatch::~GLES3Line3DBatch()
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

	bool GLES3Line3DBatch::init()
	{
		::glGenVertexArrays(1, &m_vao);
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);

		::glBindVertexArray(m_vao);
		{
			{
				::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				::glBufferData(GL_ARRAY_BUFFER, (sizeof(VertexLine3D) * VertexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			{
				::glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)0);	// VertexLine3D::pos
				::glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)16);	// VertexLine3D::color

				::glEnableVertexAttribArray(0);
				::glEnableVertexAttribArray(1);
			}

			{
				::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(VertexLine3D::IndexType) * IndexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}
		}
		::glBindVertexArray(0);

		return true;
	}

	VertexLine3DBufferPointer GLES3Line3DBatch::requestBuffer(const VertexLine3D::IndexType vertexSize, const uint32 indexSize, GLES3Renderer3DCommandManager& commandManager)
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
			LOG_TRACE(U"ℹ️ Resized GLES3Line3DBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
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
			LOG_TRACE(U"ℹ️ Resized GLES3Line3DBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
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

	size_t GLES3Line3DBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}

	bool GLES3Line3DBatch::isEmpty() const noexcept
	{
		return (m_vertexArrayWritePos == 0);
	}

	void GLES3Line3DBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();

		m_vertexArrayWritePos = 0;
		m_indexArrayWritePos = 0;

		m_vertexBufferWritePos = 0;
	}

	void GLES3Line3DBatch::setBuffers()
	{
		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	}

	BatchInfoLine3D GLES3Line3DBatch::updateBuffers(const size_t batchIndex)
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

		BatchInfoLine3D batchInfo;
		const auto& currentBatch = m_batches[batchIndex];

		// VB
		if (const VertexLine3D::IndexType vertexSize = currentBatch.vertexPos)
		{
			const VertexLine3D* pSrc = &m_vertexArray[vertexArrayReadPos];

			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				m_vertexBufferWritePos = 0;
				::glBufferData(GL_ARRAY_BUFFER, (sizeof(VertexLine3D) * VertexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			void* const pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(VertexLine3D) * m_vertexBufferWritePos, sizeof(VertexLine3D) * vertexSize,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
				// GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			{
				std::memcpy(pDst, pSrc, sizeof(VertexLine3D) * vertexSize);
			}
			::glUnmapBuffer(GL_ARRAY_BUFFER);

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
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(VertexLine3D::IndexType) * IndexBufferSize), nullptr, GL_DYNAMIC_DRAW);
			}

			void* const pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexLine3D::IndexType) * m_indexBufferWritePos, sizeof(VertexLine3D::IndexType) * indexSize,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
				// GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			{
				std::memcpy(pDst, pSrc, (sizeof(VertexLine3D::IndexType) * indexSize));
			}
			::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += indexSize;
		}

		return batchInfo;
	}

	void GLES3Line3DBatch::advanceArrayWritePos(const VertexLine3D::IndexType vertexSize, const uint32 indexSize) noexcept
	{
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
	}
}
