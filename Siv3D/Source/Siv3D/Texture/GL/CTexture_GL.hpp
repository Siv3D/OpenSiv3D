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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../ITexture.hpp"
# include "Texture_GL.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CTexture_GL : public ISiv3DTexture
	{
	private:
		
		AssetHandleManager<Texture::IDType, std::shared_ptr<Texture_GL>> m_textures{ S3DSTR("Texture") };
		
	public:

		~CTexture_GL();
		
		bool init();

		Texture::IDType createFromBackBuffer() override;

		Texture::IDType create(const Image&, TextureDesc) override;

		Texture::IDType create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc) override;

		Texture::IDType createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format) override;

		Texture::IDType createDynamic(const Size& size, const ColorF& color, TextureFormat format) override;

		Texture::IDType createRT(const Size& size, uint32 multisampleCount) override;

		void release(Texture::IDType handleID) override;

		Size getSize(Texture::IDType handleID) override;

		void clearRT(Texture::IDType, const ColorF&) override
		{
			// [Siv3D ToDo]
		}

		void beginResize(Texture::IDType) override
		{
			// [Siv3D ToDo]
		}

		bool endResizeRT(Texture::IDType, const Size&, const uint32) override
		{
			// [Siv3D ToDo]
			return false;
		}

		bool endResizeBackBuffer(Texture::IDType) override
		{
			// [Siv3D ToDo]
			return false;
		}


		void setPS(uint32 slot, Texture::IDType handleID) override;

		bool fill(Texture::IDType handleID, const ColorF& color, bool wait) override;

		bool fill(Texture::IDType handleID, const void* src, uint32 stride, bool wait) override;
	};
}

# endif
