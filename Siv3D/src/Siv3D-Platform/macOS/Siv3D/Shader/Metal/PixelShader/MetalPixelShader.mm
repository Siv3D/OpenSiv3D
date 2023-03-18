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
		
		if (not m_psFunction)
		{
			LOG_FAIL(U"MetalPixelShader::MetalPixelShader(): function `{}` not found"_fmt(name));
		}
		else if (m_psFunction.functionType != MTLFunctionTypeFragment)
		{
			m_psFunction = nil;
			LOG_FAIL(U"MetalPixelShader::MetalPixelShader(): function `{}` is not a pixel shader function"_fmt(name));
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
