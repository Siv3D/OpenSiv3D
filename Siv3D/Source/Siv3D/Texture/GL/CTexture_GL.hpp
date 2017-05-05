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

namespace s3d
{
	class CTexture_GL : public ISiv3DTexture
	{
	public:

		bool init() { return true; }

		Texture::IDType createFromBackBuffer() override;

		Texture::IDType createRT(const Size& size, uint32 multisampleCount) override;

		void release(Texture::IDType handleID) override;

		Size getSize(Texture::IDType handleID) override;

		void clearRT(Texture::IDType handleID, const ColorF& color) override
		{
			// [Siv3D ToDo]
		}

		void beginResize(Texture::IDType handleID) override
		{
			// [Siv3D ToDo]
		}

		bool endResizeRT(Texture::IDType handleID, const Size& size, uint32 multisampleCount) override
		{
			// [Siv3D ToDo]
			return false;
		}

		bool endResizeBackBuffer(Texture::IDType handleID) override
		{
			// [Siv3D ToDo]
			return false;
		}
	};
}

# endif
