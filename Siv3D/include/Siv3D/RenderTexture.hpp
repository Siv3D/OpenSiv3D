//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Texture.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	class RenderTexture : public Texture
	{
	protected:

		struct MSRender {};

		RenderTexture(MSRender, uint32 width, uint32 height, const TextureFormat& format);

	public:

		RenderTexture();

		RenderTexture(uint32 width, uint32 height, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		explicit RenderTexture(const Size& size, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		RenderTexture(uint32 width, uint32 height, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		RenderTexture(const Size& size, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		RenderTexture(const Image& image);

		RenderTexture(const Grid<float>& image);

		RenderTexture(const Grid<Float2>& image);

		RenderTexture(const Grid<Float4>& image);

		void clear(const ColorF& color);

		// TextureFormat::R8G8B8A8_Unorm のみサポート
		void readAsImage(Image& image);

		// TextureFormat::R32_Float のみサポート
		void read(Grid<float>& image);

		// TextureFormat::R32G32_Float のみサポート
		void read(Grid<Float2>& image);

		// TextureFormat::R32G32B32A32_Float のみサポート
		void read(Grid<Float4>& image);
	};
}
