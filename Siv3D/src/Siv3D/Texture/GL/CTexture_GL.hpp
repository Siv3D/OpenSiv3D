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
		
		AssetHandleManager<TextureID, Texture_GL> m_textures{ U"Texture" };
		
	public:

		~CTexture_GL();
		
		bool init();

		TextureID createFromBackBuffer() override;

		TextureID create(const Image&, TextureDesc) override;

		TextureID create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) override;

		TextureID createRT(const Size& size, uint32 multisampleCount) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;

		void clearRT(TextureID, const ColorF&) override
		{
			// [Siv3D ToDo]
		}

		void beginResize(TextureID) override
		{
			// [Siv3D ToDo]
		}

		bool endResizeRT(TextureID, const Size&, const uint32) override
		{
			// [Siv3D ToDo]
			return false;
		}

		bool endResizeBackBuffer(TextureID) override
		{
			// [Siv3D ToDo]
			return false;
		}


		void setPS(uint32 slot, TextureID handleID) override;

		bool fill(TextureID handleID, const ColorF& color, bool wait) override;

		bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) override;
	};
}

# endif
