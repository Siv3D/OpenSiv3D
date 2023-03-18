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

# include <Siv3D/DLL.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Renderer2D/D3D11/CRenderer2D_D3D11.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "D3D11BackBuffer.hpp"

namespace s3d
{
	D3D11BackBuffer::D3D11BackBuffer(const D3D11Device& device, const D3D11SwapChain& swapChain)
		: m_device(device.getDevice())
		, m_context(device.getContext())
		, m_swapChain1(swapChain.getSwapChain1())
	{
		LOG_SCOPED_TRACE(U"D3D11BackBuffer::D3D11BackBuffer()");

		pRenderer2D		= static_cast<CRenderer2D_D3D11*>(SIV3D_ENGINE(Renderer2D));

		m_backBuffer	= D3D11InternalTexture2D::GetTextureFromSwapChain(m_device, m_swapChain1);

		m_sceneSize		= Window::GetState().virtualSize;

		m_sceneBuffers =
		{
			.scene = D3D11InternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize, m_sampleCount)
		};

		clear(D3D11ClearTarget::All);
	}

	D3D11BackBuffer::~D3D11BackBuffer()
	{

	}

	void D3D11BackBuffer::clear(const D3D11ClearTarget clearTargets)
	{
		if (clearTargets & D3D11ClearTarget::BackBuffer)
		{
			m_backBuffer.clear(m_context, m_letterboxColor);
		}

		if (clearTargets & D3D11ClearTarget::Scene)
		{
			m_sceneBuffers.scene.clear(m_context, m_backgroundColor);
		}
	}

	void D3D11BackBuffer::updateFromSceneBuffer()
	{
		unbindAllRenderTargets();

		if (m_sampleCount == 1)
		{
			if (m_backBuffer.size() == m_sceneBuffers.scene.size())
			{
				m_sceneBuffers.scene.copyTo(m_context, m_backBuffer);
			}
			else
			{
				setRenderTarget(m_backBuffer);
				m_context->PSSetShaderResources(0, 1, m_sceneBuffers.scene.getSRVPtr());
				pRenderer2D->drawFullScreenTriangle(m_sceneTextureFilter);
				
				D3D11::ResetPSShaderResources(m_context);
			}
		}
		else
		{
			if (m_backBuffer.size() == m_sceneBuffers.scene.size())
			{
				m_sceneBuffers.scene.resolveTo(m_context, m_backBuffer);
			}
			else
			{
				if (m_sceneBuffers.resolved.size() != m_sceneBuffers.scene.size())
				{
					m_sceneBuffers.resolved = D3D11InternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize);
				}
				m_sceneBuffers.scene.resolveTo(m_context, m_sceneBuffers.resolved);

				setRenderTarget(m_backBuffer);
				m_context->PSSetShaderResources(0, 1, m_sceneBuffers.resolved.getSRVPtr());
				pRenderer2D->drawFullScreenTriangle(m_sceneTextureFilter);

				D3D11::ResetPSShaderResources(m_context);
			}
		}
	}

	void D3D11BackBuffer::bindRenderTarget(ID3D11RenderTargetView* const rtv)
	{
		ID3D11RenderTargetView* pRTV[1] =
		{
			rtv
		};

		m_context->OMSetRenderTargets(static_cast<UINT>(std::size(pRTV)), std::data(pRTV), nullptr);
	}

	std::pair<ID3D11Texture2D*, Size> D3D11BackBuffer::getCaptureTexture()
	{
		unbindAllRenderTargets();

		if (m_sampleCount == 1)
		{
			return{ m_sceneBuffers.scene.getTexture(), m_sceneBuffers.scene.size() };
		}
		else
		{
			if (m_backBuffer.size() == m_sceneBuffers.scene.size())
			{
				if (m_sceneBuffers.resolved.size() != m_sceneBuffers.scene.size())
				{
					m_sceneBuffers.resolved = D3D11InternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize);
				}
				m_sceneBuffers.scene.resolveTo(m_context, m_sceneBuffers.resolved);
			}

			return{ m_sceneBuffers.resolved.getTexture(), m_sceneBuffers.resolved.size() };
		}
	}

	//////////////////////////////////////////////////
	//
	//	LetterboxColor
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setLetterboxColor(const ColorF& color) noexcept
	{
		m_letterboxColor = color;
	}

	const ColorF& D3D11BackBuffer::getLetterBoxColor() const noexcept
	{
		return m_letterboxColor;
	}

	//////////////////////////////////////////////////
	//
	//	BackgroundColor
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setBackgroundColor(const ColorF& color) noexcept
	{
		m_backgroundColor = color;
	}

	const ColorF& D3D11BackBuffer::getBackgroundColor() const noexcept
	{
		return m_backgroundColor;
	}

	//////////////////////////////////////////////////
	//
	//	SceneTextureFilter
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setSceneTextureFilter(const TextureFilter textureFilter) noexcept
	{
		m_sceneTextureFilter = textureFilter;
	}

	TextureFilter D3D11BackBuffer::getSceneTextureFilter() const noexcept
	{
		return m_sceneTextureFilter;
	}

	//////////////////////////////////////////////////
	//
	//	SceneResizeMode
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_sceneResizeMode = resizeMode;

		updateSceneSize();
	}

	ResizeMode D3D11BackBuffer::getSceneResizeMode() const noexcept
	{
		return m_sceneResizeMode;
	}

	//////////////////////////////////////////////////
	//
	//	BackBuffer
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setBackBufferSize(const Size backBufferSize)
	{
		assert((0 < backBufferSize.x) && (0 < backBufferSize.y));

		LOG_TRACE(U"D3D11BackBuffer::setBackBufferSize({})"_fmt(backBufferSize));

		unbindAllRenderTargets();

		m_backBuffer.reset();
		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};
			m_swapChain1->GetDesc1(&desc);
			if (FAILED(m_swapChain1->ResizeBuffers(desc.BufferCount, backBufferSize.x, backBufferSize.y, desc.Format, desc.Flags)))
			{
				throw EngineError(U"IDXGISwapChain1->ResizeBuffers() failed");
			}

			m_backBuffer = D3D11InternalTexture2D::GetTextureFromSwapChain(m_device, m_swapChain1);
			clear(D3D11ClearTarget::BackBuffer);
		}

		updateSceneSize();
	}

	const Size& D3D11BackBuffer::getBackBufferSize() const noexcept
	{
		return m_backBuffer.size();
	}

	std::pair<float, RectF> D3D11BackBuffer::getLetterboxComposition() const noexcept
	{
		const Float2 sceneSize = m_sceneSize;
		const Float2 backBufferSize = m_backBuffer.size();

		const float sx = (backBufferSize.x / sceneSize.x);
		const float sy = (backBufferSize.y / sceneSize.y);
		const float s = Min(sx, sy);

		if (sx <= sy)
		{
			const float offsetY = ((backBufferSize.y - sceneSize.y * s) * 0.5f);
			const float width = backBufferSize.x;
			const float height = (backBufferSize.y - offsetY * 2.0f);

			return{ s, RectF(0.0f, offsetY, width, height) };
		}
		else
		{
			const float offsetX = ((backBufferSize.x - sceneSize.x * s) * 0.5f);
			const float width = (backBufferSize.x - offsetX * 2.0f);
			const float height = backBufferSize.y;

			return{ s, RectF(offsetX, 0.0f, width, height) };
		}
	}

	//////////////////////////////////////////////////
	//
	//	SceneBuffer
	//
	//////////////////////////////////////////////////

	void D3D11BackBuffer::setSceneBufferSize(const Size size)
	{
		assert((0 < size.x) && (0 < size.y));

		if (size == m_sceneSize)
		{
			return;
		}

		LOG_TRACE(U"D3D11BackBuffer::setSceneSize({})"_fmt(size));

		unbindAllRenderTargets();

		m_sceneSize = size;

		m_sceneBuffers = {};

		m_sceneBuffers =
		{
			.scene = D3D11InternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize, m_sampleCount)
		};

		clear(D3D11ClearTarget::All);
	}

	const Size& D3D11BackBuffer::getSceneBufferSize() const noexcept
	{
		return m_sceneSize;
	}

	void D3D11BackBuffer::updateSceneSize()
	{
		if (m_sceneResizeMode == ResizeMode::Actual)
		{
			setSceneBufferSize(Window::GetState().frameBufferSize);
		}
		else if (m_sceneResizeMode == ResizeMode::Virtual)
		{
			setSceneBufferSize(Window::GetState().virtualSize);
		}
	}

	const D3D11InternalTexture2D& D3D11BackBuffer::getSceneBuffer() const noexcept
	{
		return m_sceneBuffers.scene;
	}

	void D3D11BackBuffer::bindSceneToContext()
	{
		ID3D11RenderTargetView* pRTV[1] =
		{
			m_sceneBuffers.scene.getRTV()
		};

		m_context->OMSetRenderTargets(static_cast<UINT>(std::size(pRTV)), std::data(pRTV), nullptr);
	}

	void D3D11BackBuffer::bindToContext(ID3D11RenderTargetView* const rtv, ID3D11DepthStencilView* const dsv)
	{
		ID3D11RenderTargetView* pRTV[1] =
		{
			rtv
		};

		m_context->OMSetRenderTargets(static_cast<UINT>(std::size(pRTV)), std::data(pRTV), dsv);
	}

	void D3D11BackBuffer::unbindAllRenderTargets()
	{
		m_context->OMSetRenderTargets(0, nullptr, nullptr);
	}

	void D3D11BackBuffer::setRenderTarget(const D3D11InternalTexture2D& texture)
	{
		assert(not texture.isEmpty());

		bindRenderTarget(texture.getRTV());
	}
}
