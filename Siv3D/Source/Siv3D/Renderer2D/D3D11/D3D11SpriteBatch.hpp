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

# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef WIN32_LEAN_AND_MEAN
#	define  WIN32_LEAN_AND_MEAN
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
# include <wrl.h>
# include <d3d11.h>
# include "../IRenderer2D.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Logger.hpp>
# include "D3D11Renderer2DCommandManager.hpp"

using namespace Microsoft::WRL;

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

	class D3D11SpriteBatch
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11Buffer> m_vertexBuffer;

		ComPtr<ID3D11Buffer> m_indexBuffer;

		Array<Vertex2D> m_vertices;

		Array<IndexType> m_indices;

		uint32 m_vertexArrayWritePos = 0;

		uint32 m_indexArrayWritePos = 0;

		uint32 m_vertexBufferWritePos = 0;

		uint32 m_indexBufferWritePos = 0;

		Array<BatchBufferPos> m_batches;

		// 仮の値
		static constexpr uint32 InitialVertexSize = 4096;
		static constexpr uint32 InitialIndexSize = 4096 * 8;

		static constexpr uint32 MaxVertexSize	= 65536 * 64;
		static constexpr uint32 MaxIndexSize	= 65536 * 64;

		static constexpr uint32 VertexBufferSize	= 65536;
		static constexpr uint32 IndexBufferSize		= VertexBufferSize * 8;

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

		D3D11SpriteBatch()
			: m_vertices(InitialVertexSize)
			, m_indices(InitialIndexSize)
			, m_batches(1)
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

		bool getBuffer(const uint32 vertexSize, const uint32 indexSize, Vertex2D** pVertex, IndexType** pIndices, IndexType* indexOffset, D3D11Render2DCommandManager& commandManager)
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

			//Log << L"{} - {} - {}"_fmt(batchIndex, m_batches[batchIndex].vertexPos, m_batches[batchIndex].indexPos);

			size_t vertexArrayOffset = 0;
			size_t indexArrayOffset = 0;

			for (size_t i = 0; i < batchIndex; ++i)
			{
				vertexArrayOffset += m_batches[i].vertexPos;
				indexArrayOffset += m_batches[i].indexPos;
			}

			{
				const Vertex2D* vertexData = m_vertices.data() + vertexArrayOffset;
				const uint32 vertexSize = m_batches[batchIndex].vertexPos;

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

				batchDrawOffset.vertexStartLocation = m_vertexBufferWritePos;
				m_vertexBufferWritePos += vertexSize;
			}

			{
				const IndexType* indexData = m_indices.data() + indexArrayOffset;
				const uint32 indexSize = m_batches[batchIndex].indexPos;

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

				batchDrawOffset.indexCount = indexSize;
				batchDrawOffset.indexStartLocation = m_indexBufferWritePos;
				m_indexBufferWritePos += indexSize;
			}

			ID3D11Buffer* const pBuf[3] = { m_vertexBuffer.Get(), nullptr, nullptr };

			const UINT stride[3] = { sizeof(Vertex2D), 0, 0 };

			const UINT offset[3] = { 0, 0, 0 };

			constexpr auto indexFormat = sizeof(IndexType) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;

			m_context->IASetVertexBuffers(0, 3, pBuf, stride, offset);

			m_context->IASetIndexBuffer(m_indexBuffer.Get(), indexFormat, 0);

			//Log << L"={} - {} - {}"_fmt(batchDrawOffset.indexCount, batchDrawOffset.indexStartLocation, batchDrawOffset.vertexStartLocation);

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
