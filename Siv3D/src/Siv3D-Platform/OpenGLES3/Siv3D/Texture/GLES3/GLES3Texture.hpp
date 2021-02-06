//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	class GLES3Texture
	{
	public:

		SIV3D_NODISCARD_CXX20
		GLES3Texture(const Image& image, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		GLES3Texture(const Image& image, const Array<Image>& mips, TextureDesc desc);

		~GLES3Texture();

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

	private:

		enum class TextureType
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

		Size m_size = { 0, 0 };

		TextureFormat m_format = TextureFormat::Unknown;

		TextureDesc m_textureDesc = TextureDesc::Unmipped;

		TextureType m_type = TextureType::Default;

		bool m_initialized = false;
	};
}
