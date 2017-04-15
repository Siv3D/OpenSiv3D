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

namespace s3d
{
	using IndexType = uint32;

	class GLSpriteBatch
	{
	private:

		Array<Vertex2D> m_vertices;
		
		Array<IndexType> m_indices;

		
		GLuint m_vao = 0;
		
		GLuint m_vertexBuffer = 0;
		
		GLuint m_indexBuffer = 0;
		
		uint32 m_vertexBufferWritePos = 0;
		
		uint32 m_indexBufferWritePos = 0;
		
		uint32 m_vertexPos = 0;
		
		uint32 m_indexPos = 0;
		
		
		bool m_initialized = false;

		// 仮の値
		static constexpr uint32 MaxVertexSize	= 65536;
		static constexpr uint32 MaxIndexSize	= 65536 * 8;

		static constexpr uint32 VertexBufferSize	= 65536;
		static constexpr uint32 IndexBufferSize		= 65536 * 8;

		void resizeVertixes(const uint32 requiredVertexSize)
		{
			size_t newVertexSize = m_vertices.size() * 2;

			while (newVertexSize < requiredVertexSize)
			{
				newVertexSize *= 2;
			}

			m_vertices.resize(newVertexSize);
		}

		void resizeIndices(const uint32 requiredIndexSize)
		{
			size_t newIndexSize = m_indices.size() * 2;

			while (newIndexSize < requiredIndexSize)
			{
				newIndexSize *= 2;
			}

			m_indices.resize(newIndexSize);
		}
	public:

		GLSpriteBatch()
			: m_vertices(MaxVertexSize)
			, m_indices(MaxIndexSize)
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
				
				::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)0);
				::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)8);
				::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)16);
				
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

		bool getBuffer(const uint32 vertexSize, const uint32 indexSize, Vertex2D** pVertex, IndexType** pIndices, IndexType* indexOffset)
		{
			// VB
			const uint32 requiredVertexSize = m_vertexPos + vertexSize;

			if (m_vertices.size() < requiredVertexSize)
			{
				if (MaxVertexSize < requiredVertexSize
					|| VertexBufferSize < requiredVertexSize) // 仮
				{
					return false;
				}

				resizeVertixes(requiredVertexSize);
			}

			// IB
			const uint32 requiredIndexSize = m_indexPos + indexSize;

			if (m_indices.size() < requiredIndexSize)
			{
				if (MaxIndexSize < requiredIndexSize
					|| IndexBufferSize < requiredIndexSize) // 仮
				{
					return false;
				}

				resizeIndices(requiredIndexSize);
			}

			*pVertex = m_vertices.data() + m_vertexPos;
			*pIndices = m_indices.data() + m_indexPos;
			*indexOffset = m_vertexPos;

			m_vertexPos = requiredVertexSize;
			m_indexPos = requiredIndexSize;

			return true;
		}

		// 仮の実装
		std::pair<uint32, uint32> setBuffers()
		{
			std::pair<uint32, uint32> vi{ 0,0 };

			::glBindVertexArray(m_vao);
			
			{
				const Vertex2D* vertexData = m_vertices.data();
				const size_t vertexSize = m_vertexPos;
				
				if (VertexBufferSize < m_vertexBufferWritePos + vertexSize)
				{
					m_vertexBufferWritePos = 0;
				}
				
				const uint32 vertexOffset = m_vertexBufferWritePos;
				{
					void* pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * m_vertexBufferWritePos, sizeof(Vertex2D) * vertexSize,
													GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
					
					::memcpy(pDst, vertexData, sizeof(Vertex2D) * vertexSize);
					
					::glUnmapBuffer(GL_ARRAY_BUFFER);
				}

				m_vertexBufferWritePos += vertexSize;
				vi.first = vertexOffset;

				
				IndexType* indexData = m_indices.data();
				const size_t indexSize = m_indexPos;
				
				if (IndexBufferSize < m_indexBufferWritePos + indexSize)
				{
					m_indexBufferWritePos = 0;
				}

				for (uint32 i = 0; i < indexSize; ++i)
				{
					indexData[i] += vertexOffset;
				}
				
				const uint32 indexOffset = m_indexBufferWritePos;
				{
					void* pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * m_indexBufferWritePos, sizeof(uint32) * indexSize,
													GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
					
					::memcpy(pDst, indexData, sizeof(uint32) * indexSize);
					
					::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
				}

				m_indexBufferWritePos += indexSize;
				vi.second = indexOffset;
			}
			
			return vi;
		}

		void clear()
		{
			m_vertexPos = 0;

			m_indexPos = 0;
		}
	};
}

# endif
