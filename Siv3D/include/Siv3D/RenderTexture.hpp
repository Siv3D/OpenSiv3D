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
	private:

	public:

		RenderTexture();

		RenderTexture(uint32 width, uint32 height, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		explicit RenderTexture(const Size& size, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		RenderTexture(uint32 width, uint32 height, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		RenderTexture(const Size& size, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		void clear(const ColorF& color);

		void readAsImage(Image& image);
	};
}
