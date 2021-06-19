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

# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	RenderTexture::RenderTexture()
		: Texture{} {}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format)
		: RenderTexture{ width, height, format }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const Size& size, const ColorF& color, const TextureFormat& format)
		: RenderTexture{ size.x, size.y, format }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const TextureFormat& format)
		: RenderTexture{ Size{ width, height }, format } {}

	RenderTexture::RenderTexture(const Size& size, const TextureFormat& format)
		: Texture{ Texture::Render{}, size, format } {}

	RenderTexture::RenderTexture(const Image& image)
		: Texture{ Texture::Render{}, image } {}

	RenderTexture::RenderTexture(const Grid<float>& image)
		: Texture{ Texture::Render{}, image } {}

	RenderTexture::RenderTexture(const Grid<Float2>& image)
		: Texture{ Texture::Render{}, image } {}

	RenderTexture::RenderTexture(const Grid<Float4>& image)
		: Texture{ Texture::Render{}, image } {}

	RenderTexture::RenderTexture(MSRender, const Size& size, const TextureFormat& format)
		: Texture{ Texture::MSRender{}, size, format } {}

	RenderTexture::~RenderTexture() {}

	void RenderTexture::clear(const ColorF& color) const
	{
		SIV3D_ENGINE(Texture)->clearRT(m_handle->id(), color);
	}

	void RenderTexture::readAsImage(Image& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<float>& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<Float2>& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}

	void RenderTexture::read(Grid<Float4>& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}
}
