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

# include <Siv3D/DynamicTexture.hpp>

namespace s3d
{
	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, Size{ width, height }, nullptr, 0, format, desc } {}

	DynamicTexture::DynamicTexture(const uint32 width, const uint32 height, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, Size{ width, height }, color, format, desc } {}

	DynamicTexture::DynamicTexture(const Image& image, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, image.size(), image.data(), image.stride(), TextureFormat::R8G8B8A8_Unorm, desc } {}

	DynamicTexture::DynamicTexture(const Image& image, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, image.size(), image.data(), image.stride(), format, desc } {}

	DynamicTexture::DynamicTexture(const Size& size, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, size, nullptr, 0, format, desc } {}

	DynamicTexture::DynamicTexture(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: Texture{ Texture::Dynamic{}, size, color, format, desc } {}
}
