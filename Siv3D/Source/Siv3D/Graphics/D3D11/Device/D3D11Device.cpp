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

# include "D3D11Device.hpp"
# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>
# include "../../../EngineUtility.hpp"

# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		enum class AdapterVendor
		{
			NVIDIA,
			AMD,
			Intel,
			Microsoft,
			Unknown,
		};

		struct Adapter
		{
			ComPtr<IDXGIAdapter> pAdapter;

			DXGI_ADAPTER_DESC desc;

			AdapterVendor vendor;

			uint32 outputCount;
		};

		static uint32 CountAdapterOutputs(ComPtr<IDXGIAdapter>& pAdapter)
		{
			for (uint32 count = 0;; ++count)
			{
				ComPtr<IDXGIOutput> pOutput;

				if (FAILED(pAdapter->EnumOutputs(count, &pOutput)))
				{
					return count;
				}
			}
		}

		static Array<Adapter> EnumAdapters()
		{
			HINSTANCE dxgi = ::LoadLibraryW(L"dxgi.dll");

			if (!dxgi)
			{
				return{};
			}

			decltype(CreateDXGIFactory1)* p_CreateDXGIFactory1 = FunctionPointer(dxgi, "CreateDXGIFactory1");

			if (!p_CreateDXGIFactory1)
			{
				return{};
			}

			ComPtr<IDXGIFactory1> pFactory;

			if (FAILED(p_CreateDXGIFactory1(__uuidof(IDXGIFactory1), &pFactory)))
			{
				return{};
			}

			Array<Adapter> adapters;

			for (uint32 index = 0;; ++index)
			{
				ComPtr<IDXGIAdapter> adapter;

				if (pFactory->EnumAdapters(index, &adapter) == DXGI_ERROR_NOT_FOUND)
				{
					break;
				}

				DXGI_ADAPTER_DESC desc;
				adapter->GetDesc(&desc);

				//LOG_INFO(L"[{}] {} (VRAM: {}, System: {}, Shared: {})"_fmt,
				//	index,
				//	desc.Description,
				//	FormatBytes(desc.DedicatedVideoMemory),
				//	FormatBytes(desc.DedicatedSystemMemory),
				//	FormatBytes(desc.SharedSystemMemory));

				const AdapterVendor vendor =
					(desc.VendorId == 0x10DE) ? AdapterVendor::NVIDIA
					: (desc.VendorId == 0x1002) ? AdapterVendor::AMD
					: (desc.VendorId == 0x8086) ? AdapterVendor::Intel
					: (desc.VendorId == 0x1414) ? AdapterVendor::Microsoft
					: AdapterVendor::Unknown;

				const uint32 outputCount = CountAdapterOutputs(adapter);

				adapters.push_back(detail::Adapter{ std::move(adapter), desc, vendor, outputCount });
			}

			std::stable_sort(adapters.begin(), adapters.end(), [](const Adapter& a, const Adapter& b)
			{
				return a.desc.DedicatedVideoMemory > b.desc.DedicatedVideoMemory;
			});

			::FreeLibrary(dxgi);

			return adapters;
		}

		static String ToString(const D3D_FEATURE_LEVEL featureLevel)
		{
			switch (featureLevel)
			{
			case D3D_FEATURE_LEVEL_11_0:
				return L"11_0";
			case D3D_FEATURE_LEVEL_10_1:
				return L"10_1";
			case D3D_FEATURE_LEVEL_10_0:
				return L"10_0";
			default:
				return L"UNKNOWN";
			}
		}
	}

	D3D11Device::~D3D11Device()
	{

	}

	bool D3D11Device::init()
	{
		m_d3d11 = ::LoadLibraryW(L"d3d11.dll");

		if (!m_d3d11)
		{
			LOG_FAIL(L"❌ Failed to load \"d3d11.dll\"");

			return false;
		}

		if (!initDevice())
		{
			return false;
		}

		ComPtr<IDXGIDevice1> pDXGI;

		if (FAILED(m_device.Get()->QueryInterface(__uuidof(IDXGIDevice1), &pDXGI)))
		{
			LOG_FAIL(L"❌ ID3D11Device::QueryInterface() failed");

			return false;
		}

		if (FAILED(pDXGI->GetAdapter(&m_adapter)))
		{
			LOG_FAIL(L"❌ IDXGIDevice1::GetAdapter() failed");

			return false;
		}

		DXGI_ADAPTER_DESC adapterDesc;

		if (SUCCEEDED(m_adapter->GetDesc(&adapterDesc)))
		{
			LOG_INFO(L"🆗 Graphics adapter: {0}"_fmt(adapterDesc.Description));
		}

		return true;
	}

	ID3D11Device* D3D11Device::getDevice() const
	{
		return m_device.Get();
	}

	ID3D11DeviceContext* D3D11Device::getContext() const
	{
		return m_context.Get();
	}

	IDXGIAdapter* D3D11Device::getAdapter() const
	{
		return m_adapter.Get();
	}

	D3D_DRIVER_TYPE D3D11Device::getDriverType() const
	{
		return m_driverType;
	}

	DXGI_SAMPLE_DESC D3D11Device::getBestMSAA(const DXGI_FORMAT format, const uint32 maxSample)
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
					//Log(L"MSAA x", count, L" (quality: ", quality, L")");

					m_bestMSAAs.emplace(format, desc);

					return desc;
				}
			}
		}

		m_bestMSAAs.emplace(format, desc);

		return desc;
	}

	bool D3D11Device::initDevice()
	{
		PFN_D3D11_CREATE_DEVICE p_D3D11CreateDevice = FunctionPointer(m_d3d11, "D3D11CreateDevice");

		if (!p_D3D11CreateDevice)
		{
			return false;
		}

		Array<detail::Adapter> adapters = detail::EnumAdapters();

		if (adapters.isEmpty())
		{
			return false;
		}

		LOG_INFO(L"Available graphics adapters:");

		for (const auto& adapter : adapters)
		{
			LOG_INFO(adapter.desc.Description);
		}

		const std::array<D3D_FEATURE_LEVEL, 3> featureLevels =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		Optional<size_t> adapterIndexFromConfig;
		const bool favor_iGPU = false;

		uint32 creationFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;

	# ifdef _DEBUG

		if (HINSTANCE D3D11_1SDKLayersLibrary = ::LoadLibraryW(L"D3D11_1SDKLayers.dll"))
		{
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

			::FreeLibrary(D3D11_1SDKLayersLibrary);

			LOG_INFO(L"🆗 D3D11 debug layer supported");
		}
		else
		{
			LOG_INFO(L"ℹ️ D3D11 debug layer not supported");
		}

	# endif

		if (!adapterIndexFromConfig && favor_iGPU)
		{
			for (uint32 i = 0; i < adapters.size(); ++i)
			{
				if (adapters[i].vendor == detail::AdapterVendor::Intel)
				{
					adapterIndexFromConfig = i;
					break;
				}
			}
		}

		if (adapterIndexFromConfig)
		{
			const size_t adapterIndex = std::min(adapterIndexFromConfig.value(), adapters.size() - 1);
			const auto& adapter = adapters[adapterIndex];

			if (SUCCEEDED(p_D3D11CreateDevice(
				adapter.pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				creationFlags,
				featureLevels.data(),
				UINT(featureLevels.size()),
				D3D11_SDK_VERSION,
				&m_device,
				&m_featureLevel,
				&m_context)))
			{
				if (adapter.vendor == detail::AdapterVendor::NVIDIA
					|| adapter.vendor == detail::AdapterVendor::AMD
					|| adapter.vendor == detail::AdapterVendor::Intel)
				{
					m_driverType = D3D_DRIVER_TYPE_HARDWARE;
					
					LOG_INFO(L"✅ D3D11 device created. Driver type: Hardware (feature level {0})"_fmt(detail::ToString(m_featureLevel)));
				}
				else
				{
					m_driverType = D3D_DRIVER_TYPE_UNKNOWN;

					LOG_INFO(L"✅ D3D11 device created. Driver type: Unknown (feature level {0})"_fmt(detail::ToString(m_featureLevel)));
				}

				return true;
			}
		}

		D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

		if (driverType == D3D_DRIVER_TYPE_HARDWARE)
		{
			if (SUCCEEDED(p_D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				creationFlags,
				featureLevels.data(),
				UINT(featureLevels.size()),
				D3D11_SDK_VERSION,
				&m_device,
				&m_featureLevel,
				&m_context)))
			{
				m_driverType = D3D_DRIVER_TYPE_HARDWARE;

				LOG_INFO(L"✅ D3D11 device created. Driver type: Hardware (feature level {0})"_fmt(detail::ToString(m_featureLevel)));

				return true;
			}
			else
			{
				driverType = D3D_DRIVER_TYPE_WARP;
			}
		}

		if (driverType == D3D_DRIVER_TYPE_WARP)
		{
			if (SUCCEEDED(p_D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP,
				nullptr,
				creationFlags,
				featureLevels.data(),
				UINT(featureLevels.size()),
				D3D11_SDK_VERSION,
				&m_device,
				&m_featureLevel,
				&m_context)))
			{
				m_driverType = D3D_DRIVER_TYPE_WARP;

				LOG_INFO(L"✅ D3D11 device created. Driver type: WARP (feature level {0})"_fmt(detail::ToString(m_featureLevel)));

				return true;
			}
			else
			{
				driverType = D3D_DRIVER_TYPE_REFERENCE;
			}
		}

		if (driverType == D3D_DRIVER_TYPE_REFERENCE)
		{
			if (SUCCEEDED(p_D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_REFERENCE,
				nullptr,
				creationFlags,
				featureLevels.data(),
				UINT(featureLevels.size()),
				D3D11_SDK_VERSION,
				&m_device,
				&m_featureLevel,
				&m_context)))
			{
				m_driverType = D3D_DRIVER_TYPE_REFERENCE;

				LOG_WARNING(L"✅⚠️ D3D11 device created. Driver type: Reference (feature level {0})"_fmt(detail::ToString(m_featureLevel)));

				return true;
			}
			else
			{
				LOG_FAIL(L"❌ Failed to create D3D11 device (Driver type: Reference)");

				return false;
			}
		}

		if (driverType == D3D_DRIVER_TYPE_NULL)
		{
			if (SUCCEEDED(p_D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_NULL,
				nullptr,
				creationFlags,
				featureLevels.data(),
				UINT(featureLevels.size()),
				D3D11_SDK_VERSION,
				&m_device,
				&m_featureLevel,
				&m_context)))
			{
				m_driverType = D3D_DRIVER_TYPE_NULL;

				LOG_WARNING(L"✅⚠️ D3D11 device created. Driver type: NULL (feature level {0})"_fmt(detail::ToString(m_featureLevel)));

				return true;
			}
			else
			{
				LOG_FAIL(L"❌ Failed to create D3D11 device (Driver type: NULL)");

				return false;
			}
		}

		return true;
	}
}

# endif
