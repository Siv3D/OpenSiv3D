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
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/TextureDesc.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Texture/WebGPU/WebGPURenderTargetState.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUTexture
	{
	public:

		struct Dynamic {};
		struct Render {};
		struct MSRender {};

		SIV3D_NODISCARD_CXX20
		WebGPUTexture(wgpu::Device* device, const Image& image, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		WebGPUTexture(wgpu::Device* device, const Image& image, const Array<Image>& mips, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		WebGPUTexture(Dynamic, wgpu::Device* device, const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc);

		WebGPUTexture(Render, wgpu::Device* device, const Size& size, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		WebGPUTexture(Render, wgpu::Device* device, const Image& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		WebGPUTexture(Render, wgpu::Device* device, const Grid<float>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		WebGPUTexture(Render, wgpu::Device* device, const Grid<Float2>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		WebGPUTexture(Render, wgpu::Device* device, const Grid<Float4>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		WebGPUTexture(MSRender, wgpu::Device* device, const Size& size, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		~WebGPUTexture();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		wgpu::Texture getTexture() const noexcept;

		[[nodiscard]]
		wgpu::TextureView getTextureView() const noexcept;

		[[nodiscard]]
		wgpu::RenderPassEncoder begin(const wgpu::CommandEncoder& encoder);

		[[nodiscard]]
		WebGPURenderTargetState getRenderTargetState() const;

		[[nodiscard]]
		Size getSize() const noexcept;

		[[nodiscard]]
		TextureDesc getDesc() const noexcept;

		[[nodiscard]]
		TextureFormat getFormat() const noexcept;

		[[nodiscard]]
		bool hasDepth() const noexcept;

		// 動的テクスチャを指定した色で塗りつぶす
		bool fill(wgpu::Device* device, const ColorF& color, bool wait);

		bool fillRegion(wgpu::Device* device, const ColorF& color, const Rect& rect);

		bool fill(wgpu::Device* device, const void* src, uint32 stride, bool wait);

		bool fillRegion(wgpu::Device* device, const void* src, uint32 stride, const Rect& rect, bool wait);

		// レンダーテクスチャを指定した色でクリアする
		void clearRT(wgpu::Device* device, const ColorF& color);

		// レンダーテクスチャの内容を Image にコピーする
		void readRT(Image& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<float>& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<Float2>& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<Float4>& image);

		void resolveMSRT(wgpu::Device* device);

	private:

		enum class TextureType : uint8
		{
			// 通常テクスチャ
			// [メインテクスチャ]<-[シェーダ・リソース・ビュー]
			Default,

			// 動的テクスチャ
			// [メインテクスチャ]<-[シェーダ・リソース・ビュー], [ステージング・テクスチャ]
			Dynamic,

			// レンダーテクスチャ
			// [メインテクスチャ]<-[レンダー・ターゲット・ビュー]<-[シェーダ・リソース・ビュー]
			Render,

			// マルチサンプル・レンダーテクスチャ
			// [マルチサンプル・テクスチャ]<-[レンダー・ターゲット・ビュー], [メインテクスチャ]<-[シェーダ・リソース・ビュー]
			MSRender,
		};

		void copyToTexture(wgpu::Device* device, Size dstTextureSize, uint32 mipLevel, const void* src, uint32 stride);

		// [メインテクスチャ]
		wgpu::Texture m_texture = nullptr;

		wgpu::TextureView m_textureView = nullptr;

		// [マルチサンプル・テクスチャ]
		wgpu::Texture m_multiSampledTexture = nullptr;

		wgpu::TextureView m_multiSampledTextureView = nullptr;

		// [デプステクスチャ]
		wgpu::Texture m_depthTexture = nullptr;

		wgpu::TextureView m_depthTextureView = nullptr;

		Size m_size = { 0, 0 };

		TextureFormat m_format = TextureFormat::Unknown;

		TextureDesc m_textureDesc = TextureDesc::Unmipped;

		TextureType m_type = TextureType::Default;

		bool m_hasDepth = false;

		bool m_initialized = false;

		bool initDepthBuffer(wgpu::Device* device);
	};
}
