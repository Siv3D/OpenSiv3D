//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "IEyeTracking.hpp"

namespace s3d
{
	class CEyeTracking_macOS : public ISiv3DEyeTracking
	{
	private:

	public:

		CEyeTracking_macOS();

		~CEyeTracking_macOS() override;

		bool init() override;

		void update() override;
	};
}

# endif
