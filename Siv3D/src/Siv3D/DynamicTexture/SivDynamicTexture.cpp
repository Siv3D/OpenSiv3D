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

# include <Siv3D/DynamicTexture.hpp>
# include "../Siv3DEngine.hpp"
# include "../Texture/ITexture.hpp"

namespace s3d
{
	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const TextureFormat format, const TextureDesc desc)
		: Texture(Texture::Dynamic{}, width, height, nullptr, 0, format, desc)
	{

	}

	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat format, const TextureDesc desc)
		: Texture(Texture::Dynamic{}, width, height, color, format, desc)
	{

	}

	DynamicTexture::DynamicTexture(const Image& image, const TextureFormat format, const TextureDesc desc)
		: Texture(Texture::Dynamic{}, image.width(), image.height(), image.data(), image.stride(), format, desc)
	{

	}

	bool DynamicTexture::fill(const ColorF& color)
	{
		if (isEmpty())
		{
			return false;
		}

		return Siv3DEngine::GetTexture()->fill(m_handle->id(), color, true);
	}

	bool DynamicTexture::fill(const Image& image)
	{
		if (isEmpty())
		{
			*this = DynamicTexture(image);

			return true;
		}

		if (image.size() != size())
		{
			return false;
		}

		return Siv3DEngine::GetTexture()->fill(m_handle->id(), image.data(), image.stride(), true);
	}
}
