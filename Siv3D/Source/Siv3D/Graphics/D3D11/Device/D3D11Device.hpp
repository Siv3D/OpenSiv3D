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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/HashMap.hpp>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>

namespace s3d
{
	class D3D11Device
	{
	private:

		HINSTANCE m_d3d11 = nullptr;

		ComPtr<ID3D11Device> m_device;

		ComPtr<ID3D11DeviceContext> m_context;

		ComPtr<IDXGIAdapter> m_adapter;

		D3D_FEATURE_LEVEL m_featureLevel;

		D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_UNKNOWN;

		HashMap<DXGI_FORMAT, DXGI_SAMPLE_DESC> m_bestMSAAs;

		bool initDevice();

	public:

		~D3D11Device();

		bool init();

		ID3D11Device* getDevice() const;

		ID3D11DeviceContext* getContext() const;

		IDXGIAdapter* getAdapter() const;

		D3D_DRIVER_TYPE getDriverType() const;

		DXGI_SAMPLE_DESC getBestMSAA(DXGI_FORMAT format);
	};
}

# endif
