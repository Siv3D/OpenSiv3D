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
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "D3D11Texture2DDesc.hpp"

namespace s3d
{
	class D3D11Texture
	{
	public:

		struct Dynamic {};
		struct Render {};
		struct MSRender {};

		SIV3D_NODISCARD_CXX20
		D3D11Texture(ID3D11Device* device, const Image& image, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		D3D11Texture(ID3D11Device* device, const Image& image, const Array<Image>& mips, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		D3D11Texture(Dynamic, ID3D11Device* device, const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc);

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		const D3D11Texture2DDesc& getDesc() const noexcept;

		[[nodiscard]]
		ID3D11ShaderResourceView** getSRVPtr();

		[[nodiscard]]
		ID3D11RenderTargetView* getRTV();

		// 動的テクスチャを指定した色で塗りつぶす
		bool fill(ID3D11DeviceContext* context, const ColorF& color, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const ColorF& color, const Rect& rect);

		bool fill(ID3D11DeviceContext* context, const void* src, uint32 stride, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const void* src, uint32 stride, const Rect& rect, bool wait);

	private:

		enum class TextureType
		{
			// 通常テクスチャ
			// [メインテクスチャ]<-[シェーダ・リソース・ビュー]
			Default,

			// 動的テクスチャ
			// [メインテクスチャ]<-[シェーダ・リソース・ビュー], [ステージング・テクスチャ]
			Dynamic,

			// レンダーテクスチャ
			// [メインテクスチャ]<-[レンダー・ターゲット・ビュー]<-[シェーダ・リソース・ビュー]
			Render,

			// マルチサンプル・レンダーテクスチャ
			// [マルチサンプル・テクスチャ]<-[レンダー・ターゲット・ビュー], [メインテクスチャ]<-[シェーダ・リソース・ビュー]
			MSRender,
		};

		// [メインテクスチャ]
		ComPtr<ID3D11Texture2D> m_texture;

		// [マルチサンプル・テクスチャ]
		ComPtr<ID3D11Texture2D> m_multiSampledTexture;

		// [ステージング・テクスチャ]
		ComPtr<ID3D11Texture2D> m_stagingTexture;

		// [レンダー・ターゲット・ビュー]
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		// [シェーダ・リソース・ビュー]
		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		D3D11Texture2DDesc m_desc;

		TextureType m_type = TextureType::Default;

		bool m_initialized = false;
	};
}
