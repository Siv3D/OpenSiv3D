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
# include <Siv3D/Common.hpp>
# include <Siv3D/Audio.hpp>

namespace SoLoud
{
	class Soloud;
}

namespace s3d
{
	class AudioBus;
	struct FFTResult;
	struct SoundTouchFunctions;
	struct KlattTTSParameters;

	class SIV3D_NOVTABLE ISiv3DAudio
	{
	public:

		static ISiv3DAudio* Create();

		virtual ~ISiv3DAudio() = default;

		virtual void init() = 0;

		virtual size_t getAudioCount() const = 0;

		virtual Audio::IDType create(Wave&& wave, const Optional<AudioLoopTiming>& loop) = 0;

		virtual Audio::IDType create(Wave&& wave, const Duration& loopBegin, const Duration& loopEnd) = 0;

		virtual Audio::IDType createStreamingNonLoop(FilePathView path) = 0;

		virtual Audio::IDType createStreamingLoop(FilePathView path, uint64 loopBegin) = 0;

		virtual Audio::IDType createDynamic(const std::shared_ptr<IAudioStream>& pAudioStream, Arg::sampleRate_<uint32> sampleRate) = 0;

		virtual void release(Audio::IDType handleID) = 0;

		virtual bool isStreaming(Audio::IDType handleID) = 0;

		virtual uint32 sampleRate(Audio::IDType handleID) = 0;

		virtual size_t samples(Audio::IDType handleID) = 0;

		virtual int64 samplesPlayed(Audio::IDType handleID) = 0;

		virtual bool isActive(Audio::IDType handleID) = 0;

		virtual bool isPlaying(Audio::IDType handleID) = 0;

		virtual bool isPaused(Audio::IDType handleID) = 0;

		virtual bool isLoop(Audio::IDType handleID) = 0;

		virtual AudioLoopTiming getLoopTiming(Audio::IDType handleID) = 0;

		virtual void setLoop(Audio::IDType handleID, bool loop) = 0;

		virtual void setLoopPoint(Audio::IDType handleID, const Duration& loopBegin) = 0;

		virtual void play(Audio::IDType handleID, size_t busIndex) = 0;

		virtual void play(Audio::IDType handleID, size_t busIndex, const Duration& duration) = 0;

		virtual void pause(Audio::IDType handleID) = 0;

		virtual void pause(Audio::IDType handleID, const Duration& duration) = 0;

		virtual void stop(Audio::IDType handleID) = 0;

		virtual void stop(Audio::IDType handleID, const Duration& duration) = 0;


		virtual uint32 createAudioGroup(const Array<Audio::IDType>& handleIDs, Array<uint32>& handles) = 0;


		virtual void playOneShot(Audio::IDType handleID, size_t busIndex, double volume, double pan, double speed) = 0;

		virtual void pauseAllShots(Audio::IDType handleID) = 0;

		virtual void pauseAllShots(Audio::IDType handleID, const Duration& fadeTime) = 0;

		virtual void resumeAllShots(Audio::IDType handleID) = 0;

		virtual void resumeAllShots(Audio::IDType handleID, const Duration& fadeTime) = 0;

		virtual void stopAllShots(Audio::IDType handleID) = 0;

		virtual void stopAllShots(Audio::IDType handleID, const Duration& fadeTime) = 0;


		virtual double posSec(Audio::IDType handleID) = 0;

		virtual void seekTo(Audio::IDType handleID, const Duration& pos) = 0;

		virtual size_t getLoopCount(Audio::IDType handleID) = 0;

		virtual double getVolume(Audio::IDType handleID) = 0;

		virtual void setVolume(Audio::IDType handleID, double volume) = 0;

		virtual void fadeVolume(Audio::IDType handleID, double volume, const Duration& time) = 0;

		virtual double getPan(Audio::IDType handleID) = 0;

		virtual void setPan(Audio::IDType handleID, double pan) = 0;

		virtual void fadePan(Audio::IDType handleID, double pan, const Duration& time) = 0;

		virtual double getSpeed(Audio::IDType handleID) = 0;

		virtual void setSpeed(Audio::IDType handleID, double speed) = 0;

		virtual void fadeSpeed(Audio::IDType handleID, double speed, const Duration& time) = 0;

		virtual const float* getSamples(Audio::IDType handleID, size_t channel) = 0;


		virtual size_t getActiveVoiceCount() = 0;

		virtual void globalPause() = 0;

		virtual void globalResume() = 0;

		virtual double getGlobalVolume() = 0;

		virtual void setGlobalVolume(double volume) = 0;

		virtual void fadeGlobalVolume(double volume, const Duration& time) = 0;

		virtual void getGlobalSamples(Array<float>& samples) = 0;

		virtual void getGlobalFFT(FFTResult& result) = 0;

		virtual void getBusSamples(size_t busIndex, Array<float>& samples) = 0;

		virtual void getBusFFT(size_t busIndex, FFTResult& result) = 0;

		virtual double getBusVolume(size_t busIndex) = 0;

		virtual void setBusVolume(size_t busIndex, double volume) = 0;

		virtual void fadeBusVolume(size_t busIndex, double volume, const Duration& time) = 0;

		virtual void clearFilter(size_t busIndex, size_t filterIndex) = 0;

		virtual void setLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet) = 0;

		virtual void setHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet) = 0;

		virtual void setEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay, double wet) = 0;

		virtual void setReverbFilter(size_t busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet) = 0;

		virtual void setPitchShiftFilter(size_t busIndex, size_t filterIndex, double pitchShift) = 0;

		virtual AudioBus& getBus(size_t busIndex) = 0;

		virtual SoLoud::Soloud& getSoloud() = 0;

		virtual const SoundTouchFunctions* getSoundTouchFunctions() const noexcept = 0;

		virtual bool supportsPitchShift() const noexcept = 0;



		virtual void speakKlatt(StringView text, const KlattTTSParameters& param) = 0;

		virtual bool isSpeakingKlatt() = 0;

		virtual void pauseKlatt() = 0;

		virtual void resumeKlatt() = 0;

		virtual void stopKlatt() = 0;
	};
}
