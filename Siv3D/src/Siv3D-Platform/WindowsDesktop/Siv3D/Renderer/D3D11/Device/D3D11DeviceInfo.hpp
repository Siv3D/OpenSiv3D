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
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	struct D3D11DeviceInfo
	{
		Optional<size_t> adapterIndex;

		D3D_DRIVER_TYPE deviceType		= D3D_DRIVER_TYPE_UNKNOWN;

		D3D_FEATURE_LEVEL featureLevel	= D3D_FEATURE_LEVEL_9_1;

		bool d3d11_1_runtimeSupport		= false;

		ComPtr<ID3D11Device> device;

		ComPtr<ID3D11DeviceContext> context;
	};
}
