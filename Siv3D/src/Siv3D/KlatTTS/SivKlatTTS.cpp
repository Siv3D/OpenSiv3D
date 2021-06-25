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

# include <Siv3D/KlatTTS.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace KlatTTS
	{
		void Speak(const StringView text, const KlatTTSParameters& params)
		{
			SIV3D_ENGINE(Audio)->speakKlat(text, params);
		}

		bool IsSpeaking()
		{
			return SIV3D_ENGINE(Audio)->isSpeakingKlat();
		}

		void Pause()
		{
			SIV3D_ENGINE(Audio)->pauseKlat();
		}

		void Resume()
		{
			SIV3D_ENGINE(Audio)->resumeKlat();
		}

		void Stop()
		{
			SIV3D_ENGINE(Audio)->stopKlat();
		}
	}
}
