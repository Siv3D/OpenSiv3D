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

# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	RenderTexture::RenderTexture()
		: Texture{} {}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const HasDepth hasDepth)
		: RenderTexture{ Size{ width, height }, format, hasDepth }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const Size& size, const ColorF& color, const TextureFormat& format, const HasDepth hasDepth)
		: RenderTexture{ size, format, hasDepth }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const TextureFormat& format, const HasDepth hasDepth)
		: RenderTexture{ Size{ width, height }, format, hasDepth } {}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const HasDepth hasDepth)
		: RenderTexture{ Size{ width, height }, TextureFormat::R8G8B8A8_Unorm, hasDepth } {}

	RenderTexture::RenderTexture(const Size& size, const TextureFormat& format, const HasDepth hasDepth)
		: Texture{ Texture::Render{}, size, format, hasDepth } {}

	RenderTexture::RenderTexture(const Size& size, const HasDepth hasDepth)
		: RenderTexture{ size, TextureFormat::R8G8B8A8_Unorm, hasDepth } {}

	RenderTexture::RenderTexture(const Image& image, const HasDepth hasDepth)
		: Texture{ Texture::Render{}, image, hasDepth } {}

	RenderTexture::RenderTexture(const Grid<float>& image, const HasDepth hasDepth)
		: Texture{ Texture::Render{}, image, hasDepth } {}

	RenderTexture::RenderTexture(const Grid<Float2>& image, const HasDepth hasDepth)
		: Texture{ Texture::Render{}, image, hasDepth } {}

	RenderTexture::RenderTexture(const Grid<Float4>& image, const HasDepth hasDepth)
		: Texture{ Texture::Render{}, image, hasDepth } {}

	RenderTexture::RenderTexture(MSRender, const Size& size, const TextureFormat& format, const HasDepth hasDepth)
		: Texture{ Texture::MSRender{}, size, format, hasDepth } {}

	RenderTexture::~RenderTexture() {}

	const RenderTexture& RenderTexture::clear(const ColorF& color) const
	{
		SIV3D_ENGINE(Texture)->clearRT(m_handle->id(), color);

		return *this;
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

	void RenderTexture::swap(RenderTexture& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
