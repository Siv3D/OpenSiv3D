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
//# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CRenderer_GL4;
	class CShader_GL4;
	class CTexture_GL4;

	class CRenderer3D_GL4 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_GL4();

		~CRenderer3D_GL4() override;

		void init() override;

	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;
		CTexture_GL4* pTexture = nullptr;
	};
}
