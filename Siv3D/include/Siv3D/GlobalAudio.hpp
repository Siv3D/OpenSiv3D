//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Duration.hpp"

namespace s3d
{
	namespace GlobalAudio
	{
		void FadeVolume(double volume, const Duraton& time);

		void FadePan(double pan, const Duraton& time);

		void FadeSpeed(double speed, const Duraton& time);
	}
}
