//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Logger.hpp>
# include "GLRenderer2DCommandManager.hpp"

namespace s3d
{
	using IndexType = uint32;

	
	struct BatchBufferPos
	{
		uint32 vertexPos = 0;
		
		uint32 indexPos = 0;
	};
	
	struct BatchDrawOffset
	{
		uint32 indexCount = 0;
		
		uint32 indexStartLocation = 0;
		
		uint32 vertexStartLocation = 0;
	};
	
	class GLSpriteBatch
	{
	private:
		
		GLuint m_vao = 0;
		
		GLuint m_vertexBuffer = 0;
		
		GLuint m_indexBuffer = 0;

		
		
		
		Array<Vertex2D> m_vertices;
		
		Array<IndexType> m_indices;
		
		uint32 m_vertexArrayWritePos = 0;
		
		uint32 m_indexArrayWritePos = 0;
		
		
		uint32 m_vertexBufferWritePos = 0;
		
		uint32 m_indexBufferWritePos = 0;
		
		
		Array<BatchBufferPos> m_batches;
		
		
		bool m_initialized = false;

		// 仮の値
		static constexpr uint32 InitialVertexSize = 4096;
		static constexpr uint32 InitialIndexSize = 4096 * 8;
		
		static constexpr uint32 MaxVertexSize	= 65536 * 64;
		static constexpr uint32 MaxIndexSize	= 65536 * 64;

		static constexpr uint32 VertexBufferSize	= 65536;
		static constexpr uint32 IndexBufferSize		= 65536 * 8;

		void resizeVertices(const uint32 requiredVertexSize)
		{
			size_t newVertexSize = m_vertices.size() * 2;

			while (newVertexSize < requiredVertexSize)
			{
				newVertexSize *= 2;
			}
			
			LOG_DEBUG(L"ℹ️ Resized 2D vertex array (size: {0})"_fmt(newVertexSize));

			m_vertices.resize(newVertexSize);
		}

		void resizeIndices(const uint32 requiredIndexSize)
		{
			size_t newIndexSize = m_indices.size() * 2;

			while (newIndexSize < requiredIndexSize)
			{
				newIndexSize *= 2;
			}
			
			LOG_DEBUG(L"ℹ️ Resized 2D index array (size: {0})"_fmt(newIndexSize));

			m_indices.resize(newIndexSize);
		}
		
	public:

		GLSpriteBatch()
			: m_vertices(InitialVertexSize)
			, m_indices(InitialIndexSize)
			, m_batches(1)
		{

		}
		
		~GLSpriteBatch()
		{
			if (m_initialized)
			{
				::glDeleteVertexArrays(1, &m_vao);
				::glDeleteBuffers(1, &m_indexBuffer);
				::glDeleteBuffers(1, &m_vertexBuffer);
			}
		}
		
		bool init()
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
			
			m_initialized = true;

			return true;
		}

		bool getBuffer(const uint32 vertexSize, const uint32 indexSize, Vertex2D** pVertex, IndexType** pIndices, IndexType* indexOffset, GLRender2DCommandManager& commandManager)
		{
			// VB
			const uint32 requiredVertexSize = m_vertexArrayWritePos + vertexSize;

			if (m_vertices.size() < requiredVertexSize)
			{
				if (MaxVertexSize < requiredVertexSize)
				{
					return false;
				}

				resizeVertices(requiredVertexSize);
			}

			// IB
			const uint32 requiredIndexSize = m_indexArrayWritePos + indexSize;

			if (m_indices.size() < requiredIndexSize)
			{
				if (MaxIndexSize < requiredIndexSize)
				{
					return false;
				}

				resizeIndices(requiredIndexSize);
			}
			
			if (VertexBufferSize < (m_batches.back().vertexPos + vertexSize)
				|| IndexBufferSize < (m_batches.back().indexPos + indexSize))
			{
				m_batches.emplace_back();
				
				commandManager.pushNextBatch();
			}

			*pVertex = m_vertices.data() + m_vertexArrayWritePos;
			*pIndices = m_indices.data() + m_indexArrayWritePos;
			*indexOffset = m_batches.back().vertexPos;

			m_vertexArrayWritePos += vertexSize;
			m_indexArrayWritePos += indexSize;
			
			m_batches.back().vertexPos += vertexSize;
			m_batches.back().indexPos += indexSize;

			return true;
		}
		
		size_t getBatchCount() const
		{
			return m_batches.size();
		}

		// 仮の実装
		BatchDrawOffset setBuffers(const size_t batchIndex)
		{
			BatchDrawOffset batchDrawOffset;
			
			size_t vertexArrayOffset = 0;
			size_t indexArrayOffset = 0;
			
			for (size_t i = 0; i < batchIndex; ++i)
			{
				vertexArrayOffset += m_batches[i].vertexPos;
				indexArrayOffset += m_batches[i].indexPos;
			}

			::glBindVertexArray(m_vao);
			
			{
				const Vertex2D* vertexData = m_vertices.data() + vertexArrayOffset;
				const size_t vertexSize = m_batches[batchIndex].vertexPos;
				
				if (VertexBufferSize < m_vertexBufferWritePos + vertexSize)
				{
					m_vertexBufferWritePos = 0;
					::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * VertexBufferSize, nullptr, GL_DYNAMIC_DRAW);
				}
				
				const uint32 vertexOffset = m_vertexBufferWritePos;

				if (vertexSize)
				{
					void* pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * vertexSize,
													GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
					
					::memcpy(pDst, vertexData, sizeof(Vertex2D) * vertexSize);
					
					::glUnmapBuffer(GL_ARRAY_BUFFER);
				}

				m_vertexBufferWritePos += vertexSize;
				batchDrawOffset.vertexStartLocation = vertexOffset;
				
				IndexType* indexData = m_indices.data() + indexArrayOffset;
				const uint32 indexSize = m_batches[batchIndex].indexPos;
				
				if (IndexBufferSize < m_indexBufferWritePos + indexSize)
				{
					m_indexBufferWritePos = 0;
					::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * IndexBufferSize, nullptr, GL_DYNAMIC_DRAW);
				}
				
				const uint32 indexOffset = m_indexBufferWritePos;

				if (indexSize)
				{
					void* pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * m_indexBufferWritePos, sizeof(uint32) * indexSize,
													GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
					
					::memcpy(pDst, indexData, sizeof(uint32) * indexSize);
					
					::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
				}

				m_indexBufferWritePos += indexSize;
				batchDrawOffset.indexCount = indexSize;
				batchDrawOffset.indexStartLocation = indexOffset;
			}

			return batchDrawOffset;
		}

		void clear()
		{
			m_batches = Array<BatchBufferPos>(1);
			
			m_vertexArrayWritePos = m_indexArrayWritePos = 0;
		}
	};
}

# endif
