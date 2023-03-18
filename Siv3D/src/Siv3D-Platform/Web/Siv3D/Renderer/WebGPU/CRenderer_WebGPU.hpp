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
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Renderer/WebGPU/BackBuffer/WebGPUBackBuffer.hpp>
# include <Siv3D/Renderer/WebGPU/SamplerState/WebGPUSamplerState.hpp>
# include <Siv3D/Texture/WebGPU/CTexture_WebGPU.hpp>
# include <Siv3D/Renderer2D/WebGPU/CRenderer2D_WebGPU.hpp>
# include <Siv3D/Renderer3D/WebGPU/CRenderer3D_WebGPU.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class CRenderer_WebGPU final : public ISiv3DRenderer
	{
	private:
		
		CRenderer2D_WebGPU* pRenderer2D = nullptr;
		CRenderer3D_WebGPU* pRenderer3D = nullptr;
		CTexture_WebGPU* pTexture = nullptr;
		GLFWwindow* m_window = nullptr;

		std::unique_ptr<WebGPUBackBuffer> m_backBuffer;
		
		std::unique_ptr<WebGPUSamplerState> m_samplerState;

		bool m_vSyncEnabled = true;

        // wgpu::Instance m_instance;

        wgpu::Device m_device;

        wgpu::SwapChain m_swapChain;

		wgpu::Queue m_queue;

		wgpu::CommandEncoder m_renderingCommandEncoder;

		Array<wgpu::CommandBuffer> m_commandBuffers;

	public:

		CRenderer_WebGPU();

		~CRenderer_WebGPU() override;

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

		//
		// WebGPU
		//
		WebGPUBackBuffer& getBackBuffer() noexcept;

		WebGPUSamplerState& getSamplerState() noexcept;

		wgpu::Device* getDevice();

		wgpu::CommandEncoder* getCommandEncoder();

		void pushCommands(wgpu::CommandBuffer commands);
	};
}
