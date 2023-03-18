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
# include <Siv3D/ColorHSV.hpp>

# include <Siv3D/Texture/WebGPU/WebGPURenderTargetState.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUInternalTexture2D
	{
	private:

		wgpu::Texture m_texture = nullptr;

		Size m_size = Size{ 0, 0 };

	public:

		WebGPUInternalTexture2D() = default;

		~WebGPUInternalTexture2D();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const Size& size() const noexcept;

		[[nodiscard]]
		wgpu::TextureView getTextureView() const noexcept;

		[[nodiscard]]
		WebGPURenderTargetState getRenderTargetState() const noexcept;

		[[nodiscard]]
		static std::unique_ptr<WebGPUInternalTexture2D> CreateRenderTargetTexture2D(const wgpu::Device& device, Size size, uint32 sampleCount = 1);
	};
}
