//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GLES3Mesh.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	GLES3Mesh::GLES3Mesh(const Array<Vertex3D>& vertices, const Array<Vertex3D::IndexType>& indices)
		: m_vertexCount{ static_cast<uint32>(vertices.size()) }
		, m_indexCount{ static_cast<uint32>(indices.size()) }
		, m_vertexStride{ sizeof(Vertex3D) }
	{
		::glGenVertexArrays(1, &m_vao);
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);

		::glBindVertexArray(m_vao);
		{
			{
				::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				::glBufferData(GL_ARRAY_BUFFER, (m_vertexStride * m_vertexCount), vertices.data(), GL_DYNAMIC_DRAW);
			}

			{
				::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)0);	// Vertex3D::pos
				::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)12);	// Vertex3D::normal
				::glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (const GLubyte*)24);	// Vertex3D::tex

				::glEnableVertexAttribArray(0);
				::glEnableVertexAttribArray(1);
				::glEnableVertexAttribArray(2);
			}

			{
				::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(Vertex3D::IndexType) * m_indexCount), indices.data(), GL_DYNAMIC_DRAW);
			}
		}
		::glBindVertexArray(0);

		m_initialized = true;
	}

	GLES3Mesh::~GLES3Mesh()
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

	bool GLES3Mesh::isInitialized() const noexcept
	{
		return m_initialized;
	}

	uint32 GLES3Mesh::getVertexCount() const noexcept
	{
		return m_vertexCount;
	}

	uint32 GLES3Mesh::getIndexCount() const noexcept
	{
		return m_indexCount;
	}

	void GLES3Mesh::bindToContext()
	{
		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	}
}
