//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "ISoundFont.hpp"
# define TSF_IMPLEMENTATION
# define TSF_STATIC
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4505)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4701)
# include <TinySoundFont/tsf.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	class CSoundFont : public ISiv3DSoundFont
	{
	private:

		tsf* m_standardSoundFont = nullptr;

		bool m_unavailable = false;

	public:

		CSoundFont();

		~CSoundFont() override;

		bool init() override;

		void render(Wave& wave, size_t samples, uint32 samplingRate, uint8 instrument, uint8 key, double velocity) override;
	};
}
