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

# include <Siv3D/Windows.hpp>
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

		AssetHandleManager<TextureID, Texture_D3D11> m_textures{ U"Texture" };

	public:

		~CTexture_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain);

		TextureID createFromBackBuffer() override;

		TextureID create(const Image& image, TextureDesc desc) override;

		TextureID create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) override;

		TextureID createRT(const Size& size, uint32 multisampleCount) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;

		void clearRT(TextureID handleID, const ColorF& color) override;

		void beginResize(TextureID handleID) override;

		bool endResizeRT(TextureID handleID, const Size& size, uint32 multisampleCount) override;

		bool endResizeBackBuffer(TextureID handleID) override;

		ID3D11Texture2D* getTexture(TextureID handleID);

		ID3D11RenderTargetView* getRTV(TextureID handleID);



		void setPS(uint32 slot, TextureID handleID) override;

		bool fill(TextureID handleID, const ColorF& color, bool wait) override;

		bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) override;
	};
}

# endif
