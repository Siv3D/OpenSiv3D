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

# include "CShader_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>

namespace s3d
{
	CShader_Metal::CShader_Metal()
	{

	}

	CShader_Metal::~CShader_Metal()
	{
		LOG_SCOPED_TRACE(U"CShader_Metal::~CShader_Metal()");

		m_pixelShaders.destroy();
		m_vertexShaders.destroy();
	}

	void CShader_Metal::init()
	{
		LOG_SCOPED_TRACE(U"CShader_Metal::init()");
		
		pRenderer = dynamic_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer));
		m_device = pRenderer->getDevice();
		
		m_defaultLibrary = [m_device newDefaultLibrary];

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<MetalVertexShader>(MetalVertexShader::Null{});

			if (!nullVertexShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null VertexShader initialization failed");
			}

			// 管理に登録
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		// null PS を管理に登録
		{
			// null PS を作成
			auto nullPixelShader = std::make_unique<MetalPixelShader>(MetalPixelShader::Null{});

			if (!nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null PixelShader initialization failed");
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}
	}

	VertexShader::IDType CShader_Metal::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>&)
	{
		// VS を作成
		auto vertexShader = std::make_unique<MetalVertexShader>(m_defaultLibrary, entryPoint);

		if (!vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShader::IDType::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	VertexShader::IDType CShader_Metal::createVSFromSource(const StringView source, const StringView entryPoint, const Array<ConstantBufferBinding>&)
	{
		// [Siv3D ToDo]
		return VertexShader::IDType::NullAsset();
	}

	PixelShader::IDType CShader_Metal::createPSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>&)
	{
		// PS を作成
		auto pixelShader = std::make_unique<MetalPixelShader>(m_defaultLibrary, entryPoint);

		if (!pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShader::IDType::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	PixelShader::IDType CShader_Metal::createPSFromSource(const StringView source, const StringView entryPoint, const Array<ConstantBufferBinding>&)
	{
		// [Siv3D ToDo]
		return PixelShader::IDType::NullAsset();
	}

	void CShader_Metal::releaseVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_Metal::releasePS(const PixelShader::IDType handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}
/*
	void CShader_GL4::setVS(const VertexShader::IDType handleID)
	{
		const GLuint vsProgram = m_vertexShaders[handleID]->getProgram();
		::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vsProgram);
	}

	void CShader_GL4::setPS(const PixelShader::IDType handleID)
	{
		const auto& pixelShader = m_pixelShaders[handleID];

		const GLuint psProgram = pixelShader->getProgram();
		::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, psProgram);

		pixelShader->setPSSamplerUniform();
	}
*/
	const Blob& CShader_Metal::getBinaryVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBinary();
	}

	const Blob& CShader_Metal::getBinaryPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBinary();
	}

	id<MTLFunction> CShader_Metal::getFunctionVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getFunction();
	}

	id<MTLFunction> CShader_Metal::getFunctionPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getFunction();
	}

/*
	void CShader_GL4::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 vsUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, dynamic_cast<const ConstantBufferDetail_GL4*>(cb._detail())->getHandle());
	}

	void CShader_GL4::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 psUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, psUniformBlockBinding, dynamic_cast<const ConstantBufferDetail_GL4*>(cb._detail())->getHandle());
	}

	void CShader_GL4::usePipeline()
	{
		::glUseProgram(0);
		::glBindProgramPipeline(m_pipeline);
	}
*/
}
