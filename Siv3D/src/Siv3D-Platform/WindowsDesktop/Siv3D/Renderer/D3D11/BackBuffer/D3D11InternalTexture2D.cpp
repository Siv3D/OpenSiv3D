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
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Error.hpp>
# include "D3D11InternalTexture2D.hpp"

namespace s3d
{
	bool D3D11InternalTexture2D::isEmpty() const noexcept
	{
		return m_size.isZero();
	}

	D3D11InternalTexture2D::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	const Size& D3D11InternalTexture2D::size() const noexcept
	{
		return m_size;
	}

	void D3D11InternalTexture2D::clear(ID3D11DeviceContext* context, const ColorF& color)
	{
		if (isEmpty())
		{
			return;
		}

		const Float4 rgba = color.toFloat4();
		
		context->ClearRenderTargetView(m_renderTargetView.Get(), rgba.getPointer());
	}

	void D3D11InternalTexture2D::copyTo(ID3D11DeviceContext* context, D3D11InternalTexture2D& dst)
	{
		assert(size() == dst.size());

		context->CopyResource(dst.m_texture.Get(), m_texture.Get());
	}

	void D3D11InternalTexture2D::resolveTo(ID3D11DeviceContext* context, D3D11InternalTexture2D& dst)
	{
		assert(size() == dst.size());

		context->ResolveSubresource(dst.m_texture.Get(), 0,
			m_texture.Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
	}

	void D3D11InternalTexture2D::reset()
	{
		m_texture.Reset();

		m_renderTargetView.Reset();

		m_shaderResourceView.Reset();

		m_size = Size{ 0, 0 };
	}

	ID3D11ShaderResourceView* const* D3D11InternalTexture2D::getSRVPtr() const noexcept
	{
		return m_shaderResourceView.GetAddressOf();
	}

	ID3D11RenderTargetView* D3D11InternalTexture2D::getRTV() const noexcept
	{
		return m_renderTargetView.Get();
	}

	ID3D11Texture2D* D3D11InternalTexture2D::getTexture() const noexcept
	{
		return m_texture.Get();
	}

	[[nodiscard]]
	D3D11InternalTexture2D D3D11InternalTexture2D::GetTextureFromSwapChain(ID3D11Device* device, IDXGISwapChain1* swapChain1)
	{
		LOG_TRACE(U"detail::GetTextureFromSwapChain()");

		D3D11InternalTexture2D texture;

		// バックバッファのサイズを取得
		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};

			if (FAILED(swapChain1->GetDesc1(&desc)))
			{
				throw EngineError(U"IDXGISwapChain1::GetDesc1() failed");
			}

			texture.m_size = { desc.Width, desc.Height };
			LOG_TRACE(U"Back buffer size = {}"_fmt(texture.m_size));
		}

		if (FAILED(swapChain1->GetBuffer(0, __uuidof(ID3D11Texture2D), &texture.m_texture)))
		{
			throw EngineError(U"IDXGISwapChain1::GetBuffer() failed");
		}

		if (FAILED(device->CreateRenderTargetView(texture.m_texture.Get(), nullptr, &texture.m_renderTargetView)))
		{
			throw EngineError(U"ID3D11Device::CreateRenderTargetView() failed");
		}

		return texture;
	}

	[[nodiscard]]
	D3D11InternalTexture2D D3D11InternalTexture2D::CreateRenderTargetTexture2D(ID3D11Device* device, const Size size, const uint32 sampleCount)
	{
		LOG_TRACE(U"detail::CreateRenderTargetTexture2D(size = {}, sampleCount = {})"_fmt(size, sampleCount));

		const CD3D11_TEXTURE2D_DESC desc(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			size.x, size.y,
			1, 1,
			(D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			D3D11_USAGE_DEFAULT,
			0,
			sampleCount, 0,
			0);

		D3D11InternalTexture2D texture;
		texture.m_sampleDesc = desc.SampleDesc;
		{
			{
				if (FAILED(device->CreateTexture2D(&desc, nullptr, &texture.m_texture)))
				{
					throw EngineError{ U"ID3D11Device::CreateTexture2D() failed" };
				}
			}

			{
				const CD3D11_RENDER_TARGET_VIEW_DESC rtDesc(
					((sampleCount == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS),
					desc.Format);

				if (FAILED(device->CreateRenderTargetView(texture.m_texture.Get(), &rtDesc, &texture.m_renderTargetView)))
				{
					throw EngineError{ U"ID3D11Device::CreateRenderTargetView() failed" };
				}
			}

			{
				const CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(
					texture.m_texture.Get(),
					((sampleCount == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS),
					desc.Format);

				if (FAILED(device->CreateShaderResourceView(texture.m_texture.Get(), &srvDesc, &texture.m_shaderResourceView)))
				{
					throw EngineError{ U"ID3D11Device::CreateShaderResourceView() failed" };
				}
			}
		}
		texture.m_size = size;

		return texture;
	}
}
