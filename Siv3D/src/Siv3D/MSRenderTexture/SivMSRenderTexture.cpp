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

# include <Siv3D/MSRenderTexture.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	MSRenderTexture::MSRenderTexture()
		: RenderTexture{} {}

	MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const TextureFormat& format)
		: MSRenderTexture{ Size{ width, height }, format } {}

	MSRenderTexture::MSRenderTexture(const Size& size, const TextureFormat& format)
		: RenderTexture{ RenderTexture::MSRender{}, size, format } {}

	MSRenderTexture::MSRenderTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format)
		: MSRenderTexture{ Size{ width, height }, format }
	{
		clear(color);
		resolve();
	}

	MSRenderTexture::MSRenderTexture(const Size& size, const ColorF& color, const TextureFormat& format)
		: MSRenderTexture{ size, format }
	{
		clear(color);
		resolve();
	}

	void MSRenderTexture::resolve() const
	{
		SIV3D_ENGINE(Texture)->resolveMSRT(m_handle->id());
	}

	void MSRenderTexture::clear(const ColorF& color) const
	{
		SIV3D_ENGINE(Texture)->clearRT(m_handle->id(), color);
	}

	void MSRenderTexture::readAsImage(Image& image) const
	{
		SIV3D_ENGINE(Texture)->readRT(m_handle->id(), image);
	}
}
