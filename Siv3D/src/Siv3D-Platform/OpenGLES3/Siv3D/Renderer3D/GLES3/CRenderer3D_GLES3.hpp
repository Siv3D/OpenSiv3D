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
	class CRenderer_GLES3;
	class CShader_GLES3;
	class CTexture_GLES3;

	class CRenderer3D_GLES3 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_GLES3();

		~CRenderer3D_GLES3() override;

		void init() override;

	private:

		CRenderer_GLES3* pRenderer = nullptr;
		CShader_GLES3* pShader = nullptr;
		CTexture_GLES3* pTexture = nullptr;
	};
}
