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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ResizeMode.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Image.hpp>
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>
# include "WebGPUInternalTexture2D.hpp"

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	enum class WebGPUClearTarget
	{
		BackBuffer = 1 << 0,

		Scene = 1 << 1,

		All = (BackBuffer | Scene),
	};
	DEFINE_BITMASK_OPERATORS(WebGPUClearTarget);

	class CRenderer2D_WebGPU;
	class CShader_WebGPU;

	class WebGPUBackBuffer
	{
	private:

		CRenderer2D_WebGPU* pRenderer2D	= nullptr;

		CShader_WebGPU* pShader = nullptr;

		uint32 m_sampleCount			= Graphics::DefaultSampleCount;

		ResizeMode m_sceneResizeMode	= Scene::DefaultResizeMode;

		Size m_backBufferSize			= Window::DefaultClientSize;

		Size m_sceneSize				= Scene::DefaultSceneSize;

		struct SceneBuffer
		{
			std::unique_ptr<WebGPUInternalTexture2D> scene;
			std::unique_ptr<WebGPUInternalTexture2D> resolved;
		} m_sceneBuffers;

		ColorF m_letterboxColor				= Scene::DefaultLetterBoxColor;
		
		ColorF m_backgroundColor			= Scene::DefaultBackgroundColor;

		TextureFilter m_sceneTextureFilter	= Scene::DefaultTextureFilter;

		Image m_screenCaptureImage;

		wgpu::Device m_device;

		wgpu::SwapChain m_swapChain;

		wgpu::Sampler m_sampler;

		Array<wgpu::BindGroupEntry> m_uniforms;

	public:

		WebGPUBackBuffer(const wgpu::Device& device, const wgpu::SwapChain& swapChain);

		~WebGPUBackBuffer();

		wgpu::RenderPassEncoder clear(const wgpu::CommandEncoder& encoder);

		wgpu::RenderPassEncoder begin(const wgpu::CommandEncoder& encoder);

		wgpu::TextureView getTextureView() const;

		WebGPURenderTargetState getRenderTargetState() const;

		void updateFromSceneBuffer(const wgpu::RenderPassEncoder& pass);

		void capture();

		const Image& getScreenCapture() const;

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

		void updateSceneSize();

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



	};
}
