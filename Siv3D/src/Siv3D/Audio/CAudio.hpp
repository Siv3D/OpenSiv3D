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
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "IAudio.hpp"
# include "AudioData.hpp"
# include "AudioBus.hpp"
# include "SoundTouchFunctions.hpp"
# include <Siv3D/DLL.hpp>

namespace s3d
{
	class CAudio final : public ISiv3DAudio
	{
	public:

		CAudio();

		~CAudio();

		void init() override;

		size_t getAudioCount() const override;

		Audio::IDType create(Wave&& wave, const Optional<AudioLoopTiming>& loop) override;

		Audio::IDType create(Wave&& wave, const Duration& loopBegin, const Duration& loopEnd) override;

		Audio::IDType createStreamingNonLoop(FilePathView path) override;

		Audio::IDType createStreamingLoop(FilePathView path, uint64 loopBegin) override;

		Audio::IDType createDynamic(const std::shared_ptr<IAudioStream>& pAudioStream, Arg::sampleRate_<uint32> sampleRate) override;

		void release(Audio::IDType handleID) override;

		bool isStreaming(Audio::IDType handleID) override;

		uint32 sampleRate(Audio::IDType handleID) override;

		size_t samples(Audio::IDType handleID) override;

		int64 samplesPlayed(Audio::IDType handleID) override;

		bool isActive(Audio::IDType handleID) override;

		bool isPlaying(Audio::IDType handleID) override;

		bool isPaused(Audio::IDType handleID) override;

		bool isLoop(Audio::IDType handleID) override;

		AudioLoopTiming getLoopTiming(Audio::IDType handleID) override;

		void setLoop(Audio::IDType handleID, bool loop) override;

		void setLoopPoint(Audio::IDType handleID, const Duration& loopBegin) override;

		void play(Audio::IDType handleID, size_t busIndex) override;

		void play(Audio::IDType handleID, size_t busIndex, const Duration& duration) override;

		void pause(Audio::IDType handleID) override;

		void pause(Audio::IDType handleID, const Duration& duration) override;

		void stop(Audio::IDType handleID) override;

		void stop(Audio::IDType handleID, const Duration& duration) override;


		uint32 createAudioGroup(const Array<Audio::IDType>& handleIDs, Array<uint32>& handles) override;


		void playOneShot(Audio::IDType handleID, size_t busIndex, double volume, double pan, double speed) override;

		void pauseAllShots(Audio::IDType handleID) override;

		void pauseAllShots(Audio::IDType handleID, const Duration& fadeTime) override;

		void resumeAllShots(Audio::IDType handleID) override;

		void resumeAllShots(Audio::IDType handleID, const Duration& fadeTime) override;

		void stopAllShots(Audio::IDType handleID) override;

		void stopAllShots(Audio::IDType handleID, const Duration& fadeTime) override;


		double posSec(Audio::IDType handleID) override;

		void seekTo(Audio::IDType handleID, const Duration& pos) override;

		size_t getLoopCount(Audio::IDType handleID) override;

		double getVolume(Audio::IDType handleID) override;

		void setVolume(Audio::IDType handleID, double volume) override;

		void fadeVolume(Audio::IDType handleID, double volume, const Duration& time) override;

		double getPan(Audio::IDType handleID) override;

		void setPan(Audio::IDType handleID, double pan) override;

		void fadePan(Audio::IDType handleID, double pan, const Duration& time) override;

		double getSpeed(Audio::IDType handleID) override;

		void setSpeed(Audio::IDType handleID, double speed) override;

		void fadeSpeed(Audio::IDType handleID, double speed, const Duration& time) override;

		const float* getSamples(Audio::IDType handleID, size_t channel) override;


		size_t getActiveVoiceCount() override;

		void globalPause() override;

		void globalResume() override;

		double getGlobalVolume() override;

		void setGlobalVolume(double volume) override;

		void fadeGlobalVolume(double volume, const Duration& time) override;

		void getGlobalSamples(Array<float>& samples) override;

		void getGlobalFFT(FFTResult& result) override;

		void getBusSamples(size_t busIndex, Array<float>& samples) override;

		void getBusFFT(size_t busIndex, FFTResult& result) override;

		double getBusVolume(size_t busIndex) override;

		void setBusVolume(size_t busIndex, double volume) override;

		void fadeBusVolume(size_t busIndex, double volume, const Duration& time) override;

		void clearFilter(size_t busIndex, size_t filterIndex) override;

		void setLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet) override;

		void setHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet) override;

		void setEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay, double wet) override;

		void setReverbFilter(size_t busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet) override;

		void setPitchShiftFilter(size_t busIndex, size_t filterIndex, double pitchShift) override;

		AudioBus& getBus(size_t busIndex) override;

		SoLoud::Soloud& getSoloud() override;

		const SoundTouchFunctions* getSoundTouchFunctions() const noexcept override;

		bool supportsPitchShift() const noexcept override;


		void speakKlatt(StringView text, const KlattTTSParameters& param) override;

		bool isSpeakingKlatt() override;

		void pauseKlatt() override;

		void resumeKlatt() override;

		void stopKlatt() override;

	private:

		static constexpr uint32 MaxActiveVoiceCount = 72; // hard limit: 1024

		std::unique_ptr<SoLoud::Soloud> m_soloud;
		
		std::array<std::unique_ptr<AudioBus>, Audio::MaxBusCount> m_buses;

		AssetHandleManager<Audio::IDType, AudioData> m_audios{ U"Audio" };

		LibraryHandle m_soundTouch = nullptr;

		bool m_soundTouchAvailable = false;

		SoundTouchFunctions m_soundTouchFunctions;

		std::unique_ptr<AudioData> m_speech;
	};
}
