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
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	class CRenderer_D3D11;
	class CShader_D3D11;
	class CTexture_D3D11;

	class CRenderer3D_D3D11 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_D3D11();

		~CRenderer3D_D3D11() override;

		void init() override;

	private:

		CRenderer_D3D11* pRenderer = nullptr;
		CShader_D3D11* pShader = nullptr;
		CTexture_D3D11* pTexture = nullptr;
		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;
	};
}
