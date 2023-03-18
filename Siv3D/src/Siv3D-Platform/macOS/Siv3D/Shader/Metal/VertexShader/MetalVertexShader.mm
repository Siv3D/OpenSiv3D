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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
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
		
		if (not m_vsFunction)
		{
			LOG_FAIL(U"MetalVertexShader::MetalVertexShader(): function `{}` not found"_fmt(name));
		}
		else if (m_vsFunction.functionType != MTLFunctionTypeVertex)
		{
			m_vsFunction = nil;
			LOG_FAIL(U"MetalVertexShader::MetalVertexShader(): function `{}` is not a vertex shader function"_fmt(name));
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
