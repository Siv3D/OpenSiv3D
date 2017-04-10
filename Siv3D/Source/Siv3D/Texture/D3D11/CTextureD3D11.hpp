//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <d3d11.h>
# include "../ITexture.hpp"

namespace s3d
{
	class CTextureD3D11 : public ISiv3DTexture
	{
	private:

		ID3D11Device* m_device = nullptr;

	public:

		bool init(ID3D11Device* device, IDXGISwapChain* swapChain);

		void release(Texture::IDType handleID) override;
	};
}

# endif
