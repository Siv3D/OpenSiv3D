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
	enum class AdapterVendor
	{
		NVIDIA,

		AMD,

		Intel,

		Microsoft,

		Unknown,
	};

	struct D3D11Adapter
	{
		ComPtr<IDXGIAdapter> pAdapter;

		uint32 adapterIndex				= 0;

		String name;

		DXGI_ADAPTER_DESC adapterDesc	= {};

		AdapterVendor vendor			= AdapterVendor::Unknown;

		D3D_FEATURE_LEVEL maxLevel		= D3D_FEATURE_LEVEL_9_1;

		D3D_FEATURE_LEVEL selectedLevel	= D3D_FEATURE_LEVEL_9_1;

		bool d3d11_1_runtimeSupport		= false;

		bool computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x = false;
	};
}
