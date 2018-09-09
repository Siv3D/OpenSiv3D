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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define SIV3D_USE_DIRECT3D11_3
//# define SIV3D_USE_DIRECT3D11_4

# include "D3D11_1Device.hpp"
# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Unspecified.hpp>
# include <Siv3D/Logger.hpp>
# include "../../../EngineUtility.hpp"

namespace s3d
{
	namespace detail
	{
		using namespace std::literals::string_view_literals;

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
				return U"D3D_FEATURE_LEVEL_9_1"sv;
			case D3D_FEATURE_LEVEL_9_2:
				return U"D3D_FEATURE_LEVEL_9_2"sv;
			case D3D_FEATURE_LEVEL_9_3:
				return U"D3D_FEATURE_LEVEL_9_3"sv;
			case D3D_FEATURE_LEVEL_10_0:
				return U"D3D_FEATURE_LEVEL_10_0"sv;
			case D3D_FEATURE_LEVEL_10_1:
				return U"D3D_FEATURE_LEVEL_10_1"sv;
			case D3D_FEATURE_LEVEL_11_0:
				return U"D3D_FEATURE_LEVEL_11_0"sv;
			case D3D_FEATURE_LEVEL_11_1:
				return U"D3D_FEATURE_LEVEL_11_1"sv;
			case D3D_FEATURE_LEVEL_12_0:
				return U"D3D_FEATURE_LEVEL_12_0"sv;
			case D3D_FEATURE_LEVEL_12_1:
				return U"D3D_FEATURE_LEVEL_12_1"sv;
			default:
				return U"Unknown"sv;
			}
		}

		constexpr StringView ToString(const DXGI_MODE_SCANLINE_ORDER order)
		{
			switch (order)
			{
			case DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:
				return U"DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED"sv;
			case DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:
				return U"DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE"sv;
			case DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST:
				return U"DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST"sv;
			case DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST:
				return U"DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST"sv;
			default:
				return U"Unknown"sv;
			}
		}

		constexpr StringView ToString(const DXGI_MODE_SCALING scaling)
		{
			switch (scaling)
			{
			case DXGI_MODE_SCALING_UNSPECIFIED:
				return U"DXGI_MODE_SCALING_UNSPECIFIED"sv;
			case DXGI_MODE_SCALING_CENTERED:
				return U"DXGI_MODE_SCALING_CENTERED"sv;
			case DXGI_MODE_SCALING_STRETCHED:
				return U"DXGI_MODE_SCALING_STRETCHED"sv;
			default:
				return U"Unknown"sv;
			}
		}

		static String ToString(const DXGI_MODE_DESC desc)
		{
			return U"{}x{} @{} Hz ({}/{}) -{}, -{}"_fmt(desc.Width, desc.Height,
				static_cast<double>(desc.RefreshRate.Numerator) / desc.RefreshRate.Denominator,
				desc.RefreshRate.Numerator, desc.RefreshRate.Denominator,
				ToString(desc.ScanlineOrdering),
				ToString(desc.Scaling)
			);
		}

		bool DisplayModeFilter(const DXGI_MODE_DESC& desc)
		{
			if (desc.Scaling == DXGI_MODE_SCALING_CENTERED)
			{
				return true;
			}

			return false;
		}
	}

	String D3D11_1AdapterInfo::name() const
	{
		return Unicode::FromWString(adapterDesc.Description);
	}

	D3D11_1Device::~D3D11_1Device()
	{

	}

	bool D3D11_1Device::init()
	{
		LOG_INFO(U"ℹ️ Enumerating D3D11 adapters");

		if (!loadLibraries())
		{
			return false;
		}

		m_adapterInfoList = getAdapterInfoList();
		LOG_INFO(U"ℹ️ {} adapters available"_fmt(m_adapterInfoList.size()));

		m_WARPFeatureLevel = getWARPFeatureLevel();
		LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_WARP] supports {}"_fmt(detail::ToString(m_WARPFeatureLevel)));

		m_REFFeatureLevel = getREFFeatureLevel();
		LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_REFERENCE] supports {}"_fmt(detail::ToString(m_REFFeatureLevel)));

		if (!createDevice(TargetD3DDevice::Hardware, unspecified, 0))
		{
			return false;
		}

		if (createDevice11_1())
		{
			LOG_INFO(U"ℹ️ Direct3D 11.1 device and context available");
		}

		return true;
	}

	ID3D11Device* D3D11_1Device::getDevice() const
	{
		return m_device.Get();
	}

	ID3D11DeviceContext* D3D11_1Device::getContext() const
	{
		return m_context.Get();
	}

	IDXGIAdapter* D3D11_1Device::getAdapter() const
	{
		return m_adapter.Get();
	}

	D3D_DRIVER_TYPE D3D11_1Device::getDeviceType() const
	{
		return m_deviceType;
	}

	D3D_FEATURE_LEVEL D3D11_1Device::featureLevel() const
	{
		return m_selectedFeatureLevel;
	}

	bool D3D11_1Device::supportD3D11_1Runtime() const
	{
		return m_d3d_11_1_runtimeSupprot;
	}

	DXGI_SAMPLE_DESC D3D11_1Device::getBestMSAA(const DXGI_FORMAT format, const uint32 maxSample)
	{
		const auto it = m_bestMSAAs.find(format);

		if (it != m_bestMSAAs.end())
		{
			return it->second;
		}

		DXGI_SAMPLE_DESC desc{ 1,0 };

		for (uint32 count = std::min<uint32>(D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT, maxSample); count > 0; count /= 2)
		{
			uint32 quality;

			if (SUCCEEDED(m_device->CheckMultisampleQualityLevels(format, count, &quality)))
			{
				if (quality > 0)
				{
					desc.Count = count;
					desc.Quality = quality - 1;

					m_bestMSAAs.emplace(format, desc);

					return desc;
				}
			}
		}

		m_bestMSAAs.emplace(format, desc);

		return desc;
	}

	bool D3D11_1Device::loadLibraries()
	{
		if (HMODULE moduleD3D11 = ::LoadLibraryExW(L"d3d11.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
		{
			LOG_INFO(U"🆗 Loaded `d3d11.dll`");

			if (m_pD3D11CreateDevice = FunctionPointer(moduleD3D11, "D3D11CreateDevice");
				m_pD3D11CreateDevice)
			{
				LOG_INFO(U"🆗 D3D11CreateDevice found");
			}
			else
			{
				LOG_FAIL(U"❌ D3D11CreateDevice not found");
				return false;
			}
		}
		else
		{
			LOG_FAIL(U"❌ Failed to load d3d11.dll");
			return false;
		}

		if (HMODULE moduleDXGI = ::LoadLibraryExW(L"dxgi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
		{
			LOG_INFO(U"🆗 Loaded `dxgi.dll`");

			if (m_pCreateDXGIFactory1 = FunctionPointer(moduleDXGI, "CreateDXGIFactory1");
				m_pCreateDXGIFactory1)
			{
				LOG_INFO(U"🆗 CreateDXGIFactory1 found");
			}
			else
			{
				LOG_FAIL(U"❌ CreateDXGIFactory1 not found");
				return false;
			}
		}
		else
		{
			LOG_FAIL(U"❌ Failed to load dxgi.dll");
			return false;
		}

		if (HMODULE moduleDXGIDebug = LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
		{
			LOG_INFO(U"🆗 Loaded `dxgidebug.dll`");

			if (m_pDXGIGetDebugInterface = FunctionPointer(moduleDXGIDebug, "DXGIGetDebugInterface");
				m_pDXGIGetDebugInterface)
			{
				LOG_INFO(U"🆗 DXGIGetDebugInterface found");
			}
			else
			{
				LOG_INFO(U"ℹ️ DXGIGetDebugInterface not found");
			}
		}
		else
		{
			LOG_INFO(U"ℹ️ dxgidebug.dll not found");
		}

		if (FAILED(m_pCreateDXGIFactory1(__uuidof(IDXGIFactory1), &m_pFactory)))
		{
			LOG_FAIL(U"❌ CreateDXGIFactory1() failed");
			return false;
		}
		else
		{
			LOG_INFO(U"🆗 CreateDXGIFactory1() succeeded");
		}

		return true;
	}

	Array<D3D11_1AdapterInfo> D3D11_1Device::getAdapterInfoList() const
	{
		Array<D3D11_1AdapterInfo> adapterInfoList;

		for (uint32 adapterIndex = 0; ; ++adapterIndex)
		{
			ComPtr<IDXGIAdapter> pAdapter;
			HRESULT hr = m_pFactory->EnumAdapters(adapterIndex, &pAdapter);

			// リストの最後で DXGIERR_NOT_FOUND が返る
			if (FAILED(hr))
			{
				break;
			}

			// Direct3D 11.1 ランタイムを使用可能かチェック
			bool d3d_11_1_runtimeSupprot = false;
			ComPtr<IDXGIAdapter2> pAdapter2;
			if (hr = pAdapter->QueryInterface(__uuidof(IDXGIAdapter2), &pAdapter2);
				SUCCEEDED(hr))
			{
				DXGI_ADAPTER_DESC2 desc;
				if (hr = pAdapter2->GetDesc2(&desc);
					(SUCCEEDED(hr) && (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)))
				{
					// Microsoft Basics Display Driver はスキップ
					LOG_INFO(U"ℹ️ IDXGIAdapter [{}] is Microsoft Basics Display Driver (skipped)"_fmt(adapterIndex));
					continue;
				}

				d3d_11_1_runtimeSupprot = true;
			}

			D3D11_1AdapterInfo adapterInfo;
			adapterInfo.pAdapter = pAdapter;
			adapterInfo.adapterIndex = adapterIndex;
			adapterInfo.d3d_11_1_runtimeSupprot = d3d_11_1_runtimeSupprot;
			pAdapter->GetDesc(&adapterInfo.adapterDesc);
			adapterInfo.vendor = (adapterInfo.adapterDesc.VendorId == 0x10DE) ? AdapterVendor::NVIDIA
				: (adapterInfo.adapterDesc.VendorId == 0x1002) ? AdapterVendor::AMD
				: (adapterInfo.adapterDesc.VendorId == 0x8086) ? AdapterVendor::Intel
				: (adapterInfo.adapterDesc.VendorId == 0x1414) ? AdapterVendor::Microsoft
				: AdapterVendor::Unknown;

			LOG_INFO(U"ℹ️ IDXGIAdapter [{}]: {} (supports Direct3D 11.{} runtime)"_fmt(
				adapterIndex,
				detail::ToString(adapterInfo.adapterDesc),
				d3d_11_1_runtimeSupprot ? 1 : 0
			));

			if (!getHardwareDevice(adapterInfo, D3D_FEATURE_LEVEL_10_0, unspecified))
			{
				LOG_FAIL(U"❌ - getHardwareDevice() failed");
				continue;
			}

			if (!enumerateOutputs(adapterInfo))
			{
				LOG_FAIL(U"❌ - enumerateOutputs() failed");
				continue;
			}

			if (adapterInfo.outputInfoList.isEmpty())
			{
				LOG_INFO(U"ℹ️ - adapterInfo.hardwareDevice.outputInfoList is empty");
			}

			adapterInfoList.push_back(adapterInfo);
		}

		return adapterInfoList;
	}

	bool D3D11_1Device::getHardwareDevice(D3D11_1AdapterInfo& adapterInfo, const D3D_FEATURE_LEVEL minimumFeatureLevel, const Optional<D3D_FEATURE_LEVEL>& forceFeatureLevel) const
	{
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

		HRESULT hr = m_pD3D11CreateDevice(adapterInfo.pAdapter.Get(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			0,
			FeatureLevels,
			static_cast<UINT>(std::size(FeatureLevels)),
			D3D11_SDK_VERSION,
			&pDevice,
			&adapterInfo.maxLevel,
			&pDeviceContext);
			
		if (hr == E_INVALIDARG)
		{
		# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4) 

			// DirectX 11.1 ランタイムは D3D_FEATURE_LEVEL_12_x を認識しないので、除外してやり直す
			hr = m_pD3D11CreateDevice(adapterInfo.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				0,
				&FeatureLevels[2],
				static_cast<UINT>(std::size(FeatureLevels) - 2),
				D3D11_SDK_VERSION,
				&pDevice,
				&adapterInfo.maxLevel,
				&pDeviceContext);

			if (hr == E_INVALIDARG)
			{
				// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
				hr = m_pD3D11CreateDevice(adapterInfo.pAdapter.Get(),
					D3D_DRIVER_TYPE_UNKNOWN,
					nullptr,
					0,
					&FeatureLevels[3],
					static_cast<UINT>(std::size(FeatureLevels) - 3),
					D3D11_SDK_VERSION,
					&pDevice,
					&adapterInfo.maxLevel,
					&pDeviceContext);
			}

		# else

			// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
			hr = m_pD3D11CreateDevice(adapterInfo.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				0,
				&FeatureLevels[1],
				static_cast<UINT>(std::size(FeatureLevels) - 1),
				D3D11_SDK_VERSION,
				&pDevice,
				&adapterInfo.maxLevel,
				&pDeviceContext);

		# endif
		}

		if (FAILED(hr))
		{
			LOG_FAIL(U"❌ - D3D11CreateDevice() failed");
			return false;
		}
		else if (adapterInfo.maxLevel < minimumFeatureLevel)
		{
			LOG_FAIL(U"❌ - adapterInfo.maxLevel ({}) does not meet minimumFeatureLevel requirments ({})"_fmt(
			detail::ToString(adapterInfo.maxLevel), detail::ToString(minimumFeatureLevel)));
			return false;
		}

		if (!forceFeatureLevel || forceFeatureLevel == adapterInfo.maxLevel)
		{
			adapterInfo.selectedLevel = adapterInfo.maxLevel;
		}
		else if (forceFeatureLevel > adapterInfo.maxLevel)
		{
			LOG_FAIL(U"❌ - adapterInfo.maxLevel ({}) does not meet forceFeatureLevel requirments ({})"_fmt(
				detail::ToString(adapterInfo.maxLevel), detail::ToString(forceFeatureLevel.value())));
			return false;
		}
		else
		{
			pDevice.Reset();
			pDeviceContext.Reset();

			D3D_FEATURE_LEVEL returnedFeatureLevel;
			hr = m_pD3D11CreateDevice(adapterInfo.pAdapter.Get(),
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
				adapterInfo.selectedLevel = forceFeatureLevel.value();
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
			adapterInfo.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = ho.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
		}

		LOG_INFO(U"ℹ️ - [D3D_DRIVER_TYPE_HARDWARE] selected: {} (max: {})"_fmt(
			detail::ToString(adapterInfo.selectedLevel), detail::ToString(adapterInfo.maxLevel)));
		return true;
	}

	bool D3D11_1Device::enumerateOutputs(D3D11_1AdapterInfo& adapterInfo) const
	{
		LOG_INFO(U"ℹ️ - Enumerating outputs");

		for (uint32 outputIndex = 0; ; ++outputIndex)
		{
			ComPtr<IDXGIOutput> pOutput;

			HRESULT hr = adapterInfo.pAdapter->EnumOutputs(outputIndex, &pOutput);

			if (DXGI_ERROR_NOT_FOUND == hr)
			{
				return true;
			}
			else if (FAILED(hr))
			{
				LOG_INFO(U"ℹ️ -- EnumOutputs({}) failed"_fmt(outputIndex));
				return false;
			}
			else
			{
				LOG_INFO(U"ℹ️ -- Output [{}]"_fmt(outputIndex));

				D3D11_1OutputInfo outputInfo;
				outputInfo.pOutput = pOutput;
				pOutput->GetDesc(&outputInfo.desc);

				enumerateDisplayModes(outputInfo);
				if (outputInfo.displayModeList.isEmpty())
				{
					LOG_INFO(U"ℹ️ -- outputInfo.displayModeList is empty");
					return false;
				}

				adapterInfo.outputInfoList.push_back(outputInfo);
			}
		}
	}

	bool D3D11_1Device::enumerateDisplayModes(D3D11_1OutputInfo& outputInfo) const
	{
		LOG_INFO(U"ℹ️ --- Enumerating display modes");

		HRESULT hr = S_OK;
		static constexpr DXGI_FORMAT adapterFormats[] =
		{
			DXGI_FORMAT_R8G8B8A8_UNORM,
			//DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			//DXGI_FORMAT_R16G16B16A16_FLOAT,
			//DXGI_FORMAT_R10G10B10A2_UNORM
		};

		constexpr DXGI_FORMAT RemoteMode = DXGI_FORMAT_R8G8B8A8_UNORM;

		for (const auto& adapterFormat : adapterFormats)
		{
			UINT numDescs = 512; // 多いと時間がかかる
			Array<DXGI_MODE_DESC> descs(numDescs);
			hr = outputInfo.pOutput->GetDisplayModeList(adapterFormat,
				DXGI_ENUM_MODES_SCALING,
				&numDescs,
				descs.data());

			if (DXGI_ERROR_NOT_FOUND == hr)
			{
				break;
			}
			else if ((MAKE_DXGI_HRESULT(34) == hr)
				&& (RemoteMode == adapterFormat))
			{
				LOG_INFO(U"ℹ️ ---- Remote session detected");

				if (::GetSystemMetrics(0x1000)) // リモートセッション
				{
					DEVMODE devMode;
					devMode.dmSize = sizeof(DEVMODE);
					if (::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode))
					{
						numDescs = 1;
						descs[0].Width				= devMode.dmPelsWidth;
						descs[0].Height				= devMode.dmPelsHeight;
						descs[0].Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
						descs[0].RefreshRate		= { 0, 0 };
						descs[0].ScanlineOrdering	= DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
						descs[0].Scaling			= DXGI_MODE_SCALING_CENTERED;
						hr = S_OK;
					}
				}
			}
			else if (DXGI_ERROR_MORE_DATA == hr)
			{
				// 512 以上の descs
				hr = outputInfo.pOutput->GetDisplayModeList(adapterFormat,
					DXGI_ENUM_MODES_SCALING,
					&numDescs,
					nullptr);

				if (FAILED(hr))
				{
					numDescs = 0;
					break;
				}

				descs.resize(numDescs);

				hr = outputInfo.pOutput->GetDisplayModeList(adapterFormat,
					DXGI_ENUM_MODES_SCALING,
					&numDescs,
					descs.data());

				if (FAILED(hr))
				{
					break;
				}
			}

			if (SUCCEEDED(hr))
			{
				descs.resize(numDescs);

				for (const auto& desc : descs)
				{
					if (detail::DisplayModeFilter(desc))
					{
						continue;
					}

					LOG_DEBUG(U"ℹ️ ---- {}"_fmt(detail::ToString(desc)));
					outputInfo.displayModeList.push_back(desc);
				}
			}
		}

		return SUCCEEDED(hr);
	}

	D3D_FEATURE_LEVEL D3D11_1Device::getWARPFeatureLevel() const
	{
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
		HRESULT hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
			0, 0, FeatureLevels, static_cast<UINT>(std::size(FeatureLevels)),
			D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);

		if (hr == E_INVALIDARG)
		{
		# if defined(SIV3D_USE_DIRECT3D11_3) || defined(SIV3D_USE_DIRECT3D11_4)

			// DirectX 11.1 ランタイムは D3D_FEATURE_LEVEL_12_x を認識しないので、除外してやり直す
			hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
				0, 0, &FeatureLevels[2], static_cast<UINT>(std::size(FeatureLevels) - 2),
				D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);

			if (hr == E_INVALIDARG)
			{
				// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
				hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
					0, 0, &FeatureLevels[3], static_cast<UINT>(std::size(FeatureLevels) - 3),
					D3D11_SDK_VERSION, &pDevice, &warpFeatureLevel, nullptr);
			}

		# else

			// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
			hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP,
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

	D3D_FEATURE_LEVEL D3D11_1Device::getREFFeatureLevel() const
	{
		D3D_FEATURE_LEVEL refFeatureLevel = D3D_FEATURE_LEVEL_10_1;

		static constexpr D3D_FEATURE_LEVEL FeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1
		};

		ComPtr<ID3D11Device> pDevice;
		HRESULT hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_REFERENCE,
			0, 0, FeatureLevels, static_cast<UINT>(std::size(FeatureLevels)),
			D3D11_SDK_VERSION, &pDevice, &refFeatureLevel, nullptr);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 ランタイムは D3D_FEATURE_LEVEL_11_1 を認識しないので、除外してやり直す
			hr = m_pD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_REFERENCE,
				0, 0, &FeatureLevels[1], static_cast<UINT>(std::size(FeatureLevels) - 1),
				D3D11_SDK_VERSION, &pDevice, &refFeatureLevel, nullptr);
		}

		if (FAILED(hr))
		{
			refFeatureLevel = D3D_FEATURE_LEVEL_10_1;
		}

		return refFeatureLevel;
	}

	bool D3D11_1Device::createDevice(TargetD3DDevice targetDevice, const Optional<size_t> targetAdapterIndex, uint32 deviceFlags)
	{
		if (m_adapterInfoList.isEmpty())
		{
			targetDevice = TargetD3DDevice::WARP;
		}

		if (targetDevice == TargetD3DDevice::Hardware
			|| targetDevice == TargetD3DDevice::Hardware_FavorIntegrated)
		{
			size_t selectedAdapterIndex = 0;

			if (targetAdapterIndex)
			{
				selectedAdapterIndex = std::min(targetAdapterIndex.value(), m_adapterInfoList.size() - 1);
			}
			else
			{
				if (targetDevice == TargetD3DDevice::Hardware)
				{
					size_t maxDedicatedMemory = 0;
					size_t maxDedicatedMemoryAdapterIndex = 0;

					for (size_t adapterIndex = 0; adapterIndex < m_adapterInfoList.size(); ++adapterIndex)
					{
						const size_t dedicatedMemory = m_adapterInfoList[adapterIndex].adapterDesc.DedicatedVideoMemory;

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
					for (size_t adapterIndex = 0; adapterIndex < m_adapterInfoList.size(); ++adapterIndex)
					{
						if (m_adapterInfoList[adapterIndex].vendor == AdapterVendor::Intel)
						{
							selectedAdapterIndex = adapterIndex;
							break;
						}
					}
				}
			}

			const auto& adapter = m_adapterInfoList[selectedAdapterIndex];
			LOG_INFO(U"ℹ️ selectedAdapterIndex: {} ({})"_fmt(selectedAdapterIndex, adapter.name()));

			if (SUCCEEDED(m_pD3D11CreateDevice(
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
				m_deviceType = D3D_DRIVER_TYPE_HARDWARE;
				m_d3d_11_1_runtimeSupprot = adapter.d3d_11_1_runtimeSupprot;
				m_adapter = adapter.pAdapter;

				LOG_INFO(U"✅ D3D11 device created. Driver type: Hardware ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
				return true;
			}
			else
			{
				if (SUCCEEDED(m_pD3D11CreateDevice(
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
					m_deviceType = D3D_DRIVER_TYPE_HARDWARE;
					m_d3d_11_1_runtimeSupprot = (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);
					
					LOG_INFO(U"✅ D3D11 device created. Driver type: Hardware ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
					return true;
				}

				targetDevice = TargetD3DDevice::WARP;
			}
		}

		if (targetDevice == TargetD3DDevice::WARP)
		{
			if (SUCCEEDED(m_pD3D11CreateDevice(
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
				m_deviceType = D3D_DRIVER_TYPE_WARP;
				m_d3d_11_1_runtimeSupprot = (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);
				
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
			if (SUCCEEDED(m_pD3D11CreateDevice(
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
				m_deviceType = D3D_DRIVER_TYPE_REFERENCE;
				m_d3d_11_1_runtimeSupprot = (m_selectedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);

				LOG_INFO(U"✅ D3D11 device created. Driver type: Reference ({0})"_fmt(detail::ToString(m_selectedFeatureLevel)));
				return true;
			}
		}

		return false;
	}

	bool D3D11_1Device::createDevice11_1()
	{
		HRESULT hr = m_device->QueryInterface(__uuidof(ID3D11Device1), &m_device1);
		
		if (SUCCEEDED(hr) && m_device1)
		{
			hr = m_context->QueryInterface(__uuidof(ID3D11DeviceContext1), &m_context1);

			if (SUCCEEDED(hr) && m_context1)
			{
				return true;
			}
		}

		return false;
	}
}

# endif
