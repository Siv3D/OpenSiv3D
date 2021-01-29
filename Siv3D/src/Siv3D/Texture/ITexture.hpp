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

		//virtual Texture::IDType createUnmipped(const Image& image, TextureDesc desc) = 0;

		//virtual Texture::IDType createMipped(const Image& image, const Array<Image>& mips, TextureDesc desc) = 0;
	};
}
