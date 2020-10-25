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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include "MetalVertexShader.hpp"

namespace s3d
{
	MetalVertexShader::MetalVertexShader(Null)
	{
		m_initialized = true;
	}

	MetalVertexShader::MetalVertexShader(id<MTLLibrary> library, const StringView name)
	{
		const std::string nameUTF8 = name.toUTF8();
		NSString* nameNS = [NSString stringWithUTF8String:nameUTF8.c_str()];
		m_vsFunction = [library newFunctionWithName:nameNS];
		
		if (m_vsFunction && m_vsFunction.functionType != MTLFunctionTypeVertex)
		{
			m_vsFunction = nil;
		}
		
		m_initialized = (m_vsFunction != nil);
	}

	MetalVertexShader::~MetalVertexShader()
	{

	}

	bool MetalVertexShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& MetalVertexShader::getBinary() const noexcept
	{
		return m_binary;
	}

	id<MTLFunction> MetalVertexShader::getFunction() const
	{
		return m_vsFunction;
	}
}
