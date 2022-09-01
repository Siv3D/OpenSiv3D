//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "../Device/D3D11Device.hpp"

namespace s3d
{
	class D3D11SwapChain
	{
	private:

		HWND m_hWnd						= nullptr;
		
		ID3D11Device* m_device			= nullptr;
		
		ID3D11DeviceContext* m_context	= nullptr;

		DXGI_SWAP_CHAIN_DESC1 m_desc	= {};

		ComPtr<IDXGISwapChain1> m_swapChain1;

		double m_displayFrequency		= 60.0;

		Rect m_previousWindowBounds		= Rect::Empty();

		uint64 m_lastPresentTime = 0;

		void updateDisplayInfo();

		[[nodiscard]]
		bool presentVSync();

		[[nodiscard]]
		bool presentNonVSync();

	public:

		D3D11SwapChain(const D3D11Device& device, HWND hWnd, const Size& frameBufferSize);

		~D3D11SwapChain();

		[[nodiscard]]
		bool present(bool vSync);

		[[nodiscard]]
		double getDisplayFrequency() const noexcept;

		//void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz);

		//[[nodiscard]]
		//const Optional<double>& getTargetFrameRateHz() const noexcept;

		[[nodiscard]]
		IDXGISwapChain1* getSwapChain1() const noexcept;

		[[nodiscard]]
		Optional<Rect> getFullscreenRect();
	};
}
