﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CAudio_AL.hpp"
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	CAudio_AL::CAudio_AL()
	{

	}

	CAudio_AL::~CAudio_AL()
	{
		m_audios.destroy();
		
		if (m_context)
		{
			m_device = ::alcGetContextsDevice(m_context);
			
			::alcMakeContextCurrent(nullptr);

			::alcDestroyContext(m_context);
			
			::alcCloseDevice(m_device);
		}
	}

	bool CAudio_AL::hasAudioDevice() const
	{
		// [Siv3D ToDo]
		return true;
	}

	bool CAudio_AL::init()
	{
		m_device = ::alcOpenDevice(nullptr);
		
		if (!m_device)
		{
			return false;
		}
		
		m_context = ::alcCreateContext(m_device, nullptr);
		
		if (!m_context)
		{
			return false;
		}
		
		if (!::alcMakeContextCurrent(m_context))
		{
			return false;
		}
		
		const auto nullAudio = std::make_shared<Audio_AL>(
			Wave(SecondsF(0.5), Arg::generator = [](double t) {
				return 0.5 * std::sin(t * Math::TwoPi) * std::sin(t * Math::TwoPi * 220.0 * (t * 4.0 + 1.0)); }));
		
		if (!nullAudio->isInitialized())
		{
			return false;
		}
		
		m_audios.setNullData(nullAudio);

		return true;
	}

	Audio::IDType CAudio_AL::create(Wave&& wave)
	{
		if (!wave)
		{
			return Audio::NullHandleID;
		}
		
		const auto audio = std::make_shared<Audio_AL>(std::move(wave));
		
		if (!audio->isInitialized())
		{
			return Audio::NullHandleID;
		}
		
		return m_audios.add(audio);
	}

	void CAudio_AL::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}

	uint32 CAudio_AL::samplingRate(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samplingRate();
	}

	size_t CAudio_AL::samples(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samples();
	}

	void CAudio_AL::setLoop(const Audio::IDType handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		return m_audios[handleID]->setLoop(loop);
	}

	bool CAudio_AL::play(const Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		// [Siv3D ToDo]
		m_audios[handleID]->changeState(AudioControlState::Playing);
		
		return true;
	}
	
	void CAudio_AL::pause(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
		m_audios[handleID]->changeState(AudioControlState::Paused);
	}
	
	void CAudio_AL::stop(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
		m_audios[handleID]->changeState(AudioControlState::Stopped);
	}

	bool CAudio_AL::isPlaying(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isPlaying();
	}

	bool CAudio_AL::isPaused(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isPaused();
	}

	uint64 CAudio_AL::posSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_AL::streamPosSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_AL::samplesPlayed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return m_audios[handleID]->getSamplesPlayed();
	}

	const Wave& CAudio_AL::getWave(Audio::IDType handleID)
	{
		return m_audios[handleID]->getWave();
	}

	void CAudio_AL::setVolume(const Audio::IDType handleID, const std::pair<double, double>& volume)
	{
		// [Siv3D ToDo]
	}

	std::pair<double, double> CAudio_AL::getVolume(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
	}

	void CAudio_AL::setSpeed(const Audio::IDType handleID, const double speed)
	{
		// [Siv3D ToDo]
	}

	double CAudio_AL::getSpeed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	std::pair<double, double> CAudio_AL::getMinMaxSpeed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
	}

	bool CAudio_AL::updateFade()
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_AL::fadeMasterVolume()
	{
		// [Siv3D ToDo]
	}
}

# endif
