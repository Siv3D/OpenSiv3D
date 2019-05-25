//------m_context------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11RenderTarget.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	namespace detail
	{
		static void CreateRTVFromBackBuffer(ID3D11Device* device, IDXGISwapChain1* swapChain1, BackBuffer& backBuffer)
		{
			LOG_TRACE(U"CreateRTVFromBackBuffer()");

			if (FAILED(swapChain1->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer.texture)))
			{
				throw EngineError(U"IDXGISwapChain1::GetBuffer() failed");
			}

			if (FAILED(device->CreateRenderTargetView(backBuffer.texture.Get(), nullptr, &backBuffer.renderTargetView)))
			{
				throw EngineError(U"ID3D11Device::CreateRenderTargetView() failed");
			}
		}

		static void CreateRenderTarget2D(ID3D11Device* device, RenderTarget2D& rt, const Size& size, const uint32 sampleCount)
		{
			LOG_TRACE(U"CreateRenderTarget2D(size = {}, sampleCount = {})"_fmt(size, sampleCount));

			const CD3D11_TEXTURE2D_DESC desc(
				DXGI_FORMAT_R8G8B8A8_UNORM,
				size.x, size.y,
				1, 1,
				D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
				D3D11_USAGE_DEFAULT,
				0,
				sampleCount, 0,
				0);

			if (FAILED(device->CreateTexture2D(&desc, nullptr, &rt.texture)))
			{
				throw EngineError(U"ID3D11Device::CreateTexture2D() failed");
			}

			const CD3D11_RENDER_TARGET_VIEW_DESC rtDesc(
				(sampleCount == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS,
				desc.Format);

			if (FAILED(device->CreateRenderTargetView(rt.texture.Get(), &rtDesc, &rt.renderTargetView)))
			{
				throw EngineError(U"ID3D11Device::CreateRenderTargetView() failed");
			}

			const CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(
				rt.texture.Get(),
				(sampleCount == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS,
				desc.Format);

			if (FAILED(device->CreateShaderResourceView(rt.texture.Get(), &srvDesc, &rt.shaderResourceView)))
			{
				throw EngineError(U"ID3D11Device::CreateShaderResourceView() failed");
			}

			rt.size = size;
		}
	}

	D3D11RenderTarget::D3D11RenderTarget(const D3D11Device& device, const D3D11SwapChain& swapChain)
		: m_device(device.getDevice())
		, m_context(device.getContext())
		, m_swapChain1(swapChain.getSwapChain1())
	{
		LOG_TRACE(U"D3D11RenderTarget::D3D11RenderTarget()");

		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};
			m_swapChain1->GetDesc1(&desc);
			m_backBuffer.size.set(desc.Width, desc.Height);
			LOG_TRACE(U"D3D11RenderTarget::m_backBuffer.size = {}"_fmt(m_backBuffer.size));
		}

		detail::CreateRTVFromBackBuffer(m_device, m_swapChain1, m_backBuffer);
		detail::CreateRenderTarget2D(m_device, m_msScene, m_backBuffer.size, SampleCount);

		clear(true);
	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	void D3D11RenderTarget::clear(const bool clearAll)
	{
		int32 clearTarget = clearAll ? ClearTarget::All : m_clearTarget;

		if (m_skipClearScreen)
		{
			if (!clearAll)
			{
				clearTarget &= ~ClearTarget::RenderTarget2D;
			}

			m_skipClearScreen = false;
		}

		if (clearTarget & ClearTarget::BackBuffer)
		{
			const float colors[4]
			{
				static_cast<float>(m_letterboxColor.r),
				static_cast<float>(m_letterboxColor.g),
				static_cast<float>(m_letterboxColor.b),
				static_cast<float>(m_letterboxColor.a),
			};

			m_context->ClearRenderTargetView(m_backBuffer.renderTargetView.Get(), colors);
		}

		if (clearTarget & ClearTarget::RenderTarget2D)
		{
			const float colors[4]
			{
				static_cast<float>(m_backgroundColor.r),
				static_cast<float>(m_backgroundColor.g),
				static_cast<float>(m_backgroundColor.b),
				static_cast<float>(m_backgroundColor.a),
			};

			m_context->ClearRenderTargetView(m_msScene.renderTargetView.Get(), colors);
		}

		ID3D11RenderTargetView* pRTV[3]
		{
			m_msScene.renderTargetView.Get(),
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);
	}

	void D3D11RenderTarget::resolve()
	{
		if (m_backBuffer.size == m_msScene.size)
		{
			m_context->OMSetRenderTargets(0, nullptr, nullptr);

			m_context->ResolveSubresource(m_backBuffer.texture.Get(), 0,
				m_msScene.texture.Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
		}
		else
		{
			if (m_sceneTextureFilter == TextureFilter::Nearest)
			{
				ID3D11RenderTargetView* pRTV[3]
				{
					m_backBuffer.renderTargetView.Get(),
					nullptr,
					nullptr,
				};
				m_context->OMSetRenderTargets(3, pRTV, nullptr);
				m_context->PSSetShaderResources(0, 1, m_msScene.shaderResourceView.GetAddressOf());

				// draw
				Siv3DEngine::Get<ISiv3DRenderer2D>()->drawFullscreen(true);

				ID3D11ShaderResourceView* nullAttach[16] =
				{
					nullptr
				};
				m_context->PSSetShaderResources(0, 16, nullAttach);
			}
			else
			{
				if (m_msScene.size != m_resolvedScene.size)
				{
					detail::CreateRenderTarget2D(m_device, m_resolvedScene, m_msScene.size, 1);
				}

				// resolve
				{
					m_context->OMSetRenderTargets(0, nullptr, nullptr);

					m_context->ResolveSubresource(m_resolvedScene.texture.Get(), 0,
						m_msScene.texture.Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
				}

				ID3D11RenderTargetView* pRTV[3]
				{
					m_backBuffer.renderTargetView.Get(),
					nullptr,
					nullptr,
				};
				m_context->OMSetRenderTargets(3, pRTV, nullptr);
				m_context->PSSetShaderResources(0, 1, m_resolvedScene.shaderResourceView.GetAddressOf());

				// draw
				Siv3DEngine::Get<ISiv3DRenderer2D>()->drawFullscreen(false);

				ID3D11ShaderResourceView* nullAttach[16] =
				{
					nullptr
				};
				m_context->PSSetShaderResources(0, 16, nullAttach);
			}
		}
	}

	void D3D11RenderTarget::setBackgroundColor(const ColorF& color)
	{
		m_backgroundColor = color;
	}

	void D3D11RenderTarget::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_sceneTextureFilter = textureFilter;
	}

	TextureFilter D3D11RenderTarget::getSceneTextureFilter() const
	{
		return m_sceneTextureFilter;
	}

	void D3D11RenderTarget::setLetterboxColor(const ColorF& color)
	{
		m_letterboxColor = color;
	}

	void D3D11RenderTarget::skipClearScreen()
	{
		m_skipClearScreen = true;
	}

	const Size& D3D11RenderTarget::getBackBufferSize() const
	{
		return m_backBuffer.size;
	}

	const Size& D3D11RenderTarget::getSceneSize() const
	{
		return m_msScene.size;
	}

	void D3D11RenderTarget::resizeScene(const Size& sceneSize)
	{
		LOG_TRACE(U"D3D11RenderTarget::resizeScene(sceneSize = {})"_fmt(sceneSize));

		if (sceneSize == m_msScene.size)
		{
			return;
		}

		m_context->OMSetRenderTargets(0, nullptr, nullptr);
		m_msScene.reset();
		detail::CreateRenderTarget2D(m_device, m_msScene, sceneSize, SampleCount);
		clear(true);
	}

	void D3D11RenderTarget::resizeBuffers(const Size& backBufferSize, const Size& sceneSize)
	{
		LOG_TRACE(U"D3D11RenderTarget::resizeBuffers(backBufferSize = {}, sceneSize = {})"_fmt(backBufferSize, sceneSize));

		m_context->OMSetRenderTargets(0, nullptr, nullptr);
		m_backBuffer.reset();
		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};
			m_swapChain1->GetDesc1(&desc);
			if (FAILED(m_swapChain1->ResizeBuffers(desc.BufferCount, backBufferSize.x, backBufferSize.y, desc.Format, desc.Flags)))
			{
				throw EngineError(U"IDXGISwapChain1->ResizeBuffers() failed");
			}

			m_swapChain1->GetDesc1(&desc);
			m_backBuffer.size.set(desc.Width, desc.Height);
			LOG_TRACE(U"D3D11RenderTarget::m_backBuffer.size = {}"_fmt(m_backBuffer.size));
		}
		detail::CreateRTVFromBackBuffer(m_device, m_swapChain1, m_backBuffer);

		if (sceneSize != m_msScene.size)
		{
			m_msScene.reset();
			detail::CreateRenderTarget2D(m_device, m_msScene, sceneSize, SampleCount);
		}

		clear(true);
	}

	const BackBuffer& D3D11RenderTarget::getBackBuffer() const
	{
		return m_backBuffer;
	}
}
