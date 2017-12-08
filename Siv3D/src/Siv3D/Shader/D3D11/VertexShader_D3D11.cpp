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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "VertexShader_D3D11.hpp"

namespace s3d
{
	VertexShader_D3D11::VertexShader_D3D11(Null)
	{
		m_initialized = true;
	}

	VertexShader_D3D11::VertexShader_D3D11(ByteArray&& binary, ID3D11Device* const device)
		: m_binary(std::move(binary))
	{
		if (FAILED(device->CreateVertexShader(m_binary.data(), static_cast<size_t>(m_binary.size()), nullptr, &m_shader)))
		{
			return;
		}

		m_initialized = true;
	}

	ID3D11VertexShader* VertexShader_D3D11::getShader()
	{
		return m_shader.Get();
	}

	ByteArrayView VertexShader_D3D11::getView() const
	{
		return m_binary.view();
	}
}

# endif
