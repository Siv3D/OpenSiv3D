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

# include "CRenderer2D_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/ConstantBuffer/GL4/ConstantBufferDetail_GL4.hpp>

/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer2D_GL4::CRenderer2D_GL4() = default;

	CRenderer2D_GL4::~CRenderer2D_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::~CRenderer2D_GL4()");

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////

		if (m_sampler)
		{
			::glDeleteSamplers(1, &m_sampler);
			m_sampler = 0;
		}

		if (m_vertexArray)
		{
			::glDeleteVertexArrays(1, &m_vertexArray);
			m_vertexArray = 0;
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::init()");

		pRenderer = dynamic_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer));
		pShader = dynamic_cast<CShader_GL4*>(SIV3D_ENGINE(Shader));

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer2D_GL4:");
			m_standardVS = std::make_unique<GL4StandardVS2D>();
			m_standardVS->sprite = GLSL(Resource(U"engine/shader/glsl/sprite.vert"), { { U"VSConstants2D", 0 } });
			m_standardVS->fullscreen_triangle = GLSL(Resource(U"engine/shader/glsl/fullscreen_triangle.vert"), {});
			if (not m_standardVS->ok())
			{
				throw EngineError(U"CRenderer2D_GL4::m_standardVS initialization failed");
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer2D_GL4:");
			m_standardPS = std::make_unique<GL4StandardPS2D>();
			m_standardPS->shape = GLSL(Resource(U"engine/shader/glsl/shape.frag"), { { U"PSConstants2D", 0 } });
			m_standardPS->fullscreen_triangle = GLSL(Resource(U"engine/shader/glsl/fullscreen_triangle.frag"), {});
			if (not m_standardPS->ok())
			{
				throw EngineError(U"CRenderer2D_GL4::m_standardPS initialization failed");
			}
		}

		// Batch 管理を初期化
		{
			if (not m_batches.init())
			{
				throw EngineError(U"GL4Vertex2DBatch::init() failed");
			}
		}

		// バッファ作成関数を作成
		m_bufferCreator = [this](Vertex2D::IndexType vertexSize, Vertex2D::IndexType indexSize)
		{
			return m_batches.requestBuffer(vertexSize, indexSize, m_commandManager);
		};

		// full screen triangle
		{
			::glGenVertexArrays(1, &m_vertexArray);
			::glBindVertexArray(m_vertexArray);

			::glGenSamplers(1, &m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_batches.reset();
			m_commandManager.reset();
		};

		m_commandManager.flush();

		pShader->setVS(m_standardVS->sprite.id());
		pShader->setPS(m_standardPS->shape.id());
		pShader->usePipeline();

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		::glViewport(0, 0, currentRenderTargetSize.x, currentRenderTargetSize.y);

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = (transform * screenMat);

		m_vsConstants2D->transform[0] = Float4(matrix._11, -matrix._12, matrix._31, -matrix._32);
		m_vsConstants2D->transform[1] = Float4(matrix._21, -matrix._22, 0.0f, 1.0f);
		m_vsConstants2D->colorMul = Float4(1, 1, 1, 1);

		pShader->setConstantBufferVS(0, m_vsConstants2D.base());
		pShader->setConstantBufferPS(0, m_psConstants2D.base());

		GL4BatchInfo batchInfo;

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case GL4Renderer2DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case GL4Renderer2DCommandType::SetBuffers:
				{
					// do nothing

					LOG_COMMAND(U"SetBuffers[{}]"_fmt(command.index));
					break;
				}
			case GL4Renderer2DCommandType::UpdateBuffers:
				{
					batchInfo = m_batches.updateBuffers(command.index);

					LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
					break;
				}
			case GL4Renderer2DCommandType::Draw:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					const GL4DrawCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfo.startIndexLocation;
					const uint32 baseVertexLocation = batchInfo.baseVertexLocation;
					constexpr Vertex2D::IndexType* pBase = 0;

					::glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (pBase + startIndexLocation), baseVertexLocation);
					batchInfo.startIndexLocation += indexCount;

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			}
		}

		::glBindVertexArray(0);

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::addRect(const FloatRect& rect, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, color))
		{
			//if (!m_currentCustomPS)
			//{
			//	m_commandManager.pushStandardPS(m_standardPS->shapeID);
			//}

			m_commandManager.pushDraw(indexCount);
		}
	}

	/*
	void CRenderer2D_GL4::test_renderRectangle(const RectF& rect, const ColorF& _color)
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
	*/

	void CRenderer2D_GL4::drawFullScreenTriangle(const TextureFilter textureFilter)
	{
		// view port
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			auto [s, viewRect] = pRenderer->getLetterboxComposition();
			::glViewport(
				static_cast<int32>(viewRect.x),
				static_cast<int32>(viewRect.y),
				static_cast<int32>(viewRect.w),
				static_cast<int32>(viewRect.h));
		}

		// render states
		{
			const bool linearFilter = (textureFilter == TextureFilter::Linear);
			::glBindSampler(0, m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
		}

		pShader->setVS(m_standardVS->fullscreen_triangle.id());
		pShader->setPS(m_standardPS->fullscreen_triangle.id());
		pShader->usePipeline();
		{
			::glBindVertexArray(m_vertexArray);
			{
				::glBindBuffer(GL_ARRAY_BUFFER, 0);
				::glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			::glBindVertexArray(0);
		}

		CheckOpenGLError();
	}
}
