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

# include <Siv3D/Array.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
	
	}

	D3D11SwapChain::D3D11SwapChain(ID3D11Device* device, ID3D11DeviceContext* context)
		: m_device(device)
		, m_context(context)
	{

	}

	D3D11SwapChain::~D3D11SwapChain()
	{

	}

	bool D3D11SwapChain::init()
	{
		ComPtr<IDXGIDevice1> pDXGI;

		if (FAILED(m_device->QueryInterface(__uuidof(IDXGIDevice1), &pDXGI)))
		{
			return false;
		}

		ComPtr<IDXGIAdapter> pAdapter;

		if (FAILED(pDXGI->GetAdapter(&pAdapter)))
		{
			return false;
		}

		DXGI_ADAPTER_DESC adapterDesc;

		if (SUCCEEDED(pAdapter->GetDesc(&adapterDesc)))
		{
			Log(L"Graphics adapter:\n", adapterDesc.Description);
		}

		ComPtr<IDXGIOutput> pOutput;
		Array<DXGI_MODE_DESC> displayModeList;

		if (SUCCEEDED(pAdapter->EnumOutputs(0, &pOutput)))
		{
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

		return true;
	}
}

# endif
