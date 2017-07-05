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

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN8
# define  NTDDI_VERSION NTDDI_WIN8
# include <Windows.h>
# include <XAudio2.h>
# include <XAudio2fx.h>
# include <X3DAudio.h>
# include "../IAudio.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	struct AudioDevice28
	{
		IXAudio2* xAudio2 = nullptr;

		DWORD channelMask = 0;

		IXAudio2MasteringVoice* masteringVoice = nullptr;

		IUnknown* pXAPO = nullptr;

		X3DAUDIO_HANDLE x3DInstance;

		void release()
		{
			if (pXAPO)
			{
				pXAPO->Release();
				pXAPO = nullptr;
			}

			if (masteringVoice)
			{
				masteringVoice->DestroyVoice();
				masteringVoice = nullptr;
			}

			if (xAudio2)
			{
				xAudio2->Release();
				xAudio2 = nullptr;
			}
		}
	};

	enum class AudioControlState
	{
		PlayImmediately,
		
		PlayWithFade,
		
		PauseImmediately,
		
		PauseWithFade,
		
		StopImmediately,
		
		StopWithFade,
	};

	enum class VoiceState
	{
		Ready,

		Waiting,

		Done,

		EndOfStream,
	};

	struct AudioControlManager
	{
		Stopwatch m_stopwatch;

		double m_durationSec = 0.0;

		double m_currentVolume = 0.0;

		VoiceState voiceState = VoiceState::Ready;

		AudioControlState m_state = AudioControlState::StopImmediately;

		bool m_seekBegin = false;
	};

	class VoiceStream28 : public IXAudio2VoiceCallback
	{
	private:

		IXAudio2* m_xAudio2 = nullptr;

		const Wave* m_pWave;

		Wave m_buffer;

		Optional<std::pair<int64, int64>> m_loop;

		IXAudio2SourceVoice* m_sourceVoice = nullptr;

		uint64 m_samplesSent = 0;

		int64 m_writePos = 0;

		bool m_is3D = false;

		bool m_isActive = false;

		bool m_isPaused = false;

		bool m_isEnd = false;

		bool m_useStretcher = false;

		double m_maxSpeed = 2.0;

		void WINAPI OnVoiceProcessingPassStart(UINT32 bytes_required) override
		{
			//LOG_TEST(L"OnVoiceProcessingPassStart: {} bytes required"_fmt(bytes_required));

			const uint64 samplesPlayed = calculateSamplesPlayed();
			const uint64 samples_bufferTarget = m_pWave->samplingRate() / 30;
			const uint64 samples_buffer = m_samplesSent - samplesPlayed;

			if (bytes_required == 0 && samples_buffer > samples_bufferTarget / 2)
			{
				return;
			}

			const uint64 samples_required = bytes_required / sizeof(WaveSample);
			uint64 samples_toWrite = samples_required;

			if (samples_buffer < samples_bufferTarget)
			{
				samples_toWrite = std::max(samples_toWrite, samples_bufferTarget - samples_buffer);
			}

			samples_toWrite = std::min<uint64>(samples_toWrite, m_buffer.size());

			if (!m_loop)
			{
				if (m_useStretcher)
				{
					// [Siv3D ToDo]
				}
				else
				{
					processBufferNoLoop(samples_toWrite);
				}
			}
			else
			{
				if (m_useStretcher)
				{
					// [Siv3D ToDo]
				}
				else
				{
					// [Siv3D ToDo]
				}
			}
		}

		void WINAPI OnVoiceProcessingPassEnd() override
		{
			//LOG_TEST(L"OnVoiceProcessingPassEnd");
		}

		void WINAPI OnStreamEnd() override
		{
			//LOG_TEST(L"OnStreamEnd");

			m_sourceVoice->Stop();

			m_isActive = false;
			m_isPaused = false;
			m_isEnd = true;
			readPos = 0;
			m_writePos = 0;
			m_samplesSent = 0;
		}

		void WINAPI OnBufferStart(void*) override
		{
			//LOG_TEST(L"OnBufferStart");
		}

		void WINAPI OnBufferEnd(void*) override
		{
			//LOG_TEST(L"OnBufferEnd");
		}

		void WINAPI OnLoopEnd(void*) override
		{
			//LOG_TEST(L"OnLoopEnd");
		}

		void WINAPI OnVoiceError(void *, HRESULT) override
		{
			//LOG_TEST(L"OnVoiceError");
		}

		void processBufferNoLoop(uint64 samples_toRead)
		{
			if (readPos + samples_toRead > m_pWave->size())
			{
				samples_toRead = m_pWave->size() - readPos;
			}

			while (samples_toRead)
			{
				const uint64 samples_read = samples_toRead;
				const bool reachedEoS = (readPos + samples_read) == m_pWave->size();

				const XAUDIO2_BUFFER buffer =
				{
					reachedEoS ? static_cast<UINT32>(XAUDIO2_END_OF_STREAM) : 0,
					static_cast<UINT32>(samples_read * sizeof(WaveSample)),
					static_cast<const uint8*>(static_cast<const void*>(m_pWave->data())) + readPos * sizeof(WaveSample),
					0,
					static_cast<UINT32>(samples_read),
					0,
					0,
					XAUDIO2_NO_LOOP_REGION,
					nullptr
				};

				m_sourceVoice->SubmitSourceBuffer(&buffer);
				m_samplesSent += samples_read;

				samples_toRead -= samples_read;
				readPos += samples_read;
			}
		}

	public:

		int64 readPos = 0;

		VoiceStream28() = default;

		explicit VoiceStream28(IXAudio2* const xAudio2, const Wave& wave, const Optional<std::pair<int64, int64>>& loop)
			: m_xAudio2(xAudio2)
			, m_pWave(&wave)
			, m_buffer(wave.samplingRate(), WaveSample::Zero())
			, m_loop(loop)
		{

		}

		bool create(const bool is3D, const double maxSpeed)
		{
			const WAVEFORMATEX waveFormat =
			{
				static_cast<WORD>(WAVE_FORMAT_IEEE_FLOAT),
				static_cast<WORD>(m_is3D ? 1 : 2),
				m_pWave->samplingRate(),
				m_pWave->samplingRate() * sizeof(WaveSample),
				static_cast<WORD>(sizeof(WaveSample)),
				static_cast<WORD>(32),
				static_cast<WORD>(0)
			};

			if (FAILED(m_xAudio2->CreateSourceVoice(
				&m_sourceVoice,
				&waveFormat,
				is3D ? XAUDIO2_VOICE_USEFILTER : 0,
				static_cast<float>(maxSpeed),
				this,
				nullptr
			)))
			{
				return false;
			}

			m_isActive = false;
			m_isEnd = false;
			m_isPaused = false;
			//m_readPos = 0;
			m_writePos = 0;
			m_samplesSent = 0;
			//m_volume = { 1.0,1.0 };
			//m_currentTempo = 1.0;
			//m_currentPitchSemitones = 0.0;
			m_useStretcher = false;

			return true;
		}

		void destroy()
		{
			if (m_sourceVoice)
			{
				m_sourceVoice->Stop();
				m_sourceVoice->FlushSourceBuffers();
				m_sourceVoice->DestroyVoice();
				m_sourceVoice = nullptr;
			}
		}

		void setFadeVolume(const double volume)
		{
			m_sourceVoice->SetVolume(static_cast<float>(volume));
		}

		const Optional<std::pair<int64, int64>>& getLoop() const
		{
			return m_loop;
		}

		bool play()
		{
			if (m_isActive && !m_isPaused)
			{
				return true;
			}

			m_isActive = true;
			m_isPaused = false;
			m_isEnd = false;

			if (FAILED(m_sourceVoice->Start()))
			{
				m_isActive = false;
			
				return false;
			}

			return true;
		}

		void pause()
		{
			if (!m_isActive)
			{
				return;
			}

			m_sourceVoice->Stop();

			m_isPaused = true;
		}

		void stop()
		{
			if (!m_isActive)
			{
				return;
			}

			destroy();

			create(m_is3D, m_maxSpeed);
		}
		
		uint64 calculateSamplesPlayed()
		{
			XAUDIO2_VOICE_STATE state;
			
			m_sourceVoice->GetState(&state);
			
			return state.SamplesPlayed;
		}

		uint64 streamPosSample() const
		{
			return static_cast<uint64>(readPos);
		}

		bool readchedEnd() const
		{
			return m_isEnd;
		}

		//WaveStretcher stretcher;

		//std::mutex stretcherMutex;

		//double currentTempo = 1.0;

		//double currentPitchSemitones = 0.0;

		//std::pair<double, double> volume = { 1.0, 1.0 };

		//double speed = 1.0;

		//double minSpeed = XAUDIO2_MIN_FREQ_RATIO;
	};






	class Audio_XAudio28
	{
	private:

		AudioDevice28* m_device = nullptr;

		Wave m_wave;

		VoiceStream28 m_stream;

		AudioControlManager m_audioControl;

		bool m_is3D = false;

		bool m_initialized = false;

	public:

		Audio_XAudio28() = default;

		Audio_XAudio28(Wave&& wave, AudioDevice28* const device, const Optional<std::pair<int64, int64>>& loop, const double maxSpeed)
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

		~Audio_XAudio28()
		{
			m_stream.destroy();
		}

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		bool changeState(const AudioControlState state, const double durationSec)
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

		bool updateFadeManager()
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

		void setFadeVolume(const double volume)
		{
			assert(0.0 <= volume && volume <= 1.0);

			m_stream.setFadeVolume(volume * volume);
		}

		void setPosSample(int64 posSample)
		{
			const auto loop = m_stream.getLoop();

			if (loop && posSample >= loop->second)
			{
				posSample = loop->second - 1;
			}

			posSample = std::min<int64>(posSample, m_wave.size());

			m_stream.readPos = posSample;
		}

		uint64 samplesPlayed()
		{
			return m_stream.calculateSamplesPlayed();
		}

		uint64 streamPosSample() const
		{
			return m_stream.streamPosSample();
		}
	};

	class CAudio_XAudio28 : public ISiv3DAudio
	{
	private:

		HINSTANCE m_xaudio28 = nullptr;

		decltype(XAudio2Create)* p_XAudio2Create = nullptr;

		bool m_hasAudioDevice = false;

		AudioDevice28 m_device;

		double m_masterVolume = 1.0;

		AssetHandleManager<Audio::IDType, std::shared_ptr<Audio_XAudio28>> m_audios{ S3DSTR("Audio") };

		static std::atomic_bool fadeManagementEnabled;

		std::thread m_fadeManagingThread;

		std::mutex m_mutex;

	public:

		static bool IsAvalibale();

		CAudio_XAudio28();

		~CAudio_XAudio28() override;

		bool hasAudioDevice() const override;

		bool init() override;

		Audio::IDType create(Wave&& wave) override;

		void release(Audio::IDType handleID) override;

		bool play(Audio::IDType handleID, const SecondsF& fadeinDuration) override;

		void pause(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		void stop(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		uint64 samplesPlayed(Audio::IDType handleID) override;

		uint64 streamPosSample(Audio::IDType handleID) override;

		bool updateFade() override;
		
		void fadeMasterVolume() override;
	};
}

# endif
