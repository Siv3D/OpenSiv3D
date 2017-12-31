//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

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

	bool D3D11ScreenCapture::capture(CTexture_D3D11* texture, const TextureID renderTargetTextureID, const Size& size)
	{
		m_requested = false;

		if (size != m_image.size())
		{
			if (m_stagingTexture)
			{
				m_stagingTexture.Reset();
			}

			D3D11_TEXTURE2D_DESC desc{};
			desc.Width				= size.x;
			desc.Height				= size.y;
			desc.MipLevels			= 1;
			desc.ArraySize			= 1;
			desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count	= 1;
			desc.SampleDesc.Quality	= 0;
			desc.Usage				= D3D11_USAGE_STAGING;
			desc.BindFlags			= 0;
			desc.CPUAccessFlags		= D3D11_CPU_ACCESS_READ;
			desc.MiscFlags			= 0;

			if (FAILED(m_device->CreateTexture2D(&desc, nullptr, &m_stagingTexture)))
			{
				return false;
			}

			m_image.resize(size);
		}

		m_context->CopyResource(m_stagingTexture.Get(), texture->getTexture(renderTargetTextureID));

		D3D11_MAPPED_SUBRESOURCE mapped;

		if (FAILED(m_context->Map(m_stagingTexture.Get(), 0, D3D11_MAP_READ, 0, &mapped)))
		{
			return false;
		}

		const uint8* pSrc = static_cast<const uint8*>(mapped.pData);
		const size_t srcStride = mapped.RowPitch;
		const size_t dstStride = m_image.stride();

		if (srcStride == dstStride)
		{
			::memcpy(m_image.data(), pSrc, m_image.size_bytes());
		}
		else
		{
			const size_t width = m_image.width();
			const size_t height = m_image.height();
			Color* pDst = m_image.data();

			for (size_t y = 0; y < height; ++y)
			{
				::memcpy(pDst, pSrc, dstStride);
				pDst += width;
				pSrc += srcStride;
			}
		}

		m_context->Unmap(m_stagingTexture.Get(), 0);

		return true;
	}

	const Image& D3D11ScreenCapture::getImage() const
	{
		return m_image;
	}
}

# endif
