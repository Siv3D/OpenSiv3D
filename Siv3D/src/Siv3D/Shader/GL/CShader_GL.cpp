//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CShader_GL.hpp"
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Resource.hpp>

namespace s3d
{
	CShader_GL::CShader_GL()
	{

	}

	CShader_GL::~CShader_GL()
	{
		m_standardVSs.clear();
		
		m_standardPSs.clear();
		
		m_vertexShaders.destroy();
		
		m_pixelShaders.destroy();
	}

	bool CShader_GL::init()
	{		
		{
			const auto nullVertexShader = std::make_shared<VertexShader_GL>(VertexShader_GL::Null{});
			
			if (!nullVertexShader->isInitialized())
			{
				return false;
			}
			
			m_vertexShaders.setNullData(nullVertexShader);
		}
		
		{
			const auto nullPixelShader = std::make_shared<PixelShader_GL>(PixelShader_GL::Null{});
			
			if (!nullPixelShader->isInitialized())
			{
				return false;
			}
			
			m_pixelShaders.setNullData(nullPixelShader);
		}
		
		m_standardVSs.push_back(VertexShader(Resource(U"engine/shader/sprite.vert"), { { U"SpriteCB", 0 } }));
		m_standardPSs.push_back(PixelShader(Resource(U"engine/shader/shape.frag")));
		m_standardPSs.push_back(PixelShader(Resource(U"engine/shader/line_dot.frag")));
		m_standardPSs.push_back(PixelShader(Resource(U"engine/shader/line_round_dot.frag")));
		m_standardPSs.push_back(PixelShader(Resource(U"engine/shader/sprite.frag")));
		m_standardPSs.push_back(PixelShader(Resource(U"engine/shader/sprite_sdf.frag")));
		
		if (m_standardVSs.count_if(!Lambda::_) > 1)
		{
			LOG_FAIL(U"❌ CShader_GL: Failed to load standard vertex shaders");
			return false;
		}

		if (m_standardPSs.count_if(!Lambda::_) > 1)
		{
			LOG_FAIL(U"❌ CShader_GL: Failed to load standard pixel shaders");
			return false;
		}
		
		LOG_INFO(U"ℹ️ Shader initialized");
		
		return true;
	}
	
	VertexShaderID CShader_GL::createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		TextReader reader(path);
		
		if (!reader)
		{
			return VertexShaderID::NullAsset();
		}
		
		return createVSFromSource(reader.readAll(), bindingPoints);
	}
	
	VertexShaderID CShader_GL::createVSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	{
		const auto vertexShader = std::make_shared<VertexShader_GL>(source);
		
		if (!vertexShader->isInitialized())
		{
			return VertexShaderID::NullAsset();
		}
		
		for (const auto& bindingPoint : bindingPoints)
		{
			vertexShader->setUniformBlockBinding(bindingPoint.bufferName.narrow().c_str(), bindingPoint.index);
		}
		
		return m_vertexShaders.add(vertexShader);
	}
	
	PixelShaderID CShader_GL::createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		TextReader reader(path);
		
		if (!reader)
		{
			return PixelShaderID::NullAsset();
		}
		
		return createPSFromSource(reader.readAll(), bindingPoints);
	}
	
	PixelShaderID CShader_GL::createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	{
		const auto pixelShader = std::make_shared<PixelShader_GL>(source);
		
		if (!pixelShader->isInitialized())
		{
			return PixelShaderID::NullAsset();
		}
		
		for (const auto& bindingPoint : bindingPoints)
		{
			pixelShader->setUniformBlockBinding(bindingPoint.bufferName.narrow().c_str(), bindingPoint.index);
		}
		
		return m_pixelShaders.add(pixelShader);
	}
	
	void CShader_GL::releaseVS(const VertexShaderID handleID)
	{
		m_vertexShaders.erase(handleID);
	}
	
	void CShader_GL::releasePS(const PixelShaderID handleID)
	{
		m_pixelShaders.erase(handleID);
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

# endif
