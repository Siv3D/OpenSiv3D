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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class ISiv3DTexture
	{
	public:

		static ISiv3DTexture* Create();

		virtual ~ISiv3DTexture() = default;
		
		virtual void update(size_t maxUpdate) = 0;

		virtual TextureID createFromBackBuffer() = 0;

		virtual TextureID create(const Image& image, TextureDesc desc) = 0;

		virtual TextureID create(const Image& image, const Array<Image>& images, TextureDesc desc) = 0;

		virtual TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) = 0;

		virtual TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) = 0;

		virtual TextureID createRT(const Size& size, uint32 multisampleCount) = 0;

		virtual void release(TextureID handleID) = 0;

		virtual Size getSize(TextureID handleID) = 0;

		virtual TextureDesc getDesc(TextureID handleID) = 0;

		virtual void clearRT(TextureID handleID, const ColorF& color) = 0;

		virtual void beginResize(TextureID handleID) = 0;

		virtual bool endResizeRT(TextureID handleID, const Size& size, uint32 multisampleCount) = 0;

		virtual bool endResizeBackBuffer(TextureID handleID) = 0;



		virtual void setPS(uint32 slot, TextureID handleID) = 0;


		virtual bool fill(TextureID handleID, const ColorF& color, bool wait) = 0;

		virtual bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) = 0;
	};
}
