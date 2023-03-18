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
# include <Siv3D/Scene.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# define GLFW_EXPOSE_NATIVE_COCOA
# include <ThirdParty/GLFW/glfw3native.h>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Renderer/Metal/BackBuffer/MetalBackBuffer.hpp>
# include <Siv3D/Renderer/Metal/SamplerState/MetalSamplerState.hpp>
# include <Siv3D/Texture/Metal/CTexture_Metal.hpp>
# import <Metal/Metal.h>
# import <QuartzCore/CAMetalLayer.h>

namespace s3d
{
	class CRenderer2D_Metal;

	class CRenderer_Metal final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;
		CRenderer2D_Metal* pRenderer2D = nullptr;
		CTexture_Metal* pTexture = nullptr;

		id<MTLDevice> m_device = nil;
		
		id<MTLCommandQueue> m_commandQueue = nil;
		
		CAMetalLayer* m_swapchain = nullptr;
		
		std::unique_ptr<MetalBackBuffer> m_backBuffer;
		std::unique_ptr<MetalSamplerState> m_samplerState;

		bool m_vSyncEnabled = true;

	public:

		CRenderer_Metal();

		~CRenderer_Metal() override;

		EngineOption::Renderer getRendererType() const noexcept override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void setVSyncEnabled(bool enabled) override;

		bool isVSyncEnabled() const override;

		void captureScreenshot() override;
	
		const Image& getScreenCapture() const override;
	
		void setSceneResizeMode(ResizeMode resizeMode) override;

		ResizeMode getSceneResizeMode() const noexcept override;

		void setSceneBufferSize(Size size) override;

		Size getSceneBufferSize() const noexcept override;

		void setSceneTextureFilter(TextureFilter textureFilter) override;

		TextureFilter getSceneTextureFilter() const noexcept override;

		void setBackgroundColor(const ColorF& color) override;

		const ColorF& getBackgroundColor() const noexcept override;

		void setLetterboxColor(const ColorF& color) override;

		const ColorF& getLetterboxColor() const noexcept override;
		
		std::pair<float, RectF> getLetterboxComposition() const noexcept override;

		void updateSceneSize() override;
		
		
		id<MTLDevice> getDevice() const;
		
		id<MTLCommandQueue> getCommandQueue() const;

		CAMetalLayer* getSwapchain() const;

		MetalSamplerState& getSamplerState();
		
		void changeFrameBufferSize(Size size);
		
		uint32 getSampleCount() const;
		
		id<MTLTexture> getSceneTexture() const;
		
		id<MTLTexture> getResolvedTexture() const;
	};
}
