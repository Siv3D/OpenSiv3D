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

# include "D3D11ScreenCapture.hpp"

namespace s3d
{
	D3D11ScreenCapture::D3D11ScreenCapture(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{

	}

	void D3D11ScreenCapture::request()
	{
		m_requested = true;
	}

	bool D3D11ScreenCapture::isRequested() const
	{
		return m_requested;
	}

	bool D3D11ScreenCapture::capture(ID3D11Texture2D* texture, const Size& size)
	{
		m_requested = false;

		if (size != m_image.size())
		{
			if (m_stagingTexture)
			{
				m_stagingTexture.Reset();
			}

			const D3D11_TEXTURE2D_DESC desc = CD3D11_TEXTURE2D_DESC(
				DXGI_FORMAT_R8G8B8A8_UNORM,
				size.x, size.y,
				1, 1,
				0,
				D3D11_USAGE_STAGING,
				D3D11_CPU_ACCESS_READ,
				1, 0,
				0);

			if (FAILED(m_device->CreateTexture2D(&desc, nullptr, &m_stagingTexture)))
			{
				return false;
			}

			m_image.resize(size);
		}

		m_context->CopyResource(m_stagingTexture.Get(), texture);

		D3D11_MAPPED_SUBRESOURCE mapped;
		{
			if (FAILED(m_context->Map(m_stagingTexture.Get(), 0, D3D11_MAP_READ, 0, &mapped)))
			{
				return false;
			}

			if (!mapped.pData)
			{
				return false;
			}

			const size_t srcStride = mapped.RowPitch;
			const size_t dstStride = m_image.stride();

			if (srcStride == dstStride)
			{
				std::memcpy(m_image.data(), mapped.pData, m_image.size_bytes());
			}
			else
			{
				const size_t width = m_image.width();
				const size_t height = m_image.height();

				const uint8* pSrc = static_cast<const uint8*>(mapped.pData);
				Color* pDst = m_image.data();

				for (size_t y = 0; y < height; ++y)
				{
					std::memcpy(pDst, pSrc, dstStride);
					pDst += width;
					pSrc += srcStride;
				}
			}

			m_context->Unmap(m_stagingTexture.Get(), 0);
		}

		return true;
	}

	const Image& D3D11ScreenCapture::getImage() const
	{
		return m_image;
	}
}
