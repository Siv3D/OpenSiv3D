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

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const HasDepth hasDpeth)
		: RenderTexture{ Size{ width, height }, format, hasDpeth }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const Size& size, const ColorF& color, const TextureFormat& format, const HasDepth hasDpeth)
		: RenderTexture{ size, format, hasDpeth }
	{
		clear(color);
	}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const TextureFormat& format, const HasDepth hasDpeth)
		: RenderTexture{ Size{ width, height }, format, hasDpeth } {}

	RenderTexture::RenderTexture(const uint32 width, const uint32 height, const HasDepth hasDpeth)
		: RenderTexture{ Size{ width, height }, TextureFormat::R8G8B8A8_Unorm, hasDpeth } {}

	RenderTexture::RenderTexture(const Size& size, const TextureFormat& format, const HasDepth hasDpeth)
		: Texture{ Texture::Render{}, size, format, hasDpeth } {}

	RenderTexture::RenderTexture(const Size& size, const HasDepth hasDpeth)
		: RenderTexture{ size, TextureFormat::R8G8B8A8_Unorm, hasDpeth } {}

	RenderTexture::RenderTexture(const Image& image, const HasDepth hasDpeth)
		: Texture{ Texture::Render{}, image, hasDpeth } {}

	RenderTexture::RenderTexture(const Grid<float>& image, const HasDepth hasDpeth)
		: Texture{ Texture::Render{}, image, hasDpeth } {}

	RenderTexture::RenderTexture(const Grid<Float2>& image, const HasDepth hasDpeth)
		: Texture{ Texture::Render{}, image, hasDpeth } {}

	RenderTexture::RenderTexture(const Grid<Float4>& image, const HasDepth hasDpeth)
		: Texture{ Texture::Render{}, image, hasDpeth } {}

	RenderTexture::RenderTexture(MSRender, const Size& size, const TextureFormat& format, const HasDepth hasDpeth)
		: Texture{ Texture::MSRender{}, size, format, hasDpeth } {}

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
