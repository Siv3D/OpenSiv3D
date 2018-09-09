//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/Image.hpp>
# include "../Device/D3D11_1Device.hpp"

using namespace Microsoft::WRL;

namespace s3d
{
	class D3D11_1SwapChain
	{
	private:

		IDXGIFactory1* m_DXGIFactory = nullptr;

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGIAdapter* m_adapter = nullptr;

		DXGI_SWAP_CHAIN_DESC m_desc = {};

		ComPtr<IDXGISwapChain> m_swapChain;

		double m_currentDisplayRefreshRateHz = 60.0;

		Optional<double> m_targetFrameRateHz;

		uint64 m_lastPresentTime = 0;

		bool m_fullScreen = false;

		Size m_targetSize = Window::DefaultClientSize;

		Size m_actualSize = Window::DefaultClientSize;

		size_t m_currentDisplayIndex = 0;

	public:

		D3D11_1SwapChain(const D3D11_1Device& device);

		~D3D11_1SwapChain();

		bool init();

		IDXGISwapChain* getSwapChain() const;

		double getDisplayRefreshRateHz() const;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz);

		Optional<double> getTargetFrameRateHz() const;

		bool present();

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz, const D3D11_1Device& device);

		bool resizeTargetWindowed(const Size& size);

		bool resizeTarget(const DXGI_MODE_DESC& modeDesc);

		Optional<Size> pendingResize() const;
	};
}

# endif
