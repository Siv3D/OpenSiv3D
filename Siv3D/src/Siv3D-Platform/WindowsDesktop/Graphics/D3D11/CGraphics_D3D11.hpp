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
# include <memory>
# include <Graphics/IGraphics.hpp>
# include "D3D11Device.hpp"
# include "D3D11SwapChain.hpp"
# include "D3D11RenderTarget.hpp"
# include "D3D11BlendState.hpp"
# include "D3D11RasterizerState.hpp"
# include "D3D11DepthStencilState.hpp"
# include "D3D11SamplerState.hpp"
# include "D3D11ScreenCapture.hpp"

namespace s3d
{
	class CGraphics_D3D11 : public ISiv3DGraphics
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11RenderTarget> m_renderTarget;

		std::unique_ptr<D3D11BlendState> m_pBlendState;

		std::unique_ptr<D3D11RasterizerState> m_pRasterizerState;

		std::unique_ptr<D3D11DepthStencilState> m_pDepthStencilState;

		std::unique_ptr<D3D11SamplerState> m_pSamplerState;

		std::unique_ptr<D3D11ScreenCapture> m_pScreenCapture;

	public:

		CGraphics_D3D11();

		~CGraphics_D3D11() override;

		void init() override;

		bool present() override;

		void clear() override;

		void flush() override;

		void setSceneTextureFilter(TextureFilter textureFilter) override;

		TextureFilter getSceneTextureFilter() const override;

		void setBackgroundColor(const ColorF& color) override;

		void setLetterboxColor(const ColorF& color) override;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override;

		Optional<double> getTargetFrameRateHz() const override;

		double getDPIScaling() const override;

		double getDisplayRefreshRateHz() const override;

		void skipClearScreen() override;

		const Size& getBackBufferSize() const override;

		const Size& getSceneSize() const override;

		void setSceneSize(const Size& sceneSize) override;

		void resizeBuffers(const Size& backBufferSize, const Size& sceneSize) override;

		Optional<Rect> getFullscreenRect() override;

		void requestScreenCapture() override;

		const Image& getScreenCapture() const override;

		ID3D11Device* getDevice() const { return m_device->getDevice(); }

		ID3D11DeviceContext* getContext() const { return m_device->getContext(); }

		D3D11RenderTarget* getRenderTarget() const { return m_renderTarget.get(); }

		D3D11BlendState* getBlendState() const { return m_pBlendState.get(); }

		D3D11RasterizerState* getRasterizerState() const { return m_pRasterizerState.get(); }

		D3D11SamplerState* getSamplerState() const { return m_pSamplerState.get(); }
	};
}
