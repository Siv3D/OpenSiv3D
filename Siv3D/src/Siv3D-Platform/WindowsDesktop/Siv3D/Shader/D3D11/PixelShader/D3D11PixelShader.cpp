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

# include "D3D11PixelShader.hpp"

namespace s3d
{
	D3D11PixelShader::D3D11PixelShader(Null)
		: m_initialized(true) {}

	D3D11PixelShader::D3D11PixelShader(Blob&& binary, ID3D11Device* device)
		: m_binary(std::move(binary))
	{
		if (FAILED(device->CreatePixelShader(m_binary.data(), static_cast<size_t>(m_binary.size()), nullptr, &m_shader)))
		{
			return;
		}

		m_initialized = true;
	}

	bool D3D11PixelShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	ID3D11PixelShader* D3D11PixelShader::getShader() const
	{
		return m_shader.Get();
	}

	const Blob& D3D11PixelShader::getBinary() const noexcept
	{
		return m_binary;
	}
}
