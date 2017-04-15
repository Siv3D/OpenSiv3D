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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IRenderer2D.hpp"

# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>

namespace s3d
{
	using IndexType = uint32;

	class D3D11SpriteBatch
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11Buffer> m_vertexBuffer;

		ComPtr<ID3D11Buffer> m_indexBuffer;

		Array<Vertex2D> m_vertices;

		Array<IndexType> m_indices;

		uint32 m_indexBufferWritePos = 0;

		uint32 m_vertexBufferWritePos = 0;

		uint32 m_vertexPos = 0;

		uint32 m_indexPos = 0;


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

		D3D11SpriteBatch()
			: m_vertices(MaxVertexSize)
			, m_indices(MaxIndexSize)
		{

		}

		bool init(ID3D11Device* const device, ID3D11DeviceContext* const context)
		{
			m_device = device;
			m_context = context;

			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth				= sizeof(Vertex2D) * VertexBufferSize;
				desc.Usage					= D3D11_USAGE_DYNAMIC;
				desc.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
				desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
				desc.MiscFlags				= 0;
				desc.StructureByteStride	= 0;

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_vertexBuffer)))
				{
					return false;
				}
			}

			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth				= sizeof(IndexType) * IndexBufferSize;
				desc.Usage					= D3D11_USAGE_DYNAMIC;
				desc.BindFlags				= D3D11_BIND_INDEX_BUFFER;
				desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
				desc.MiscFlags				= 0;
				desc.StructureByteStride	= 0;

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_indexBuffer)))
				{
					return false;
				}
			}

			return true;
		}

		bool getBuffer(const uint32 vertexSize, const uint32 indexSize, Vertex2D** pVertex, IndexType** pIndices, IndexType* indexOffset)
		{
			// VB
			const size_t requiredVertexSize = m_vertexPos + vertexSize;

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
			const size_t requiredIndexSize = m_indexPos + indexSize;

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

			{
				const Vertex2D* vertexData = m_vertices.data();
				const size_t vertexSize = m_vertexPos;

				D3D11_MAP mapType = D3D11_MAP_WRITE_NO_OVERWRITE;

				if (VertexBufferSize < m_vertexBufferWritePos + vertexSize)
				{
					mapType = D3D11_MAP_WRITE_DISCARD;
					m_vertexBufferWritePos = 0;
				}

				D3D11_MAPPED_SUBRESOURCE vres;

				if (SUCCEEDED(m_context->Map(m_vertexBuffer.Get(), 0, mapType, 0, &vres)))
				{
					if (Vertex2D* const vtxbuf = static_cast<Vertex2D*>(vres.pData) + m_vertexBufferWritePos)
					{
						::memcpy(vtxbuf, vertexData, sizeof(Vertex2D) * vertexSize);

						m_context->Unmap(m_vertexBuffer.Get(), 0);
					}
				}

				m_vertexBufferWritePos += vertexSize;
				vi.first = m_vertexBufferWritePos - vertexSize;
			}

			{
				const IndexType* indexData = m_indices.data();
				const size_t indexSize = m_indexPos;

				D3D11_MAP mapType = D3D11_MAP_WRITE_NO_OVERWRITE;

				if (IndexBufferSize < m_indexBufferWritePos + indexSize)
				{
					mapType = D3D11_MAP_WRITE_DISCARD;
					m_indexBufferWritePos = 0;
				}

				D3D11_MAPPED_SUBRESOURCE ires;

				if (FAILED(m_context->Map(m_indexBuffer.Get(), 0, mapType, 0, &ires)))
				{
					return{ 0, 0 };
				}

				if (IndexType* const idxbuf = static_cast<IndexType*>(ires.pData) + m_indexBufferWritePos)
				{
					::memcpy(idxbuf, indexData, sizeof(IndexType) * indexSize);

					m_context->Unmap(m_indexBuffer.Get(), 0);
				}

				m_indexBufferWritePos += indexSize;
				vi.second = m_indexBufferWritePos - indexSize;
			}

			ID3D11Buffer* const pBuf[3] = { m_vertexBuffer.Get(), nullptr, nullptr };

			const UINT stride[3] = { sizeof(Vertex2D), 0, 0 };

			const UINT offset[3] = { 0, 0, 0 };

			constexpr auto indexFormat = sizeof(IndexType) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;

			m_context->IASetVertexBuffers(0, 3, pBuf, stride, offset);

			m_context->IASetIndexBuffer(m_indexBuffer.Get(), indexFormat, 0);

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
