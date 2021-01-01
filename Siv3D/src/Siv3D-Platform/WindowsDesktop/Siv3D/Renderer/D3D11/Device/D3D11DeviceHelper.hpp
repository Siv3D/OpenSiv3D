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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "D3D11Adapter.hpp"
# include "D3D11DeviceInfo.hpp"

namespace s3d::detail
{
	[[nodiscard]]
	AdapterVendor ToAdapterVendor(uint32 vendorID) noexcept;

	[[nodiscard]]
	String ToString(const DXGI_ADAPTER_DESC& desc);

	[[nodiscard]]
	StringView ToString(const D3D_FEATURE_LEVEL featureLevel) noexcept;

	[[nodiscard]]
	bool CheckHardwareDevice(D3D11Adapter& adapter, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice, const D3D_FEATURE_LEVEL minimumFeatureLevel, const Optional<D3D_FEATURE_LEVEL>& requestedFeatureLevel);

	[[nodiscard]]
	Array<D3D11Adapter> GetAdapters(IDXGIFactory2* pDXGIFactory2, PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice);

	[[nodiscard]]
	D3D_FEATURE_LEVEL GetWARPFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice);

	[[nodiscard]]
	D3D_FEATURE_LEVEL GetReferenceFeatureLevel(PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice);

	[[nodiscard]]
	size_t ChooseAdapterIndex(const Array<D3D11Adapter>& adapters, const bool favorIntegrated);

	[[nodiscard]]
	Optional<D3D11DeviceInfo> CreateDeviceHardware(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const D3D11Adapter& adapter,
		const size_t adapterIndex,
		const uint32 deviceFlags);

	[[nodiscard]]
	Optional<D3D11DeviceInfo> CreateDeviceWARP(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const uint32 deviceFlags,
		const D3D_FEATURE_LEVEL WARPFeatureLevel);

	[[nodiscard]]
	Optional<D3D11DeviceInfo> CreateDeviceReference(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const uint32 deviceFlags,
		const D3D_FEATURE_LEVEL referenceFeatureLevel);

	[[nodiscard]]
	Optional<D3D11DeviceInfo> CreateDevice(
		PFN_D3D11_CREATE_DEVICE pD3D11CreateDevice,
		const Array<D3D11Adapter>& adapters,
		EngineOption::D3D11Driver driver,
		Optional<size_t> requestedAdapterIndex,
		const uint32 deviceFlags,
		const D3D_FEATURE_LEVEL WARPFeatureLevel,
		const D3D_FEATURE_LEVEL ReferenceFeatureLevel);
}
