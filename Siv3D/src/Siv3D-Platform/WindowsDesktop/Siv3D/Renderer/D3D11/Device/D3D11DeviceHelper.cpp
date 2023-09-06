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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Unspecified.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>
# include "D3D11DeviceHelper.hpp"

namespace s3d::detail
{
	AdapterVendor ToAdapterVendor(const uint32 vendorID) noexcept
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

	String ToString(const DXGI_ADAPTER_DESC& desc)
	{
		return U"{} (Dedicated GPU memory: {}, System: {}, Shared: {})"_fmt(
			Unicode::FromWstring(desc.Description),
			FormatDataSize(desc.DedicatedVideoMemory),
			FormatDataSize(desc.DedicatedSystemMemory),
			FormatDataSize(desc.SharedSystemMemory));
	}

	StringView ToString(const D3D_FEATURE_LEVEL featureLevel) noexcept
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

	bool CheckHardwareDevice(D3D11Adapter& adapter, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, const D3D_FEATURE_LEVEL minimumFeatureLevel, const Optional<D3D_FEATURE_LEVEL>& requestedFeatureLevel)
	{
		LOG_SCOPED_TRACE(U"detail::CheckHardwareDevice()");

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

		LOG_TRACE(U"D3D11CreateDevice()");

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

			LOG_TRACE(U"D3D11CreateDevice()");

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
				LOG_TRACE(U"D3D11CreateDevice()");

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

		if (!requestedFeatureLevel || (requestedFeatureLevel == adapter.maxLevel))
		{
			adapter.selectedLevel = adapter.maxLevel;
		}
		else if (requestedFeatureLevel > adapter.maxLevel)
		{
			LOG_FAIL(U"❌ - adapterInfo.maxLevel ({}) does not meet requestedFeatureLevel requirments ({})"_fmt(
				detail::ToString(adapter.maxLevel), detail::ToString(*requestedFeatureLevel)));
			return false;
		}
		else
		{
			pDevice.Reset();
			pDeviceContext.Reset();

			LOG_TRACE(U"D3D11CreateDevice()");

			D3D_FEATURE_LEVEL returnedFeatureLevel;
			hr = pD3D11CreateDevice(adapter.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				0,
				&requestedFeatureLevel.value(),
				1,
				D3D11_SDK_VERSION,
				&pDevice,
				&returnedFeatureLevel,
				&pDeviceContext);

			if (SUCCEEDED(hr) && (returnedFeatureLevel == requestedFeatureLevel))
			{
				adapter.selectedLevel = *requestedFeatureLevel;
			}
			else
			{
				LOG_FAIL(U"❌ - D3D11CreateDevice() failed with specified requestedFeatureLevel {}"_fmt(
					detail::ToString(requestedFeatureLevel.value())));
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

	Array<D3D11Adapter> GetAdapters(IDXGIFactory2* pDXGIFactory2, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
	{
		LOG_SCOPED_TRACE(U"detail::GetAdapters()");

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
			bool d3d11_1_runtimeSupport = false;
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

				d3d11_1_runtimeSupport = true;
			}

			DXGI_ADAPTER_DESC adapterDesc;
			pAdapter->GetDesc(&adapterDesc);

			D3D11Adapter adapter =
			{
				.pAdapter					= pAdapter,
				.adapterIndex				= adapterIndex,
				.name						= Unicode::FromWstring(adapterDesc.Description),
				.adapterDesc				= adapterDesc,
				.vendor						= ToAdapterVendor(adapter.adapterDesc.VendorId),
				.d3d11_1_runtimeSupport		= d3d11_1_runtimeSupport,
			};

			LOG_INFO(U"ℹ️ IDXGIAdapter [{}]: {} (supports Direct3D 11.{} runtime)"_fmt(
				adapterIndex,
				detail::ToString(adapter.adapterDesc),
				(d3d11_1_runtimeSupport ? 1 : 0)
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

	Array<D3D11Adapter> GetAdaptersFast(IDXGIFactory2* pDXGIFactory2, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, const AdapterCache& cache)
	{
		LOG_SCOPED_TRACE(U"detail::GetAdaptersFast()");

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

			DXGI_ADAPTER_DESC adapterDesc;
			pAdapter->GetDesc(&adapterDesc);

			// キャッシュされたアダプターと一致したらこれ以上調べない
			if ((std::memcmp(&adapterDesc.AdapterLuid, &cache.luid, sizeof(LUID)) == 0)
				&& (adapterDesc.VendorId == cache.vendorId)
				&& (adapterDesc.DeviceId == cache.deviceId)
				&& (adapterDesc.SubSysId == cache.subSysId)
				&& (adapterDesc.Revision == cache.revision))
			{
				LOG_INFO(U"ℹ️ Cached adapter info found");

				D3D11Adapter adapter =
				{
					.pAdapter		= pAdapter,
					.adapterIndex	= adapterIndex,
					.name			= Unicode::FromWstring(adapterDesc.Description),
					.adapterDesc	= adapterDesc,
					.vendor			= ToAdapterVendor(adapter.adapterDesc.VendorId),
					.maxLevel		= cache.maxLevel,
					.selectedLevel	= cache.selectedLevel,
					.d3d11_1_runtimeSupport = cache.d3d11_1_runtimeSupport,
					.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = cache.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x
				};

				LOG_INFO(U"ℹ️ IDXGIAdapter [{}]: {} (supports Direct3D 11.{} runtime)"_fmt(
					adapterIndex,
					detail::ToString(adapter.adapterDesc),
					(adapter.d3d11_1_runtimeSupport ? 1 : 0)
				));

				adapters.push_back(adapter);
				break;
			}

			// Direct3D 11.1 ランタイムを使用可能かチェック
			bool d3d11_1_runtimeSupport = false;
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

				d3d11_1_runtimeSupport = true;
			}

			D3D11Adapter adapter =
			{
				.pAdapter = pAdapter,
				.adapterIndex = adapterIndex,
				.name = Unicode::FromWstring(adapterDesc.Description),
				.adapterDesc = adapterDesc,
				.vendor = ToAdapterVendor(adapter.adapterDesc.VendorId),
				.d3d11_1_runtimeSupport = d3d11_1_runtimeSupport,
			};

			LOG_INFO(U"ℹ️ IDXGIAdapter [{}]: {} (supports Direct3D 11.{} runtime)"_fmt(
				adapterIndex,
				detail::ToString(adapter.adapterDesc),
				(d3d11_1_runtimeSupport ? 1 : 0)
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

	D3D_FEATURE_LEVEL GetWARPFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
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

	D3D_FEATURE_LEVEL GetReferenceFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice)
	{
		LOG_TRACE(U"GetReferenceFeatureLevel()");

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

	size_t ChooseAdapterIndex(const Array<D3D11Adapter>& adapters, const bool favorIntegrated)
	{
		if (favorIntegrated)
		{
			size_t selectedAdapterIndex = 0;

			for (size_t adapterIndex = 0; adapterIndex < adapters.size(); ++adapterIndex)
			{
				selectedAdapterIndex = adapterIndex;

				if (adapters[adapterIndex].vendor == AdapterVendor::Intel)
				{
					break;
				}
			}

			return selectedAdapterIndex;
		}
		else
		{
			size_t selectedAdapterIndex = 0;
			size_t maxDedicatedMemory = 0;

			for (size_t adapterIndex = 0; adapterIndex < adapters.size(); ++adapterIndex)
			{
				const size_t dedicatedMemory = adapters[adapterIndex].adapterDesc.DedicatedVideoMemory;

				if (maxDedicatedMemory < dedicatedMemory)
				{
					maxDedicatedMemory = dedicatedMemory;
					selectedAdapterIndex = adapterIndex;
				}
			}

			return selectedAdapterIndex;
		}
	}

	Optional<D3D11DeviceInfo> CreateDeviceHardware(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const D3D11Adapter& adapter,
		const size_t adapterIndex,
		const uint32 deviceFlags)
	{
		D3D_FEATURE_LEVEL featureLevel;
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		if (SUCCEEDED(pD3D11CreateDevice(
			adapter.pAdapter.Get(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			deviceFlags,
			&adapter.selectedLevel,
			1,
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context)))
		{
			return D3D11DeviceInfo
			{
				.adapterIndex			= adapterIndex,
				.deviceType				= D3D_DRIVER_TYPE_HARDWARE,
				.featureLevel			= featureLevel,
				.d3d11_1_runtimeSupport	= adapter.d3d11_1_runtimeSupport,
				.device					= device,
				.context				= context,
			};
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
				&device,
				&featureLevel,
				&context)))
			{
				return D3D11DeviceInfo
				{
					.adapterIndex			= adapterIndex,
					.deviceType				= D3D_DRIVER_TYPE_HARDWARE,
					.featureLevel			= featureLevel,
					.d3d11_1_runtimeSupport	= (featureLevel >= D3D_FEATURE_LEVEL_11_1),
					.device					= device,
					.context				= context,
				};
			}
		}

		return none;
	}

	Optional<D3D11DeviceInfo> CreateDeviceWARP(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const uint32 deviceFlags,
		const D3D_FEATURE_LEVEL WARPFeatureLevel)
	{
		D3D_FEATURE_LEVEL featureLevel;
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		if (SUCCEEDED(pD3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_WARP,
			nullptr,
			deviceFlags,
			&WARPFeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context)))
		{
			return D3D11DeviceInfo
			{
				.adapterIndex			= none,
				.deviceType				= D3D_DRIVER_TYPE_WARP,
				.featureLevel			= featureLevel,
				.d3d11_1_runtimeSupport	= (featureLevel >= D3D_FEATURE_LEVEL_11_1),
				.device					= device,
				.context				= context,
			};
		}

		return none;
	}

	Optional<D3D11DeviceInfo> CreateDeviceReference(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const uint32 deviceFlags,
		const D3D_FEATURE_LEVEL referenceFeatureLevel)
	{
		D3D_FEATURE_LEVEL featureLevel;
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		if (SUCCEEDED(pD3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_REFERENCE,
			nullptr,
			deviceFlags,
			&referenceFeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context)))
		{
			return D3D11DeviceInfo
			{
				.adapterIndex			= none,
				.deviceType				= D3D_DRIVER_TYPE_REFERENCE,
				.featureLevel			= featureLevel,
				.d3d11_1_runtimeSupport	= (featureLevel >= D3D_FEATURE_LEVEL_11_1),
				.device					= device,
				.context				= context,
			};
		}

		return none;
	}

	Optional<D3D11DeviceInfo> CreateDevice(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const Array<D3D11Adapter>& adapters,
		EngineOption::D3D11Driver driver,
		Optional<size_t> requestedAdapterIndex,
		const uint32 deviceFlags)
	{
		LOG_SCOPED_TRACE(U"detail::CreateDevice()");

		// adapterIndex の範囲チェック
		if (requestedAdapterIndex >= adapters.size())
		{
			LOG_FAIL(U"❌ requestedAdapterIndex >= adapters.size()");
			return none;
		}

		// ハードウェアアダプタが見つからない場合は WARP にフォールバック
		if (adapters.isEmpty())
		{
			LOG_WARNING(U"ℹ️ Adapter not found. Fallback to WARP");
			driver = EngineOption::D3D11Driver::WARP;
		}

		if ((driver == EngineOption::D3D11Driver::Hardware)
			|| (driver == EngineOption::D3D11Driver::Hardware_FavorIntegrated))
		{
			size_t targetAdapterIndex;

			if (requestedAdapterIndex)
			{
				targetAdapterIndex = *requestedAdapterIndex;
			}
			else
			{
				const bool favorIntegrated = (driver == EngineOption::D3D11Driver::Hardware_FavorIntegrated);
				targetAdapterIndex = ChooseAdapterIndex(adapters, favorIntegrated);
			}

			const auto& adapter = adapters[targetAdapterIndex];
			LOG_INFO(U"ℹ️ targetAdapterIndex: {} ({})"_fmt(targetAdapterIndex, adapter.name));

			if (const auto deviceInfo = CreateDeviceHardware(pD3D11CreateDevice,
				adapter, targetAdapterIndex, deviceFlags))
			{
				LOG_INFO(U"✅ D3D11 device created. Driver type: Hardware ({0}) ({1})"_fmt(
					adapter.name, detail::ToString(deviceInfo->featureLevel)));

				// 次回実行時のために、選択したアダプターの情報を保存
				if (driver == EngineOption::D3D11Driver::Hardware)
				{
					const AdapterCache cache
					{
						.luid = adapter.adapterDesc.AdapterLuid,
						.vendorId = adapter.adapterDesc.VendorId,
						.deviceId = adapter.adapterDesc.DeviceId,
						.subSysId = adapter.adapterDesc.SubSysId,
						.revision = adapter.adapterDesc.Revision,
						.maxLevel = adapter.maxLevel,
						.selectedLevel = adapter.selectedLevel,
						.d3d11_1_runtimeSupport = adapter.d3d11_1_runtimeSupport,
						.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = adapter.computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x,
					};

					SaveAdapterCache(cache);
				}

				return deviceInfo;
			}

			LOG_WARNING(U"ℹ️ Failed to create device from hardware. Fallback to WARP");
			driver = EngineOption::D3D11Driver::WARP;
		}

		if (driver == EngineOption::D3D11Driver::WARP)
		{
			// WARP ドライバの feature level を取得
			const D3D_FEATURE_LEVEL warpFeatureLevel = detail::GetWARPFeatureLevel(pD3D11CreateDevice);
			LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_WARP] supports {}"_fmt(detail::ToString(warpFeatureLevel)));

			if (const auto deviceInfo = CreateDeviceWARP(pD3D11CreateDevice,
				deviceFlags, warpFeatureLevel))
			{
				LOG_INFO(U"✅ D3D11 device created. Driver type: WARP ({0})"_fmt(detail::ToString(deviceInfo->featureLevel)));
				return deviceInfo;
			}

			LOG_WARNING(U"ℹ️ Failed to create WARP driver. Fallback to the reference driver");
		}

		{
			// Reference ドライバの feature level を取得
			const D3D_FEATURE_LEVEL referenceFeatureLevel = detail::GetReferenceFeatureLevel(pD3D11CreateDevice);
			LOG_INFO(U"ℹ️ [D3D_DRIVER_TYPE_REFERENCE] supports {}"_fmt(detail::ToString(referenceFeatureLevel)));

			if (const auto deviceInfo = CreateDeviceReference(pD3D11CreateDevice,
				deviceFlags, referenceFeatureLevel))
			{
				LOG_INFO(U"✅ D3D11 device created. Driver type: Reference ({0})"_fmt(detail::ToString(deviceInfo->featureLevel)));
				return deviceInfo;
			}
		}

		return none;
	}

	void SaveAdapterCache(const AdapterCache& cache)
	{
		LOG_SCOPED_TRACE(U"detail::SaveAdapterCache()");

		const FilePath adapterCacheFile = CacheDirectory::Engine() + U"gpu/adapter.cache";

		BinaryWriter{ adapterCacheFile }.write(cache);
	}

	Optional<AdapterCache> LoadAdapterCache()
	{
		LOG_SCOPED_TRACE(U"detail::LoadAdapterCache()");

		const FilePath adapterCacheFile = CacheDirectory::Engine() + U"gpu/adapter.cache";

		BinaryReader reader{ adapterCacheFile };

		if (not reader)
		{
			return none;
		}

		if (AdapterCache cache{}; reader.read(cache))
		{
			return cache;
		}

		return none;
	}
}
