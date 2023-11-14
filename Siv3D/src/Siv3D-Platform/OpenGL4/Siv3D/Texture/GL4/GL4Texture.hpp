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

namespace s3d
{
	class GL4Texture
	{
	public:

		struct Dynamic {};
		struct Render {};
		struct MSRender {};

		SIV3D_NODISCARD_CXX20
		GL4Texture(const Image& image, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		GL4Texture(const Image& image, const Array<Image>& mips, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		GL4Texture(Dynamic, const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc);

		GL4Texture(Render, const Size& size, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		GL4Texture(Render, const Image& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		GL4Texture(Render, const Grid<float>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		GL4Texture(Render, const Grid<Float2>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		GL4Texture(Render, const Grid<Float4>& image, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		GL4Texture(MSRender, const Size& size, const TextureFormat& format, TextureDesc desc, HasDepth hasDepth);

		~GL4Texture();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		GLuint getTexture() const noexcept;

		[[nodiscard]]
		GLuint getFrameBuffer() const noexcept;

		[[nodiscard]]
		Size getSize() const noexcept;

		[[nodiscard]]
		TextureDesc getDesc() const noexcept;

		[[nodiscard]]
		TextureFormat getFormat() const noexcept;

		[[nodiscard]]
		bool hasDepth() const noexcept;

		// 動的テクスチャを指定した色で塗りつぶす
		bool fill(const ColorF& color, bool wait);

		bool fillRegion(const ColorF& color, const Rect& rect);

		bool fill(const void* src, uint32 stride, bool wait);

		bool fillRegion(const void* src, uint32 stride, const Rect& rect, bool wait);

		// レンダーテクスチャを指定した色でクリアする
		void clearRT(const ColorF& color);

		// ミップマップを生成する
		void generateMips();

		// レンダーテクスチャの内容を Image にコピーする
		void readRT(Image& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<float>& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<Float2>& image);

		// レンダーテクスチャの内容を Grid にコピーする
		void readRT(Grid<Float4>& image);

		void resolveMSRT();

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

		// [メインテクスチャ]
		GLuint m_texture = 0;

		// [マルチサンプル・テクスチャ]
		GLuint m_multiSampledTexture = 0;

		// [フレームバッファ]
		GLuint m_frameBuffer = 0;

		// [resolved フレームバッファ]
		GLuint m_resolvedFrameBuffer = 0;

		// [デプステクスチャ]
		GLuint m_depthTexture = 0;

		Size m_size = { 0, 0 };

		TextureFormat m_format = TextureFormat::Unknown;

		TextureDesc m_textureDesc = TextureDesc::Unmipped;

		TextureType m_type = TextureType::Default;

		bool m_hasDepth = false;

		bool m_hasMipMap = false;

		bool m_initialized = false;

		bool initDepthBuffer();
	};
}
