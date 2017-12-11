﻿//-----------------------------------------------
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

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/ByteArray.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	class VertexShader_D3D11
	{
	private:

		ByteArray m_binary;

		ComPtr<ID3D11VertexShader> m_shader;

		bool m_initialized = false;

	public:

		struct Null {};

		VertexShader_D3D11() = default;

		VertexShader_D3D11(Null);

		VertexShader_D3D11(ByteArray&& binary, ID3D11Device* device);

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		ID3D11VertexShader* getShader();

		ByteArrayView getView() const;
	};
}

# endif
