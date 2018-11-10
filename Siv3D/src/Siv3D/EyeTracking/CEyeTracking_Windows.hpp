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
# if defined(SIV3D_TARGET_WINDOWS)

# include "IEyeTracking.hpp"

namespace s3d
{
	class CEyeTracking_Windows : public ISiv3DEyeTracking
	{
	private:

	public:

		CEyeTracking_Windows();

		~CEyeTracking_Windows() override;

		bool init() override;

		void update() override;
	};
}

# endif
