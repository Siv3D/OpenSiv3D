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

# include "GLES3Mesh.hpp"
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	GLES3Mesh::GLES3Mesh(const MeshData& meshData, const bool isDynamic)
		: GLES3Mesh{ meshData.vertices, meshData.indices, isDynamic } {}

	GLES3Mesh::GLES3Mesh(const size_t vertexCount, const size_t triangleCount)
		: m_vertexCount{ static_cast<uint32>(vertexCount) }
		, m_indexCount{ static_cast<uint32>(triangleCount * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_isDynamic{ true }
	{
		::glGenVertexArrays(1, &m_vao);
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);

		::glBindVertexArray(m_vao);
		{
			{
				::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				::glBufferData(GL_ARRAY_BUFFER, (m_vertexStride * m_vertexCount), nullptr, GL_DYNAMIC_DRAW);
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
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(TriangleIndex32::value_type)* m_indexCount), nullptr, GL_DYNAMIC_DRAW);
			}
		}
		::glBindVertexArray(0);

		m_initialized = true;
	}

	GLES3Mesh::GLES3Mesh(const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices, const bool isDynamic)
		: m_vertexCount{ static_cast<uint32>(vertices.size()) }
		, m_indexCount{ static_cast<uint32>(indices.size() * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_boundingSphere{ Geometry3D::BoundingSphere(vertices) }
		, m_boundingBox{ Geometry3D::BoundingBox(vertices) }
		, m_isDynamic{ isDynamic }
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
				::glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(TriangleIndex32::value_type) * m_indexCount), indices.data(), GL_DYNAMIC_DRAW);
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

	const Sphere& GLES3Mesh::getBoundingSphere() const noexcept
	{
		return m_boundingSphere;
	}

	const Box& GLES3Mesh::getBoundingBox() const noexcept
	{
		return m_boundingBox;
	}

	bool GLES3Mesh::fill(const MeshData& meshData)
	{
		if (not m_isDynamic)
		{
			return false;
		}

		if ((meshData.vertices.size() != m_vertexCount)
			|| ((meshData.indices.size() * 3) != m_indexCount))
		{
			return false;
		}

		{
			::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			::glBufferSubData(GL_ARRAY_BUFFER, 0, meshData.vertices.size_bytes(), meshData.vertices.data());
		}

		{
			::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			::glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, meshData.indices.size_bytes(), meshData.indices.data());
		}

		m_boundingSphere = meshData.computeBoundingSphere();
		m_boundingBox = meshData.computeBoundingBox();

		return true;
	}

	bool GLES3Mesh::fill(const size_t offset, const Vertex3D* vertices, const size_t count)
	{
		if (not m_isDynamic)
		{
			return false;
		}

		if (count == 0)
		{
			return true;
		}

		if ((vertices == nullptr)
			|| (m_vertexCount < (offset + count)))
		{
			return false;
		}

		{
			::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			::glBufferSubData(GL_ARRAY_BUFFER, (sizeof(Vertex3D) * offset), (sizeof(Vertex3D) * count), vertices);
		}

		m_boundingSphere = Geometry3D::MergeBoundingSpheres(m_boundingSphere, Geometry3D::BoundingSphere(vertices, count));
		m_boundingBox = Geometry3D::MergeBoundingBoxes(m_boundingBox, Geometry3D::BoundingBox(vertices, count));

		return true;
	}

	bool GLES3Mesh::fill(const Array<TriangleIndex32>& indices)
	{
		if (not m_isDynamic)
		{
			return false;
		}

		if ((indices.size() * 3) != m_indexCount)
		{
			return false;
		}

		{
			::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			::glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size_bytes(), indices.data());
		}

		return true;
	}

	void GLES3Mesh::bindToContext()
	{
		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	}
}
