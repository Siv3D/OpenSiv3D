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
# include "Texture_D3D11.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CTexture_D3D11 : public ISiv3DTexture
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGISwapChain* m_swapChain = nullptr;

		AssetHandleManager<Texture::IDType, std::shared_ptr<Texture_D3D11>> m_textures{ S3DSTR("Texture") };

	public:

		~CTexture_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain);

		Texture::IDType createFromBackBuffer() override;

		Texture::IDType create(const Image& image, TextureDesc desc) override;

		Texture::IDType create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc) override;

		Texture::IDType createRT(const Size& size, uint32 multisampleCount) override;

		void release(Texture::IDType handleID) override;

		Size getSize(Texture::IDType handleID) override;

		void clearRT(Texture::IDType handleID, const ColorF& color) override;

		void beginResize(Texture::IDType handleID) override;

		bool endResizeRT(Texture::IDType handleID, const Size& size, uint32 multisampleCount) override;

		bool endResizeBackBuffer(Texture::IDType handleID) override;

		ID3D11Texture2D* getTexture(Texture::IDType handleID);

		ID3D11RenderTargetView* getRTV(Texture::IDType handleID);



		void setPS(uint32 slot, Texture::IDType handleID) override;
	};
}

# endif
