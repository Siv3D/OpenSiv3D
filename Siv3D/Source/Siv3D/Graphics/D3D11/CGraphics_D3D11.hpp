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

# include <memory>
# include "../IGraphics.hpp"
# include "Device/D3D11Device.hpp"
# include "SwapChain/D3D11SwapChain.hpp"
# include "RenderTarget/D3D11RenderTarget.hpp"
# include "../../Texture/D3D11/CTexture_D3D11.hpp"
# include "../../Shader/D3D11/CShader_D3D11.hpp"
# include "BlendState/D3D11BlendState.hpp"
# include "RasterizerState/D3D11RasterizerState.hpp"
# include "DepthStencilState/D3D11DepthStencilState.hpp"
# include "SamplerState/D3D11SamplerState.hpp"
# include "../../Renderer2D/D3D11/CRenderer2D_D3D11.hpp"

namespace s3d
{
	class CGraphics_D3D11 : public ISiv3DGraphics
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11RenderTarget> m_renderTarget;

		CTexture_D3D11* m_texture = nullptr;

		CShader_D3D11* m_shader = nullptr;

		std::unique_ptr<D3D11BlendState> m_pBlendState;

		std::unique_ptr<D3D11RasterizerState> m_pRasterizerState;

		std::unique_ptr<D3D11DepthStencilState> m_pDepthStencilState;

		std::unique_ptr<D3D11SamplerState> m_pSamplerState;

		CRenderer2D_D3D11* m_renderer2D = nullptr;

	public:

		CGraphics_D3D11();

		~CGraphics_D3D11() override;

		bool init() override;

		ID3D11Device* getDevice() const { return m_device->getDevice(); }

		ID3D11DeviceContext* getContext() const { return m_device->getContext(); }

		D3D11RenderTarget* getRenderTarget() const { return m_renderTarget.get(); }

		D3D11BlendState* getBlendState() const { return m_pBlendState.get(); }

		D3D11RasterizerState* getRasterizerState() const { return m_pRasterizerState.get(); }

		D3D11SamplerState* getSamplerState() const { return m_pSamplerState.get(); }

		void setClearColor(const ColorF& color) override;

		Array<DisplayOutput> enumOutputs() override;

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) override;

		bool present() override;

		void clear() override;

		void beginResize() override;

		bool endResize(const Size& size) override;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override;

		Optional<double> getTargetFrameRateHz() const override;

		double getDisplayRefreshRateHz() const override;

		bool flush() override;

		const Size& getCurrentRenderTargetSize() const override;

		const RenderTexture& getBackBuffer2D() const override;

		bool resizeTargetWindowed(const Size& size)
		{
			return m_swapChain->resizeTargetWindowed(size);
		}

		Optional<Size> shouldResize() const
		{
			return m_swapChain->shouldResize();
		}
	};
}

# endif
