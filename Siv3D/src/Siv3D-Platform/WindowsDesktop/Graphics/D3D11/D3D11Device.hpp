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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <d3d11_1.h>
# include <dxgi1_5.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>

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

	struct D3D11Adapter
	{
		ComPtr<IDXGIAdapter> pAdapter;
		uint32 adapterIndex = 0;

		bool d3d11_1_runtimeSupprot = false;
		DXGI_ADAPTER_DESC adapterDesc = {};
		AdapterVendor vendor = AdapterVendor::Unknown;

		D3D_FEATURE_LEVEL maxLevel = D3D_FEATURE_LEVEL_9_1;
		D3D_FEATURE_LEVEL selectedLevel = D3D_FEATURE_LEVEL_9_1;
		bool computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = false;

		String name() const;
	};

	class D3D11Device
	{
	private:

		ComPtr<IDXGIFactory2> m_DXGIFactory2;
		ComPtr<IDXGIFactory5> m_DXGIFactory5;

		Array<D3D11Adapter> m_adapters;
		D3D_FEATURE_LEVEL m_WARPFeatureLevel = D3D_FEATURE_LEVEL_10_1;
		D3D_FEATURE_LEVEL m_REFFeatureLevel = D3D_FEATURE_LEVEL_10_1;

		Optional<size_t> m_selectedAdapterIndex;
		D3D_DRIVER_TYPE m_deviceType = D3D_DRIVER_TYPE_UNKNOWN;
		D3D_FEATURE_LEVEL m_selectedFeatureLevel = D3D_FEATURE_LEVEL_10_0;
		bool m_d3d11_1_runtimeSupprot = false;

		ComPtr<IDXGIAdapter> m_adapter;
		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;

		bool createDevice(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, TargetD3DDevice targetDevice, const Optional<size_t> targetAdapterIndex, uint32 deviceFlags);

	public:

		D3D11Device();

		~D3D11Device();

		IDXGIFactory2* getDXGIFactory2() const;

		IDXGIFactory5* getDXGIFactory5() const;

		ID3D11Device* getDevice() const;

		ID3D11DeviceContext* getContext() const;

		bool hasDXGI_1_4() const;
	};
}
