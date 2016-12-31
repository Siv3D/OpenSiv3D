//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "IDragDrop.hpp"

namespace s3d
{
	class CDragDrop_macOS : public ISiv3DDragDrop
	{
	private:

	public:

		CDragDrop_macOS();

		~CDragDrop_macOS() override;

		bool init() override;
		
		bool update() override;
	};
}

# endif
