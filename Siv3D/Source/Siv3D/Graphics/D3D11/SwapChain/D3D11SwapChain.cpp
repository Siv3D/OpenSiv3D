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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "D3D11SwapChain.hpp"
# include "../../../Siv3DEngine.hpp"
# include "../../../Window/IWindow.hpp"

# include <Siv3D/PointVector.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
	
	}

	D3D11SwapChain::D3D11SwapChain(ID3D11Device* device, ID3D11DeviceContext* context, IDXGIAdapter* adapter)
		: m_device(device)
		, m_context(context)
		, m_adapter(adapter)
	{

	}

	D3D11SwapChain::~D3D11SwapChain()
	{
		//m_swapChain->SetFullscreenState(false, nullptr);
	}

	bool D3D11SwapChain::init()
	{
		return true;

		const Size resolution(640, 480);
		const HWND hWnd = Siv3DEngine::GetWindow()->getHandle();

		m_desc.BufferDesc.Width						= resolution.x;
		m_desc.BufferDesc.Height					= resolution.y;
		m_desc.BufferDesc.RefreshRate.Numerator		= 0;
		m_desc.BufferDesc.RefreshRate.Denominator	= 0;
		m_desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		m_desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
		m_desc.SampleDesc.Count						= 1;
		m_desc.SampleDesc.Quality					= 0;
		m_desc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		m_desc.BufferCount							= 1;
		m_desc.OutputWindow							= hWnd;
		m_desc.Windowed								= true;
		m_desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
		m_desc.Flags								= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		ComPtr<IDXGIFactory> pDXGIFactory;

		if (FAILED(m_adapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory)))
		{
			return false;
		}

		// スワップチェーンを作成
		if (FAILED(pDXGIFactory->CreateSwapChain(m_device, &m_desc, &m_swapChain)))
		{
			Log(L"スワップチェーンの作成に失敗しました。");

			return false;
		}

		//m_swapChain->SetFullscreenState(true, nullptr);

		//if (FAILED(pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
		//{
		//	Log(L"failed: MakeWindowAssociation");

		//	return false;
		//}

		return true;
	}

	Array<ComPtr<IDXGIOutput>> D3D11SwapChain::enumOutputs()
	{
		Array<ComPtr<IDXGIOutput>> outputs;

		/*
		for(uint32 i = 0; ; ++i)
		{
			ComPtr<IDXGIOutput> pOutput;
			
			if (SUCCEEDED(pAdapter->EnumOutputs(i, &pOutput)))
			{
				Array<DXGI_MODE_DESC> displayModeList;

				uint32 numModes;

				if (SUCCEEDED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr)))
				{
					displayModeList.resize(numModes);

					if (FAILED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModeList.data())))
					{
						return false;
					}
				}

				# ifdef _DEBUG

				const String DXGI_MODE_SCALINGstr[3] =
				{
					L"",
					L"Centered",
					L"Stretched",
				};

				for (auto const& desc : displayModeList)
				{
					Log(desc.Width, L'x', desc.Height,
						L'(', (1.0*desc.RefreshRate.Numerator / desc.RefreshRate.Denominator),
						L" Hz [", desc.RefreshRate.Numerator, L'/', desc.RefreshRate.Denominator, L"])",
						DXGI_MODE_SCALINGstr[desc.Scaling]
					);
				}

			# endif
			}
			else
			{
				Log(L"failed: EnumOutputs");
			}
		}
		*/

		return outputs;
	}
}

# endif
