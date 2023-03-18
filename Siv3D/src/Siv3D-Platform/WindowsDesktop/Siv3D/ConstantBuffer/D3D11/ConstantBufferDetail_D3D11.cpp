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

# include "ConstantBufferDetail_D3D11.hpp"
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	ConstantBufferDetail_D3D11::ConstantBufferDetail_D3D11(const size_t size)
		: m_bufferSize{ size }
	{
		// do nothing
	}

	bool ConstantBufferDetail_D3D11::update(const void* const data, const size_t size)
	{
		if (not m_buffer)
		{
			init();
		}

		D3D11_MAPPED_SUBRESOURCE mapped;

		if (FAILED(m_context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
		{
			return false;
		}

		if (void* const dst = mapped.pData)
		{
			std::memcpy(dst, data, size);

			m_context->Unmap(m_buffer.Get(), 0);
		}

		return true;
	}

	ID3D11Buffer* const* ConstantBufferDetail_D3D11::getBufferPtr() const
	{
		if (not m_buffer)
		{
			init();
		}

		return m_buffer.GetAddressOf();
	}

	bool ConstantBufferDetail_D3D11::ConstantBufferDetail_D3D11::init() const
	{
		CRenderer_D3D11* const pRenderer = static_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));

		ID3D11Device* device = pRenderer->getDevice();

		if (not device)
		{
			return false;
		}

		m_context = pRenderer->getContext();

		const D3D11_BUFFER_DESC desc =
		{
			.ByteWidth				= static_cast<uint32>(m_bufferSize),
			.Usage					= D3D11_USAGE_DYNAMIC,
			.BindFlags				= D3D11_BIND_CONSTANT_BUFFER,
			.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
			.MiscFlags				= 0,
			.StructureByteStride	= 0,
		};

		if (FAILED(device->CreateBuffer(&desc, nullptr, &m_buffer)))
		{
			return false;
		}

		return true;
	}
}
