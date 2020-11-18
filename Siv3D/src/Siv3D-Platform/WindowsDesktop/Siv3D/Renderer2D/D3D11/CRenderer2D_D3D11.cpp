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

/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

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

		// バッファ作成関数を作成
		m_bufferCreator = [this](Vertex2D::IndexType vertexSize, Vertex2D::IndexType indexSize)
		{
			return m_batches.requestBuffer(vertexSize, indexSize, m_commandManager);
		};
	}

	void CRenderer2D_D3D11::addLine(const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildDefaultLine(m_bufferCreator, begin, end, thickness, colors))
		{
			//if (!m_currentCustomPS)
			//{
			//	m_commands.pushStandardPS(m_standardPS->shapeID);
			//}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_D3D11::addRect(const FloatRect& rect, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, color))
		{
			//if (!m_currentCustomPS)
			//{
			//	m_commands.pushStandardPS(m_standardPS->shapeID);
			//}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_D3D11::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_batches.reset();
			m_commandManager.reset();
		};

		m_commandManager.flush();

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


		D3D11BatchInfo batchInfo;

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case D3D11Renderer2DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case D3D11Renderer2DCommandType::SetBuffers:
				{
					m_batches.setBuffers();

					LOG_COMMAND(U"SetBuffers[{}]"_fmt(command.index));
					break;
				}
			case D3D11Renderer2DCommandType::UpdateBuffers:
				{
					batchInfo = m_batches.updateBuffers(command.index);
					
					LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
					break;
				}
			case D3D11Renderer2DCommandType::Draw:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					const D3D11DrawCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfo.startIndexLocation;
					const uint32 baseVertexLocation = batchInfo.baseVertexLocation;

					m_context->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
					batchInfo.startIndexLocation += indexCount;

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			}
		}
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
