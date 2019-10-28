//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Math.hpp>
# include <ConstantBuffer/GL/GLConstantBuffer.hpp>
# include <Graphics/IGraphics.hpp>
# include <Graphics/GL/CGraphics_GL.hpp>
# include <Texture/GL/CTexture_GL.hpp>
# include <Shader/GL/CShader_GL.hpp>
# include <Profiler/IProfiler.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/Vertex2DBuilder.hpp>
# include "CRenderer2D_GL.hpp"
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>


/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	using Math::Constants::Pi_v;

	struct StandardVSIndex
	{
		enum Type
		{
			Sprite,
		};
	};
	
	struct StandardPSIndex
	{
		enum Type
		{
			Shape,
			Texture,
			SquareDot,
			RoundDot,
			SDF,
		};
	};
	
	inline void CheckError(const String& s)
	{
		Logger << U"---" << s << U"---";
		
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR)
		{
			Logger << U"Error: 0x" << ToHex(err);
		}
	}
	
	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		LOG_TRACE(U"CRenderer2D_GL::~CRenderer2D_GL()");
	}

	void CRenderer2D_GL::init()
	{
		LOG_TRACE(U"CRenderer2D_GL::init()");
		
		// 標準 VS をロード
		{
			m_standardVS = std::make_unique<GLStandardVS2D>();
			m_standardVS->sprite = VertexShader(Resource(U"engine/shader/sprite.vert"), { { U"VSConstants2D", 0 } });
			if (!m_standardVS->ok())
			{
				throw EngineError(U"CRenderer2D_GL::m_standardVSs initialization failed");
			}
		}
		
		// 標準 PS をロード
		{
			m_standardPS = std::make_unique<GLStandardPS2D>();
			m_standardPS->shape			= PixelShader(Resource(U"engine/shader/shape.frag"), { { U"PSConstants2D", 0 } });
			m_standardPS->texture		= PixelShader(Resource(U"engine/shader/texture.frag"), { { U"PSConstants2D", 0 } });
			m_standardPS->square_dot	= PixelShader(Resource(U"engine/shader/square_dot.frag"), { { U"PSConstants2D", 0 } });
			m_standardPS->round_dot		= PixelShader(Resource(U"engine/shader/round_dot.frag"), { { U"PSConstants2D", 0 } });
			m_standardPS->sdf			= PixelShader(Resource(U"engine/shader/sdf.frag"), { { U"PSConstants2D", 0 } });
			if (!m_standardPS->setup())
			{
				throw EngineError(U"CRenderer2D_GL::m_standardPSs initialization failed");
			}
		}
		
		// パイプライン管理を初期化
		if (!m_pipeline.init())
		{
			throw EngineError(U"ShaderPipeline::init() failed");
		}
		
		// Batch 管理を初期化
		if (!m_batches.init())
		{
			throw EngineError(U"GLSpriteBatch::init() failed");
		}

		// バッファ作成関数を作成
		m_bufferCreator = [this](IndexType vertexSize, IndexType indexSize)
		{
			return m_batches.getBuffer(vertexSize, indexSize, m_commands);
		};
		
		// シャドウ画像を作成
		{
			const Image boxShadowImage(Resource(U"engine/texture/box-shadow/256.png"));
			
			const Array<Image> boxShadowImageMips =
			{
				Image(Resource(U"engine/texture/box-shadow/128.png")),
				Image(Resource(U"engine/texture/box-shadow/64.png")),
				Image(Resource(U"engine/texture/box-shadow/32.png")),
				Image(Resource(U"engine/texture/box-shadow/16.png")),
				Image(Resource(U"engine/texture/box-shadow/8.png")),
			};
			
			m_boxShadowTexture = std::make_unique<Texture>(boxShadowImage, boxShadowImageMips);
			
			if (!(*m_boxShadowTexture))
			{
				throw EngineError(U"Failed to create CRenderer2D_GL::m_boxShadowTexture");
			}
		}

		LOG_INFO(U"ℹ️ CRenderer2D_GL initialized");
	}

	void CRenderer2D_GL::flush()
	{
		//CheckError(U"F00");
		
		ScopeGuard cleanUp = [this]()
		{
			m_currentCustomPS.reset();
			m_batches.reset();
			m_commands.reset();
		};
		
		m_commands.flush();

		CGraphics_GL* const pGraphics = dynamic_cast<CGraphics_GL* const>(Siv3DEngine::Get<ISiv3DGraphics>());
		CShader_GL* const pShader = dynamic_cast<CShader_GL* const>(Siv3DEngine::Get<ISiv3DShader>());
		CTexture_GL* const pTexture = dynamic_cast<CTexture_GL* const>(Siv3DEngine::Get<ISiv3DTexture>());

		m_pipeline.setVS(pShader->getVSProgram(m_standardVS->sprite.id()));
		m_pipeline.setPS(pShader->getPSProgram(m_standardPS->shape.id()));
		m_pipeline.use();
		
		Size currentRenderTargetSize = pGraphics->getSceneSize();
		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		BatchInfo batchInfo;
		size_t profile_drawcalls = 0, profile_vertices = 0;
		
		const uint32 vsUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, 0);
		::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, m_vsConstants2D.base()._detail()->getHandle());
		
		const uint32 psUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, 0);
		::glBindBufferBase(GL_UNIFORM_BUFFER, psUniformBlockBinding, m_psConstants2D.base()._detail()->getHandle());
		
		LOG_COMMAND(U"--Renderer2D commands--");
		
		for (auto[command, index] : m_commands.getList())
		{
			switch (command)
			{
			case RendererCommand::SetBuffers:
				{
					LOG_COMMAND(U"SetBuffers[{}]"_fmt(index));
					break;
				}
			case RendererCommand::UpdateBuffers:
				{
					batchInfo = m_batches.updateBuffers(index);
					
					LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
																																	  index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
					break;
				}
			case RendererCommand::Draw:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();
					
					const DrawCommand& draw = m_commands.getDraw(index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfo.startIndexLocation;
					const uint32 baseVertexLocation = batchInfo.baseVertexLocation;
					
					::glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (IndexType*)(nullptr) + startIndexLocation, baseVertexLocation);
					batchInfo.startIndexLocation += indexCount;
					
					++profile_drawcalls;
					profile_vertices += indexCount;
					
					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(index, indexCount, startIndexLocation));
					break;
				}
				case RendererCommand::ColorMul:
				{
					m_vsConstants2D->colorMul = m_commands.getColorMul(index);
					
					LOG_COMMAND(U"ColorMul[{}] {}"_fmt(index, m_vsConstants2D->colorMul));
					break;
				}
				case RendererCommand::ColorAdd:
				{
					m_psConstants2D->colorAdd = m_commands.getColorAdd(index);
					
					LOG_COMMAND(U"ColorAdd[{}] {}"_fmt(index, m_psConstants2D->colorAdd));
					break;
				}
				case RendererCommand::BlendState:
				{
					const auto& blendState = m_commands.getBlendState(index);
					pGraphics->getBlendState()->set(blendState);
					LOG_COMMAND(U"BlendState[{}]"_fmt(index));
					break;
				}
				case RendererCommand::RasterizerState:
				{
					const auto& rasterizerState = m_commands.getRasterizerState(index);
					pGraphics->getRasterizerState()->set(rasterizerState);
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(index));
					break;
				}
				case RendererCommand::PSSamplerState0:
				case RendererCommand::PSSamplerState1:
				case RendererCommand::PSSamplerState2:
				case RendererCommand::PSSamplerState3:
				case RendererCommand::PSSamplerState4:
				case RendererCommand::PSSamplerState5:
				case RendererCommand::PSSamplerState6:
				case RendererCommand::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command) - FromEnum(RendererCommand::PSSamplerState0);
					const auto& samplerState = m_commands.getPSSamplerState(slot, index);
					pGraphics->getSamplerState()->setPS(slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, index));
					break;
				}
				case RendererCommand::Transform:
				{
					transform = m_commands.getCombinedTransform(index);
					const Mat3x2 matrix = transform * screenMat;
					m_vsConstants2D->transform[0].set(matrix._11, -matrix._12, matrix._31, -matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, -matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Transform[{}] {}"_fmt(index, matrix));
					break;
				}
				case RendererCommand::SetPS:
				{
					const PixelShaderID& psID = m_commands.getPS(index);
					
					if (psID == PixelShaderID::InvalidValue())
					{
						;// [Siv3D ToDo] set null
					}
					else
					{
						m_pipeline.setPS(pShader->getPSProgram(psID));
						pShader->setPSSamplerUniform(psID);
					}
					
					LOG_COMMAND(U"SetPS[{}]"_fmt(index));
					break;
				}
				case RendererCommand::SetCB:
				{
					auto& cb = m_commands.getCB(index);
					const __m128* p = m_commands.getConstantsPtr(cb.offset);
					
					if (cb.num_vectors)
					{
						const uint32 uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(cb.stage, cb.slot);
						::glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBinding, cb.cbBase._detail()->getHandle());
						cb.cbBase._internal_update(p, cb.num_vectors * 16);
					}
					
					LOG_COMMAND(U"SetCB[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
																										index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
					break;
				}
				case RendererCommand::SetRT:
				{
					const auto& rt = m_commands.getRT(index);
					
					if (rt) // 通常と異なる RenderTexture
					{
						const GLuint frameBuffer = pTexture->getFrameBuffer(rt->id());
						pGraphics->getRenderTarget().setFrameBuffer(frameBuffer);
					}
					else // [BackBuffer]
					{
						pGraphics->getRenderTarget().bindSceneFrameBuffer();
					}
					
					LOG_COMMAND(U"SetRT[{}]"_fmt(index));
					break;
				}
				case RendererCommand::ScissorRect:
				{
					const auto& r = m_commands.getScissorRect(index);
					::glScissor(r.x, r.y, r.w, r.h);
					LOG_COMMAND(U"ScissorRect[{}] {}"_fmt(index, r));
					break;
				}
				case RendererCommand::Viewport:
				{
					const auto& viewport = m_commands.getViewport(index);
					
					Rect rect;
					
					if (viewport)
					{
						rect = viewport.value();
					}
					else
					{
						rect.x = 0;
						rect.y = 0;
						rect.w = static_cast<float>(currentRenderTargetSize.x);
						rect.h = static_cast<float>(currentRenderTargetSize.y);
					}
					
					::glViewport(rect.x, rect.y, rect.w, rect.h);
					
					screenMat = Mat3x2::Screen(rect.w, rect.h);
					const Mat3x2 matrix = transform * screenMat;
					m_vsConstants2D->transform[0].set(matrix._11, -matrix._12, matrix._31, -matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, -matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Viewport[{}] (TopLeftX = {}, TopLeftY = {}, Width = {}, Height = {})"_fmt(index,
																																		  rect.x, rect.y, rect.w, rect.h));
					break;
				}
				case RendererCommand::PSTexture0:
				case RendererCommand::PSTexture1:
				case RendererCommand::PSTexture2:
				case RendererCommand::PSTexture3:
				case RendererCommand::PSTexture4:
				case RendererCommand::PSTexture5:
				case RendererCommand::PSTexture6:
				case RendererCommand::PSTexture7:
				{
					const uint32 slot = FromEnum(command) - FromEnum(RendererCommand::PSTexture0);
					const auto& textureID = m_commands.getPSTexture(slot, index);

					if (textureID == TextureID::InvalidValue())
					{
						::glActiveTexture(GL_TEXTURE0 + slot);
						::glBindTexture(GL_TEXTURE_2D, 0);
					}
					else
					{
						::glActiveTexture(GL_TEXTURE0 + slot);
						::glBindTexture(GL_TEXTURE_2D, pTexture->getTexture(textureID));
					}

					LOG_COMMAND(U"PSTexture{}[{}] "_fmt(slot, index));
					break;
				}
				case RendererCommand::SDFParam:
				{
					m_psConstants2D->sdfParam = m_commands.getSdfParam(index);
					
					LOG_COMMAND(U"SDFParam[{}] {}"_fmt(index, m_psConstants2D->sdfParam));
					break;
				}
				case RendererCommand::InternalPSConstants:
				{
					m_psConstants2D->internalParam = m_commands.getInternalPSConstants(index);

					LOG_COMMAND(U"InternalPSConstants[{}] {}"_fmt(index, m_psConstants2D->internalParam));
					break;
				}
				default:
				{
					LOG_COMMAND(U"???[{}] "_fmt(index));
				}
			}
		}
		
		::glBindVertexArray(0);
		
		LOG_COMMAND(U"--({} commands)--"_fmt(m_commands.getList().size()));
		
		Siv3DEngine::Get<ISiv3DProfiler>()->reportDrawcalls(profile_drawcalls, profile_vertices / 3);

		//CheckError(U"F300");
	}

	std::pair<float, FloatRect> CRenderer2D_GL::getLetterboxingTransform() const
	{
		const Float2 sceneSize = Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize();
		const Float2 backBufferSize = Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize();
		
		const float sx = backBufferSize.x / sceneSize.x;
		const float sy = backBufferSize.y / sceneSize.y;
		const float s = std::min(sx, sy);
		
		if (sx <= sy)
		{
			const float offsetY = (backBufferSize.y - sceneSize.y * s) * 0.5f;
			return{ s, FloatRect(0.0f, offsetY,
								 static_cast<float>(backBufferSize.x),
								 static_cast<float>(backBufferSize.y - offsetY * 2.0f)) };
		}
		else
		{
			const float offsetX = (backBufferSize.x - sceneSize.x * s) * 0.5f;
			return{ s, FloatRect(offsetX, 0.0f,
								 static_cast<float>(backBufferSize.x - offsetX * 2.0f),
								 static_cast<float>(backBufferSize.y)) };
		}
	}

	void CRenderer2D_GL::setColorMul(const Float4& color)
	{
		m_commands.pushColorMul(color);
	}

	ColorF CRenderer2D_GL::getColorMul() const
	{
		return ColorF(m_commands.getCurrentColorMul());
	}

	void CRenderer2D_GL::setColorAdd(const Float4& color)
	{
		m_commands.pushColorAdd(color);
	}

	ColorF CRenderer2D_GL::getColorAdd() const
	{
		return ColorF(m_commands.getCurrentColorAdd());
	}

	void CRenderer2D_GL::setBlendState(const BlendState& state)
	{
		m_commands.pushBlendState(state);
	}

	BlendState CRenderer2D_GL::getBlendState() const
	{
		return m_commands.getCurrentBlendState();
	}

	void CRenderer2D_GL::setRasterizerState(const RasterizerState& state)
	{
		m_commands.pushRasterizerState(state);
	}

	RasterizerState CRenderer2D_GL::getRasterizerState() const
	{
		return m_commands.getCurrentRasterizerState();
	}

	void CRenderer2D_GL::setPSSamplerState(const uint32 slot, const SamplerState& state)
	{
		m_commands.pushPSSamplerState(state, slot);
	}

	SamplerState CRenderer2D_GL::getPSSamplerState(const uint32 slot) const
	{
		return m_commands.getPSCurrentSamplerState(slot);
	}

	void CRenderer2D_GL::setLocalTransform(const Mat3x2& matrix)
	{
		m_commands.pushLocalTransform(matrix);
	}

	const Mat3x2& CRenderer2D_GL::getLocalTransform() const
	{
		return m_commands.getCurrentLocalTransform();
	}

	void CRenderer2D_GL::setCameraTransform(const Mat3x2& matrix)
	{
		m_commands.pushCameraTransform(matrix);
	}

	const Mat3x2& CRenderer2D_GL::getCameraTransform() const
	{
		return m_commands.getCurrentCameraTransform();
	}

	float CRenderer2D_GL::getMaxScaling() const
	{
		return m_commands.getCurrentMaxScaling();
	}

	void CRenderer2D_GL::setScissorRect(const Rect& rect)
	{
		m_commands.pushScissorRect(rect);
	}

	Rect CRenderer2D_GL::getScissorRect() const
	{
		return m_commands.getCurrentScissorRect();
	}

	void CRenderer2D_GL::setViewport(const Optional<Rect>& viewport)
	{
		m_commands.pushViewport(viewport);
	}

	Optional<Rect> CRenderer2D_GL::getViewport() const
	{
		return m_commands.getCurrentViewport();
	}

	void CRenderer2D_GL::setSDFParameters(const Float4& parameters)
	{
		m_commands.pushSdfParam(parameters);
	}

	Float4 CRenderer2D_GL::getSDFParameters() const
	{
		return m_commands.getCurrentSdfParam();
	}
	
	void CRenderer2D_GL::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		if (texture)
		{
			m_commands.pushPSTexture(slot, texture.value());
		}
		else
		{
			m_commands.pushPSTextureUnbound(slot);
		}
	}
	
	void CRenderer2D_GL::setCustomPS(const Optional<PixelShader>& ps)
	{
		if (ps && !ps->isEmpty())
		{
			m_currentCustomPS = ps.value();
			m_commands.pushCustomPS(ps.value());
		}
		else
		{
			m_currentCustomPS.reset();
		}
	}
	
	Optional<PixelShader> CRenderer2D_GL::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer2D_GL::setConstant(const ShaderStage stage, const uint32 slot, const s3d::detail::ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		m_commands.pushCB(stage, slot, buffer, data, num_vectors);
	}
	
	void CRenderer2D_GL::setInternalConstantBufferValue(const ShaderStage stage, const Float4& value)
	{
		if (stage == ShaderStage::Vertex)
		{
			// [Siv3D ToDo] v0.4.1 では未実装
		}
		else if (stage == ShaderStage::Pixel)
		{
			m_commands.pushInternalPSConstants(value);
		}
	}
	
	void CRenderer2D_GL::setRT(const Optional<RenderTexture>& rt)
	{
		if (rt)
		{
			bool hasChanged = false;
			
			const TextureID textureID = rt->id();
			const auto& currentPSTextures = m_commands.getCurrentPSTextures();
			
			for (uint32 slot = 0; slot < currentPSTextures.size(); ++slot)
			{
				if (currentPSTextures[slot] == textureID)
				{
					m_commands.pushPSTexture(slot, Texture());
					hasChanged = true;
				}
			}
			
			if (hasChanged)
			{
				m_commands.flush();
			}
		}
		
		m_commands.pushRT(rt);
	}
	
	Optional<RenderTexture> CRenderer2D_GL::getRT() const
	{
		return m_commands.getCurrentRT();
	}
	
	void CRenderer2D_GL::addLine(const LineStyle& style, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
	{
		if (style.isSquareCap())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildSquareCappedLine(m_bufferCreator, begin, end, thickness, colors))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isRoundCap())
		{
			float startAngle = 0.0f;
			
			if (const uint16 indexCount = Vertex2DBuilder::BuildRoundCappedLine(m_bufferCreator, begin, end, thickness, colors, startAngle))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
				
				const float thicknessHalf = thickness * 0.5f;
				addCirclePie(begin, thicknessHalf, startAngle, Pi_v<float>, colors[0]);
				addCirclePie(end, thicknessHalf, startAngle + Pi_v<float>, Pi_v<float>, colors[1]);
			}
		}
		else if (style.isNoCap())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildUncappedLine(m_bufferCreator, begin, end, thickness, colors))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isSquareDot())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildSquareDotLine(m_bufferCreator, begin, end, thickness, colors, static_cast<float>(style.dotOffset), getMaxScaling()))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->square_dotID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isRoundDot())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildRoundDotLine(m_bufferCreator, begin, end, thickness, colors, static_cast<float>(style.dotOffset), style.hasAlignedDot))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->round_dotID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTriangle(m_bufferCreator, pts, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4(&colors)[3])
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTriangle(m_bufferCreator, pts, colors))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, colors))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addRectFrame(const FloatRect& rect, const float thickness, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRectFrame(m_bufferCreator, rect, thickness, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addCircle(const Float2& center, const float r, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildCircle(m_bufferCreator, center, r, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addCircleFrame(const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildCircleFrame(m_bufferCreator, center, rInner, thickness, innerColor, outerColor, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addCirclePie(const Float2& center, const float r, const float startAngle, const float angle, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildCirclePie(m_bufferCreator, center, r, startAngle, angle, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addCircleArc(const Float2& center, const float rInner, const float startAngle, float angle, const float thickness, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildCircleArc(m_bufferCreator, center, rInner, startAngle, angle, thickness, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addEllipse(const Float2& center, const float a, const float b, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildEllipse(m_bufferCreator, center, a, b, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addEllipseFrame(const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildEllipseFrame(m_bufferCreator, center, aInner, bInner, thickness, innerColor, outerColor, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildQuad(m_bufferCreator, quad, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildQuad(m_bufferCreator, quad, colors))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addRoundRect(const FloatRect& rect, const float w, const float h, const float r, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRoundRect(m_bufferCreator, rect, w, h, r, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addLineString(const LineStyle& style, const Vec2* pts, const uint16 size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const bool isClosed)
	{
		if (style.isSquareCap() || (style.isRoundCap() && isClosed))
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildSquareCappedLineString(m_bufferCreator, pts, size, offset, thickness, inner, color, isClosed, getMaxScaling()))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isRoundCap())
		{
			float startAngle = 0.0f, endAngle = 0.0f;
			
			if (const uint16 indexCount = Vertex2DBuilder::BuildRoundCappedLineString(m_bufferCreator, pts, size, offset, thickness, inner, color, getMaxScaling(), startAngle, endAngle))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
				
				const float thicknessHalf = thickness * 0.5f;
				addCirclePie(*pts, thicknessHalf, startAngle, Pi_v<float>, color);
				addCirclePie(*(pts + size - 1), thicknessHalf, endAngle, Pi_v<float>, color);
			}
		}
		else if (style.isNoCap())
		{
			float startAngle = 0.0f, endAngle = 0.0f;
			
			if (const uint16 indexCount = Vertex2DBuilder::BuildRoundCappedLineString(m_bufferCreator, pts, size, offset, thickness, inner, color, getMaxScaling(), startAngle, endAngle))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->shapeID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isSquareDot())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildDotLineString(m_bufferCreator, pts, size, offset, thickness, color, isClosed, true, static_cast<float>(style.dotOffset), false, getMaxScaling()))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->square_dotID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
		else if (style.isRoundDot())
		{
			if (const uint16 indexCount = Vertex2DBuilder::BuildDotLineString(m_bufferCreator, pts, size, offset, thickness, color, isClosed, false, static_cast<float>(style.dotOffset), style.hasAlignedDot, getMaxScaling()))
			{
				if (!m_currentCustomPS)
				{
					m_commands.pushStandardPS(m_standardPS->round_dotID);
				}
				m_commands.pushDraw(indexCount);
			}
		}
	}

	void CRenderer2D_GL::addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color)
	{
		if (const uint16 count = Vertex2DBuilder::BuildShape2D(m_bufferCreator, vertices, indices, offset, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(count);
		}
	}

	void CRenderer2D_GL::addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, const float s, const float c, const Float2& offset, const Float4& color)
	{
		if (const uint16 count = Vertex2DBuilder::BuildShape2DTransformed(m_bufferCreator, vertices, indices, s, c, offset, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(count);
		}
	}

	void CRenderer2D_GL::addShape2DFrame(const Float2* pts, const uint16 size, const float thickness, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildShape2DFrame(m_bufferCreator, pts, size, thickness, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addSprite(const Sprite& sprite, const uint16 startIndex, const uint16 indexCount)
	{
		if (const uint16 count = Vertex2DBuilder::BuildSprite(m_bufferCreator, sprite, startIndex, indexCount))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(m_standardPS->shapeID);
			}
			m_commands.pushDraw(count);
		}
	}

	void CRenderer2D_GL::addSprite(const Texture& texture, const Sprite& sprite, const uint16 startIndex, const uint16 indexCount)
	{
		if (const uint16 count = Vertex2DBuilder::BuildSprite(m_bufferCreator, sprite, startIndex, indexCount))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(count);
		}
	}

	void CRenderer2D_GL::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTextureRegion(m_bufferCreator, rect, uv, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTextureRegion(m_bufferCreator, rect, uv, colors))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTexturedCircle(m_bufferCreator, circle, uv, color, getMaxScaling()))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTexturedQuad(m_bufferCreator, quad, uv, color))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(indexCount);
		}
	}

	void CRenderer2D_GL::addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
		ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
		ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildTexturedParticles(m_bufferCreator, particles, sizeOverLifeTimeFunc, colorOverLifeTimeFunc))
		{
			if (!m_currentCustomPS)
			{
				m_commands.pushStandardPS(texture.isSDF() ? m_standardPS->sdfID : m_standardPS->textureID);
			}
			m_commands.pushPSTexture(0, texture);
			m_commands.pushDraw(indexCount);
		}
	}

	const Texture& CRenderer2D_GL::getBoxShadowTexture() const
	{
		return *m_boxShadowTexture;
	}
}
