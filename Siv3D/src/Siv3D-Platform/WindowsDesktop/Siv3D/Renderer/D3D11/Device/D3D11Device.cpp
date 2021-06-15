//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/DLL.hpp>
# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Unspecified.hpp>
# include <Siv3D/EngineLog.hpp>
# include "D3D11Device.hpp"
# include "D3D11DeviceHelper.hpp"

namespace s3d
{
	D3D11Device::D3D11Device()
	{
		LOG_SCOPED_TRACE(U"D3D11Device::D3D11Device()");

		// d3d11.dll から D3D11CreateDevice() を取得
		LibraryHandle moduleD3D11 = DLL::LoadSystemLibrary(L"d3d11.dll");
		m_pD3D11CreateDevice = DLL::GetFunction(moduleD3D11, "D3D11CreateDevice");

		// dxgi.dll から　CreateDXGIFactory1() を取得
		LibraryHandle moduleDXGI = DLL::LoadSystemLibrary(L"dxgi.dll");
		decltype(CreateDXGIFactory1)* pCreateDXGIFactory1 = DLL::GetFunction(moduleDXGI, "CreateDXGIFactory1");

		// D3D11_CREATE_DEVICE_DEBUG が使えるかのチェック
		m_hasDebugLayer = SIV3D_BUILD(DEBUG)
			? (DLL::LoadSystemLibraryNoThrow(L"D3D11_1SDKLayers.dll") != nullptr)
			: false;

		// DXGI 1.2
		if (FAILED(pCreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory2))))
		{
			throw EngineError(U"CreateDXGIFactory1() failed");
		}

		// DXGI 1.5
		if (SUCCEEDED(pCreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory5))))
		{
			LOG_INFO(U"ℹ️ DXGIFactory5 is available");
		}
	}

	D3D11Device::~D3D11Device()
	{

	}

	void D3D11Device::init()
	{
		// 利用可能なハードウェアアダプタを取得
		{
			m_adapters = detail::GetAdapters(m_DXGIFactory2.Get(), m_pD3D11CreateDevice);
			LOG_INFO(U"ℹ️ {} adapters available"_fmt(m_adapters.size()));
		}

		// WARP ドライバの feature level を取得
		{
			m_WARPFeatureLevel = detail::GetWARPFeatureLevel(m_pD3D11CreateDevice);
			LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_WARP] supports {}"_fmt(detail::ToString(m_WARPFeatureLevel)));
		}

		// Reference ドライバの feature level を取得
		{
			m_referenceFeatureLevel = detail::GetReferenceFeatureLevel(m_pD3D11CreateDevice);
			LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_REFERENCE] supports {}"_fmt(detail::ToString(m_referenceFeatureLevel)));
		}

		// D3D11 デバイスを作成
		{
			Optional<D3D11DeviceInfo> deviceInfo;
			uint32 deviceFlag = D3D11_CREATE_DEVICE_DEBUG;

			for (size_t i = (m_hasDebugLayer ? 0 : 1); i < 2; ++i)
			{
				if (i == 1)
				{
					deviceFlag = 0;
				}

				deviceInfo = detail::CreateDevice(m_pD3D11CreateDevice, m_adapters,
					g_applicationOptions.d3d11Driver, unspecified, deviceFlag,
					m_WARPFeatureLevel, m_referenceFeatureLevel);

				if (deviceInfo)
				{
					break;
				}
			}

			if (deviceInfo)
			{
				m_deviceInfo = *deviceInfo;
			}
			else
			{
				throw EngineError(U"detail::CreateDevice() failed");
			}
		}
	}

	IDXGIFactory2* D3D11Device::getDXGIFactory2() const noexcept
	{
		return m_DXGIFactory2.Get();
	}

	IDXGIFactory5* D3D11Device::getDXGIFactory5() const noexcept
	{
		return m_DXGIFactory5.Get();
	}

	ID3D11Device* D3D11Device::getDevice() const noexcept
	{
		return m_deviceInfo.device.Get();
	}

	ComPtr<ID3D11Device> D3D11Device::getDeiviceComPtr() const noexcept
	{
		return m_deviceInfo.device;
	}

	ID3D11DeviceContext* D3D11Device::getContext() const noexcept
	{
		return m_deviceInfo.context.Get();
	}

	bool D3D11Device::hasDXGI_1_4() const noexcept
	{
		return (m_DXGIFactory5.Get() != nullptr);
	}
}
