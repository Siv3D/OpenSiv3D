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
		
		GLuint m_texture = 0;
		
		GLuint m_frameBuffer = 0;
		
		Size m_size = { 0, 0 };
		
		TextureFormat m_format = TextureFormat::Unknown;
		
		TextureDesc m_textureDesc = TextureDesc::Unmipped;
		
		bool m_isDynamic = false;
		
		bool m_initialized = false;
		
		bool isSRGB() const
		{
			// [Siv3D ToDo]
			return false;
		}
		
	public:
		
		struct Null {};
		
		struct Render {};
		
		Texture_GL() = default;
		
		Texture_GL(Null);
		
		Texture_GL(const Image& image, TextureDesc desc);
		
		Texture_GL(const Image& image, const Array<Image>& mipmaps, TextureDesc desc);
		
		Texture_GL(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);
		
		Texture_GL(const Render&, const Size& size, TextureFormat format, TextureDesc desc);
		
		~Texture_GL();
		
		bool isInitialized() const noexcept
		{
			return m_initialized;
		}
		
		GLuint getTexture() const
		{
			return m_texture;
		}
		
		GLuint getFrameBuffer() const
		{
			return m_frameBuffer;
		}
		
		Size getSize() const
		{
			return m_size;
		}
		
		TextureDesc getDesc() const
		{
			return m_textureDesc;
		}
		
		void clearRT(const ColorF& color);
		
		void readRT(Image& image);
		
		bool fill(const ColorF& color, bool wait);
		
		bool fillRegion(const ColorF& color, const Rect& rect);
		
		bool fill(const void* src, uint32 stride, bool wait);
		
		bool fillRegion(const void* src, uint32 stride, const Rect& rect, bool wait);
	};
}
