//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline VertexShader VertexShader::HLSL(const FilePathView path, const StringView entryPoint)
	{
		return VertexShader{ path, entryPoint, {} };
	}

	inline VertexShader VertexShader::GLSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return VertexShader{ path, {}, bindings };
	}

	inline VertexShader VertexShader::MSL(const StringView entryPoint, const FilePathView path)
	{
		return VertexShader{ path, entryPoint, {} };
	}

	inline VertexShader VertexShader::ESSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return VertexShader{ path, {}, bindings };
	}
}
