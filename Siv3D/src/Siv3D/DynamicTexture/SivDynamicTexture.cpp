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

# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, Size{ width, height }, nullptr, 0, format, desc } {}

	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, Size{ width, height }, color, format, desc } {}

	DynamicTexture::DynamicTexture(const Image& image, const TextureDesc desc)
		: DynamicTexture{ image, TextureFormat::R8G8B8A8_Unorm, desc } {}

	DynamicTexture::DynamicTexture(const Image& image, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, image.size(), image.data(), image.stride(), format, desc }
	{
		if (detail::HasMipMap(desc))
		{
			generateMips();
		}
	}

	DynamicTexture::DynamicTexture(const Size& size, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, size, nullptr, 0, format, desc } {}

	DynamicTexture::DynamicTexture(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, size, color, format, desc } {}

	bool DynamicTexture::fill(const ColorF& color)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fill(m_handle->id(), color, true);
	}

	bool DynamicTexture::fillRegion(const ColorF& color, const Rect& rect)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fillRegion(m_handle->id(), color, rect);
	}

	bool DynamicTexture::fill(const Image& image)
	{
		if (isEmpty())
		{
			*this = DynamicTexture{ image };
			return true;
		}
		else if (image.size() != size())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fill(m_handle->id(), image.data(), image.stride(), true);
	}

	bool DynamicTexture::fillRegion(const Image& image, const Rect& rect)
	{
		if (isEmpty())
		{
			return false;
		}
		else if (image.size() != size())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fillRegion(m_handle->id(), image.data(), image.stride(), rect, true);
	}

	bool DynamicTexture::fillIfNotBusy(const Image& image)
	{
		if (isEmpty())
		{
			*this = DynamicTexture(image);
			return true;
		}
		else if (image.size() != size())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fill(m_handle->id(), image.data(), image.stride(), false);
	}

	bool DynamicTexture::fillRegionIfNotBusy(const Image& image, const Rect& rect)
	{
		if (isEmpty())
		{
			return false;
		}
		else if (image.size() != size())
		{
			return false;
		}

		return SIV3D_ENGINE(Texture)->fillRegion(m_handle->id(), image.data(), image.stride(), rect, false);
	}

	void DynamicTexture::generateMips()
	{
		if (isEmpty())
		{
			return;
		}

		SIV3D_ENGINE(Texture)->generateMips(m_handle->id());
	}

	void DynamicTexture::swap(DynamicTexture& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
