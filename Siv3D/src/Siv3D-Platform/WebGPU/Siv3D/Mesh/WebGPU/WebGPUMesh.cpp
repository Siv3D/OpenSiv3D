//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "WebGPUMesh.hpp"
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	WebGPUMesh::WebGPUMesh(const wgpu::Device& device, const MeshData& meshData, const bool isDynamic)
		: WebGPUMesh{ device, meshData.vertices, meshData.indices, isDynamic } {}

	WebGPUMesh::WebGPUMesh(const wgpu::Device& device, const size_t vertexCount, const size_t triangleCount)
		: m_vertexCount{ static_cast<uint32>(vertexCount) }
		, m_indexCount{ static_cast<uint32>(triangleCount * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_isDynamic{ true }
	{
		{
			wgpu::BufferDescriptor indexBufferDescripter
			{
				.size = sizeof(TriangleIndex32::value_type) * m_indexCount,
				.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
			};

			m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
		}

		{
			wgpu::BufferDescriptor vertexBufferDescripter
			{
				.size = m_vertexStride * m_vertexCount,
				.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
			};

			m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
		}
		
		m_initialized = true;
	}

	WebGPUMesh::WebGPUMesh(const wgpu::Device& device, const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices, const bool isDynamic)
		: m_vertexCount{ static_cast<uint32>(vertices.size()) }
		, m_indexCount{ static_cast<uint32>(indices.size() * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_boundingSphere{ Geometry3D::BoundingSphere(vertices) }
		, m_boundingBox{ Geometry3D::BoundingBox(vertices) }
		, m_isDynamic{ isDynamic }
	{
		{
			wgpu::BufferDescriptor indexBufferDescripter
			{
				.size = sizeof(TriangleIndex32::value_type) * m_indexCount,
				.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst
			};

			m_indexBuffer = device.CreateBuffer(&indexBufferDescripter);
			device.GetQueue().WriteBuffer(m_indexBuffer, 0, indices.data(), indexBufferDescripter.size);
		}

		{
			wgpu::BufferDescriptor vertexBufferDescripter
			{
				.size = m_vertexStride * m_vertexCount,
				.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst
			};

			m_vertexBuffer = device.CreateBuffer(&vertexBufferDescripter);
			device.GetQueue().WriteBuffer(m_vertexBuffer, 0, vertices.data(), vertexBufferDescripter.size);
		}
	
		m_initialized = true;
	}

	WebGPUMesh::~WebGPUMesh()
	{
	}

	bool WebGPUMesh::isInitialized() const noexcept
	{
		return m_initialized;
	}

	uint32 WebGPUMesh::getVertexCount() const noexcept
	{
		return m_vertexCount;
	}

	uint32 WebGPUMesh::getIndexCount() const noexcept
	{
		return m_indexCount;
	}

	const Sphere& WebGPUMesh::getBoundingSphere() const noexcept
	{
		return m_boundingSphere;
	}

	const Box& WebGPUMesh::getBoundingBox() const noexcept
	{
		return m_boundingBox;
	}

	bool WebGPUMesh::fill(const wgpu::Device& device, const MeshData& meshData)
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
		
		device.GetQueue().WriteBuffer(m_vertexBuffer, 0, meshData.vertices.data(), meshData.vertices.size_bytes());		
		device.GetQueue().WriteBuffer(m_indexBuffer, 0, meshData.indices.data(), meshData.indices.size_bytes());
		
		m_boundingSphere = meshData.computeBoundingSphere();
		m_boundingBox = meshData.computeBoundingBox();

		return true;
	}

	bool WebGPUMesh::fill(const wgpu::Device& device, const size_t offset, const Vertex3D* vertices, const size_t count)
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

		device.GetQueue().WriteBuffer(m_vertexBuffer, (sizeof(Vertex3D) * offset), vertices, (sizeof(Vertex3D) * count));

		m_boundingSphere = Geometry3D::MergeBoundingSpheres(m_boundingSphere, Geometry3D::BoundingSphere(vertices, count));
		m_boundingBox = Geometry3D::MergeBoundingBoxes(m_boundingBox, Geometry3D::BoundingBox(vertices, count));

		return true;
	}

	bool WebGPUMesh::fill(const wgpu::Device& device, const Array<TriangleIndex32>& indices)
	{
		if (not m_isDynamic)
		{
			return false;
		}

		if ((indices.size() * 3) != m_indexCount)
		{
			return false;
		}

		device.GetQueue().WriteBuffer(m_indexBuffer, 0, indices.data(), indices.size_bytes());

		return true;
	}

	void WebGPUMesh::bindToContext(const wgpu::RenderPassEncoder& pass)
	{
		// ::glBindVertexArray(m_vao);
		// ::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		pass.SetVertexBuffer(0, m_vertexBuffer, 0, m_vertexStride * m_vertexCount);
		pass.SetIndexBuffer(m_indexBuffer, wgpu::IndexFormat::Uint32, 0, sizeof(TriangleIndex32::value_type) * m_indexCount);
	}
}
