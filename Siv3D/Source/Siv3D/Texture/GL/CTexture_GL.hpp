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

		Texture::IDType createRT(const Size& size) override;

		void release(Texture::IDType handleID) override;

		Size getSize(Texture::IDType handleID) override;
	};
}

# endif
