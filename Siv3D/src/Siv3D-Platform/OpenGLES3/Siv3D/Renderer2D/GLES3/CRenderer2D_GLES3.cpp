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

# include "CRenderer2D_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	CRenderer2D_GLES3::CRenderer2D_GLES3() = default;

	CRenderer2D_GLES3::~CRenderer2D_GLES3()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GLES3::~CRenderer2D_GLES3()");

		if (m_uniformBuffer)
		{
			::glDeleteBuffers(1, &m_uniformBuffer);
			m_uniformBuffer = 0;
		}

		if (m_program)
		{
			::glDeleteProgram(m_program);
			m_program = 0;
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GLES3::init()");

		{
			BinaryReader shader(Resource(U"engine/shader/glsl/test.vert"));

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size() + 1);
			shader.read(source.data(), shader.size());
			const char* pSource = source.data();
			m_vertexShader = ::glCreateShader(GL_VERTEX_SHADER);

			::glShaderSource(m_vertexShader, 1, &pSource, NULL);
			::glCompileShader(m_vertexShader);

			GLint status = GL_FALSE;
			::glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);

			GLint logLen = 0;
			::glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetShaderInfoLog(m_vertexShader, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
				throw EngineError();
			}

			if (status == GL_FALSE) // もしリンクに失敗していたら
			{
				::glDeleteShader(m_vertexShader);
				m_vertexShader = 0;
				throw EngineError();
			}
		}

		{
			BinaryReader shader(Resource(U"engine/shader/glsl/test.frag"));

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size() + 1);
			shader.read(source.data(), shader.size());
			const char* pSource = source.data();
			m_pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);

			::glShaderSource(m_pixelShader, 1, &pSource, NULL);
			::glCompileShader(m_pixelShader);

			GLint status = GL_FALSE;
			::glGetShaderiv(m_pixelShader, GL_COMPILE_STATUS, &status);

			GLint logLen = 0;
			::glGetShaderiv(m_pixelShader, GL_INFO_LOG_LENGTH, &logLen);

			// ログメッセージ
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetShaderInfoLog(m_pixelShader, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Pixel shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
				throw EngineError();
			}

			if (status == GL_FALSE) // もしリンクに失敗していたら
			{
				::glDeleteShader(m_pixelShader);
				m_pixelShader = 0;
				throw EngineError();
			}
		}

		{
			m_program = ::glCreateProgram();

			::glAttachShader(m_program, m_vertexShader);
			::glAttachShader(m_program, m_pixelShader);

			::glLinkProgram(m_program);

			::glDetachShader(m_program, m_vertexShader);
			::glDetachShader(m_program, m_pixelShader);

			::glDeleteShader(m_vertexShader);
			::glDeleteShader(m_pixelShader);

			m_vertexShader = 0;
			m_pixelShader = 0;
		}

		{
			const GLuint blockIndex = ::glGetUniformBlockIndex(m_program, "VSConstants2D");

			if (blockIndex == GL_INVALID_INDEX)
			{
				LOG_FAIL(U"Uniform block `VSConstants2D` not found");
			}

			::glUniformBlockBinding(m_program, blockIndex, 0);
		}

		::glGenBuffers(1, &m_uniformBuffer);

		// Batch 管理を初期化
		if (!m_batches.init())
		{
			throw EngineError(U"Vertex2DBatch_GLES3::init() failed");
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GLES3::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_batches.reset();
			m_draw_indexCount = 0;
		};

		::glUseProgram(m_program);

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneSize();

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = transform * screenMat;
		
		Float4 cb[3];
		//cb[0] = Float4(matrix._11, -matrix._12, matrix._31, -matrix._32);
		//cb[1] = Float4(matrix._21, -matrix._22, 0.0f, 1.0f);
		cb[0] = Float4(matrix._11, matrix._12, matrix._31, matrix._32);
		cb[1] = Float4(matrix._21, matrix._22, 0.0f, 1.0f);
		cb[2] = Float4(1, 1, 1, 1);

		{
			::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
			::glBufferData(GL_UNIFORM_BUFFER, sizeof(Float4) * 3, cb, GL_STATIC_DRAW);
			::glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		{
			const uint32 vsUniformBlockBinding = 0;
			::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, m_uniformBuffer);
		}

		auto batchInfo = m_batches.updateBuffers(0);

		const uint32 indexCount = m_draw_indexCount;
		const uint32 startIndexLocation = batchInfo.startIndexLocation;
		const uint32 baseVertexLocation = batchInfo.baseVertexLocation;
		const Vertex2D::IndexType* pBase = 0;
		
		// ::glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (pBase + startIndexLocation), baseVertexLocation);
		::glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (pBase + startIndexLocation));

		batchInfo.startIndexLocation += indexCount;

		::glBindVertexArray(0);

		CheckOpenGLError();
	}

	void CRenderer2D_GLES3::test_renderRectangle(const RectF& rect, const ColorF& _color)
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
}
