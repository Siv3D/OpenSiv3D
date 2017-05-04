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

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/Graphics.hpp>

namespace s3d
{
	class D3D11SwapChain
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGIAdapter* m_adapter = nullptr;

		HWND m_hWnd = nullptr;

		DXGI_SWAP_CHAIN_DESC m_desc{};

		ComPtr<IDXGISwapChain> m_swapChain;

		Size m_size{ 640, 480 };

		size_t m_currentDisplayIndex = 0;

		bool m_fullScreen = false;

		bool m_vSyncEnabled = true;

		// ディスプレイの設定の中でユーザー設定に最も近いものを適用
		// 利用可能なサイズのうち size に一致するものがなければ false を返す
		bool setBestFullScreenMode(const Size& size, size_t displayIndex, double refreshRateHz);

	public:

		D3D11SwapChain(ID3D11Device* device, ID3D11DeviceContext* context, IDXGIAdapter* adapter);

		~D3D11SwapChain();

		bool init();

		Array<DisplayOutput> enumOutputs();

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz);

		IDXGISwapChain* getSwapChain() const;

		bool present();

		void setVSyncEnabled(bool enabled);

		bool isVSyncEnabled() const;
	};
}

# endif
