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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class ISiv3DTexture
	{
	public:

		static ISiv3DTexture* Create();

		virtual ~ISiv3DTexture() = default;

		virtual void updateAsync(size_t maxUpdate) = 0;

		virtual TextureID createUnmipped(const Image& image, TextureDesc desc) = 0;

		virtual TextureID create(const Image& image, const Array<Image>& mips, TextureDesc desc) = 0;

		virtual TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) = 0;

		virtual TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) = 0;

		virtual TextureID createRT(const Size& size, TextureFormat format) = 0;

		virtual TextureID createRT(const Image& image) = 0;

		virtual TextureID createMSRT(const Size& size, TextureFormat format) = 0;

		virtual void release(TextureID handleID) = 0;

		virtual Size getSize(TextureID handleID) = 0;

		virtual TextureDesc getDesc(TextureID handleID) = 0;

		virtual TextureFormat getFormat(TextureID handleID) = 0;

		virtual void clearRT(TextureID handleID, const ColorF& color) = 0;

		virtual void readRT(TextureID handleID, Image& image) = 0;

		virtual void resolveMSRT(TextureID handleID) = 0;


		virtual bool fill(TextureID handleID, const ColorF& color, bool wait) = 0;

		virtual bool fillRegion(TextureID handleID, const ColorF& color, const Rect& rect) = 0;

		virtual bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) = 0;

		virtual bool fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, bool wait) = 0;
	};
}
