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

# include <Siv3D/DynamicTexture.hpp>
# include <Siv3DEngine.hpp>
# include <Texture/ITexture.hpp>

namespace s3d
{
	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const TextureFormat& format, const TextureDesc desc)
		: Texture(Texture::Dynamic(), width, height, nullptr, 0, format, desc)
	{

	}

	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: Texture(Texture::Dynamic(), width, height, color, format, desc)
	{

	}

	DynamicTexture::DynamicTexture(const Image& image, const TextureDesc desc)
		: Texture(Texture::Dynamic(), image.width(), image.height(), image.data(), image.stride(), TextureFormat::R8G8B8A8_Unorm, desc)
	{

	}

	DynamicTexture::DynamicTexture(const Image& image, const TextureFormat& format, const TextureDesc desc)
		: Texture(Texture::Dynamic(), image.width(), image.height(), image.data(), image.stride(), format, desc)
	{

	}

	DynamicTexture::DynamicTexture(const Size& size, const TextureFormat& format, const TextureDesc desc)
		: DynamicTexture(size.x, size.y, format, desc)
	{
	
	}

	DynamicTexture::DynamicTexture(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: DynamicTexture(size.x, size.y, color, format, desc)
	{
	
	}

	bool DynamicTexture::fill(const ColorF& color)
	{
		if (isEmpty())
		{
			return false;
		}

		return Siv3DEngine::Get<ISiv3DTexture>()->fill(m_handle->id(), color, true);
	}

	bool DynamicTexture::fillRegion(const ColorF& color, const Rect& rect)
	{
		if (isEmpty())
		{
			return false;
		}

		return Siv3DEngine::Get<ISiv3DTexture>()->fillRegion(m_handle->id(), color, rect);
	}

	bool DynamicTexture::fill(const Image& image)
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

		return Siv3DEngine::Get<ISiv3DTexture>()->fill(m_handle->id(), image.data(), image.stride(), true);
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

		return Siv3DEngine::Get<ISiv3DTexture>()->fillRegion(m_handle->id(), image.data(), image.stride(), rect, true);
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

		return Siv3DEngine::Get<ISiv3DTexture>()->fill(m_handle->id(), image.data(), image.stride(), false);
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

		return Siv3DEngine::Get<ISiv3DTexture>()->fillRegion(m_handle->id(), image.data(), image.stride(), rect, false);
	}
}
