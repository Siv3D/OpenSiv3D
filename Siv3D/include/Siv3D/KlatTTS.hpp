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
# include "StringView.hpp"
# include "KlatTTSParameters.hpp"

namespace s3d
{
	namespace KlatTTS
	{
		void Speak(StringView text, const KlatTTSParameters& params = {});

		[[nodiscard]]
		bool IsSpeaking();

		void Pause();

		void Resume();

		void Stop();
	}
}
