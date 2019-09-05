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
# include <Siv3D/Image.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class Texture_GL
	{
	private:
		
		enum class TextureType
		{
			// 通常テクスチャ
			Normal,
			
			// 動的テクスチャ
			Dynamic,
			
			// レンダーテクスチャ
			Render,
		};
		
		// [メインテクスチャ]
		GLuint m_texture = 0;
		
		GLuint m_frameBuffer = 0;
		
		Size m_size = { 0, 0 };
		
		TextureFormat m_format = TextureFormat::Unknown;
		
		TextureDesc m_textureDesc = TextureDesc::Unmipped;
		
		TextureType m_type = TextureType::Normal;

		bool m_initialized = false;
		
		bool isSRGB() const
		{
			// [Siv3D ToDo]
			return false;
		}
		
	public:
		
		struct Null {};
		struct Dynamic {};
		struct Render {};
		
		Texture_GL() = default;
		
		Texture_GL(Null);
		
		Texture_GL(const Image& image, TextureDesc desc);
		
		Texture_GL(const Image& image, const Array<Image>& mipmaps, TextureDesc desc);
		
		Texture_GL(const Dynamic&, const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);
		
		Texture_GL(const Render&, const Size& size, TextureFormat format, TextureDesc desc);
		
		~Texture_GL();
		
		bool isInitialized() const noexcept;
		
		GLuint getTexture() const noexcept;
		
		GLuint getFrameBuffer() const noexcept;
		
		Size getSize() const noexcept;
		
		TextureDesc getDesc() const noexcept;
		
		// レンダーテクスチャを指定した色でクリアする
		void clearRT(const ColorF& color);
		
		// レンダーテクスチャの内容を Image によコピーする
		void readRT(Image& image);
		
		// 動的テクスチャを指定した色で塗りつぶす
		bool fill(const ColorF& color, bool wait);
		
		bool fillRegion(const ColorF& color, const Rect& rect);
		
		bool fill(const void* src, uint32 stride, bool wait);
		
		bool fillRegion(const void* src, uint32 stride, const Rect& rect, bool wait);
	};
}
