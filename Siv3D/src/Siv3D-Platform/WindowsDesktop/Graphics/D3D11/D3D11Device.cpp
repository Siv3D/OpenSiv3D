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

# define SIV3D_USE_DIRECT3D11_3
//# define SIV3D_USE_DIRECT3D11_4

# include <Siv3D/Windows.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Unspecified.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/DLL.hpp>
# include "D3D11Device.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr AdapterVendor ToAdapterVendor(const uint32 vendorID)
		{
			switch (vendorID)
			{
			case 0x10DE:
				return AdapterVendor::NVIDIA;
			case 0x1002:
				return AdapterVendor::AMD;
			case 0x8086:
				return AdapterVendor::Intel;
			case 0x1414:
				return AdapterVendor::Microsoft;
			default:
				return AdapterVendor::Unknown;
			}
		}

		static String ToString(const DXGI_ADAPTER_DESC& desc)
		{
			return Format(U"{} (Dedicated GPU memory: {}, System: {}, Shared: {})"_fmt(
				Unicode::FromWString(desc.Description),
				FormatDataSize(desc.DedicatedVideoMemory),
				FormatDataSize(desc.DedicatedSystemMemory),
				FormatDataSize(desc.SharedSystemMemory)));
		}

		constexpr StringView ToString(const D3D_FEATURE_LEVEL featureLevel)
		{
			switch (featureLevel)
			{
			case D3D_FEATURE_LEVEL_9_1:
				return U"D3D_FEATURE_LEVEL_9_1"_sv;
			case D3D_FEATURE_LEVEL_9_2:
				return U"D3D_FEATURE_LEVEL_9_2"_sv;
			case D3D_FEATURE_LEVEL_9_3:
				return U"D3D_FEATURE_LEVEL_9_3"_sv;
			case D3D_FEATURE_LEVEL_10_0:
				return U"D3D_FEATURE_LEVEL_10_0"_sv;
			case D3D_FEATURE_LEVEL_10_1:
				return U"D3D_FEATURE_LEVEL_10_1"_sv;
			case D3D_FEATURE_LEVEL_11_0:
				return U"D3D_FEATURE_LEVEL_11_0"_sv;
			case D3D_FEATURE_LEVEL_11_1:
				return U"D3D_FEATURE_LEVEL_11_1"_sv;
			case D3D_FEATURE_LEVEL_12_0:
				return U"D3D_FEATURE_LEVEL_12_0"_sv;
			case D3D_FEATURE_LEVEL_12_1:
				return U"D3D_FEATURE_LEVEL_12_1"_sv;
			default:
				return U"Unknown"_sv;
			}
		}

		bool CheckHardwareDevice(D3D11Adapter& adapter, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, const D3D_FEATURE_LEVEL minimumFeatureLevel, const Optional<D3D_FEATURE_LEVEL>& forceFeatureLevel)
		{
			LOG_TRACE(U"CheckHardwareDevice()");

			static constexpr D3D_FEATURE_LEVEL FeatureLevels[] =
			{
			# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4) 
				D3D_FEATURE_LEVEL_12_1,
				D3D_FEATURE_LEVEL_12_0,
			# endif
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0
			};

			ComPtr<ID3D11Device> pDevice;
			ComPtr<ID3D11DeviceContext> pDeviceContext;

			HRESULT hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				0,
				FeatureLevels,
				static_cast<UINT>(std::size(FeatureLevels)),
				D3D11_SDK_VERSION,
				&pDevice,
				&adapter.maxLevel,
				&pDeviceContext);

			if (hr == E_INVALIDARG)
			{
			# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4) 

				// DirectX 11.1 ランタイムは D3D_FEATURE_LEVEL_12_x を認識しないので、除外してやり直す
				hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
					D3D_DRIVER_TYPE_UNKNOWN,
					nullptr,
					0,
					&FeatureLevels[2],
					static_cast<UINT>(std::size(FeatureLevels) - 2),
					D3D11_SDK_VERSION,
					&pDevice,
					&adapter.maxLevel,
					&pDeviceContext);

				if (hr == E_INVALIDARG)
				{
					// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
					hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
						D3D_DRIVER_TYPE_UNKNOWN,
						nullptr,
						0,
						&FeatureLevels[3],
						static_cast<UINT>(std::size(FeatureLevels) - 3),
						D3D11_SDK_VERSION,
						&pDevice,
						&adapter.maxLevel,
						&pDeviceContext);
				}

			# else

				// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
				hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
					D3D_DRIVER_TYPE_UNKNOWN,
					nullptr,
					0,
					&FeatureLevels[1],
					static_cast<UINT>(std::size(FeatureLevels) - 1),
					D3D11_SDK_VERSION,
					&pDevice,
					&adapter.maxLevel,
					&pDeviceContext);

			# endif
			}

			if (FAILED(hr))
			{
				LOG_FAIL(U"❌ - D3D11CreateDevice() failed");
				return false;
			}
			else if (adapter.maxLevel < minimumFeatureLevel)
			{
				LOG_FAIL(U"❌ - adapter.maxLevel ({}) does not meet minimumFeatureLevel requirments ({})"_fmt(
					detail::ToString(adapter.maxLevel), detail::ToString(minimumFeatureLevel)));
				return false;
			}

			if (!forceFeatureLevel || forceFeatureLevel == adapter.maxLevel)
			{
				adapter.selectedLevel = adapter.maxLevel;
			}
			else if (forceFeatureLevel > adapter.maxLevel)
			{
				LOG_FAIL(U"❌ - adapterInfo.maxLevel ({}) does not meet forceFeatureLevel requirments ({})"_fmt(
					detail::ToString(adapter.maxLevel), detail::ToString(forceFeatureLevel.value())));
				return false;
			}
			else
			{
				pDevice.Reset();
				pDeviceContext.Reset();

				D3D_FEATURE_LEVEL returnedFeatureLevel;
				hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
					D3D_DRIVER_TYPE_UNKNOWN,
					nullptr,
					0,
					&forceFeatureLevel.value(),
					1,
					D3D11_SDK_VERSION,
					&pDevice,
					&returnedFeatureLevel,
					&pDeviceContext);

				if (SUCCEEDED(hr) && (returnedFeatureLevel == forceFeatureLevel))
				{
					adapter.selectedLevel = forceFeatureLevel.value();
				}
				else
				{
					LOG_FAIL(U"❌ - D3D11CreateDevice() failed with specified forceFeatureLevel {}"_fmt(
						detail::ToString(forceFeatureLevel.value())));
					return false;
				}
			}

			if (D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS ho = {};
				SUCCEEDED(pDevice->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &ho, sizeof(ho))))
			{
				adapter.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = ho.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
			}

			LOG_INFO(U"ℹ️ - [D3D_DRIVER_TYPE_HARDWARE] selected: {} (max: {})"_fmt(
				detail::ToString(adapter.selectedLevel), detail::ToString(adapter.maxLevel)));
			return true;
		}

		static Array<D3D11Adapter> GetAdapters(IDXGIFactory2* pDXGIFactory2, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
		{
			LOG_TRACE(U"GetAdapters()");

			Array<D3D11Adapter> adapters;

			for (uint32 adapterIndex = 0; ; ++adapterIndex)
			{
				ComPtr<IDXGIAdapter> pAdapter;
				HRESULT hr = pDXGIFactory2->EnumAdapters(adapterIndex, &pAdapter);

				// リストの最後で DXGIERR_NOT_FOUND が返る
				if (FAILED(hr))
				{
					break;
				}

				// Direct3D 11.1 ランタイムを使用可能かチェック
				bool d3d11_1_runtimeSupprot = false;
				ComPtr<IDXGIAdapter2> pAdapter2;
				if (hr = pAdapter->QueryInterface(__uuidof(IDXGIAdapter2), &pAdapter2);
					SUCCEEDED(hr))
				{
					DXGI_ADAPTER_DESC2 desc;
					if (hr = pAdapter2->GetDesc2(&desc);
						(SUCCEEDED(hr) && (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)))
					{
						// Microsoft Basics Display Driver はスキップ
						LOG_DEBUG(U"ℹ️ IDXGIAdapter [{}] is Microsoft Basics Display Driver (skipped)"_fmt(adapterIndex));
						continue;
					}

					d3d11_1_runtimeSupprot = true;
				}

				D3D11Adapter adapter;
				adapter.pAdapter				= pAdapter;
				adapter.adapterIndex			= adapterIndex;
				adapter.d3d11_1_runtimeSupprot	= d3d11_1_runtimeSupprot;
				pAdapter->GetDesc(&adapter.adapterDesc);
				adapter.vendor = detail::ToAdapterVendor(adapter.adapterDesc.VendorId);

				LOG_INFO(U"ℹ️ IDXGIAdapter [{}]: {} (supports Direct3D 11.{} runtime)"_fmt(
					adapterIndex,
					detail::ToString(adapter.adapterDesc),
					d3d11_1_runtimeSupprot ? 1 : 0
				));

				if (!CheckHardwareDevice(adapter, pD3D11CreateDevice, D3D_FEATURE_LEVEL_10_0, unspecified))
				{
					LOG_FAIL(U"❌ - getHardwareDevice() failed");
					continue;
				}

				adapters.push_back(adapter);
			}

			return adapters;
		}

		static D3D_FEATURE_LEVEL GetWARPFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
		{
			LOG_TRACE(U"GetWARPFeatureLevel()");

			D3D_FEATURE_LEVEL warpFeatureLevel = D3D_FEATURE_LEVEL_10_1;

			static constexpr D3D_FEATURE_LEVEL FeatureLevels[] =
			{
			# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4) 
				D3D_FEATURE_LEVEL_12_1,
				D3D_FEATURE_LEVEL_12_0,
			# endif
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1
			};

			ComPtr<ID3D11Device> pDevice;
			HRESULT hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
				0, 0, FeatureLevels, static_cast<UINT>(std::size(FeatureLevels)),
				D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);

			if (hr == E_INVALIDARG)
			{
			# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4)

				// DirectX 11.1 ランタイムは D3D_FEATURE_LEVEL_12_x を認識しないので、除外してやり直す
				hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
					0, 0, &FeatureLevels[2], static_cast<UINT>(std::size(FeatureLevels) - 2),
					D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);

				if (hr == E_INVALIDARG)
				{
					// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
					hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
						0, 0, &FeatureLevels[3], static_cast<UINT>(std::size(FeatureLevels) - 3),
						D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);
				}

			# else

				// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
				hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
					0, 0, &FeatureLevels[1], static_cast<UINT>(std::size(FeatureLevels) - 1),
					D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);

			# endif
			}

			if (FAILED(hr))
			{
				warpFeatureLevel = D3D_FEATURE_LEVEL_10_1;
			}

			return warpFeatureLevel;
		}

		static D3D_FEATURE_LEVEL GetREFFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
		{
			LOG_TRACE(U"GetREFFeatureLevel()");

			D3D_FEATURE_LEVEL refFeatureLevel = D3D_FEATURE_LEVEL_10_1;

			static constexpr D3D_FEATURE_LEVEL FeatureLevels[] =
			{
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1
			};

			ComPtr<ID3D11Device> pDevice;
			HRESULT hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_REFERENCE,
				0, 0, FeatureLevels, static_cast<UINT>(std::size(FeatureLevels)),
				D3D11_SDK_VERSION, &pDevice, &refFeatureLevel, nullptr);

			if (hr == E_INVALIDARG)
			{
				// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
				hr = pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_REFERENCE,
					0, 0, &FeatureLevels[1], static_cast<UINT>(std::size(FeatureLevels) - 1),
					D3D11_SDK_VERSION, &pDevice, &refFeatureLevel, nullptr);
			}

			if (FAILED(hr))
			{
				refFeatureLevel = D3D_FEATURE_LEVEL_10_1;
			}

			return refFeatureLevel;
		}
	}

	String D3D11Adapter::name() const
	{
		return Unicode::FromWString(adapterDesc.Description);
	}

	D3D11Device::D3D11Device()
	{
		LOG_TRACE(U"D3D11Device::D3D11Device()");

		HMODULE moduleD3D11 = DLL::LoadSystemLibrary(L"d3d11.dll");
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice = DLL::GetFunction(moduleD3D11, "D3D11CreateDevice");

		HMODULE moduleDXGI = DLL::LoadSystemLibrary(L"dxgi.dll");
		decltype(CreateDXGIFactory1)* pCreateDXGIFactory1 = DLL::GetFunction(moduleDXGI, "CreateDXGIFactory1");

		const bool hasDebugLayer = Platform::DebugBuild
			? (DLL::LoadSystemLibrary(L"D3D11_1SDKLayers.dll") != nullptr)
			: false;

		if (FAILED(pCreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory2))))
		{
			throw EngineError(U"CreateDXGIFactory1() failed");
		}

		if (SUCCEEDED(pCreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory5))))
		{
			LOG_INFO(U"ℹ️ DXGIFactory5 is available");
		}

		m_adapters = detail::GetAdapters(m_DXGIFactory2.Get(), pD3D11CreateDevice);
		LOG_INFO(U"ℹ️ {} adapters available"_fmt(m_adapters.size()));

		m_WARPFeatureLevel = detail::GetWARPFeatureLevel(pD3D11CreateDevice);
		LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_WARP] supports {}"_fmt(detail::ToString(m_WARPFeatureLevel)));

		m_REFFeatureLevel = detail::GetREFFeatureLevel(pD3D11CreateDevice);
		LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_REFERENCE] supports {}"_fmt(detail::ToString(m_REFFeatureLevel)));

		if (!createDevice(pD3D11CreateDevice, TargetD3DDevice::Hardware, unspecified, hasDebugLayer ? D3D11_CREATE_DEVICE_DEBUG : 0))
		{
			throw EngineError(U"D3D11Device::createDevice() failed");
		}
	}

	D3D11Device::~D3D11Device()
	{

	}

	IDXGIFactory2* D3D11Device::getDXGIFactory2() const
	{
		return m_DXGIFactory2.Get();
	}

	IDXGIFactory5* D3D11Device::getDXGIFactory5() const
	{
		return m_DXGIFactory5.Get();
	}

	ID3D11Device* D3D11Device::getDevice() const
	{
		return m_device.Get();
	}

	ID3D11DeviceContext* D3D11Device::getContext() const
	{
		return m_context.Get();
	}

	bool D3D11Device::hasDXGI_1_4() const
	{
		return (m_DXGIFactory5.Get() != nullptr);
	}

	bool D3D11Device::createDevice(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, TargetD3DDevice targetDevice, const Optional<size_t> targetAdapterIndex, const uint32 deviceFlags)
	{
		LOG_TRACE(U"D3D11Device::createDevice(targetDevice = {}, targetAdapterIndex = {}, deviceFlags = {})"_fmt(FromEnum(targetDevice), targetAdapterIndex, deviceFlags));

		if (m_adapters.isEmpty())
		{
			targetDevice = TargetD3DDevice::WARP;
		}

		if (targetDevice == TargetD3DDevice::Hardware
			|| targetDevice == TargetD3DDevice::Hardware_FavorIntegrated)
		{
			size_t selectedAdapterIndex = 0;

			if (targetAdapterIndex)
			{
				selectedAdapterIndex = std::min(targetAdapterIndex.value(), m_adapters.size() - 1);
			}
			else
			{
				if (targetDevice == TargetD3DDevice::Hardware)
				{
					size_t maxDedicatedMemory = 0;
					size_t maxDedicatedMemoryAdapterIndex = 0;

					for (size_t adapterIndex = 0; adapterIndex < m_adapters.size(); ++adapterIndex)
					{
						const size_t dedicatedMemory = m_adapters[adapterIndex].adapterDesc.DedicatedVideoMemory;

						if (maxDedicatedMemory < dedicatedMemory)
						{
							maxDedicatedMemory = dedicatedMemory;
							maxDedicatedMemoryAdapterIndex = adapterIndex;
						}
					}

					selectedAdapterIndex = maxDedicatedMemoryAdapterIndex;
				}
				else if (targetDevice == TargetD3DDevice::Hardware_FavorIntegrated)
				{
					for (size_t adapterIndex = 0; adapterIndex < m_adapters.size(); ++adapterIndex)
					{
						if (m_adapters[adapterIndex].vendor == AdapterVendor::Intel)
						{
							selectedAdapterIndex = adapterIndex;
							break;
						}
					}
				}
			}

			const auto& adapter = m_adapters[selectedAdapterIndex];
			LOG_INFO(U"ℹ️ selectedAdapterIndex: {} ({})"_fmt(selectedAdapterIndex, adapter.name()));

			if (SUCCEEDED(pD3D11CreateDevice(
				adapter.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				deviceFlags,
				&adapter.selectedLevel,
				1,
				D3D11_SDK_VERSION,
				&m_device,
				&m_selectedFeatureLevel,
				&m_context)))
			{
				m_deviceType				= D3D_DRIVER_TYPE_HARDWARE;
				m_d3d11_1_runtimeSupprot	= adapter.d3d11_1_runtimeSupprot;
				m_adapter					= adapter.pAdapter;
				m_selectedAdapterIndex		= selectedAdapterIndex;
				LOG_INFO(U"✅ D3D11 device created. Driver type: Hardware ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
				return true;
			}
			else
			{
				if (SUCCEEDED(pD3D11CreateDevice(
					nullptr,
					D3D_DRIVER_TYPE_HARDWARE,
					nullptr,
					deviceFlags,
					&adapter.selectedLevel,
					1,
					D3D11_SDK_VERSION,
					&m_device,
					&m_selectedFeatureLevel,
					&m_context)))
				{
					m_deviceType				= D3D_DRIVER_TYPE_HARDWARE;
					m_d3d11_1_runtimeSupprot	= (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);
					LOG_INFO(U"✅ D3D11 device created. Driver type: Hardware ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
					return true;
				}

				targetDevice = TargetD3DDevice::WARP;
			}
		}

		if (targetDevice == TargetD3DDevice::WARP)
		{
			if (SUCCEEDED(pD3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP,
				nullptr,
				deviceFlags,
				&m_WARPFeatureLevel,
				1,
				D3D11_SDK_VERSION,
				&m_device,
				&m_selectedFeatureLevel,
				&m_context)))
			{
				m_deviceType				= D3D_DRIVER_TYPE_WARP;
				m_d3d11_1_runtimeSupprot	= (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);
				LOG_INFO(U"✅ D3D11 device created. Driver type: WARP ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
				return true;
			}
			else
			{
				targetDevice = TargetD3DDevice::Reference;
			}
		}

		if (targetDevice == TargetD3DDevice::Reference)
		{
			if (SUCCEEDED(pD3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_REFERENCE,
				nullptr,
				deviceFlags,
				&m_REFFeatureLevel,
				1,
				D3D11_SDK_VERSION,
				&m_device,
				&m_selectedFeatureLevel,
				&m_context)))
			{
				m_deviceType				= D3D_DRIVER_TYPE_REFERENCE;
				m_d3d11_1_runtimeSupprot	= (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);
				LOG_INFO(U"✅ D3D11 device created. Driver type: Reference ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
				return true;
			}
		}

		return false;
	}
}
