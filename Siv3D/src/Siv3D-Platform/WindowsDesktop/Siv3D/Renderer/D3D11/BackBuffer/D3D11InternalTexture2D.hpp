//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ColorHSV.hpp>

namespace s3d
{
	class D3D11InternalTexture2D
	{
	private:

		ComPtr<ID3D11Texture2D> m_texture;

		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		Size m_size = Size{ 0, 0 };

		DXGI_SAMPLE_DESC m_sampleDesc = { 1, 0 };

		bool m_hasDepthStencil = false;

	public:

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const Size& size() const noexcept;

		void clear(ID3D11DeviceContext* context, const ColorF& color);

		void copyTo(ID3D11DeviceContext* context, D3D11InternalTexture2D& dst);

		void resolveTo(ID3D11DeviceContext* context, D3D11InternalTexture2D& dst);

		void reset();

		[[nodiscard]]
		ID3D11ShaderResourceView* const* getSRVPtr() const noexcept;

		[[nodiscard]]
		ID3D11RenderTargetView* getRTV() const noexcept;

		[[nodiscard]]
		ID3D11Texture2D* getTexture() const noexcept;

		[[nodiscard]]
		static D3D11InternalTexture2D GetTextureFromSwapChain(ID3D11Device* device, IDXGISwapChain1* swapChain1);
	
		[[nodiscard]]
		static D3D11InternalTexture2D CreateRenderTargetTexture2D(ID3D11Device* device, Size size, uint32 sampleCount = 1);
	};
}
