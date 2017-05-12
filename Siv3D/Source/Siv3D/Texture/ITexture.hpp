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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class ISiv3DTexture
	{
	public:

		static ISiv3DTexture* Create();

		virtual ~ISiv3DTexture() = default;

		virtual Texture::IDType createFromBackBuffer() = 0;

		virtual Texture::IDType create(const Image& image, TextureDesc desc) = 0;

		virtual Texture::IDType create(const Image& image, const Array<Image>& images, TextureDesc desc) = 0;

		virtual Texture::IDType createRT(const Size& size, uint32 multisampleCount) = 0;

		virtual void release(Texture::IDType handleID) = 0;

		virtual Size getSize(Texture::IDType handleID) = 0;

		virtual void clearRT(Texture::IDType handleID, const ColorF& color) = 0;

		virtual void beginResize(Texture::IDType handleID) = 0;

		virtual bool endResizeRT(Texture::IDType handleID, const Size& size, uint32 multisampleCount) = 0;

		virtual bool endResizeBackBuffer(Texture::IDType handleID) = 0;



		virtual void setPS(uint32 slot, Texture::IDType handleID) = 0;
	};
}
