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
# if defined(SIV3D_TARGET_WINDOWS)

# include "../IAudio.hpp"

namespace s3d
{
	class CAudio_XAudio28 : public ISiv3DAudio
	{
	private:

	public:

		static bool IsAvalibale();

		CAudio_XAudio28();

		~CAudio_XAudio28() override;

		bool init() override;
	};
}

# endif
