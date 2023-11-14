﻿//-----------------------------------------------
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
# include <Siv3D/Texture/ITexture.hpp>

namespace s3d
{
	class CTexture_Null final : public ISiv3DTexture
	{
	private:

	public:

		CTexture_Null();

		~CTexture_Null() override;

		void updateAsyncTextureLoad(size_t maxUpdate) override;

		size_t getTextureCount() const override;

		Texture::IDType create(const Image& image, TextureDesc desc) override;

		Texture::IDType create(const Image& image, const Array<Image>& mips, TextureDesc desc) override;

		Texture::IDType createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc) override;

		Texture::IDType createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc) override;

		Texture::IDType createRT(const Size& size, const TextureFormat& format, HasDepth hasDepth, HasMipMap hasMipMap) override;

		Texture::IDType createRT(const Image& image, HasDepth hasDepth, HasMipMap hasMipMap) override;

		Texture::IDType createRT(const Grid<float>& image, HasDepth hasDepth, HasMipMap hasMipMap) override;

		Texture::IDType createRT(const Grid<Float2>& image, HasDepth hasDepth, HasMipMap hasMipMap) override;

		Texture::IDType createRT(const Grid<Float4>& image, HasDepth hasDepth, HasMipMap hasMipMap) override;

		Texture::IDType createMSRT(const Size& size, const TextureFormat& format, HasDepth hasDepth, HasMipMap hasMipMap) override;

		void release(Texture::IDType handleID) override;

		Size getSize(Texture::IDType handleID) override;

		TextureDesc getDesc(Texture::IDType handleID) override;

		TextureFormat getFormat(Texture::IDType handleID) override;

		bool hasDepth(Texture::IDType handleID) override;

		bool fill(Texture::IDType handleID, const ColorF& color, bool wait) override;

		bool fillRegion(Texture::IDType handleID, const ColorF& color, const Rect& rect) override;

		bool fill(Texture::IDType handleID, const void* src, uint32 stride, bool wait) override;

		bool fillRegion(Texture::IDType handleID, const void* src, uint32 stride, const Rect& rect, bool wait) override;


		void clearRT(Texture::IDType handleID, const ColorF& color) override;

		void generateMips(Texture::IDType handleID) override;

		void readRT(Texture::IDType handleID, Image& image) override;

		void readRT(Texture::IDType handleID, Grid<float>& image) override;

		void readRT(Texture::IDType handleID, Grid<Float2>& image) override;

		void readRT(Texture::IDType handleID, Grid<Float4>& image) override;

		void resolveMSRT(Texture::IDType handleID) override;
	};
}
