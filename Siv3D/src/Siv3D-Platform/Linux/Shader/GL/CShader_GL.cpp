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

		m_pixelShaders.destroy();
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
		
		LOG_INFO(U"ℹ️ CShader_GL initialized");
		
		return true;
	}
	
	VertexShaderID CShader_GL::createVS(ByteArray&& binary)
	{
		// [Siv3D ToDo]
		return VertexShaderID::NullAsset();
	}
	
	VertexShaderID CShader_GL::createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		// [Siv3D ToDo]
		return VertexShaderID::NullAsset();
	}
	
	//VertexShaderID createVSFromSource(const String&, const Array<BindingPoint>&) override
	
	PixelShaderID CShader_GL::createPS(ByteArray&& binary)
	{
		// [Siv3D ToDo]
		return PixelShaderID::NullAsset();
	}

	PixelShaderID CShader_GL::createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		// [Siv3D ToDo]
		return PixelShaderID::NullAsset();
	}
	
	//PixelShaderID createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;
	
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
	
	void CShader_GL::setVS(const VertexShaderID handleID)
	{
		
	}
	
	void CShader_GL::setPS(const PixelShaderID handleID)
	{
		
	}
}
