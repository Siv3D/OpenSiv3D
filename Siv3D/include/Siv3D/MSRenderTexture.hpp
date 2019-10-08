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

# pragma once
# include "Fwd.hpp"
# include "Texture.hpp"
# include "RenderTexture.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	class MSRenderTexture : public RenderTexture
	{
	private:

	public:

		MSRenderTexture();

		MSRenderTexture(uint32 width, uint32 height, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		explicit MSRenderTexture(const Size& size, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		MSRenderTexture(uint32 width, uint32 height, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		MSRenderTexture(const Size& size, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm);

		// レンダリングされたマルチサンプルテクスチャを通常のテクスチャに resolve し、描画可能にする
		void resolve();

		void clear(const ColorF& color);

		// TextureFormat::R8G8B8A8_Unorm のみサポート
		void readAsImage(Image& image);
	};
}
