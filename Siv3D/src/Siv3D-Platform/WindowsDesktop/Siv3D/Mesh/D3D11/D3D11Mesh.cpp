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

# include "D3D11Mesh.hpp"
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	D3D11Mesh::D3D11Mesh(ID3D11Device* device, const MeshData& meshData, const bool isDynamic)
		: D3D11Mesh{ device, meshData.vertices, meshData.indices, isDynamic } {}

	D3D11Mesh::D3D11Mesh(ID3D11Device* device, const size_t vertexCount, const size_t triangleCount)
		: m_vertexCount{ static_cast<uint32>(vertexCount) }
		, m_indexCount{ static_cast<uint32>(triangleCount * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_isDynamic{ true }
	{
		// Vertex Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (m_vertexStride * m_vertexCount),
				.Usage					= D3D11_USAGE_DYNAMIC,
				.BindFlags				= D3D11_BIND_VERTEX_BUFFER,
				.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
				.MiscFlags				= 0,
				.StructureByteStride	= 0, 
			};

			if (FAILED(device->CreateBuffer(&desc, nullptr, &m_vertexBuffer)))
			{
				return;
			}
		}

		// Index Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (sizeof(TriangleIndex32::value_type) * m_indexCount),
				.Usage					= D3D11_USAGE_DYNAMIC,
				.BindFlags				= D3D11_BIND_INDEX_BUFFER,
				.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
				.MiscFlags				= 0,
				.StructureByteStride	= 0,
			};

			if (FAILED(device->CreateBuffer(&desc, nullptr, &m_indexBuffer)))
			{
				return;
			}
		}

		m_initialized = true;
	}

	D3D11Mesh::D3D11Mesh(ID3D11Device* device, const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices, const bool isDynamic)
		: m_vertexCount{ static_cast<uint32>(vertices.size()) }
		, m_indexCount{ static_cast<uint32>(indices.size() * 3) }
		, m_vertexStride{ sizeof(Vertex3D) }
		, m_boundingSphere{ Geometry3D::BoundingSphere(vertices) }
		, m_boundingBox{ Geometry3D::BoundingBox(vertices) }
		, m_isDynamic{ isDynamic }
	{
		// Vertex Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (m_vertexStride * m_vertexCount),
				.Usage					= (isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE),
				.BindFlags				= D3D11_BIND_VERTEX_BUFFER,
				.CPUAccessFlags			= (isDynamic ? D3D11_CPU_ACCESS_WRITE : 0u),
				.MiscFlags				= 0,
				.StructureByteStride	= 0, 
			};

			if (D3D11_SUBRESOURCE_DATA initData{ vertices.data() }; 
				FAILED(device->CreateBuffer(&desc, &initData, &m_vertexBuffer)))
			{
				return;
			}
		}

		// Index Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (sizeof(TriangleIndex32::value_type) * m_indexCount),
				.Usage					= (isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE),
				.BindFlags				= D3D11_BIND_INDEX_BUFFER,
				.CPUAccessFlags			= (isDynamic ? D3D11_CPU_ACCESS_WRITE : 0u),
				.MiscFlags				= 0,
				.StructureByteStride	= 0,
			};

			if (D3D11_SUBRESOURCE_DATA initData{ indices.data() }; 
				FAILED(device->CreateBuffer(&desc, &initData, &m_indexBuffer)))
			{
				return;
			}
		}

		m_initialized = true;
	}

	bool D3D11Mesh::isInitialized() const noexcept
	{
		return m_initialized;
	}

	ID3D11Buffer* D3D11Mesh::getVertexBuffer()
	{
		return m_vertexBuffer.Get();
	}

	ID3D11Buffer* D3D11Mesh::getIndexBuffer()
	{
		return m_indexBuffer.Get();
	}

	uint32 D3D11Mesh::getVertexCount() const noexcept
	{
		return m_vertexCount;
	}

	uint32 D3D11Mesh::getIndexCount() const noexcept
	{
		return m_indexCount;
	}

	const Sphere& D3D11Mesh::getBoundingSphere() const noexcept
	{
		return m_boundingSphere;
	}

	const Box& D3D11Mesh::getBoundingBox() const noexcept
	{
		return m_boundingBox;
	}

	bool D3D11Mesh::fill(ID3D11DeviceContext* context, const MeshData& meshData)
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
			D3D11_MAPPED_SUBRESOURCE mapped;

			if (FAILED(context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
			{
				return false;
			}

			if (mapped.pData)
			{
				::memcpy(mapped.pData, meshData.vertices.data(), meshData.vertices.size_bytes());
			}

			context->Unmap(m_vertexBuffer.Get(), 0);
		}

		{
			D3D11_MAPPED_SUBRESOURCE mapped;

			if (FAILED(context->Map(m_indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
			{
				return false;
			}

			if (mapped.pData)
			{
				::memcpy(mapped.pData, meshData.indices.data(), meshData.indices.size_bytes());
			}

			context->Unmap(m_indexBuffer.Get(), 0);
		}

		m_boundingSphere = meshData.computeBoundingSphere();
		m_boundingBox = meshData.computeBoundingBox();

		return true;
	}

	bool D3D11Mesh::fill(ID3D11DeviceContext* context, const size_t offset, const Vertex3D* vertices, const size_t count)
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
			D3D11_MAPPED_SUBRESOURCE mapped;

			if (FAILED(context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
			{
				return false;
			}

			if (mapped.pData)
			{
				::memcpy((static_cast<Vertex3D*>(mapped.pData) + offset), vertices, (count * sizeof(Vertex3D)));
			}

			context->Unmap(m_vertexBuffer.Get(), 0);
		}

		m_boundingSphere = Geometry3D::MergeBoundingSpheres(m_boundingSphere, Geometry3D::BoundingSphere(vertices, count));
		m_boundingBox = Geometry3D::MergeBoundingBoxes(m_boundingBox, Geometry3D::BoundingBox(vertices, count));

		return true;
	}

	bool D3D11Mesh::fill(ID3D11DeviceContext* context, const Array<TriangleIndex32>& indices)
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
			D3D11_MAPPED_SUBRESOURCE mapped;

			if (FAILED(context->Map(m_indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
			{
				return false;
			}

			if (mapped.pData)
			{
				::memcpy(mapped.pData, indices.data(), indices.size_bytes());
			}

			context->Unmap(m_indexBuffer.Get(), 0);
		}

		return true;
	}

	void D3D11Mesh::bindToContext(ID3D11DeviceContext* context)
	{
		uint32 offset = 0;
		context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_vertexStride, &offset);

		constexpr auto indexFormat = ((sizeof(Vertex3D::IndexType) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT);
		context->IASetIndexBuffer(m_indexBuffer.Get(), indexFormat, 0);
	}
}
