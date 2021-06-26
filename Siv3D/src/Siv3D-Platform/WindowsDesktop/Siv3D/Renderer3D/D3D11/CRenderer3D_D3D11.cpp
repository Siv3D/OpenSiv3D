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

# include "CRenderer3D_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Vertex3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>
# include <Siv3D/Texture/D3D11/CTexture_D3D11.hpp>
# include <Siv3D/Mesh/D3D11/CMesh_D3D11.hpp>

//*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer3D_D3D11::CRenderer3D_D3D11() {}

	CRenderer3D_D3D11::~CRenderer3D_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::~CRenderer3D_D3D11()");
	}

	void CRenderer3D_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_D3D11*>(SIV3D_ENGINE(Shader)); assert(pShader);
			pTexture	= dynamic_cast<CTexture_D3D11*>(SIV3D_ENGINE(Texture)); assert(pTexture);
			pMesh		= dynamic_cast<CMesh_D3D11*>(SIV3D_ENGINE(Mesh)); assert(pMesh);
			m_device	= pRenderer->getDevice(); assert(m_device);
			m_context	= pRenderer->getContext(); assert(m_context);
		}

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer3D_D3D11:");
			m_standardVS = std::make_unique<D3D11StandardVS3D>();
			m_standardVS->forward = HLSL{ U"engine/shader/d3d11/forward3d.hlsl", U"VS" };
			
			if (not m_standardVS->setup())
			{
				throw EngineError{ U"CRenderer3D_D3D11::m_standardVS initialization failed" };
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer3D_D3D11:");
			m_standardPS = std::make_unique<D3D11StandardPS3D>();
			m_standardPS->forwardShape = HLSL{ U"engine/shader/d3d11/forward3d.hlsl", U"PS_Shape" };
			m_standardPS->forwardTexture = HLSL{ U"engine/shader/d3d11/forward3d.hlsl", U"PS_Texture" };
			
			if (not m_standardPS->setup())
			{
				throw EngineError{ U"CRenderer3D_D3D11::m_standardPS initialization failed" };
			}
		}

		// 標準 InputLayout を作成
		{
			const D3D11_INPUT_ELEMENT_DESC layout[3] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				//{ "TANGENT" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			const Blob& binary = m_standardVS->forward.getBinary();
			if (FAILED(m_device->CreateInputLayout(layout, static_cast<UINT>(std::size(layout)), binary.data(), binary.size(), &m_inputLayout)))
			{
				throw EngineError{ U"ID3D11Device::CreateInputLayout() failed" };
			}
		}
	}

	void CRenderer3D_D3D11::addMesh(const Mesh& mesh, const Mat4x4& mat, const Float4& color)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardShapeID);
		}

		m_commandManager.pushMesh(mesh);

		const uint32 startIndex = 0;
		const uint32 indexCount = static_cast<uint32>(mesh.num_triangles() * 3);
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, &mat, &color, instanceCount);
	}

	void CRenderer3D_D3D11::addTexturedMesh(const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const Float4& color)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardTextureID);
		}

		m_commandManager.pushMesh(mesh);
		m_commandManager.pushPSTexture(0, texture);

		const uint32 startIndex = 0;
		const uint32 indexCount = static_cast<uint32>(mesh.num_triangles() * 3);
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, &mat, &color, instanceCount);
	}

	void CRenderer3D_D3D11::setCameraTransform(const Mat4x4& matrix)
	{
		m_commandManager.pushCameraTransform(matrix);
	}

	void CRenderer3D_D3D11::setRenderTarget(const Optional<RenderTexture>& rt)
	{
		if (rt)
		{
			bool hasChanged = false;
			const Texture::IDType textureID = rt->id();

			// バインドされていたら解除
			{
				{
					const auto& currentPSTextures = m_commandManager.getCurrentPSTextures();

					for (uint32 slot = 0; slot < currentPSTextures.size(); ++slot)
					{
						if (currentPSTextures[slot] == textureID)
						{
							m_commandManager.pushPSTextureUnbind(slot);
							hasChanged = true;
						}
					}
				}

				{
					const auto& currentVSTextures = m_commandManager.getCurrentVSTextures();

					for (uint32 slot = 0; slot < currentVSTextures.size(); ++slot)
					{
						if (currentVSTextures[slot] == textureID)
						{
							m_commandManager.pushVSTextureUnbind(slot);
							hasChanged = true;
						}
					}
				}
			}

			if (hasChanged)
			{
				m_commandManager.flush();
			}
		}

		m_commandManager.pushRT(rt);
	}

	Optional<RenderTexture> CRenderer3D_D3D11::getRenderTarget() const
	{
		return m_commandManager.getCurrentRT();
	}

	void CRenderer3D_D3D11::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_commandManager.reset();
			m_currentCustomVS.reset();
			m_currentCustomPS.reset();
		};

		m_commandManager.flush();

		m_context->IASetInputLayout(m_inputLayout.Get());
		pShader->setConstantBufferVS(0, m_vsConstants3D.base());
		pShader->setConstantBufferPS(0, m_psConstants3D.base());

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();

		{
			const CD3D11_VIEWPORT viewport{
				0.0f, 0.0f,
				static_cast<float>(currentRenderTargetSize.x), static_cast<float>(currentRenderTargetSize.y) };
			m_context->RSSetViewports(1, &viewport);
		}

		pRenderer->getBackBuffer().setRenderTargetToScene();

		LOG_COMMAND(U"----");
		uint32 instanceIndex = 0;

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case D3D11Renderer3DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case D3D11Renderer3DCommandType::Draw:
				{
					const D3D11Draw3DCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = draw.startIndex;
					const uint32 instanceCount = draw.instanceCount;

					const Mat4x4& localToWorld = m_commandManager.getDrawLocalToWorld(instanceIndex);
					const Float4& diffuse = m_commandManager.getDrawDiffuse(instanceIndex);
					m_vsConstants3D->localToWorld = localToWorld;
					m_vsConstants3D->diffuse = diffuse;

					m_vsConstants3D._update_if_dirty();
					m_psConstants3D._update_if_dirty();
					m_context->DrawIndexed(indexCount, startIndexLocation, 0);
					
					instanceIndex += instanceCount;

					//++m_stat.drawCalls;
					//m_stat.triangleCount += (indexCount / 3);

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			case D3D11Renderer3DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					pRenderer->getBlendState().set(blendState);
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case D3D11Renderer3DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					pRenderer->getRasterizerState().set(rasterizerState);
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}

			case D3D11Renderer3DCommandType::VSSamplerState0:
			case D3D11Renderer3DCommandType::VSSamplerState1:
			case D3D11Renderer3DCommandType::VSSamplerState2:
			case D3D11Renderer3DCommandType::VSSamplerState3:
			case D3D11Renderer3DCommandType::VSSamplerState4:
			case D3D11Renderer3DCommandType::VSSamplerState5:
			case D3D11Renderer3DCommandType::VSSamplerState6:
			case D3D11Renderer3DCommandType::VSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(D3D11Renderer3DCommandType::VSSamplerState0);
					const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setVS(slot, samplerState);
					LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case D3D11Renderer3DCommandType::PSSamplerState0:
			case D3D11Renderer3DCommandType::PSSamplerState1:
			case D3D11Renderer3DCommandType::PSSamplerState2:
			case D3D11Renderer3DCommandType::PSSamplerState3:
			case D3D11Renderer3DCommandType::PSSamplerState4:
			case D3D11Renderer3DCommandType::PSSamplerState5:
			case D3D11Renderer3DCommandType::PSSamplerState6:
			case D3D11Renderer3DCommandType::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(D3D11Renderer3DCommandType::PSSamplerState0);
					const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setPS(slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case D3D11Renderer3DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					if (rt)
					{
						ID3D11RenderTargetView* const rtv = pTexture->getRTV(rt->id());
						pRenderer->getBackBuffer().setRenderTarget(rtv);

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else
					{
						pRenderer->getBackBuffer().setRenderTargetToScene();
						
						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}

					break;
				}
			case D3D11Renderer3DCommandType::SetVS:
				{
					const auto& vsID = m_commandManager.getVS(command.index);

					if (vsID == VertexShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetVS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setVS(vsID);
						LOG_COMMAND(U"SetVS[{}]: {}"_fmt(command.index, vsID.value()));
					}

					break;
				}
			case D3D11Renderer3DCommandType::SetPS:
				{
					const auto& psID = m_commandManager.getPS(command.index);

					if (psID == PixelShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetPS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setPS(psID);
						LOG_COMMAND(U"SetPS[{}]: {}"_fmt(command.index, psID.value()));
					}

					break;
				}
			case D3D11Renderer3DCommandType::CameraTransform:
				{
					const Mat4x4& cameraTransform = m_commandManager.getCameraTransform(command.index);
					m_vsConstants3D->worldToProjected = cameraTransform;

					LOG_COMMAND(U"CameraTransform[{}] {}"_fmt(command.index, cameraTransform));
					break;
				}

			case D3D11Renderer3DCommandType::VSTexture0:
			case D3D11Renderer3DCommandType::VSTexture1:
			case D3D11Renderer3DCommandType::VSTexture2:
			case D3D11Renderer3DCommandType::VSTexture3:
			case D3D11Renderer3DCommandType::VSTexture4:
			case D3D11Renderer3DCommandType::VSTexture5:
			case D3D11Renderer3DCommandType::VSTexture6:
			case D3D11Renderer3DCommandType::VSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(D3D11Renderer3DCommandType::VSTexture0));
					const auto& textureID = m_commandManager.getVSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						ID3D11ShaderResourceView* nullAttach[1] = { nullptr };
						m_context->VSSetShaderResources(slot, 1, nullAttach);
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						m_context->VSSetShaderResources(slot, 1, pTexture->getSRVPtr(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}
					
					break;
				}
			case D3D11Renderer3DCommandType::PSTexture0:
			case D3D11Renderer3DCommandType::PSTexture1:
			case D3D11Renderer3DCommandType::PSTexture2:
			case D3D11Renderer3DCommandType::PSTexture3:
			case D3D11Renderer3DCommandType::PSTexture4:
			case D3D11Renderer3DCommandType::PSTexture5:
			case D3D11Renderer3DCommandType::PSTexture6:
			case D3D11Renderer3DCommandType::PSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(D3D11Renderer3DCommandType::PSTexture0));
					const auto& textureID = m_commandManager.getPSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						ID3D11ShaderResourceView* nullAttach[1] = { nullptr };
						m_context->PSSetShaderResources(slot, 1, nullAttach);
						LOG_COMMAND(U"PSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						m_context->PSSetShaderResources(slot, 1, pTexture->getSRVPtr(textureID));
						LOG_COMMAND(U"PSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}
					
					break;
				}
			case D3D11Renderer3DCommandType::SetMesh:
				{
					const auto& meshID = m_commandManager.getMesh(command.index);

					if (meshID == Mesh::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetMesh[{}]: null"_fmt(command.index));
					}
					else
					{
						pMesh->bindMeshToContext(meshID);
						LOG_COMMAND(U"SetMesh[{}]: {}"_fmt(command.index, meshID.value()));
					}

					break;
				}
			}
		}
	}
}
