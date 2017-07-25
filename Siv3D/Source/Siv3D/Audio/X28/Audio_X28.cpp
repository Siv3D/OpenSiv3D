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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "Audio_X28.hpp"

namespace s3d
{
	Audio_X28::Audio_X28(Wave&& wave, AudioDevice_X28* const device, const Optional<std::pair<int64, int64>>& loop, const double maxSpeed)
		: m_device(device)
		, m_wave(std::move(wave))
		, m_stream(m_device->xAudio2, m_wave, loop)
	{
		assert(device);

		if (!m_wave)
		{
			return;
		}

		if (!m_stream.create(false, maxSpeed))
		{
			return;
		}

		m_initialized = true;
	}

	Audio_X28::~Audio_X28()
	{
		m_stream.destroy();
	}

	bool Audio_X28::isInitialized() const noexcept
	{
		return m_initialized;
	}

	uint32 Audio_X28::samplingRate() const
	{
		return m_wave.samplingRate();
	}

	size_t Audio_X28::samples() const
	{
		return m_wave.size();
	}

	void Audio_X28::setLoop(const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		m_stream.setLoop(loop, loopBeginSample, loopEndSample);
	}

	bool Audio_X28::changeState(const AudioControlState state, const double durationSec)
	{
		const auto currentState = m_audioControl.m_state;
		const auto currentVoiceState = m_audioControl.voiceState;

		if (state == AudioControlState::PlayImmediately || state == AudioControlState::PlayWithFade)
		{
			if ((currentState == AudioControlState::PlayImmediately || currentState == AudioControlState::PlayWithFade)
				&& currentVoiceState == VoiceState::Done)
			{
				return true;
			}
		}

		if (state == AudioControlState::PauseImmediately || state == AudioControlState::PauseWithFade)
		{
			if (currentState == AudioControlState::PauseImmediately || currentState == AudioControlState::PauseWithFade)
			{
				return true;
			}
		}

		m_audioControl.m_state = state;
		m_audioControl.m_durationSec = durationSec;
		m_audioControl.voiceState = VoiceState::Ready;
		m_audioControl.m_stopwatch.reset();

		return updateFadeManager();
	}

	bool Audio_X28::updateFadeManager()
	{
		switch (m_audioControl.m_state)
		{
		case AudioControlState::PlayImmediately:
			{
				if (m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.reset();
				}

				if (m_audioControl.m_currentVolume != 1.0)
				{
					m_audioControl.m_currentVolume = 1.0;

					setFadeVolume(1.0);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					if (m_audioControl.m_seekBegin)
					{
						m_audioControl.m_seekBegin = false;

						setPosSample(0);
					}

					m_audioControl.voiceState = VoiceState::Done;

					m_stream.play();
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{
					if (m_stream.readchedEnd())
					{
						m_audioControl.voiceState = VoiceState::EndOfStream;
					}
					else
					{

					}
				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		case AudioControlState::PlayWithFade:
			{
				if (!m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.restart();
				}

				const double tVolume = std::min(m_audioControl.m_stopwatch.sF() / m_audioControl.m_durationSec, 1.0);

				if (tVolume != m_audioControl.m_currentVolume)
				{
					setFadeVolume(m_audioControl.m_currentVolume = tVolume);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					if (m_audioControl.m_seekBegin)
					{
						m_audioControl.m_seekBegin = false;

						setPosSample(0);
					}

					m_audioControl.voiceState = VoiceState::Done;

					m_stream.play();
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{
					if (m_stream.readchedEnd())
					{
						m_audioControl.voiceState = VoiceState::EndOfStream;
					}
					else
					{

					}
				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		case AudioControlState::PauseImmediately:
			{
				if (m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.reset();
				}

				if (m_audioControl.m_currentVolume != 0.0)
				{
					m_audioControl.m_currentVolume = 0.0;

					setFadeVolume(0.0);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					m_audioControl.voiceState = VoiceState::Done;

					m_stream.pause();
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{

				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		case AudioControlState::PauseWithFade:
			{
				if (!m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.restart();
				}

				const double elapsedSec = m_audioControl.m_stopwatch.sF();
				const double tVolume = 1.0 - std::min(elapsedSec / m_audioControl.m_durationSec, 1.0);

				if (std::min(tVolume, m_audioControl.m_currentVolume) != m_audioControl.m_currentVolume)
				{
					setFadeVolume(m_audioControl.m_currentVolume = tVolume);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					m_audioControl.voiceState = VoiceState::Waiting;
				}
				else if (m_audioControl.voiceState == VoiceState::Waiting)
				{
					if (elapsedSec >= m_audioControl.m_durationSec)
					{
						m_audioControl.voiceState = VoiceState::Done;

						m_stream.pause();
					}
					else
					{

					}
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{

				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		case AudioControlState::StopImmediately:
			{
				if (m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.reset();
				}

				if (m_audioControl.m_currentVolume != 0.0)
				{
					m_audioControl.m_currentVolume = 0.0;

					setFadeVolume(0.0);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					m_audioControl.voiceState = VoiceState::Done;

					m_stream.stop();
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{

				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		case AudioControlState::StopWithFade:
			{
				if (!m_audioControl.m_stopwatch.isStarted())
				{
					m_audioControl.m_stopwatch.restart();
				}

				const double elapsedSec = m_audioControl.m_stopwatch.sF();
				const double tVolume = 1.0 - std::min(elapsedSec / m_audioControl.m_durationSec, 1.0);

				if (std::min(tVolume, m_audioControl.m_currentVolume) != m_audioControl.m_currentVolume)
				{
					setFadeVolume(m_audioControl.m_currentVolume = tVolume);
				}

				if (m_audioControl.voiceState == VoiceState::Ready)
				{
					m_audioControl.m_seekBegin = true;

					m_audioControl.voiceState = VoiceState::Waiting;
				}
				else if (m_audioControl.voiceState == VoiceState::Waiting)
				{
					if (elapsedSec >= m_audioControl.m_durationSec)
					{
						m_audioControl.voiceState = VoiceState::Done;

						m_stream.stop();

						m_audioControl.m_seekBegin = false;
					}
					else
					{

					}
				}
				else if (m_audioControl.voiceState == VoiceState::Done)
				{

				}
				else if (m_audioControl.voiceState == VoiceState::EndOfStream)
				{

				}

				break;
			}
		}

		return true;
	}

	void Audio_X28::setFadeVolume(const double volume)
	{
		assert(0.0 <= volume && volume <= 1.0);

		m_stream.setFadeVolume(volume * volume);
	}

	void Audio_X28::setPosSample(int64 posSample)
	{
		const auto loop = m_stream.getLoop();

		if (loop && posSample >= loop->second)
		{
			posSample = loop->second - 1;
		}

		posSample = std::min<int64>(posSample, m_wave.size());

		m_stream.setReadPos(posSample);
	}

	uint64 Audio_X28::posSample()
	{
		return m_stream.calculatePosSample();
	}

	uint64 Audio_X28::streamPosSample() const
	{
		return m_stream.streamPosSample();
	}

	uint64 Audio_X28::samplesPlayed()
	{
		return m_stream.getSamplesPlayed();
	}

	void Audio_X28::setVolume(const std::pair<double, double>& volume)
	{
		m_stream.setVolume(volume);
	}

	std::pair<double, double> Audio_X28::getVolume() const
	{
		return m_stream.getVolume();
	}

	void Audio_X28::setSpeed(const double speed)
	{
		m_stream.setSpeed(speed);
	}

	double Audio_X28::getSpeed() const
	{
		return m_stream.getSpeed();
	}

	std::pair<double, double> Audio_X28::getMinMaxSpeed() const
	{
		return m_stream.getMinMaxSpeed();
	}
}

# endif
