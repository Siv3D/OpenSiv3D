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

# include "D3D11Mesh.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	D3D11Mesh::D3D11Mesh(ID3D11Device* device, const Array<Vertex3D>& vertices, const Array<Vertex3D::IndexType>& indices)
		: m_vertexCount{ static_cast<uint32>(vertices.size()) }
		, m_indexCount{ static_cast<uint32>(indices.size()) }
		, m_vertexStride{ sizeof(Vertex3D) }
	{
		// Vertex Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (m_vertexStride * m_vertexCount),
				.Usage					= D3D11_USAGE_IMMUTABLE,
				.BindFlags				= D3D11_BIND_VERTEX_BUFFER,
				.CPUAccessFlags			= 0,
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
				.ByteWidth				= (sizeof(Vertex3D::IndexType) * m_indexCount),
				.Usage					= D3D11_USAGE_IMMUTABLE,
				.BindFlags				= D3D11_BIND_INDEX_BUFFER,
				.CPUAccessFlags			= 0,
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

	void D3D11Mesh::bindToContext(ID3D11DeviceContext* context)
	{
		uint32 offset = 0;
		context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_vertexStride, &offset);

		constexpr auto indexFormat = ((sizeof(Vertex3D::IndexType) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT);
		context->IASetIndexBuffer(m_indexBuffer.Get(), indexFormat, 0);
	}
}
