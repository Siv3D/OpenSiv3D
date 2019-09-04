//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>
# include "Texture2DDesc_D3D11.hpp"

namespace s3d
{
	class Texture_D3D11
	{
	private:

		// [メインテクスチャ]
		ComPtr<ID3D11Texture2D> m_texture;

		// [ステージング・テクスチャ]
		ComPtr<ID3D11Texture2D> m_textureStaging;

		// [シェーダ・リソース・ビュー]
		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		// [レンダー・ターゲット・ビュー]
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		Texture2DDesc_D3D11 m_desc;

		bool m_initialized = false;

	public:

	//	struct Null {};
	//	struct BackBuffer {};
		struct Dynamic {};
		struct Render {};

	//	Texture_D3D11() = default;

	//	Texture_D3D11(Null, ID3D11Device* device);

	//	Texture_D3D11(BackBuffer, ID3D11Device* device, IDXGISwapChain* swapChain);

		Texture_D3D11(Dynamic, ID3D11Device* device, const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);

		Texture_D3D11(Render, ID3D11Device* device, const Size& size, TextureFormat format, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, const Array<Image>& mips, TextureDesc desc);

		bool isInitialized() const noexcept;

		const Texture2DDesc_D3D11& getDesc() const noexcept;

		

	//	ID3D11RenderTargetView* getRTV()
	//	{
	//		return m_renderTargetView.Get();
	//	}

		ID3D11ShaderResourceView** getSRVPtr();

		ID3D11Texture2D* getTexture();

	//	

	//	void beginResize();

	//	bool endResize(BackBuffer, ID3D11Device* device, IDXGISwapChain* swapChain);

	//	bool endResize(Render, ID3D11Device* device, const Size& size, uint32 multisampleCount);


		void clearRT(ID3D11DeviceContext* context, const ColorF& color);

		bool fill(ID3D11DeviceContext* context, const ColorF& color, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const ColorF& color, const Rect& rect);

		bool fill(ID3D11DeviceContext* context, const void* src, uint32 stride, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const void* src, uint32 stride, const Rect& rect, bool wait);
	};
}
