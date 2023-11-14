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

# include <Siv3D/MSRenderTexture.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	MSRenderTexture::MSRenderTexture()
		: RenderTexture{} {}

	MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: MSRenderTexture{ Size{ width, height }, format, hasDepth, hasMipMap } {}

	MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: MSRenderTexture{ Size{ width, height }, TextureFormat::R8G8B8A8_Unorm, hasDepth, hasMipMap } {}

	MSRenderTexture::MSRenderTexture(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: RenderTexture{ RenderTexture::MSRender{}, size, format, hasDepth, hasMipMap } {}

	MSRenderTexture::MSRenderTexture(const Size& size, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: MSRenderTexture{ size, TextureFormat::R8G8B8A8_Unorm, hasDepth, hasMipMap } {}

	MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: MSRenderTexture{ Size{ width, height }, color, format, hasDepth, hasMipMap } {}

	MSRenderTexture::MSRenderTexture(const Size& size, const ColorF& color, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: MSRenderTexture{ size, format, hasDepth, hasMipMap }
	{
		clear(color);
		resolve();

		if (hasMipMap)
		{
			generateMips();
		}
	}

	void MSRenderTexture::resolve() const
	{
		SIV3D_ENGINE(Texture)->resolveMSRT(m_handle->id());
	}

	const MSRenderTexture& MSRenderTexture::clear(const ColorF& color) const
	{
		SIV3D_ENGINE(Texture)->clearRT(m_handle->id(), color);

		return *this;
	}

	void MSRenderTexture::readAsImage(Image& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}

	void MSRenderTexture::swap(MSRenderTexture& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
