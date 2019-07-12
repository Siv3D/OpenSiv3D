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

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/Scene.hpp>
# include "D3D11SwapChain.hpp"

namespace s3d
{
	struct BackBuffer
	{
		ComPtr<ID3D11Texture2D> texture;
		ComPtr<ID3D11RenderTargetView> renderTargetView;
		Size size = Size(0, 0);

		void reset()
		{
			texture.Reset();
			renderTargetView.Reset();
			size = Size(0, 0);
		}
	};

	struct RenderTarget2D
	{
		ComPtr<ID3D11Texture2D> texture;
		ComPtr<ID3D11RenderTargetView> renderTargetView;
		ComPtr<ID3D11ShaderResourceView> shaderResourceView;
		Size size = Size(0, 0);

		void reset()
		{
			texture.Reset();
			renderTargetView.Reset();
			shaderResourceView.Reset();
			size = Size(0, 0);
		}
	};

	struct ClearTarget
	{
		enum Target
		{
			BackBuffer = 0b0001,
			RenderTarget2D = 0b0010,
			All = BackBuffer | RenderTarget2D,
		};
	};

	class D3D11RenderTarget
	{
	private:

		static constexpr uint32 SampleCount = 4;

		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;
		IDXGISwapChain1* m_swapChain1 = nullptr;

		BackBuffer m_backBuffer;
		RenderTarget2D m_msScene;
		RenderTarget2D m_resolvedScene;

		int32 m_clearTarget = ClearTarget::All;
		bool m_skipClearScreen = false;

		ColorF m_letterboxColor = Palette::DefaultLetterbox;
		ColorF m_backgroundColor = Palette::DefaultBackground;

		TextureFilter m_sceneTextureFilter = Scene::DefaultFilter;

	public:

		D3D11RenderTarget(const D3D11Device& device, const D3D11SwapChain& swapChain);

		~D3D11RenderTarget();

		void clear(bool clearAll);

		void resolve();

		void setSceneTextureFilter(TextureFilter textureFilter);

		TextureFilter getSceneTextureFilter() const;

		void setLetterboxColor(const ColorF& color);

		void setBackgroundColor(const ColorF& color);

		void skipClearScreen();

		const Size& getBackBufferSize() const;

		const Size& getSceneSize() const;

		void resizeScene(const Size& sceneSize);

		void resizeBuffers(const Size& backBufferSize, const Size& sceneSize);

		const BackBuffer& getBackBuffer() const;
	};
}
