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
# include <Siv3D/SamplerState.hpp>
# include "MetalPixelShader.hpp"

namespace s3d
{
	MetalPixelShader::MetalPixelShader(Null)
	{
		m_initialized = true;
	}

	MetalPixelShader::MetalPixelShader(id<MTLLibrary> library, const StringView name)
	{
		const std::string nameUTF8 = name.toUTF8();
		NSString* nameNS = [NSString stringWithUTF8String:nameUTF8.c_str()];
		m_psFunction = [library newFunctionWithName:nameNS];
		
		if (m_psFunction && m_psFunction.functionType != MTLFunctionTypeFragment)
		{
			m_psFunction = nil;
		}
		
		m_initialized = (m_psFunction != nil);
	}

	MetalPixelShader::~MetalPixelShader()
	{

	}

	bool MetalPixelShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& MetalPixelShader::getBinary() const noexcept
	{
		return m_binary;
	}

	id<MTLFunction> MetalPixelShader::getFunction() const
	{
		return m_psFunction;
	}
}
