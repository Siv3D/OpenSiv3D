//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer2D_D3D11::CRenderer2D_D3D11()
	{

	}

	CRenderer2D_D3D11::~CRenderer2D_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_D3D11::~CRenderer2D_D3D11()");
	}

	void CRenderer2D_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_D3D11::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_D3D11*>(SIV3D_ENGINE(Shader)); assert(pShader);
			m_device	= pRenderer->getDevice(); assert(m_device);
			m_context	= pRenderer->getContext(); assert(m_context);
		}

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer2D_D3D11:");
			m_standardVS = std::make_unique<D3D11StandardVS2D>();
			m_standardVS->sprite				= HLSL(FileOrResource(U"engine/shader/d3d11/sprite.vs"));
			m_standardVS->fullscreen_triangle	= HLSL(FileOrResource(U"engine/shader/d3d11/fullscreen_triangle.vs"));
			if (not m_standardVS->ok())
			{
				throw EngineError(U"CRenderer2D_D3D11::m_standardVS initialization failed");
			}
		}
		
		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer2D_D3D11:");
			m_standardPS = std::make_unique<D3D11StandardPS2D>();
			m_standardPS->shape					= HLSL(FileOrResource(U"engine/shader/d3d11/shape.ps"));
			m_standardPS->fullscreen_triangle	= HLSL(FileOrResource(U"engine/shader/d3d11/fullscreen_triangle.ps"));
			if (not m_standardPS->ok())
			{
				throw EngineError(U"CRenderer2D_D3D11::m_standardPS initialization failed");
			}
		}

		// 標準 InputLayout を作成
		{
			const D3D11_INPUT_ELEMENT_DESC layout[3] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			const Blob& binary = m_standardVS->sprite.getBinary();
			if (FAILED(m_device->CreateInputLayout(layout, 3, binary.data(), binary.size(), &m_inputLayout)))
			{
				throw EngineError(U"ID3D11Device::CreateInputLayout() failed");
			}
		}

		// Batch 管理を初期化
		{
			if (not m_batches.init(m_device, m_context))
			{
				throw EngineError(U"D3D11Vertex2DBatch::init() failed");
			}
		}
	}

	void CRenderer2D_D3D11::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_batches.reset();
			m_draw_indexCount = 0;
		};

		if (m_draw_indexCount == 0)
		{
			return;
		}

		m_context->IASetInputLayout(m_inputLayout.Get());
		pShader->setVS(m_standardVS->sprite.id());
		pShader->setPS(m_standardPS->shape.id());
		pShader->setConstantBufferVS(0, m_vsConstants2D.base());
		pShader->setConstantBufferPS(0, m_psConstants2D.base());

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();

		{
			const CD3D11_VIEWPORT viewport{
				0.0f, 0.0f,
				static_cast<float>(currentRenderTargetSize.x), static_cast<float>(currentRenderTargetSize.y) };
			m_context->RSSetViewports(1, &viewport);
		}

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = (transform * screenMat);
		m_vsConstants2D->transform[0].set(matrix._11, matrix._12, matrix._31, matrix._32);
		m_vsConstants2D->transform[1].set(matrix._21, matrix._22, 0.0f, 1.0f);

		pRenderer->getSamplerState().setPS(0, SamplerState::Default2D);
		pRenderer->getBlendState().set(BlendState::Default);
		pRenderer->getRasterizerState().set(RasterizerState::Default2D);

		pRenderer->getBackBuffer().bindRenderTarget(pRenderer->getBackBuffer().getSceneBuffer().getRTV());;

		m_batches.setBuffers();

		m_vsConstants2D._update_if_dirty();
		m_psConstants2D._update_if_dirty();

		auto batchInfo = m_batches.updateBuffers(0);

		const uint32 indexCount = m_draw_indexCount;
		const uint32 startIndexLocation = batchInfo.startIndexLocation;
		const uint32 baseVertexLocation = batchInfo.baseVertexLocation;

		m_context->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}

	void CRenderer2D_D3D11::test_renderRectangle(const RectF& rect, const ColorF& _color)
	{
		constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
		auto [pVertex, pIndex, indexOffset] = m_batches.requestBuffer(vertexSize, indexSize, m_command);

		if (!pVertex)
		{
			return;
		}

		const Float4 color = _color.toFloat4();

		const float left = float(rect.x);
		const float right = float(rect.x + rect.w);
		const float top = float(rect.y);
		const float bottom = float(rect.y + rect.h);

		pVertex[0].set(left, top, color);
		pVertex[1].set(right, top, color);
		pVertex[2].set(left, bottom, color);
		pVertex[3].set(right, bottom, color);

		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = (indexOffset + RectIndexTable[i]);
		}

		m_draw_indexCount += 6;
	}

	void CRenderer2D_D3D11::drawFullScreenTriangle(const TextureFilter textureFilter)
	{
		// view port
		{
			const auto [s, viewRect] = pRenderer->getLetterboxComposition();
			const CD3D11_VIEWPORT viewport{
				static_cast<float>(viewRect.x), static_cast<float>(viewRect.y),
				static_cast<float>(viewRect.w), static_cast<float>(viewRect.h) };
			m_context->RSSetViewports(1, &viewport);
		}

		// render states
		{
			const SamplerState samplerState = (textureFilter == TextureFilter::Linear) ?
				SamplerState::ClampLinear : SamplerState::ClampNearest;
			pRenderer->getSamplerState().setPS(0, samplerState);
			pRenderer->getBlendState().set(BlendState::Opaque);
			pRenderer->getRasterizerState().set(RasterizerState::Default2D);
		}
		
		// shaders
		{
			pShader->setVS(m_standardVS->fullscreen_triangle.id());
			pShader->setPS(m_standardPS->fullscreen_triangle.id());
		}

		// draw null vertex buffer
		{
			m_context->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
			m_context->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
			m_context->IASetInputLayout(nullptr);
			m_context->Draw(3, 0);
		}

		//Siv3DEngine::Get<ISiv3DProfiler>()->reportDrawcalls(1, 1);
	}
}
