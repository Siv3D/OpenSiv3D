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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Texture.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DTexture
	{
	public:

		static ISiv3DTexture* Create();

		virtual ~ISiv3DTexture() = default;

		virtual void updateAsyncTextureLoad(size_t maxUpdate) = 0;

		virtual size_t getTextureCount() const = 0;

		virtual Texture::IDType create(const Image& image, TextureDesc desc) = 0;

		virtual Texture::IDType create(const Image& image, const Array<Image>& mips, TextureDesc desc) = 0;

		virtual Texture::IDType createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc) = 0;

		virtual Texture::IDType createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc) = 0;

		virtual Texture::IDType createRT(const Size& size, const TextureFormat& format, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual Texture::IDType createRT(const Image& image, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual Texture::IDType createRT(const Grid<float>& image, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual Texture::IDType createRT(const Grid<Float2>& image, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual Texture::IDType createRT(const Grid<Float4>& image, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual Texture::IDType createMSRT(const Size& size, const TextureFormat& format, HasDepth hasDepth, HasMipMap hasMipMap) = 0;

		virtual void release(Texture::IDType handleID) = 0;

		virtual Size getSize(Texture::IDType handleID) = 0;

		virtual TextureDesc getDesc(Texture::IDType handleID) = 0;

		virtual TextureFormat getFormat(Texture::IDType handleID) = 0;

		virtual bool hasDepth(Texture::IDType handleID) = 0;

		virtual bool fill(Texture::IDType handleID, const ColorF& color, bool wait) = 0;

		virtual bool fillRegion(Texture::IDType handleID, const ColorF& color, const Rect& rect) = 0;

		virtual bool fill(Texture::IDType handleID, const void* src, uint32 stride, bool wait) = 0;

		virtual bool fillRegion(Texture::IDType handleID, const void* src, uint32 stride, const Rect& rect, bool wait) = 0;
	

		virtual void clearRT(Texture::IDType handleID, const ColorF& color) = 0;

		virtual void generateMips(Texture::IDType handleID) = 0;

		virtual void readRT(Texture::IDType handleID, Image& image) = 0;

		virtual void readRT(Texture::IDType handleID, Grid<float>& image) = 0;

		virtual void readRT(Texture::IDType handleID, Grid<Float2>& image) = 0;

		virtual void readRT(Texture::IDType handleID, Grid<Float4>& image) = 0;

		virtual void resolveMSRT(Texture::IDType handleID) = 0;
	};
}
