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

# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CShader_GL.hpp"

namespace s3d
{
	CShader_GL::CShader_GL()
	{

	}

	CShader_GL::~CShader_GL()
	{
		LOG_TRACE(U"CShader_GL::~CShader_GL()");
		
		// [エンジン PS] を破棄
		m_enginePSs.clear();

		// PS の管理を破棄
		m_pixelShaders.destroy();
	
		// VS の管理を破棄
		m_vertexShaders.destroy();
	}
	
	bool CShader_GL::init()
	{
		LOG_TRACE(U"CShader_GL::init()");
		
		{
			auto nullVertexShader = std::make_unique<VertexShader_GL>(VertexShader_GL::Null{});
			
			if (!nullVertexShader->isInitialized())
			{
				return false;
			}
			
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}
		
		{
			auto nullPixelShader = std::make_unique<PixelShader_GL>(PixelShader_GL::Null{});
			
			if (!nullPixelShader->isInitialized())
			{
				return false;
			}
			
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}
		
		// [エンジン PS] をロード
		{
			m_enginePSs << PixelShader(Resource(U"engine/shader/copy.frag"), {});
			m_enginePSs << PixelShader(Resource(U"engine/shader/gaussian_blur_9.frag"), {{ U"PSConstants2D", 0 }});
			
			if (!m_enginePSs.all([](const auto& ps) { return !!ps; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError(U"CShader_GL::m_enginePSs initialization failed");
			}
		}
		
		LOG_INFO(U"ℹ️ CShader_GL initialized");
		
		return true;
	}
	
	VertexShaderID CShader_GL::createVS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader(std::move(binary));
		
		if (!reader)
		{
			return VertexShaderID::NullAsset();
		}
		
		return createVSFromSource(reader.readAll(), bindings);
	}
	
	VertexShaderID CShader_GL::createVSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
	{
		LOG_TRACE(U"CShader_GL::createVSFromFile(path = \"{}\")"_fmt(path));
		
		TextReader reader(path);
		
		if (!reader)
		{
			return VertexShaderID::NullAsset();
		}
		
		return createVSFromSource(reader.readAll(), bindings);
	}
	
	VertexShaderID CShader_GL::createVSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings)
	{
		auto vertexShader = std::make_unique<VertexShader_GL>(source);
		
		if (!vertexShader->isInitialized())
		{
			return VertexShaderID::NullAsset();
		}
		
		vertexShader->setUniformBlockBindings(bindings);

		return m_vertexShaders.add(std::move(vertexShader));
	}
	
	PixelShaderID CShader_GL::createPS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader(std::move(binary));
		
		if (!reader)
		{
			return PixelShaderID::NullAsset();
		}
		
		return createPSFromSource(reader.readAll(), bindings);
	}

	PixelShaderID CShader_GL::createPSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
	{
		LOG_TRACE(U"CShader_GL::createPSFromFile(path = \"{}\")"_fmt(path));
		
		TextReader reader(path);
		
		if (!reader)
		{
			return PixelShaderID::NullAsset();
		}
		
		return createPSFromSource(reader.readAll(), bindings);
	}
	
	PixelShaderID CShader_GL::createPSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings)
	{
		auto pixelShader = std::make_unique<PixelShader_GL>(source);
		
		if (!pixelShader->isInitialized())
		{
			return PixelShaderID::NullAsset();
		}
		
		pixelShader->setUniformBlockBindings(bindings);

		return m_pixelShaders.add(std::move(pixelShader));
	}
	
	void CShader_GL::release(const VertexShaderID handleID)
	{
		m_vertexShaders.erase(handleID);
	}
	
	void CShader_GL::release(const PixelShaderID handleID)
	{
		m_pixelShaders.erase(handleID);
	}
	
	ByteArrayView CShader_GL::getBinaryView(const VertexShaderID handleID)
	{
		// [Siv3D ToDo]
		return ByteArrayView();
	}
	
	ByteArrayView CShader_GL::getBinaryView(const PixelShaderID handleID)
	{
		// [Siv3D ToDo]
		return ByteArrayView();
	}
	
	const PixelShader& CShader_GL::getEnginePS(const EnginePS ps) const
	{
		return m_enginePSs[FromEnum(ps)];
	}

	GLuint CShader_GL::getVSProgram(const VertexShaderID handleID)
	{
		return m_vertexShaders[handleID]->getProgram();
	}
	
	GLuint CShader_GL::getPSProgram(const PixelShaderID handleID)
	{
		return m_pixelShaders[handleID]->getProgram();
	}
	
	void CShader_GL::setPSSamplerUniform(const PixelShaderID handleID)
	{
		m_pixelShaders[handleID]->setPSSamplerUniform();
	}
}
