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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Rectangle.hpp>
# include <d3d11.h>
# include <d3d11_1.h>
# include <dxgi1_2.h>
# include "D3D11Device.hpp"

namespace s3d
{
	class D3D11SwapChain
	{
	private:

		HWND m_hWnd = nullptr;
		decltype(GetDpiForWindow)* p_GetDpiForWindow = nullptr;
		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;
		bool m_useFlipModel = false;

		DXGI_SWAP_CHAIN_DESC1 m_desc = {};
		ComPtr<IDXGISwapChain1> m_swapChain1;

		double m_dpiScaling = 1.0;
		double m_currentDisplayRefreshRateHz = 60.0;
		Rect m_previousWindowBounds = Rect(0);

		Optional<double> m_targetFrameRateHz;
		uint64 m_lastPresentTime = 0;

		bool presentVSync();

		bool presentNonVSync();

		std::pair<double, double> checkCurrentDisplay();

	public:

		D3D11SwapChain(const D3D11Device& device, HWND hWnd, const Size& clientSize);

		~D3D11SwapChain();

		bool present();

		void updateDisplayInfo();

		double getDPIScaling() const noexcept;

		double getDisplayRefreshRateHz() const noexcept;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz);

		Optional<double> getTargetFrameRateHz() const;

		IDXGISwapChain1* getSwapChain1() const;

		Optional<Rect> getFullscreenRect();
	};
}
