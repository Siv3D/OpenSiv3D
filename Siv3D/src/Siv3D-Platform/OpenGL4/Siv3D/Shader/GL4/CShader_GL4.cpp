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

# include "CShader_GL4.hpp"
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/ConstantBuffer/GL4/ConstantBufferDetail_GL4.hpp>

namespace s3d
{
	CShader_GL4::CShader_GL4()
	{
		// do nothing
	}

	CShader_GL4::~CShader_GL4()
	{
		LOG_SCOPED_TRACE(U"CShader_GL4::~CShader_GL4()");

		if (m_pipeline)
		{
			::glDeleteProgramPipelines(1, &m_pipeline);
			m_pipeline = 0;
		}

		// エンジン PS を破棄
		m_enginePSs.clear();

		// エンジン VS を破棄
		m_engineVSs.clear();

		// PS の管理を破棄
		m_pixelShaders.destroy();

		// VS の管理を破棄
		m_vertexShaders.destroy();
	}

	void CShader_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CShader_GL4::init()");

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<GL4VertexShader>(GL4VertexShader::Null{});

			if (not nullVertexShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null VertexShader initialization failed" };
			}

			// 管理に登録
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		// null PS を管理に登録
		{
			// null PS を作成
			auto nullPixelShader = std::make_unique<GL4PixelShader>(GL4PixelShader::Null{});

			if (not nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null PixelShader initialization failed" };
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		// エンジン VS をロード
		{
			m_engineVSs << GLSL{ Resource(U"engine/shader/glsl/quad_warp.vert"), {{ U"VSConstants2D", 0 }, { U"VSQuadWarp", 1 }} };

			if (not m_engineVSs.all([](const auto& vs) { return !!vs; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError{ U"CShader_GL4::m_engineVSs initialization failed" };
			}
		}

		// エンジン PS をロード
		{
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/copy.frag"), {} };
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/gaussian_blur_5.frag"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/gaussian_blur_9.frag"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/gaussian_blur_13.frag"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/apply_srgb_curve.frag"), {} };
			m_enginePSs << GLSL{ Resource(U"engine/shader/glsl/quad_warp.frag"), {{ U"PSConstants2D", 0 }, { U"PSQuadWarp", 1 }} };

			if (not m_enginePSs.all([](const auto& ps) { return !!ps; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError{ U"CShader_GL4::m_enginePSs initialization failed" };
			}
		}

		::glGenProgramPipelines(1, &m_pipeline);

		if (not m_pipeline)
		{
			throw EngineError{ U"glGenProgramPipelines() failed" };
		}
	}

	VertexShader::IDType CShader_GL4::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader{ path };

		if (not reader)
		{
			return VertexShader::IDType::NullAsset();
		}

		return createVSFromSource(reader.readAll(), entryPoint, bindings);
	}

	VertexShader::IDType CShader_GL4::createVSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// VS を作成
		auto vertexShader = std::make_unique<GL4VertexShader>(source, bindings);

		if (not vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShader::IDType::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	PixelShader::IDType CShader_GL4::createPSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader{ path };

		if (not reader)
		{
			return PixelShader::IDType::NullAsset();
		}

		return createPSFromSource(reader.readAll(), entryPoint, bindings);
	}

	PixelShader::IDType CShader_GL4::createPSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// PS を作成
		auto pixelShader = std::make_unique<GL4PixelShader>(source, bindings);

		if (not pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShader::IDType::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	void CShader_GL4::releaseVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_GL4::releasePS(const PixelShader::IDType handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}

	void CShader_GL4::setVS(const VertexShader::IDType handleID)
	{
		const auto& vertexShader = m_vertexShaders[handleID];

		const GLuint vsProgram = vertexShader->getProgram();
		::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vsProgram);

		vertexShader->setVSSamplerUniform();
	}

	void CShader_GL4::setPS(const PixelShader::IDType handleID)
	{
		const auto& pixelShader = m_pixelShaders[handleID];

		const GLuint psProgram = pixelShader->getProgram();
		::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, psProgram);

		pixelShader->setPSSamplerUniform();
	}

	const Blob& CShader_GL4::getBinaryVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBinary();
	}

	const Blob& CShader_GL4::getBinaryPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBinary();
	}

	void CShader_GL4::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 vsUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, static_cast<const ConstantBufferDetail_GL4*>(cb._detail())->getHandle());
	}

	void CShader_GL4::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 psUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, psUniformBlockBinding, static_cast<const ConstantBufferDetail_GL4*>(cb._detail())->getHandle());
	}

	const VertexShader& CShader_GL4::getEngineVS(const EngineVS vs) const
	{
		return m_engineVSs[FromEnum(vs)];
	}

	const PixelShader& CShader_GL4::getEnginePS(const EnginePS ps) const
	{
		return m_enginePSs[FromEnum(ps)];
	}

	void CShader_GL4::setQuadWarpCB(const VS2DQuadWarp& vsCB, const PS2DQuadWarp& psCB)
	{
		m_engineShaderCBs.vs2DQuadWarp = vsCB;
		m_engineShaderCBs.ps2DQuadWarp = psCB;

		Graphics2D::SetVSConstantBuffer(1, m_engineShaderCBs.vs2DQuadWarp);
		Graphics2D::SetPSConstantBuffer(1, m_engineShaderCBs.ps2DQuadWarp);
	}

	void CShader_GL4::usePipeline()
	{
		::glUseProgram(0);
		::glBindProgramPipeline(m_pipeline);
	}
}
