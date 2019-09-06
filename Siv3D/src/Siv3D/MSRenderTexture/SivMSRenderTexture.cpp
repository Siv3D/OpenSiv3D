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

# include <Siv3D/MSRenderTexture.hpp>
# include <Siv3DEngine.hpp>
# include <Texture/ITexture.hpp>

namespace s3d
{
	MSRenderTexture::MSRenderTexture()
		: Texture()
	{

	}

	//MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const TextureFormat format)
	//	: Texture(Texture::MSRender{}, width, height, format)
	//{

	//}

	//MSRenderTexture::MSRenderTexture(const Size& size, const TextureFormat format)
	//	: MSRenderTexture(size.x, size.y, format)
	//{

	//}

	//MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat format)
	//	: MSRenderTexture(width, height, format)
	//{
	//	clear(color);
	//}

	//MSRenderTexture::MSRenderTexture(const Size& size, const ColorF& color, const TextureFormat format)
	//	: MSRenderTexture(size.x, size.y, format)
	//{
	//	clear(color);
	//}

	//void MSRenderTexture::resolve()
	//{
	//	
	//}

	//void MSRenderTexture::clear(const ColorF& color)
	//{
	//	Siv3DEngine::Get<ISiv3DTexture>()->clearRT(m_handle->id(), color);
	//}
}
