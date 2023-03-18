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
# include <memory>
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include "Device/D3D11Device.hpp"
# include "SwapChain/D3D11SwapChain.hpp"
# include "BackBuffer/D3D11BackBuffer.hpp"
# include "BlendState/D3D11BlendState.hpp"
# include "RasterizerState/D3D11RasterizerState.hpp"
# include "DepthStencilState/D3D11DepthStencilState.hpp"
# include "SamplerState/D3D11SamplerState.hpp"
# include "ScreenCapture/D3D11ScreenCapture.hpp"

namespace s3d
{
	class CRenderer2D_D3D11;
	class CRenderer3D_D3D11;
	class CTexture_D3D11;

	class CRenderer_D3D11 final : public ISiv3DRenderer
	{
	private:

		CRenderer2D_D3D11* pRenderer2D = nullptr;
		CRenderer3D_D3D11* pRenderer3D = nullptr;
		CTexture_D3D11* pTexture = nullptr;

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11BackBuffer> m_backBuffer;

		std::unique_ptr<D3D11BlendState> m_blendState;

		std::unique_ptr<D3D11RasterizerState> m_rasterizerState;

		std::unique_ptr<D3D11DepthStencilState> m_depthStencilState;

		std::unique_ptr<D3D11SamplerState> m_samplerState;

		std::unique_ptr<D3D11ScreenCapture> m_screenCapture;

		bool m_vSyncEnabled = true;

	public:

		CRenderer_D3D11();

		~CRenderer_D3D11() override;

		EngineOption::Renderer getRendererType() const noexcept override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void setVSyncEnabled(bool enabled) override;

		bool isVSyncEnabled() const override;

		void captureScreenshot() override;

		const Image& getScreenCapture() const override;

		void setSceneResizeMode(ResizeMode resizeMode) override;

		ResizeMode getSceneResizeMode() const noexcept override;

		void setSceneBufferSize(Size size) override;

		Size getSceneBufferSize() const noexcept override;

		void setSceneTextureFilter(TextureFilter textureFilter) override;

		TextureFilter getSceneTextureFilter() const noexcept override;

		void setBackgroundColor(const ColorF& color) override;

		const ColorF& getBackgroundColor() const noexcept override;

		void setLetterboxColor(const ColorF& color) override;

		const ColorF& getLetterboxColor() const noexcept override;

		std::pair<float, RectF> getLetterboxComposition() const noexcept override;

		void updateSceneSize() override;

		//
		// Windows
		//

		void init2();

		ID3D11Device* getDevice() const;

		ID3D11DeviceContext* getContext() const;

		D3D11BackBuffer& getBackBuffer() noexcept;

		D3D11BlendState& getBlendState() noexcept;

		D3D11RasterizerState& getRasterizerState() noexcept;

		D3D11DepthStencilState& getDepthStencilState() noexcept;

		D3D11SamplerState& getSamplerState() noexcept;
	};
}
