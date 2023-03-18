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
# include "D3D11Line3DBatch.hpp"

namespace s3d
{
	namespace detail
	{
		static size_t CalculateNewArraySize(const size_t current, const size_t target) noexcept
		{
			size_t newArraySize = (current * 2);

			while (newArraySize < target)
			{
				newArraySize *= 2;
			}

			return newArraySize;
		}
	}

	D3D11Line3DBatch::D3D11Line3DBatch()
		: m_vertexArray(InitialVertexArraySize)
		, m_indexArray(InitialIndexArraySize)
		, m_batches(1) {}

	D3D11Line3DBatch::~D3D11Line3DBatch() {}

	bool D3D11Line3DBatch::init(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_device	= device;
		m_context	= context;

		// Vertex Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (sizeof(VertexLine3D) * VertexBufferSize),
				.Usage					= D3D11_USAGE_DYNAMIC,
				.BindFlags				= D3D11_BIND_VERTEX_BUFFER,
				.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
				.MiscFlags				= 0,
				.StructureByteStride	= 0, 
			};

			if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_vertexBuffer)))
			{
				return false;
			}
		}

		// Index Buffer
		{
			const D3D11_BUFFER_DESC desc =
			{
				.ByteWidth				= (sizeof(VertexLine3D::IndexType) * IndexBufferSize),
				.Usage					= D3D11_USAGE_DYNAMIC,
				.BindFlags				= D3D11_BIND_INDEX_BUFFER,
				.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
				.MiscFlags				= 0,
				.StructureByteStride	= 0,
			};

			if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_indexBuffer)))
			{
				return false;
			}
		}

		return true;
	}

	VertexLine3DBufferPointer D3D11Line3DBatch::requestBuffer(const VertexLine3D::IndexType vertexSize, const uint32 indexSize, D3D11Renderer3DCommandManager& commandManager)
	{
		// VB
		if (const uint32 vertexArrayWritePosTarget = m_vertexArrayWritePos + vertexSize;
			m_vertexArray.size() < vertexArrayWritePosTarget)
		{
			if (MaxVertexArraySize < vertexArrayWritePosTarget)
			{
				return{ nullptr, 0, 0 };
			}

			const size_t newVertexArraySize = detail::CalculateNewArraySize(m_vertexArray.size(), vertexArrayWritePosTarget);
			LOG_TRACE(U"ℹ️ Resized D3D11Line3DBatch::m_vertexArray (size: {} -> {})"_fmt(m_vertexArray.size(), newVertexArraySize));
			m_vertexArray.resize(newVertexArraySize);
		}

		// IB
		if (const uint32 indexArrayWritePosTarget = m_indexArrayWritePos + indexSize;
			m_indexArray.size() < indexArrayWritePosTarget)
		{
			if (MaxIndexArraySize < indexArrayWritePosTarget)
			{
				return{ nullptr, 0, 0 };
			}

			const size_t newIndexArraySize = detail::CalculateNewArraySize(m_indexArray.size(), indexArrayWritePosTarget);
			LOG_TRACE(U"ℹ️ Resized D3D11Line3DBatch::m_indexArray (size: {} -> {})"_fmt(m_indexArray.size(), newIndexArraySize));
			m_indexArray.resize(newIndexArraySize);
		}

		if (const auto& lastbatch = m_batches.back();
			(VertexBufferSize < (lastbatch.vertexPos + vertexSize) || IndexBufferSize < (lastbatch.indexPos + indexSize)))
		{
			commandManager.pushUpdateLine3DBuffers(static_cast<uint32>(m_batches.size()));
			m_batches.emplace_back();
		}

		auto& lastbatch = m_batches.back();
		VertexLine3D* const pVertex				= (m_vertexArray.data() + m_vertexArrayWritePos);
		VertexLine3D::IndexType* const pIndex	= (m_indexArray.data() + m_indexArrayWritePos);
		const auto indexOffset				= lastbatch.vertexPos;

		advanceArrayWritePos(vertexSize, indexSize);
		lastbatch.advance(vertexSize, indexSize);

		return{ pVertex, pIndex, indexOffset };
	}

	size_t D3D11Line3DBatch::num_batches() const noexcept
	{
		return m_batches.size();
	}

	bool D3D11Line3DBatch::isEmpty() const noexcept
	{
		return (m_vertexArrayWritePos == 0);
	}

	void D3D11Line3DBatch::reset()
	{
		m_batches.clear();
		m_batches.emplace_back();

		m_vertexArrayWritePos	= 0;
		m_indexArrayWritePos	= 0;
	}

	void D3D11Line3DBatch::setBuffers()
	{
		ID3D11Buffer* const pBuf[1] = { m_vertexBuffer.Get() };
		const UINT stride = sizeof(VertexLine3D);
		const UINT offset = 0;
		m_context->IASetVertexBuffers(0, 1, pBuf, &stride, &offset);

		constexpr auto indexFormat = ((sizeof(VertexLine3D::IndexType) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT);
		m_context->IASetIndexBuffer(m_indexBuffer.Get(), indexFormat, 0);
	}

	BatchInfoLine3D D3D11Line3DBatch::updateBuffers(const size_t batchIndex)
	{
		assert(batchIndex < m_batches.size());

		size_t vertexArrayReadPos = 0;
		size_t indexArrayReadPos = 0;

		for (size_t i = 0; i < batchIndex; ++i)
		{
			vertexArrayReadPos += m_batches[i].vertexPos;
			indexArrayReadPos += m_batches[i].indexPos;
		}

		BatchInfoLine3D batchInfo;
		const auto& currentBatch = m_batches[batchIndex];

		// VB
		if (const VertexLine3D::IndexType vertexSize = currentBatch.vertexPos)
		{
			//LOG_TRACE(U"Map(D3D11SpriteBatch::m_vertexBuffer)");

			const VertexLine3D* pSrc = m_vertexArray.data() + vertexArrayReadPos;

			D3D11_MAP mapType = D3D11_MAP_WRITE_NO_OVERWRITE;

			if (VertexBufferSize < (m_vertexBufferWritePos + vertexSize))
			{
				mapType = D3D11_MAP_WRITE_DISCARD;
				m_vertexBufferWritePos = 0;
			}

			D3D11_MAPPED_SUBRESOURCE res;

			if (SUCCEEDED(m_context->Map(m_vertexBuffer.Get(), 0, mapType, 0, &res)))
			{
				if (VertexLine3D* const p = static_cast<VertexLine3D*>(res.pData))
				{
					VertexLine3D* const pDst = p + m_vertexBufferWritePos;
					std::memcpy(pDst, pSrc, sizeof(VertexLine3D) * vertexSize);
				}
				m_context->Unmap(m_vertexBuffer.Get(), 0);
			}

			batchInfo.baseVertexLocation = m_vertexBufferWritePos;
			m_vertexBufferWritePos += vertexSize;
		}

		// IB
		if (const uint32 indexSize = currentBatch.indexPos)
		{
			//LOG_TRACE(U"Map(D3D11SpriteBatch::m_indexBuffer)");

			const VertexLine3D::IndexType* pSrc = m_indexArray.data() + indexArrayReadPos;

			D3D11_MAP mapType = D3D11_MAP_WRITE_NO_OVERWRITE;

			if (IndexBufferSize < (m_indexBufferWritePos + indexSize))
			{
				mapType = D3D11_MAP_WRITE_DISCARD;
				m_indexBufferWritePos = 0;
			}

			D3D11_MAPPED_SUBRESOURCE res;

			if (SUCCEEDED(m_context->Map(m_indexBuffer.Get(), 0, mapType, 0, &res)))
			{
				if (VertexLine3D::IndexType* const p = static_cast<VertexLine3D::IndexType*>(res.pData))
				{
					VertexLine3D::IndexType* const pDst = p + m_indexBufferWritePos;
					std::memcpy(pDst, pSrc, (sizeof(VertexLine3D::IndexType) * indexSize));
				}
				m_context->Unmap(m_indexBuffer.Get(), 0);
			}

			batchInfo.indexCount = indexSize;
			batchInfo.startIndexLocation = m_indexBufferWritePos;
			m_indexBufferWritePos += indexSize;
		}

		return batchInfo;
	}

	void D3D11Line3DBatch::advanceArrayWritePos(const VertexLine3D::IndexType vertexSize, const uint32 indexSize) noexcept
	{
		m_vertexArrayWritePos	+= vertexSize;
		m_indexArrayWritePos	+= indexSize;
	}
}
