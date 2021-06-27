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
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CRenderer_WebGPU;
	class CShader_WebGPU;
	class CTexture_WebGPU;

	class CRenderer3D_WebGPU final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_WebGPU();

		~CRenderer3D_WebGPU() override;

		void init() override;

	private:

		CRenderer_WebGPU* pRenderer = nullptr;
		CShader_WebGPU* pShader = nullptr;
		CTexture_WebGPU* pTexture = nullptr;
	};
}
