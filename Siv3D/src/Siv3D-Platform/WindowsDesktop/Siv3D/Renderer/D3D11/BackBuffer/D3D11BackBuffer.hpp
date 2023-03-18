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
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/FloatRect.hpp>
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>
# include "../Device/D3D11Device.hpp"
# include "../SwapChain/D3D11SwapChain.hpp"
# include "D3D11InternalTexture2D.hpp"

namespace s3d
{
	enum class D3D11ClearTarget
	{
		BackBuffer	= 1 << 0,

		Scene		= 1 << 1,

		All			= (BackBuffer | Scene),
	};
	DEFINE_BITMASK_OPERATORS(D3D11ClearTarget);

	class CRenderer2D_D3D11;

	class D3D11BackBuffer
	{
	private:

		CRenderer2D_D3D11* pRenderer2D = nullptr;

		ID3D11Device* m_device			= nullptr;
		
		ID3D11DeviceContext* m_context	= nullptr;

		IDXGISwapChain1* m_swapChain1	= nullptr;

		uint32 m_sampleCount			= Graphics::DefaultSampleCount;

		ResizeMode m_sceneResizeMode	= Scene::DefaultResizeMode;

		Size m_sceneSize				= Scene::DefaultSceneSize;
	
		D3D11InternalTexture2D m_backBuffer;

		struct SceneBuffer
		{
			D3D11InternalTexture2D scene;
			D3D11InternalTexture2D resolved;
		} m_sceneBuffers;

		ColorF m_letterboxColor				= Scene::DefaultLetterBoxColor;
		
		ColorF m_backgroundColor			= Scene::DefaultBackgroundColor;

		TextureFilter m_sceneTextureFilter	= Scene::DefaultTextureFilter;

		// 全てのレンダーターゲットを解除
		void unbindAllRenderTargets();

		void setRenderTarget(const D3D11InternalTexture2D& texture);

	public:

		D3D11BackBuffer(const D3D11Device& device, const D3D11SwapChain& swapChain);

		~D3D11BackBuffer();

		void clear(D3D11ClearTarget clearTargets);

		void updateFromSceneBuffer();

		void bindRenderTarget(ID3D11RenderTargetView* const rtv);

		std::pair<ID3D11Texture2D*, Size> getCaptureTexture();

		//////////////////////////////////////////////////
		//
		//	LetterboxColor
		//
		//////////////////////////////////////////////////

		void setLetterboxColor(const ColorF& color) noexcept;

		[[nodiscard]]
		const ColorF& getLetterBoxColor() const noexcept;

		//////////////////////////////////////////////////
		//
		//	BackgroundColor
		//
		//////////////////////////////////////////////////

		void setBackgroundColor(const ColorF& color) noexcept;

		[[nodiscard]]
		const ColorF& getBackgroundColor() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneTextureFilter
		//
		//////////////////////////////////////////////////

		void setSceneTextureFilter(TextureFilter textureFilter) noexcept;

		[[nodiscard]]
		TextureFilter getSceneTextureFilter() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneResizeMode
		//
		//////////////////////////////////////////////////

		void setSceneResizeMode(ResizeMode resizeMode);

		[[nodiscard]]
		ResizeMode getSceneResizeMode() const noexcept;

		//////////////////////////////////////////////////
		//
		//	BackBuffer
		//
		//////////////////////////////////////////////////

		void setBackBufferSize(Size backBufferSize);

		[[nodiscard]]
		const Size& getBackBufferSize() const noexcept;

		[[nodiscard]]
		std::pair<float, RectF> getLetterboxComposition() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneBuffer
		//
		//////////////////////////////////////////////////

		void setSceneBufferSize(Size size);

		[[nodiscard]]
		const Size& getSceneBufferSize() const noexcept;

		void updateSceneSize();

		const D3D11InternalTexture2D& getSceneBuffer() const noexcept;


		void bindSceneToContext();

		void bindToContext(ID3D11RenderTargetView* const rtv, ID3D11DepthStencilView* const dsv);
	};
}
