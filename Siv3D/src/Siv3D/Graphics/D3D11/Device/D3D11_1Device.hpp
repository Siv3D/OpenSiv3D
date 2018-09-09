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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <d3d11_1.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Graphics.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	enum class AdapterVendor
	{
		NVIDIA,

		AMD,

		Intel,

		Microsoft,

		Unknown,
	};

	enum class TargetD3DDevice
	{
		Hardware,

		Hardware_FavorIntegrated,

		WARP,

		Reference
	};

	struct D3D11_1OutputInfo
	{
		ComPtr<IDXGIOutput> pOutput;

		DXGI_OUTPUT_DESC desc;

		Array<DXGI_MODE_DESC> displayModeList; // 対応する D3DDISPLAYMODE 一覧
	};

	struct D3D11_1AdapterInfo
	{
		ComPtr<IDXGIAdapter> pAdapter;

		uint32 adapterIndex = 0;

		DXGI_ADAPTER_DESC adapterDesc = {};

		AdapterVendor vendor = AdapterVendor::Unknown;

		D3D_FEATURE_LEVEL maxLevel = D3D_FEATURE_LEVEL_9_1;

		D3D_FEATURE_LEVEL selectedLevel = D3D_FEATURE_LEVEL_9_1;

		bool d3d_11_1_runtimeSupprot = false;

		bool computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = false;

		Array<D3D11_1OutputInfo> outputInfoList;

		String name() const;
	};

	class D3D11_1Device
	{
	private:

		PFN_D3D11_CREATE_DEVICE m_pD3D11CreateDevice = nullptr;

		decltype(CreateDXGIFactory1)* m_pCreateDXGIFactory1 = nullptr;

		using t_DXGIGetDebugInterface = HRESULT(WINAPI*)(REFIID, void **);
		t_DXGIGetDebugInterface* m_pDXGIGetDebugInterface = nullptr;

		ComPtr<IDXGIFactory1> m_DXGIFactory;

		Array<D3D11_1AdapterInfo> m_adapterInfoList;

		D3D_FEATURE_LEVEL m_WARPFeatureLevel = D3D_FEATURE_LEVEL_10_1;

		D3D_FEATURE_LEVEL m_REFFeatureLevel = D3D_FEATURE_LEVEL_10_1;

		Optional<size_t> m_selectedAdapterIndex;

		D3D_DRIVER_TYPE m_deviceType = D3D_DRIVER_TYPE_UNKNOWN;

		D3D_FEATURE_LEVEL m_selectedFeatureLevel = D3D_FEATURE_LEVEL_10_0;

		bool m_d3d_11_1_runtimeSupprot = false;

		ComPtr<IDXGIAdapter> m_adapter;

		ComPtr<ID3D11Device> m_device;

		ComPtr<ID3D11DeviceContext> m_context;

		ComPtr<ID3D11Device1> m_device1;

		ComPtr<ID3D11DeviceContext1> m_context1;

		HashTable<DXGI_FORMAT, DXGI_SAMPLE_DESC> m_bestMSAAs;

		Array<DisplayOutput> m_displayOutputs;

		bool loadLibraries();

		Array<D3D11_1AdapterInfo> getAdapterInfoList() const;

		bool getHardwareDevice(D3D11_1AdapterInfo& adapterInfo, D3D_FEATURE_LEVEL minimumFeatureLevel, const Optional<D3D_FEATURE_LEVEL>& forceFeatureLevel) const;

		bool enumerateOutputs(D3D11_1AdapterInfo& adapterInfo) const;

		bool enumerateDisplayModes(D3D11_1OutputInfo& outputInfo) const;

		D3D_FEATURE_LEVEL getWARPFeatureLevel() const;

		D3D_FEATURE_LEVEL getREFFeatureLevel() const;

		bool createDevice(TargetD3DDevice targetDevice, const Optional<size_t> targetAdapterIndex, uint32 deviceFlags);

		bool createDevice11_1();

		void generateDisplayOutputs();

	public:

		~D3D11_1Device();

		bool init();

		IDXGIFactory1* getDXGIFactory() const;

		ID3D11Device* getDevice() const;

		ID3D11DeviceContext* getContext() const;

		IDXGIAdapter* getAdapter() const;

		D3D_DRIVER_TYPE getDeviceType() const;

		D3D_FEATURE_LEVEL featureLevel() const;

		bool supportD3D11_1Runtime() const;

		DXGI_SAMPLE_DESC getBestMSAA(DXGI_FORMAT format, uint32 maxSample);

		const Array<DisplayOutput>& getDisplayOutputs() const;

		// ディスプレイの設定の中でユーザー設定に最も近いものを取得
		Optional<std::tuple<DXGI_MODE_DESC, ComPtr<IDXGIOutput>, size_t>> getBestFullScreenMode(const Size& size, size_t displayIndex, double refreshRateHz) const;
	};
}

# endif
