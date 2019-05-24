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

# include <Siv3DEngine.hpp>
# include <Graphics/D3D11/CGraphics_D3D11.hpp>
# include "D3D11ConstantBuffer.hpp"

namespace s3d
{
	namespace detail
	{
		ConstantBufferBase::ConstantBufferDetail::ConstantBufferDetail(const size_t size)
			: m_bufferSize(size)
		{

		}

		bool ConstantBufferBase::ConstantBufferDetail::update(const void* const data, const size_t size)
		{
			if (!m_buffer)
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

		ID3D11Buffer* const* ConstantBufferBase::ConstantBufferDetail::getBufferPtr() const
		{
			if (!m_buffer)
			{
				init();
			}

			return m_buffer.GetAddressOf();
		}

		bool ConstantBufferBase::ConstantBufferDetail::init() const
		{
			CGraphics_D3D11* const graphics = dynamic_cast<CGraphics_D3D11*>(Siv3DEngine::Get<ISiv3DGraphics>());

			m_context = graphics->getContext();

			D3D11_BUFFER_DESC desc;
			desc.ByteWidth				= static_cast<uint32>(m_bufferSize);
			desc.Usage					= D3D11_USAGE_DYNAMIC;
			desc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags				= 0;
			desc.StructureByteStride	= 0;

			if (FAILED(graphics->getDevice()->CreateBuffer(&desc, nullptr, &m_buffer)))
			{
				return false;
			}

			return true;
		}
	}
}
