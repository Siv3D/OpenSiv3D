//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Image.hpp>
# include <Siv3D/TextureFormat.hpp>

namespace s3d
{
	class Texture_GL
	{
	private:
		
		GLuint m_texture = 0;
		
		Size m_size = { 0, 0 };

		TextureFormat m_format = TextureFormat::Unknown;
		
		bool m_isDynamic = false;
		
		bool m_initialized = false;

		bool isSRGB() const
		{
			// [Siv3D ToDo]
			return false;
		}

	public:

		struct Null {};

		Texture_GL() = default;

		Texture_GL(Null);
		
		Texture_GL(const Image& image, const TextureDesc desc);
		
		Texture_GL(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc);
		
		Texture_GL(const Size& size, const void* pData, uint32 stride, TextureFormat format);
		
		~Texture_GL();

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		GLuint getTexture() const
		{
			return m_texture;
		}
		
		Size getSize() const
		{
			return m_size;
		}
		
		bool fill(const ColorF& color, bool wait);
		
		bool fill(const void* src, uint32 stride, bool wait);
	};
}

# endif
