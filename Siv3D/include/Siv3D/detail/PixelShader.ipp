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

# pragma once

namespace s3d
{
	inline PixelShader PixelShader::HLSL(const FilePathView path, const StringView entryPoint)
	{
		return PixelShader{ path, entryPoint, {} };
	}

	inline PixelShader PixelShader::GLSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return PixelShader{ path, {}, bindings };
	}

	inline PixelShader PixelShader::MSL(const StringView entryPoint, const FilePathView path)
	{
		return PixelShader{ path, entryPoint, {} };
	}

	inline PixelShader PixelShader::ESSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return PixelShader{ path, {}, bindings };
	}
}
