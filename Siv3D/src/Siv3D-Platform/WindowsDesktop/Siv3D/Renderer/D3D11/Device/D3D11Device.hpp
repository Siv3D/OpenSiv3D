﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

		ComPtr<IDXGIFactory2> m_DXGIFactory2;
		
		ComPtr<IDXGIFactory5> m_DXGIFactory5;

		Array<D3D11Adapter> m_adapters;
		
		D3D_FEATURE_LEVEL m_WARPFeatureLevel = D3D_FEATURE_LEVEL_10_1;
		
		D3D_FEATURE_LEVEL m_referenceFeatureLevel = D3D_FEATURE_LEVEL_10_1;

		D3D11DeviceInfo m_deviceInfo;

	public:

		D3D11Device();

		~D3D11Device();

		[[nodiscard]]
		IDXGIFactory2* getDXGIFactory2() const noexcept;

		[[nodiscard]]
		IDXGIFactory5* getDXGIFactory5() const noexcept;

		[[nodiscard]]
		ID3D11Device* getDevice() const noexcept;

		[[nodiscard]]
		ID3D11DeviceContext* getContext() const noexcept;

		[[nodiscard]]
		bool hasDXGI_1_4() const noexcept;
	};
}
