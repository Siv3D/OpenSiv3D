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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "D3D11Adapter.hpp"
# include "D3D11DeviceInfo.hpp"

namespace s3d
{
	class D3D11Device
	{
	private:

		bool m_hasDebugLayer = false;

		PFN_D3D11_CREATE_DEVICE m_pD3D11CreateDevice = nullptr;

		ComPtr<IDXGIFactory2> m_DXGIFactory2;
		
		ComPtr<IDXGIFactory5> m_DXGIFactory5;

		Array<D3D11Adapter> m_adapters;

		D3D11DeviceInfo m_deviceInfo;

	public:

		D3D11Device();

		~D3D11Device();

		void init();

		[[nodiscard]]
		IDXGIFactory2* getDXGIFactory2() const noexcept;

		[[nodiscard]]
		IDXGIFactory5* getDXGIFactory5() const noexcept;

		[[nodiscard]]
		ID3D11Device* getDevice() const noexcept;

		[[nodiscard]]
		ComPtr<ID3D11Device> getDeviceComPtr() const noexcept;

		[[nodiscard]]
		ID3D11DeviceContext* getContext() const noexcept;

		[[nodiscard]]
		bool hasDXGI_1_4() const noexcept;
	};
}
