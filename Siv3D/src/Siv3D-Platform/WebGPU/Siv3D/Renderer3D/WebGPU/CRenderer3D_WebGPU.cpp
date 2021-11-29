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

# include "CRenderer3D_WebGPU.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>
# include <Siv3D/Shader/WebGPU/CShader_WebGPU.hpp>
# include <Siv3D/Texture/WebGPU/CTexture_WebGPU.hpp>
# include <Siv3D/Mesh/WebGPU/CMesh_WebGPU.hpp>
# include <Siv3D/ConstantBuffer/WebGPU/ConstantBufferDetail_WebGPU.hpp>

/*/
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer3D_WebGPU::CRenderer3D_WebGPU() {}

	CRenderer3D_WebGPU::~CRenderer3D_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_WebGPU::~CRenderer3D_WebGPU()");
	}

	void CRenderer3D_WebGPU::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_WebGPU::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= static_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer));
			pShader		= static_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader));
			pTexture	= static_cast<CTexture_WebGPU*>(SIV3D_ENGINE(Texture));
			pMesh		= static_cast<CMesh_WebGPU*>(SIV3D_ENGINE(Mesh));

			m_device = pRenderer->getDevice();
		}

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer3D_WebGPU:");
			m_standardVS = std::make_unique<WebGPUStandardVS3D>();
			m_standardVS->forward = WGSL{ Resource(U"engine/shader/wgsl/forward3d.vert.wgsl"), { { U"VSPerView", 0 }, { U"VSPerObject", 1 } } };
			m_standardVS->line3D = WGSL{ Resource(U"engine/shader/wgsl/line3d.vert.wgsl"), { { U"VSPerView", 0 }, { U"VSPerObject", 1 } } };

			if (not m_standardVS->setup())
			{
				throw EngineError{ U"CRenderer3D_WebGPU::m_standardVS initialization failed" };
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer3D_WebGPU:");
			m_standardPS = std::make_unique<WebGPUStandardPS3D>();
			m_standardPS->forward = WGSL{ Resource(U"engine/shader/wgsl/forward3d.frag.wgsl"), { { U"PSPerFrame", 0 }, { U"PSPerView", 1 }, { U"PSPerMaterial", 2 } } };
			m_standardPS->line3D = WGSL{ Resource(U"engine/shader/wgsl/line3d.frag.wgsl"), {} };

			if (not m_standardPS->setup())
			{
				throw EngineError{ U"CRenderer3D_WebGPU::m_standardPS initialization failed" };
			}
		}

		if (not m_line3DBatch.init(*m_device))
		{
			throw EngineError{ U"WebGPULine3DBatch::init() failed" };
		}

		{
			Image emptyImage{ Size(1, 1), Palette::Yellow };
			m_emptyTexture = std::make_unique<Texture>(emptyImage);
		}
	}

	const Renderer3DStat& CRenderer3D_WebGPU::getStat() const
	{
		return m_stat;
	}

	void CRenderer3D_WebGPU::addMesh(const uint32 startIndex, const uint32 indexCount, const Mesh& mesh, const PhongMaterial& material)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardID);
		}

		m_commandManager.pushInputLayout(WebGPUInputLayout3D::Mesh);
		m_commandManager.pushMesh(mesh);

		const PhongMaterialInternal phong{ material };
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, phong, instanceCount);
	}

	void CRenderer3D_WebGPU::addTexturedMesh(const uint32 startIndex, const uint32 indexCount, const Mesh& mesh, const Texture& texture, const PhongMaterial& material)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardID);
		}

		m_commandManager.pushInputLayout(WebGPUInputLayout3D::Mesh);
		m_commandManager.pushMesh(mesh);
		m_commandManager.pushPSTexture(0, texture);

		const PhongMaterialInternal phong{ material };
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, phong, instanceCount);
	}

	void CRenderer3D_WebGPU::addLine3D(const Float3& begin, const Float3& end, const Float4(&colors)[2])
	{
		constexpr VertexLine3D::IndexType vertexSize = 2, indexSize = 2;
		auto [pVertex, pIndex, indexOffset] = m_line3DBatch.requestBuffer(vertexSize, indexSize, m_commandManager);

		pVertex[0].pos = Float4{ begin, 1.0f };
		pVertex[1].pos = Float4{ end, 1.0f };

		pVertex[0].color = colors[0];
		pVertex[1].color = colors[1];

		pIndex[0] = indexOffset;
		pIndex[1] = (indexOffset + 1);

		m_commandManager.pushMeshUnbind();
		m_commandManager.pushInputLayout(WebGPUInputLayout3D::Line3D);
		m_commandManager.pushDrawLine3D(indexSize);
	}


	BlendState CRenderer3D_WebGPU::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}

	RasterizerState CRenderer3D_WebGPU::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}

	DepthStencilState CRenderer3D_WebGPU::getDepthStencilState() const
	{
		return m_commandManager.getCurrentDepthStencilState();
	}

	SamplerState CRenderer3D_WebGPU::getSamplerState(const ShaderStage shaderStage, const uint32 slot) const
	{
		if (shaderStage == ShaderStage::Vertex)
		{
			return m_commandManager.getVSCurrentSamplerState(slot);
		}
		else
		{
			return m_commandManager.getPSCurrentSamplerState(slot);
		}
	}

	void CRenderer3D_WebGPU::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}

	void CRenderer3D_WebGPU::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}

	void CRenderer3D_WebGPU::setDepthStencilState(const DepthStencilState& state)
	{
		m_commandManager.pushDepthStencilState(state);
	}

	void CRenderer3D_WebGPU::setSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& state)
	{
		if (shaderStage == ShaderStage::Vertex)
		{
			m_commandManager.pushVSSamplerState(state, slot);
		}
		else
		{
			m_commandManager.pushPSSamplerState(state, slot);
		}
	}

	void CRenderer3D_WebGPU::setScissorRect(const Rect& rect)
	{
		m_commandManager.pushScissorRect(rect);
	}

	Rect CRenderer3D_WebGPU::getScissorRect() const
	{
		return m_commandManager.getCurrentScissorRect();
	}

	void CRenderer3D_WebGPU::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}

	Optional<Rect> CRenderer3D_WebGPU::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}

	void CRenderer3D_WebGPU::setGlobalAmbientColor(const Float3& color)
	{
		m_commandManager.pushGlobalAmbientColor(color);
	}

	Float3 CRenderer3D_WebGPU::getGlobalAmbientColor() const
	{
		return m_commandManager.getCurrentGlobalAmbientColor();
	}

	void CRenderer3D_WebGPU::setSunDirection(const Float3& direction)
	{
		m_commandManager.pushSunDirection(direction);
	}

	Float3 CRenderer3D_WebGPU::getSunDirection() const
	{
		return m_commandManager.getCurrentSunDirection();
	}

	void CRenderer3D_WebGPU::setSunColor(const Float3& color)
	{
		m_commandManager.pushSunColor(color);
	}

	Float3 CRenderer3D_WebGPU::getSunColor() const
	{
		return m_commandManager.getCurrentSunColor();
	}

	Optional<VertexShader> CRenderer3D_WebGPU::getCustomVS() const
	{
		return m_currentCustomVS;
	}

	Optional<PixelShader> CRenderer3D_WebGPU::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer3D_WebGPU::setCustomVS(const Optional<VertexShader>& vs)
	{
		if (vs && (not vs->isEmpty()))
		{
			m_currentCustomVS = *vs;
			m_commandManager.pushCustomVS(*vs);
		}
		else
		{
			m_currentCustomVS.reset();
		}
	}

	void CRenderer3D_WebGPU::setCustomPS(const Optional<PixelShader>& ps)
	{
		if (ps && (not ps->isEmpty()))
		{
			m_currentCustomPS = *ps;
			m_commandManager.pushCustomPS(*ps);
		}
		else
		{
			m_currentCustomPS.reset();
		}
	}

	const Mat4x4& CRenderer3D_WebGPU::getCameraTransform() const
	{
		return m_commandManager.getCurrentCameraTransform();
	}

	Float3 CRenderer3D_WebGPU::getEyePosition() const
	{
		return m_commandManager.getCurrentEyePosition();
	}

	void CRenderer3D_WebGPU::setCameraTransform(const Mat4x4& matrix, const Float3& eyePosition)
	{
		m_commandManager.pushCameraTransform(matrix);
		m_commandManager.pushEyePosition(eyePosition);
	}

	const Mat4x4& CRenderer3D_WebGPU::getLocalTransform() const
	{
		return m_commandManager.getCurrentLocalTransform();
	}

	void CRenderer3D_WebGPU::setLocalTransform(const Mat4x4& matrix)
	{
		m_commandManager.pushLocalTransform(matrix);
	}

	void CRenderer3D_WebGPU::setVSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		if (texture)
		{
			m_commandManager.pushVSTexture(slot, *texture);
		}
		else
		{
			m_commandManager.pushVSTextureUnbind(slot);
		}
	}

	void CRenderer3D_WebGPU::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		if (texture)
		{
			m_commandManager.pushPSTexture(slot, *texture);
		}
		else
		{
			m_commandManager.pushPSTextureUnbind(slot);
		}
	}

	void CRenderer3D_WebGPU::setRenderTarget(const Optional<RenderTexture>& rt)
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

	Optional<RenderTexture> CRenderer3D_WebGPU::getRenderTarget() const
	{
		return m_commandManager.getCurrentRT();
	}

	void CRenderer3D_WebGPU::setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors)
	{
		m_commandManager.pushConstantBuffer(stage, slot, buffer, data, num_vectors);
	}

	void CRenderer3D_WebGPU::flush()
	{
		auto encoder = *pRenderer->getCommandEncoder();
		flush(encoder);
	}

	void CRenderer3D_WebGPU::flush(const wgpu::CommandEncoder& encoder)
	{
		ScopeGuard cleanUp = [this]()
		{
			m_line3DBatch.reset();
			m_commandManager.reset();
			m_currentCustomVS.reset();
			m_currentCustomPS.reset();
		};

		m_commandManager.flush();

		if (not m_commandManager.hasDraw())
		{
			return;
		}

		pShader->setVS(VertexShader::IDType::NullAsset());
		pShader->setPS(PixelShader::IDType::NullAsset());

		BatchInfoLine3D batchInfoLine3D;
		VertexShader::IDType vsID = m_standardVS->forwardID;
		PixelShader::IDType psID = m_standardPS->forwardID;

		BlendState currentBlendState = BlendState::Default3D;
		RasterizerState currentRasterizerState = RasterizerState::Default3D;
		DepthStencilState currentDepthStencilState = DepthStencilState::Default3D;

		auto currentMesh = Mesh::IDType::InvalidValue();
		auto currentRenderingPass = pRenderer->getBackBuffer().begin(encoder);
		auto currentRenderTargetState = pRenderer->getBackBuffer().getRenderTargetState();

		Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		currentRenderingPass.SetViewport(0.0f, 0.0f, currentRenderTargetSize.x, currentRenderTargetSize.y, 0.0f, 1.0f);

		LOG_COMMAND(U"----");
		uint32 instanceIndex = 0;

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case WebGPURenderer3DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case WebGPURenderer3DCommandType::UpdateLine3DBuffers:
				{
					batchInfoLine3D = m_line3DBatch.updateBuffers(*m_device, command.index);

					LOG_COMMAND(U"UpdateLine3DBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfoLine3D.indexCount, batchInfoLine3D.startIndexLocation, batchInfoLine3D.baseVertexLocation));
					break;
				}
			case WebGPURenderer3DCommandType::Draw:
				{
					const PhongMaterialInternal& material = m_commandManager.getDrawPhongMaterial(instanceIndex);
					m_psPerMaterialConstants->material = material;

					m_vsPerViewConstants._update_if_dirty();
					m_vsPerObjectConstants._update_if_dirty();
					m_psPerFrameConstants._update_if_dirty();
					m_psPerViewConstants._update_if_dirty();
					m_psPerMaterialConstants._update_if_dirty();

					pShader->setConstantBufferVS(0, m_vsPerViewConstants.base());
					pShader->setConstantBufferVS(1, m_vsPerObjectConstants.base());
					pShader->setConstantBufferPS(0, m_psPerFrameConstants.base());
					pShader->setConstantBufferPS(1, m_psPerViewConstants.base());
					pShader->setConstantBufferPS(2, m_psPerMaterialConstants.base());

					auto pipeline = pShader->usePipelineWithStandard3DVertexLayout(currentRenderingPass, currentRasterizerState, currentBlendState, currentRenderTargetState, currentDepthStencilState);
					pRenderer->getSamplerState().bind(m_device, pipeline, currentRenderingPass);

					pMesh->bindMeshToContext(currentRenderingPass, currentMesh);

					const WebGPUDraw3DCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = draw.startIndex;
					const uint32 instanceCount = draw.instanceCount;

					currentRenderingPass.DrawIndexed(indexCount, 1, startIndexLocation);
	
					instanceIndex += instanceCount;

					//++m_stat.drawCalls;
					//m_stat.triangleCount += (indexCount / 3);

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			case WebGPURenderer3DCommandType::DrawLine3D:
				{
					pShader->setVS(m_standardVS->line3DID);
					pShader->setPS(m_standardPS->line3DID);

					pShader->resetConstantBufferVS();
					pShader->resetConstantBufferPS();

					m_vsPerViewConstants._update_if_dirty();
					m_vsPerObjectConstants._update_if_dirty();
					m_psPerFrameConstants._update_if_dirty();
					m_psPerViewConstants._update_if_dirty();
					m_psPerMaterialConstants._update_if_dirty();

					pShader->setConstantBufferVS(0, m_vsPerViewConstants.base());
					pShader->setConstantBufferVS(1, m_vsPerObjectConstants.base());
					pShader->setConstantBufferPS(0, m_psPerFrameConstants.base());
					pShader->setConstantBufferPS(1, m_psPerViewConstants.base());
					pShader->setConstantBufferPS(2, m_psPerMaterialConstants.base());

					auto pipeline = pShader->usePipelineWithStandard3DLineVertexLayout(currentRenderingPass, currentRasterizerState, currentBlendState, currentRenderTargetState, currentDepthStencilState);
					pRenderer->getSamplerState().bind(m_device, pipeline, currentRenderingPass);

					m_line3DBatch.setBuffers(currentRenderingPass);

					const WebGPUDrawLine3DCommand& draw = m_commandManager.getDrawLine3D(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfoLine3D.startIndexLocation;
					const uint32 baseVertexLocation = batchInfoLine3D.baseVertexLocation;
				
					currentRenderingPass.DrawIndexed(indexCount, 1, startIndexLocation, baseVertexLocation);

					batchInfoLine3D.startIndexLocation += indexCount;

					if (vsID != VertexShader::IDType::InvalidValue())
					{
						pShader->setVS(vsID);
					}

					if (psID != PixelShader::IDType::InvalidValue())
					{
						pShader->setPS(psID);
					}

					LOG_COMMAND(U"DrawLine3D[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			case WebGPURenderer3DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					currentBlendState = blendState;
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer3DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					currentRasterizerState = rasterizerState;
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer3DCommandType::DepthStencilState:
				{
					const auto& depthStencilState = m_commandManager.getDepthStencilState(command.index);
					currentDepthStencilState = depthStencilState;
					LOG_COMMAND(U"DepthStencilState[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer3DCommandType::VSSamplerState0:
			case WebGPURenderer3DCommandType::VSSamplerState1:
			case WebGPURenderer3DCommandType::VSSamplerState2:
			case WebGPURenderer3DCommandType::VSSamplerState3:
			case WebGPURenderer3DCommandType::VSSamplerState4:
			case WebGPURenderer3DCommandType::VSSamplerState5:
			case WebGPURenderer3DCommandType::VSSamplerState6:
			case WebGPURenderer3DCommandType::VSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(WebGPURenderer3DCommandType::VSSamplerState0);
					const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setVSSampler(m_device, slot, samplerState);
					LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case WebGPURenderer3DCommandType::PSSamplerState0:
			case WebGPURenderer3DCommandType::PSSamplerState1:
			case WebGPURenderer3DCommandType::PSSamplerState2:
			case WebGPURenderer3DCommandType::PSSamplerState3:
			case WebGPURenderer3DCommandType::PSSamplerState4:
			case WebGPURenderer3DCommandType::PSSamplerState5:
			case WebGPURenderer3DCommandType::PSSamplerState6:
			case WebGPURenderer3DCommandType::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(WebGPURenderer3DCommandType::PSSamplerState0);
					const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setPSSampler(m_device, slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case WebGPURenderer3DCommandType::ScissorRect:
				{
					const auto& scissorRect = m_commandManager.getScissorRect(command.index);

					if (scissorRect.hasArea())
					{
						currentRenderingPass.SetScissorRect(scissorRect.x, scissorRect.y, scissorRect.w, scissorRect.h);
					}

					LOG_COMMAND(U"ScissorRect[{}] {}"_fmt(command.index, scissorRect));
					break;
				}
			case WebGPURenderer3DCommandType::Viewport:
				{
					const auto& viewport = m_commandManager.getViewport(command.index);
					Rect rect;

					if (viewport)
					{
						rect = *viewport;
					}
					else
					{
						rect.x = 0;
						rect.y = 0;
						rect.w = currentRenderTargetSize.x;
						rect.h = currentRenderTargetSize.y;
					}

					rect.w = Min(rect.w, currentRenderTargetSize.x);
					rect.h = Min(rect.h, currentRenderTargetSize.y);

					currentRenderingPass.SetViewport(rect.x, rect.y, rect.w, rect.h, 0.0f, 1.0f);

					LOG_COMMAND(U"Viewport[{}] (x = {}, y = {}, w = {}, h = {})"_fmt(command.index,
						rect.x, rect.y, rect.w, rect.h));
					break;
				}
			case WebGPURenderer3DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					currentRenderingPass.EndPass();
					
					if (rt) // [カスタム RenderTexture]
					{
						currentRenderingPass = pTexture->begin(rt->id(), encoder);
						currentRenderTargetState = pTexture->getRenderTargetState(rt->id());
						currentRenderTargetSize = pTexture->getSize(rt->id());

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else // [シーン]
					{
						currentRenderingPass = pRenderer->getBackBuffer().begin(encoder);
						currentRenderTargetState = pRenderer->getBackBuffer().getRenderTargetState();
						currentRenderTargetSize = pRenderer->getBackBuffer().getSceneBufferSize();

						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}
					break;
				}
			case WebGPURenderer3DCommandType::InputLayout:
				{
					[[maybe_unused]] const auto& inputLayout = m_commandManager.getInputLayout(command.index);

					// do nothing

					LOG_COMMAND(U"InputLayout[{}] {}"_fmt(command.index, FromEnum(inputLayout)));
					break;
				}
			case WebGPURenderer3DCommandType::SetVS:
				{
					vsID = m_commandManager.getVS(command.index);

					pShader->resetConstantBufferVS();

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
			case WebGPURenderer3DCommandType::SetPS:
				{
					psID = m_commandManager.getPS(command.index);

					pShader->resetConstantBufferPS();

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
			case WebGPURenderer3DCommandType::CameraTransform:
				{
					const Mat4x4& cameraTransform = m_commandManager.getCameraTransform(command.index);
					m_vsPerViewConstants->worldToProjected = cameraTransform.transposed();

					LOG_COMMAND(U"CameraTransform[{}] {}"_fmt(command.index, cameraTransform));
					break;
				}
			case WebGPURenderer3DCommandType::EyePosition:
				{
					const Float3& eyePosition = m_commandManager.getEyePosition(command.index);
					m_psPerViewConstants->eyePosition = Float4{ eyePosition, 0.0f };

					LOG_COMMAND(U"EyePosition[{}] {}"_fmt(command.index, eyePosition));
					break;
				}
			case WebGPURenderer3DCommandType::LocalTransform:
				{
					const Mat4x4& localTransform = m_commandManager.getLocalTransform(command.index);
					m_vsPerObjectConstants->localToWorld = localTransform.transposed();

					LOG_COMMAND(U"LocalTransform[{}] {}"_fmt(command.index, localTransform));
					break;
				}
			case WebGPURenderer3DCommandType::SetConstantBuffer:
				{
					auto& cb = m_commandManager.getConstantBuffer(command.index);
					const __m128* p = m_commandManager.getConstantBufferPtr(cb.offset);
					
					if (cb.num_vectors)
					{	
						cb.cbBase._internal_update(p, (cb.num_vectors * 16));

						if (cb.stage == ShaderStage::Vertex)
						{
							pShader->setConstantBufferVS(cb.slot, cb.cbBase);
						}
						else
						{
							pShader->setConstantBufferPS(cb.slot, cb.cbBase);
						}					
					}
					
					LOG_COMMAND(U"SetConstantBuffer[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
						command.index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
					break;
				}
			case WebGPURenderer3DCommandType::VSTexture0:
			case WebGPURenderer3DCommandType::VSTexture1:
			case WebGPURenderer3DCommandType::VSTexture2:
			case WebGPURenderer3DCommandType::VSTexture3:
			case WebGPURenderer3DCommandType::VSTexture4:
			case WebGPURenderer3DCommandType::VSTexture5:
			case WebGPURenderer3DCommandType::VSTexture6:
			case WebGPURenderer3DCommandType::VSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(WebGPURenderer3DCommandType::VSTexture0));
					const auto& textureID = m_commandManager.getVSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						pRenderer->getSamplerState().setVSTexture(slot, pTexture->getTextureView(m_emptyTexture->id()));
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						pRenderer->getSamplerState().setVSTexture(slot, pTexture->getTextureView(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case WebGPURenderer3DCommandType::PSTexture0:
			case WebGPURenderer3DCommandType::PSTexture1:
			case WebGPURenderer3DCommandType::PSTexture2:
			case WebGPURenderer3DCommandType::PSTexture3:
			case WebGPURenderer3DCommandType::PSTexture4:
			case WebGPURenderer3DCommandType::PSTexture5:
			case WebGPURenderer3DCommandType::PSTexture6:
			case WebGPURenderer3DCommandType::PSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(WebGPURenderer3DCommandType::PSTexture0));
					const auto& textureID = m_commandManager.getPSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						pRenderer->getSamplerState().setPSTexture(slot, pTexture->getTextureView(m_emptyTexture->id()));
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						pRenderer->getSamplerState().setPSTexture(slot, pTexture->getTextureView(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case WebGPURenderer3DCommandType::SetMesh:
				{
					const auto& meshID = m_commandManager.getMesh(command.index);

					if (meshID == Mesh::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetMesh[{}]: null"_fmt(command.index));
					}
					else
					{
						currentMesh = meshID;
						LOG_COMMAND(U"SetMesh[{}]: {}"_fmt(command.index, meshID.value()));
					}

					break;
				}
			case WebGPURenderer3DCommandType::SetGlobalAmbientColor:
				{
					const Float3& globalAmbient = m_commandManager.getGlobalAmbientColor(command.index);
					m_psPerFrameConstants->gloablAmbientColor = Float4{ globalAmbient, 0.0f };

					LOG_COMMAND(U"SetGlobalAmbientColor[{}] {}"_fmt(command.index, globalAmbient));
					break;
				}
			case WebGPURenderer3DCommandType::SetSunDirection:
				{
					const Float3& sunDirection = m_commandManager.getSunDirection(command.index);
					m_psPerFrameConstants->sunDirection = Float4{ sunDirection, 0.0f };

					LOG_COMMAND(U"SetSunDirection[{}] {}"_fmt(command.index, sunDirection));
					break;
				}
			case WebGPURenderer3DCommandType::SetSunColor:
				{
					const Float3& sunColor = m_commandManager.getSunColor(command.index);
					m_psPerFrameConstants->sunColor = Float4{ sunColor, 0.0f };

					LOG_COMMAND(U"SetSunColor[{}] {}"_fmt(command.index, sunColor));
					break;
				}
			}
		}

		currentRenderingPass.EndPass();
	}
}
