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

# include "CRenderer3D_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Shader/GL4/CShader_GL4.hpp>
# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>
# include <Siv3D/Mesh/GL4/CMesh_GL4.hpp>
# include <Siv3D/ConstantBuffer/GL4/ConstantBufferDetail_GL4.hpp>

/*/
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer3D_GL4::CRenderer3D_GL4() {}

	CRenderer3D_GL4::~CRenderer3D_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GL4::~CRenderer3D_GL4()");
	}

	void CRenderer3D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GL4::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= static_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer));
			pShader		= static_cast<CShader_GL4*>(SIV3D_ENGINE(Shader));
			pTexture	= static_cast<CTexture_GL4*>(SIV3D_ENGINE(Texture));
			pMesh		= static_cast<CMesh_GL4*>(SIV3D_ENGINE(Mesh));
		}

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer3D_GL4:");
			m_standardVS = std::make_unique<GL4StandardVS3D>();
			m_standardVS->forward = GLSL{ Resource(U"engine/shader/glsl/forward3d.vert"), { { U"VSPerView", 1 }, { U"VSPerObject", 2 }, { U"VSPerMaterial", 3 } } };
			m_standardVS->line3D = GLSL{ Resource(U"engine/shader/glsl/line3d.vert"), { { U"VSPerView", 1 }, { U"VSPerObject", 2 } } };

			if (not m_standardVS->setup())
			{
				throw EngineError{ U"CRenderer3D_GL4::m_standardVS initialization failed" };
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer3D_GL4:");
			m_standardPS = std::make_unique<GL4StandardPS3D>();
			m_standardPS->forward = GLSL{ Resource(U"engine/shader/glsl/forward3d.frag"), { { U"PSPerFrame", 0 }, { U"PSPerView", 1 }, { U"PSPerMaterial", 3 } } };
			m_standardPS->line3D = GLSL{ Resource(U"engine/shader/glsl/line3d.frag"), {} };

			if (not m_standardPS->setup())
			{
				throw EngineError{ U"CRenderer3D_GL4::m_standardPS initialization failed" };
			}
		}

		if (not m_line3DBatch.init())
		{
			throw EngineError{ U"GL4Line3DBatch::init() failed" };
		}
	}

	const Renderer3DStat& CRenderer3D_GL4::getStat() const
	{
		return m_stat;
	}

	void CRenderer3D_GL4::addMesh(const uint32 startIndex, const uint32 indexCount, const Mesh& mesh, const PhongMaterial& material)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardID);
		}

		m_commandManager.pushInputLayout(GL4InputLayout3D::Mesh);
		m_commandManager.pushMesh(mesh);
		m_commandManager.pushUVTransform(Float4{ 1.0f, 1.0f, 0.0f, 0.0f });

		const PhongMaterialInternal phong{ material };
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, phong, instanceCount);
	}

	void CRenderer3D_GL4::addTexturedMesh(const uint32 startIndex, const uint32 indexCount, const Mesh& mesh, const Texture& texture, const PhongMaterial& material)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardID);
		}

		m_commandManager.pushInputLayout(GL4InputLayout3D::Mesh);
		m_commandManager.pushMesh(mesh);
		m_commandManager.pushUVTransform(Float4{ 1.0f, 1.0f, 0.0f, 0.0f });
		m_commandManager.pushPSTexture(0, texture);

		const PhongMaterialInternal phong{ material };
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, phong, instanceCount);
	}

	void CRenderer3D_GL4::addTexturedMesh(const uint32 startIndex, const uint32 indexCount, const Mesh& mesh, const TextureRegion& textureRegion, const PhongMaterial& material)
	{
		if (not m_currentCustomVS)
		{
			m_commandManager.pushStandardVS(m_standardVS->forwardID);
		}

		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->forwardID);
		}

		m_commandManager.pushInputLayout(GL4InputLayout3D::Mesh);
		m_commandManager.pushMesh(mesh);

		Float4 uvTransform;
		uvTransform.x = (textureRegion.uvRect.right - textureRegion.uvRect.left);
		uvTransform.y = (textureRegion.uvRect.bottom - textureRegion.uvRect.top);
		uvTransform.z = textureRegion.uvRect.left;
		uvTransform.w = textureRegion.uvRect.top;
		m_commandManager.pushUVTransform(uvTransform);
		m_commandManager.pushPSTexture(0, textureRegion.texture);

		const PhongMaterialInternal phong{ material };
		const uint32 instanceCount = 1;
		m_commandManager.pushDraw(startIndex, indexCount, phong, instanceCount);
	}

	void CRenderer3D_GL4::addLine3D(const Float3& begin, const Float3& end, const Float4(&colors)[2])
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
		m_commandManager.pushInputLayout(GL4InputLayout3D::Line3D);
		m_commandManager.pushDrawLine3D(indexSize);
	}


	BlendState CRenderer3D_GL4::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}

	RasterizerState CRenderer3D_GL4::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}

	DepthStencilState CRenderer3D_GL4::getDepthStencilState() const
	{
		return m_commandManager.getCurrentDepthStencilState();
	}

	SamplerState CRenderer3D_GL4::getSamplerState(const ShaderStage shaderStage, const uint32 slot) const
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

	void CRenderer3D_GL4::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}

	void CRenderer3D_GL4::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}

	void CRenderer3D_GL4::setDepthStencilState(const DepthStencilState& state)
	{
		m_commandManager.pushDepthStencilState(state);
	}

	void CRenderer3D_GL4::setSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& state)
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

	void CRenderer3D_GL4::setScissorRect(const Rect& rect)
	{
		m_commandManager.pushScissorRect(rect);
	}

	Rect CRenderer3D_GL4::getScissorRect() const
	{
		return m_commandManager.getCurrentScissorRect();
	}

	void CRenderer3D_GL4::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}

	Optional<Rect> CRenderer3D_GL4::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}

	void CRenderer3D_GL4::setGlobalAmbientColor(const Float3& color)
	{
		m_commandManager.pushGlobalAmbientColor(color);
	}

	Float3 CRenderer3D_GL4::getGlobalAmbientColor() const
	{
		return m_commandManager.getCurrentGlobalAmbientColor();
	}

	void CRenderer3D_GL4::setSunDirection(const Float3& direction)
	{
		m_commandManager.pushSunDirection(direction);
	}

	Float3 CRenderer3D_GL4::getSunDirection() const
	{
		return m_commandManager.getCurrentSunDirection();
	}

	void CRenderer3D_GL4::setSunColor(const Float3& color)
	{
		m_commandManager.pushSunColor(color);
	}

	Float3 CRenderer3D_GL4::getSunColor() const
	{
		return m_commandManager.getCurrentSunColor();
	}

	Optional<VertexShader> CRenderer3D_GL4::getCustomVS() const
	{
		return m_currentCustomVS;
	}

	Optional<PixelShader> CRenderer3D_GL4::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer3D_GL4::setCustomVS(const Optional<VertexShader>& vs)
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

	void CRenderer3D_GL4::setCustomPS(const Optional<PixelShader>& ps)
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

	const Mat4x4& CRenderer3D_GL4::getCameraTransform() const
	{
		return m_commandManager.getCurrentCameraTransform();
	}

	Float3 CRenderer3D_GL4::getEyePosition() const
	{
		return m_commandManager.getCurrentEyePosition();
	}

	void CRenderer3D_GL4::setCameraTransform(const Mat4x4& matrix, const Float3& eyePosition)
	{
		m_commandManager.pushCameraTransform(matrix);
		m_commandManager.pushEyePosition(eyePosition);
	}

	const Mat4x4& CRenderer3D_GL4::getLocalTransform() const
	{
		return m_commandManager.getCurrentLocalTransform();
	}

	void CRenderer3D_GL4::setLocalTransform(const Mat4x4& matrix)
	{
		m_commandManager.pushLocalTransform(matrix);
	}

	void CRenderer3D_GL4::setVSTexture(const uint32 slot, const Optional<Texture>& texture)
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

	void CRenderer3D_GL4::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
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

	void CRenderer3D_GL4::setRenderTarget(const Optional<RenderTexture>& rt)
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

	Optional<RenderTexture> CRenderer3D_GL4::getRenderTarget() const
	{
		return m_commandManager.getCurrentRT();
	}

	void CRenderer3D_GL4::setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors)
	{
		m_commandManager.pushConstantBuffer(stage, slot, buffer, data, num_vectors);
	}

	void CRenderer3D_GL4::flush()
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

		pShader->usePipeline();

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		::glViewport(0, 0, currentRenderTargetSize.x, currentRenderTargetSize.y);

		pShader->setConstantBufferVS(1, m_vsPerViewConstants.base());
		pShader->setConstantBufferVS(2, m_vsPerObjectConstants.base());
		pShader->setConstantBufferVS(3, m_vsPerMaterialConstants.base());
		pShader->setConstantBufferPS(0, m_psPerFrameConstants.base());
		pShader->setConstantBufferPS(1, m_psPerViewConstants.base());
		pShader->setConstantBufferPS(3, m_psPerMaterialConstants.base());

		BatchInfoLine3D batchInfoLine3D;
		VertexShader::IDType vsID = m_standardVS->forwardID;
		PixelShader::IDType psID = m_standardPS->forwardID;

		LOG_COMMAND(U"----");
		uint32 instanceIndex = 0;

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case GL4Renderer3DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case GL4Renderer3DCommandType::UpdateLine3DBuffers:
				{
					batchInfoLine3D = m_line3DBatch.updateBuffers(command.index);

					LOG_COMMAND(U"UpdateLine3DBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfoLine3D.indexCount, batchInfoLine3D.startIndexLocation, batchInfoLine3D.baseVertexLocation));
					break;
				}
			case GL4Renderer3DCommandType::Draw:
				{
					const GL4Draw3DCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = draw.startIndex;
					const uint32 instanceCount = draw.instanceCount;

					const PhongMaterialInternal& material = m_commandManager.getDrawPhongMaterial(instanceIndex);
					m_psPerMaterialConstants->material = material;

					m_vsPerViewConstants._update_if_dirty();
					m_vsPerObjectConstants._update_if_dirty();
					m_vsPerMaterialConstants._update_if_dirty();
					m_psPerFrameConstants._update_if_dirty();
					m_psPerViewConstants._update_if_dirty();
					m_psPerMaterialConstants._update_if_dirty();

					constexpr Vertex3D::IndexType* pBase = 0;
					::glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (pBase + startIndexLocation), 0);

					instanceIndex += instanceCount;

					//++m_stat.drawCalls;
					//m_stat.triangleCount += (indexCount / 3);

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			case GL4Renderer3DCommandType::DrawLine3D:
				{
					m_line3DBatch.setBuffers();

					pShader->setVS(m_standardVS->line3DID);
					pShader->setPS(m_standardPS->line3DID);

					m_vsPerViewConstants._update_if_dirty();
					m_vsPerObjectConstants._update_if_dirty();
					m_vsPerMaterialConstants._update_if_dirty();
					m_psPerFrameConstants._update_if_dirty();
					m_psPerViewConstants._update_if_dirty();
					m_psPerMaterialConstants._update_if_dirty();

					const GL4DrawLine3DCommand& draw = m_commandManager.getDrawLine3D(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfoLine3D.startIndexLocation;
					const uint32 baseVertexLocation = batchInfoLine3D.baseVertexLocation;
					constexpr VertexLine3D::IndexType* pBase = 0;

					::glDrawElementsBaseVertex(GL_LINES, indexCount, GL_UNSIGNED_INT, (pBase + startIndexLocation), baseVertexLocation);
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
			case GL4Renderer3DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					pRenderer->getBlendState().set(blendState);
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case GL4Renderer3DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					pRenderer->getRasterizerState().set(rasterizerState);
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}
			case GL4Renderer3DCommandType::DepthStencilState:
				{
					const auto& depthStencilState = m_commandManager.getDepthStencilState(command.index);
					pRenderer->getDepthStencilState().set(depthStencilState);
					LOG_COMMAND(U"DepthStencilState[{}]"_fmt(command.index));
					break;
				}
			case GL4Renderer3DCommandType::VSSamplerState0:
			case GL4Renderer3DCommandType::VSSamplerState1:
			case GL4Renderer3DCommandType::VSSamplerState2:
			case GL4Renderer3DCommandType::VSSamplerState3:
			case GL4Renderer3DCommandType::VSSamplerState4:
			case GL4Renderer3DCommandType::VSSamplerState5:
			case GL4Renderer3DCommandType::VSSamplerState6:
			case GL4Renderer3DCommandType::VSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(GL4Renderer3DCommandType::VSSamplerState0);
					const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setVS(slot, samplerState);
					LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case GL4Renderer3DCommandType::PSSamplerState0:
			case GL4Renderer3DCommandType::PSSamplerState1:
			case GL4Renderer3DCommandType::PSSamplerState2:
			case GL4Renderer3DCommandType::PSSamplerState3:
			case GL4Renderer3DCommandType::PSSamplerState4:
			case GL4Renderer3DCommandType::PSSamplerState5:
			case GL4Renderer3DCommandType::PSSamplerState6:
			case GL4Renderer3DCommandType::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(GL4Renderer3DCommandType::PSSamplerState0);
					const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setPS(slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case GL4Renderer3DCommandType::ScissorRect:
				{
					const auto& scissorRect = m_commandManager.getScissorRect(command.index);
					::glScissor(scissorRect.x, scissorRect.y, scissorRect.w, scissorRect.h);
					LOG_COMMAND(U"ScissorRect[{}] {}"_fmt(command.index, scissorRect));
					break;
				}
			case GL4Renderer3DCommandType::Viewport:
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

					::glViewport(rect.x, rect.y, rect.w, rect.h);

					LOG_COMMAND(U"Viewport[{}] (x = {}, y = {}, w = {}, h = {})"_fmt(command.index,
						rect.x, rect.y, rect.w, rect.h));
					break;
				}
			case GL4Renderer3DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					if (rt) // [カスタム RenderTexture]
					{
						const GLuint frameBuffer = pTexture->getFrameBuffer(rt->id());
						const bool isSRGB = pTexture->getFormat(rt->id()).isSRGB();
						pRenderer->getBackBuffer().bindToScene(frameBuffer);
						
						if (isSRGB)
						{
							::glEnable(GL_FRAMEBUFFER_SRGB);
						}
						else
						{
							::glDisable(GL_FRAMEBUFFER_SRGB);
						}

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else // [シーン]
					{
						pRenderer->getBackBuffer().bindSceneToContext();
						
						::glDisable(GL_FRAMEBUFFER_SRGB);

						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}

					break;
				}
			case GL4Renderer3DCommandType::InputLayout:
				{
					[[maybe_unused]] const auto& inputLayout = m_commandManager.getInputLayout(command.index);

					// do nothing

					LOG_COMMAND(U"InputLayout[{}] {}"_fmt(command.index, FromEnum(inputLayout)));
					break;
				}
			case GL4Renderer3DCommandType::SetVS:
				{
					vsID = m_commandManager.getVS(command.index);

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
			case GL4Renderer3DCommandType::SetPS:
				{
					psID = m_commandManager.getPS(command.index);

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
			case GL4Renderer3DCommandType::CameraTransform:
				{
					const Mat4x4& cameraTransform = m_commandManager.getCameraTransform(command.index);
					m_vsPerViewConstants->worldToProjected = (cameraTransform * Mat4x4::Scale(Float3{ 1.0f, -1.0f, 1.0f })).transposed();

					LOG_COMMAND(U"CameraTransform[{}] {}"_fmt(command.index, cameraTransform));
					break;
				}
			case GL4Renderer3DCommandType::EyePosition:
				{
					const Float3& eyePosition = m_commandManager.getEyePosition(command.index);
					m_psPerViewConstants->eyePosition = Float4{ eyePosition, 0.0f };

					LOG_COMMAND(U"EyePosition[{}] {}"_fmt(command.index, eyePosition));
					break;
				}
			case GL4Renderer3DCommandType::LocalTransform:
				{
					const Mat4x4& localTransform = m_commandManager.getLocalTransform(command.index);
					m_vsPerObjectConstants->localToWorld = localTransform.transposed();

					LOG_COMMAND(U"LocalTransform[{}] {}"_fmt(command.index, localTransform));
					break;
				}
			case GL4Renderer3DCommandType::UVTransform:
				{
					const Float4& uvTransform = m_commandManager.getUVTransform(command.index);
					m_vsPerMaterialConstants->uvTransform = uvTransform;

					LOG_COMMAND(U"UVTransform[{}] {}"_fmt(command.index, uvTransform));
					break;
				}
			case GL4Renderer3DCommandType::SetConstantBuffer:
				{
					auto& cb = m_commandManager.getConstantBuffer(command.index);
					const __m128* p = m_commandManager.getConstantBufferPtr(cb.offset);
					
					if (cb.num_vectors)
					{
						const ConstantBufferDetail_GL4* cbd = static_cast<const ConstantBufferDetail_GL4*>(cb.cbBase._detail());
						const uint32 uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(cb.stage, cb.slot);
						::glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBinding, cbd->getHandle());
						cb.cbBase._internal_update(p, (cb.num_vectors * 16));
					}
					
					LOG_COMMAND(U"SetConstantBuffer[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
						command.index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
					break;
				}
			case GL4Renderer3DCommandType::VSTexture0:
			case GL4Renderer3DCommandType::VSTexture1:
			case GL4Renderer3DCommandType::VSTexture2:
			case GL4Renderer3DCommandType::VSTexture3:
			case GL4Renderer3DCommandType::VSTexture4:
			case GL4Renderer3DCommandType::VSTexture5:
			case GL4Renderer3DCommandType::VSTexture6:
			case GL4Renderer3DCommandType::VSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(GL4Renderer3DCommandType::VSTexture0));
					const auto& textureID = m_commandManager.getVSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot));
						::glBindTexture(GL_TEXTURE_2D, 0);
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot));
						::glBindTexture(GL_TEXTURE_2D, pTexture->getTexture(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case GL4Renderer3DCommandType::PSTexture0:
			case GL4Renderer3DCommandType::PSTexture1:
			case GL4Renderer3DCommandType::PSTexture2:
			case GL4Renderer3DCommandType::PSTexture3:
			case GL4Renderer3DCommandType::PSTexture4:
			case GL4Renderer3DCommandType::PSTexture5:
			case GL4Renderer3DCommandType::PSTexture6:
			case GL4Renderer3DCommandType::PSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(GL4Renderer3DCommandType::PSTexture0));
					const auto& textureID = m_commandManager.getPSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						::glActiveTexture(GL_TEXTURE0 + slot);
						::glBindTexture(GL_TEXTURE_2D, 0);
						LOG_COMMAND(U"PSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						::glActiveTexture(GL_TEXTURE0 + slot);
						::glBindTexture(GL_TEXTURE_2D, pTexture->getTexture(textureID));
						LOG_COMMAND(U"PSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case GL4Renderer3DCommandType::SetMesh:
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
			case GL4Renderer3DCommandType::SetGlobalAmbientColor:
				{
					const Float3& globalAmbient = m_commandManager.getGlobalAmbientColor(command.index);
					m_psPerFrameConstants->globalAmbientColor = Float4{ globalAmbient, 0.0f };

					LOG_COMMAND(U"SetGlobalAmbientColor[{}] {}"_fmt(command.index, globalAmbient));
					break;
				}
			case GL4Renderer3DCommandType::SetSunDirection:
				{
					const Float3& sunDirection = m_commandManager.getSunDirection(command.index);
					m_psPerFrameConstants->sunDirection = Float4{ sunDirection, 0.0f };

					LOG_COMMAND(U"SetSunDirection[{}] {}"_fmt(command.index, sunDirection));
					break;
				}
			case GL4Renderer3DCommandType::SetSunColor:
				{
					const Float3& sunColor = m_commandManager.getSunColor(command.index);
					m_psPerFrameConstants->sunColor = Float4{ sunColor, 0.0f };

					LOG_COMMAND(U"SetSunColor[{}] {}"_fmt(command.index, sunColor));
					break;
				}
			}
		}

		::glBindVertexArray(0);

		CheckOpenGLError();
	}
}
