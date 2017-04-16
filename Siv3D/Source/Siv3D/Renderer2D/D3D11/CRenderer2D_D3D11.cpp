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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../../Siv3DEngine.hpp"
# include "../../Shader/IShader.hpp"
# include "../../Graphics/IGraphics.hpp"
# include "CRenderer2D_D3D11.hpp"
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType rectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
	}

	CRenderer2D_D3D11::CRenderer2D_D3D11()
	{

	}

	CRenderer2D_D3D11::~CRenderer2D_D3D11()
	{

	}

	bool CRenderer2D_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		m_device = device;
		m_context = context;

		D3D11_INPUT_ELEMENT_DESC layout[3] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		const VertexShader& spriteVS = Siv3DEngine::GetShader()->getStandardVS(0);
		const ByteArrayView vsView = spriteVS.getBinaryView();

		if (FAILED(m_device->CreateInputLayout(layout, 3, vsView.data(), vsView.size(), &m_inputLayout)))
		{
			return false;
		}

		m_context->IASetInputLayout(m_inputLayout.Get());


		if (!m_spriteBatch.init(m_device, m_context))
		{
			return false;
		}


		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth				= static_cast<uint32>(sizeof(float) * 8);
			desc.Usage					= D3D11_USAGE_DYNAMIC;
			desc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags				= 0;
			desc.StructureByteStride	= 0;

			if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_cbuffer)))
			{
				return false;
			}
		}

		return true;
	}

	void CRenderer2D_D3D11::flush()
	{
		// set buffer
		const auto vi = m_spriteBatch.setBuffers();

		// setCB
		const Float2 currentRenderTargetSize = Siv3DEngine::GetGraphics()->getCurrentRenderTargetSize();
		const Mat3x2 currentMat = Mat3x2::Identity();
		const Mat3x2 currentScreen = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = currentMat * currentScreen;

		const float transform[8] =
		{
			matrix._11, matrix._12, matrix._31, matrix._32,
			matrix._21, matrix._22, 0.0f, 1.0f
		};

		D3D11_MAPPED_SUBRESOURCE mapped;

		if (SUCCEEDED(m_context->Map(m_cbuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
		{
			if (void* dst = mapped.pData)
			{
				::memcpy(dst, transform, sizeof(transform));

				m_context->Unmap(m_cbuffer.Get(), 0);
			}
		}

		m_context->VSSetConstantBuffers(0, 1, m_cbuffer.GetAddressOf());

		// setVS
		Siv3DEngine::GetShader()->setVS(Siv3DEngine::GetShader()->getStandardVS(0).id());

		// setPS
		Siv3DEngine::GetShader()->setPS(Siv3DEngine::GetShader()->getStandardPS(0).id());

		//Log << vi << L" " << m_drawIndexCount;

		// draw
		m_context->DrawIndexed(m_drawIndexCount, vi.second, vi.first);

		m_drawIndexCount = 0;

		m_spriteBatch.clear();
	}

	void CRenderer2D_D3D11::addTriangle(const Float2(&pts)[3], const Float4& color)
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= pts[0];
		pVertex[0].color	= color;

		pVertex[1].pos		= pts[1];
		pVertex[1].color	= color;

		pVertex[2].pos		= pts[2];
		pVertex[2].color	= color;

		pIndex[0] = indexOffset;
		pIndex[1] = indexOffset + 1;
		pIndex[2] = indexOffset + 2;

		m_drawIndexCount += indexSize;
	}

	void CRenderer2D_D3D11::addTriangle(const Float2(&pts)[3], const Float4(&colors)[3])
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= pts[0];
		pVertex[0].color	= colors[0];

		pVertex[1].pos		= pts[1];
		pVertex[1].color	= colors[1];

		pVertex[2].pos		= pts[2];
		pVertex[2].color	= colors[2];

		pIndex[0] = indexOffset;
		pIndex[1] = indexOffset + 1;
		pIndex[2] = indexOffset + 2;

		m_drawIndexCount += indexSize;
	}

	void CRenderer2D_D3D11::addRect(const FloatRect& rect, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos.set(rect.left, rect.top);
		pVertex[0].color = color;

		pVertex[1].pos.set(rect.right, rect.top);
		pVertex[1].color = color;

		pVertex[2].pos.set(rect.left, rect.bottom);
		pVertex[2].color = color;

		pVertex[3].pos.set(rect.right, rect.bottom);
		pVertex[3].color = color;

		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}

		m_drawIndexCount += indexSize;
	}

	void CRenderer2D_D3D11::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos.set(rect.left, rect.top);
		pVertex[0].color = colors[0];

		pVertex[1].pos.set(rect.right, rect.top);
		pVertex[1].color = colors[1];

		pVertex[2].pos.set(rect.left, rect.bottom);
		pVertex[2].color = colors[3];

		pVertex[3].pos.set(rect.right, rect.bottom);
		pVertex[3].color = colors[2];

		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}

		m_drawIndexCount += indexSize;
	}

	void CRenderer2D_D3D11::addQuad(const FloatQuad& quad, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= quad.p[0];
		pVertex[0].color	= color;

		pVertex[1].pos		= quad.p[1];
		pVertex[1].color	= color;

		pVertex[2].pos		= quad.p[3];
		pVertex[2].color	= color;

		pVertex[3].pos		= quad.p[2];
		pVertex[3].color	= color;

		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}

		m_drawIndexCount += indexSize;
	}

	void CRenderer2D_D3D11::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= quad.p[0];
		pVertex[0].color	= colors[0];

		pVertex[1].pos		= quad.p[1];
		pVertex[1].color	= colors[1];

		pVertex[2].pos		= quad.p[3];
		pVertex[2].color	= colors[3];

		pVertex[3].pos		= quad.p[2];
		pVertex[3].color	= colors[2];

		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}

		m_drawIndexCount += indexSize;
	}
}

# endif
