//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "ConstantBuffer/WebGPU/ConstantBufferDetail_WebGPU.hpp"
# include "Mesh/WebGPU/CMesh_WebGPU.hpp"
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>
# include "Renderer2D/WebGPU/CRenderer2D_WebGPU.hpp"
# include "Renderer3D/WebGPU/CRenderer3D_WebGPU.hpp"
# include "Shader/WebGPU/CShader_WebGPU.hpp"
# include "Texture/WebGPU/CTexture_WebGPU.hpp"

namespace s3d
{
    __attribute__((weak))
    ConstantBufferDetail_WebGPU::ConstantBufferDetail_WebGPU(size_t)
    {
		// do nothing
    }

	__attribute__((weak))
	CMesh_WebGPU::CMesh_WebGPU()
	{
		// do nothing
	}

	__attribute__((weak))
	CRenderer_WebGPU::CRenderer_WebGPU()
	{
		// do nothing
	}

	__attribute__((weak))
	CRenderer2D_WebGPU::CRenderer2D_WebGPU()
	{
		// do nothing
	}

	__attribute__((weak))
	CRenderer3D_WebGPU::CRenderer3D_WebGPU()
	{
		// do nothing
	}

	__attribute__((weak))
    CShader_WebGPU::CShader_WebGPU()
	{
		// do nothing
	}

	__attribute__((weak))
    CTexture_WebGPU::CTexture_WebGPU()
	{
		// do nothing
	}
}
