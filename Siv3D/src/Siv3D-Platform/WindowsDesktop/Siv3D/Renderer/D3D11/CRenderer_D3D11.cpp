//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Renderer2D/D3D11/CRenderer2D_D3D11.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer_D3D11::CRenderer_D3D11() = default;

	CRenderer_D3D11::~CRenderer_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::~CRenderer_D3D11()");
	}

	EngineOption::Renderer CRenderer_D3D11::getRendererType() const noexcept
	{
		return EngineOption::Renderer::Direct3D11;
	}

	void CRenderer_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::init()");

		pRenderer2D = dynamic_cast<CRenderer2D_D3D11*>(SIV3D_ENGINE(Renderer2D));

		HWND hWnd	= static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
		const Size frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
		
		m_device			= std::make_unique<D3D11Device>();
		m_swapChain			= std::make_unique<D3D11SwapChain>(*m_device, hWnd, frameBufferSize);
		m_backBuffer		= std::make_unique<D3D11BackBuffer>(*m_device, *m_swapChain);
		m_blendState		= std::make_unique<D3D11BlendState>(m_device->getDevice(), m_device->getContext());
		m_rasterizerState	= std::make_unique<D3D11RasterizerState>(m_device->getDevice(), m_device->getContext());
		m_depthStencilState	= std::make_unique<D3D11DepthStencilState>(m_device->getDevice(), m_device->getContext());
		m_samplerState		= std::make_unique<D3D11SamplerState>(m_device->getDevice(), m_device->getContext());

		SIV3D_ENGINE(Texture)->init();
		SIV3D_ENGINE(Shader)->init();

		m_device->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	
	}

	StringView CRenderer_D3D11::getName() const
	{
		static constexpr StringView name(U"D3D11");
		return name;
	}

	void CRenderer_D3D11::clear()
	{
		m_backBuffer->clear(D3D11ClearTarget::BackBuffer | D3D11ClearTarget::Scene);

		if (const Size frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
			frameBufferSize != m_backBuffer->getBackBufferSize())
		{
			m_backBuffer->setBackBufferSize(frameBufferSize);
		}
	}

	void CRenderer_D3D11::flush()
	{
		pRenderer2D->flush();

		m_backBuffer->updateFromSceneBuffer();
	}

	bool CRenderer_D3D11::present()
	{
		if (not m_swapChain->present())
		{
			return false;
		}

		return true;
	}

	void CRenderer_D3D11::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_D3D11::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_D3D11::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_D3D11::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_D3D11::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_D3D11::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_D3D11::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_D3D11::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_D3D11::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_D3D11::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, RectF> CRenderer_D3D11::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}



	ID3D11Device* CRenderer_D3D11::getDevice() const
	{
		return m_device->getDevice();
	}

	ID3D11DeviceContext* CRenderer_D3D11::getContext() const
	{
		return m_device->getContext();
	}

	D3D11BackBuffer& CRenderer_D3D11::getBackBuffer() noexcept
	{
		return *m_backBuffer;
	}

	D3D11BlendState& CRenderer_D3D11::getBlendState() noexcept
	{
		return *m_blendState;
	}

	D3D11RasterizerState& CRenderer_D3D11::getRasterizerState() noexcept
	{
		return *m_rasterizerState;
	}

	D3D11SamplerState& CRenderer_D3D11::getSamplerState() noexcept
	{
		return *m_samplerState;
	}
}
