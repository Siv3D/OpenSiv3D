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
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/ByteArray.hpp>

namespace s3d
{
	class PixelShader_D3D11
	{
	private:

		ByteArray m_binary;

		ComPtr<ID3D11PixelShader> m_shader;

		bool m_initialized = false;

	public:

		struct Null {};

		PixelShader_D3D11() = default;

		PixelShader_D3D11(Null);

		PixelShader_D3D11(ByteArray&& binary, ID3D11Device* device);

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		ID3D11PixelShader* getShader();

		ByteArrayView getView() const;
	};
}
