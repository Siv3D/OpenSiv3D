//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "StringView.hpp"
# include "KlattTTSParameters.hpp"

namespace s3d
{
	namespace KlattTTS
	{
		void Speak(StringView text, const KlattTTSParameters& params = {});

		[[nodiscard]]
		bool IsSpeaking();

		void Pause();

		void Resume();

		void Stop();
	}
}
