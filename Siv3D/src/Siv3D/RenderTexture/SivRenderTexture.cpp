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

# include <Siv3D/RenderTexture.hpp>
# include <Siv3DEngine.hpp>
# include <Texture/ITexture.hpp>

namespace s3d
{
	RenderTexture::RenderTexture()
		: Texture()
	{

	}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const TextureFormat& format)
		: Texture(Texture::Render{}, width, height, format)
	{

	}

	RenderTexture::RenderTexture(const Size& size, const TextureFormat& format)
		: RenderTexture(size.x, size.y, format)
	{

	}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format)
		: RenderTexture(width, height, format)
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const Size& size, const ColorF& color, const TextureFormat& format)
		: RenderTexture(size.x, size.y, format)
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const Image& image)
		: Texture(Texture::Render{}, image)
	{

	}

	RenderTexture::RenderTexture(MSRender, const uint32 width, const uint32 height, const TextureFormat& format)
		: Texture(Texture::MSRender{}, width, height, format)
	{

	}

	void RenderTexture::clear(const ColorF& color)
	{
		Siv3DEngine::Get<ISiv3DTexture>()->clearRT(m_handle->id(), color);
	}

	void RenderTexture::readAsImage(Image& image)
	{
		Siv3DEngine::Get<ISiv3DTexture>()->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<float>& image)
	{
		Siv3DEngine::Get<ISiv3DTexture>()->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<Float2>& image)
	{
		Siv3DEngine::Get<ISiv3DTexture>()->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<Float4>& image)
	{
		Siv3DEngine::Get<ISiv3DTexture>()->readRT(m_handle->id(), image);
	}
}
