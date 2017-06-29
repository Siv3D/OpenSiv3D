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
# include "CRenderer2D_D3D11.hpp"

#include <Siv3D/Mat3x2.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Logger.hpp>

namespace s3d
{
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
		//// send batch
		//
		// (add rect)
		//
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			Vertex2D* pVertex;
			IndexType* pIndex;
			IndexType indexOffset;

			if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
			{
				return;
			}

			const Rect rect(40, 80, 400, 200);

			const float left = static_cast<float>(rect.x);
			const float right = static_cast<float>(rect.x + rect.w);
			const float top = static_cast<float>(rect.y);
			const float bottom = static_cast<float>(rect.y + rect.h);
			const Float4 color(0.2f, 0.5f, 1.0f, 1.0f);

			pVertex[0].pos.set(left, top);
			pVertex[0].color = color;

			pVertex[1].pos.set(right, top);
			pVertex[1].color = color;

			pVertex[2].pos.set(left, bottom);
			pVertex[2].color = color;

			pVertex[3].pos.set(right, bottom);
			pVertex[3].color = color;

			static constexpr IndexType rectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

			for (IndexType i = 0; i < indexSize; ++i)
			{
				pIndex[i] = indexOffset + rectIndexTable[i];
			}
		}

		// set buffer
		const auto vi = m_spriteBatch.setBuffers();

		// setCB
		const Mat3x2 currentMat = Mat3x2::Identity();
		const Mat3x2 currentScreen = Mat3x2::Screen(640, 480);
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

		// draw
		m_context->DrawIndexed(6, vi.second, vi.first);


		m_spriteBatch.clear();
	}
}

# endif
