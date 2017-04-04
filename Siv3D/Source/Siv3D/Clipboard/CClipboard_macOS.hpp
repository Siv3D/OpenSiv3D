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
# if defined(SIV3D_TARGET_MACOS)

# include "IClipboard.hpp"

namespace s3d
{
	class CClipboard_macOS : public ISiv3DClipboard
	{
	private:

	public:

		CClipboard_macOS();

		~CClipboard_macOS() override;

		bool init() override;

		void update() override;
	};
}

# endif
