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

# include <Siv3D/KlattTTS.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace KlattTTS
	{
		void Speak(const StringView text, const KlattTTSParameters& params)
		{
			SIV3D_ENGINE(Audio)->speakKlatt(text, params);
		}

		bool IsSpeaking()
		{
			return SIV3D_ENGINE(Audio)->isSpeakingKlatt();
		}

		void Pause()
		{
			SIV3D_ENGINE(Audio)->pauseKlatt();
		}

		void Resume()
		{
			SIV3D_ENGINE(Audio)->resumeKlatt();
		}

		void Stop()
		{
			SIV3D_ENGINE(Audio)->stopKlatt();
		}
	}
}
