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

# include <Siv3D/Audio.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		static void CheckEngine()
		{
			if (not Siv3DEngine::isActive())
			{
				Troubleshooting::Show(Troubleshooting::Error::AssetInitializationBeforeEngineStartup, U"Audio");
				std::exit(EXIT_FAILURE);
			}
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Audio>>::AssetIDWrapper()
	{
		detail::CheckEngine();
	}

	template <>
	AssetIDWrapper<AssetHandle<Audio>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Audio))
		{
			p->release(m_id);
		}
	}

	Audio::Audio() {}

	Audio::Audio(Wave&& wave)
		: Audio{ std::move(wave), Loop::No } {}

	Audio::Audio(Wave&& wave, const Loop loop)
		: Audio{ std::move(wave), (loop ? Optional<AudioLoopTiming>{{ 0, 0 }} : none) } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ std::move(wave), AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ std::move(wave), AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ std::move(wave), loopBegin, Arg::loopEnd = Duration{ 0 } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(std::move(wave), *loopBegin, *loopEnd))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(std::move(wave), loop))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const Wave& wave)
		: Audio{ wave, Loop::No } {}

	Audio::Audio(const Wave& wave, const Loop loop)
		: Audio{ wave, (loop ? Optional<AudioLoopTiming>{{ 0, 0 }} : none) } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ wave, AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ wave, AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ wave, AudioLoopTiming{ static_cast<uint64>(loopBegin->count() * wave.sampleRate()), 0 } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio{ wave, AudioLoopTiming{ static_cast<uint64>(loopBegin->count() * wave.sampleRate()), static_cast<uint64>(loopEnd->count() * wave.sampleRate()) } } {}

	Audio::Audio(const Wave& wave, const Optional<AudioLoopTiming>& loop)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(Wave{ wave }, loop))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const FilePathView path)
		: Audio{ path, Loop::No } {}

	Audio::Audio(const FilePathView path, const Loop loop)
		: Audio{ (detail::CheckEngine(), Wave{ path }), loop } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ path, AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ path, AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ path, loopBegin, Arg::loopEnd = Duration{ 0 } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio{ (detail::CheckEngine(), Wave{ path }), loopBegin, loopEnd } {}

	Audio::Audio(const FilePathView path, const Optional<AudioLoopTiming>& loop)
		: Audio{ (detail::CheckEngine(), Wave{ path }), loop } {}

	Audio::Audio(FileStreaming, const FilePathView path)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->createStreamingNonLoop(path))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(FileStreaming, const FilePathView path, const Loop loop)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(
			((loop ? SIV3D_ENGINE(Audio)->createStreamingLoop(path, 0) : SIV3D_ENGINE(Audio)->createStreamingNonLoop(path))))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(FileStreaming, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->createStreamingLoop(path, *loopBegin))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const GMInstrument instrument, const uint8 key, const Duration& duration, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
		: Audio{ (detail::CheckEngine(), Wave{ instrument, key, duration, velocity, sampleRate }) } {}

	Audio::Audio(const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
		: Audio{ (detail::CheckEngine(), Wave{ instrument, key, noteOn, noteOff, velocity, sampleRate }) } {}

	Audio::Audio(IReader&& reader, const AudioFormat format)
		: Audio{ (detail::CheckEngine(), Wave{ std::move(reader), format }) } {}

	Audio::Audio(const std::shared_ptr<IAudioStream>& pAudioStream, const Arg::sampleRate_<uint32> sampleRate)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->createDynamic(pAudioStream, sampleRate))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::~Audio() {}

	bool Audio::isStreaming() const
	{
		return SIV3D_ENGINE(Audio)->isStreaming(m_handle->id());
	}

	uint32 Audio::sampleRate() const
	{
		return SIV3D_ENGINE(Audio)->sampleRate(m_handle->id());
	}

	size_t Audio::samples() const
	{
		return SIV3D_ENGINE(Audio)->samples(m_handle->id());
	}

	double Audio::lengthSec() const
	{
		const size_t samples = SIV3D_ENGINE(Audio)->samples(m_handle->id());
		const size_t sampleRate = SIV3D_ENGINE(Audio)->sampleRate(m_handle->id());

		if (sampleRate == 0)
		{
			return 0.0;
		}

		return (static_cast<double>(samples) / sampleRate);
	}

	int64 Audio::samplesPlayed() const
	{
		return SIV3D_ENGINE(Audio)->samplesPlayed(m_handle->id());
	}

	bool Audio::isActive() const
	{
		return SIV3D_ENGINE(Audio)->isActive(m_handle->id());
	}

	bool Audio::isPlaying() const
	{
		return SIV3D_ENGINE(Audio)->isPlaying(m_handle->id());
	}

	bool Audio::isPaused() const
	{
		return SIV3D_ENGINE(Audio)->isPaused(m_handle->id());
	}

	bool Audio::isLoop() const
	{
		return SIV3D_ENGINE(Audio)->isLoop(m_handle->id());
	}

	AudioLoopTiming Audio::getLoopTiming() const
	{
		return SIV3D_ENGINE(Audio)->getLoopTiming(m_handle->id());
	}

	void Audio::setLoop(const bool loop) const
	{
		SIV3D_ENGINE(Audio)->setLoop(m_handle->id(), loop);
	}

	void Audio::setLoopPoint(const uint64 loopBegin) const
	{
		const size_t sampleRate = SIV3D_ENGINE(Audio)->sampleRate(m_handle->id());
		const double loopBeginSec = (static_cast<double>(loopBegin) / sampleRate);

		SIV3D_ENGINE(Audio)->setLoopPoint(m_handle->id(), SecondsF{ loopBeginSec });
	}

	void Audio::setLoopPoint(const Duration& loopBegin) const
	{
		SIV3D_ENGINE(Audio)->setLoopPoint(m_handle->id(), Max(loopBegin, SecondsF{ 0.0 }));
	}

	void Audio::play(const MixBus busIndex) const
	{
		SIV3D_ENGINE(Audio)->play(m_handle->id(), FromEnum(busIndex));
	}

	void Audio::play(const Duration& fadeTime, const MixBus busIndex) const
	{
		play(busIndex, fadeTime);
	}

	void Audio::play(const MixBus busIndex, const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->play(m_handle->id(), FromEnum(busIndex), fadeTime);
	}

	void Audio::pause() const
	{
		SIV3D_ENGINE(Audio)->pause(m_handle->id());
	}

	void Audio::pause(const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->pause(m_handle->id(), fadeTime);
	}

	void Audio::stop() const
	{
		SIV3D_ENGINE(Audio)->stop(m_handle->id());
	}

	void Audio::stop(const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->stop(m_handle->id(), fadeTime);
	}

	void Audio::playOneShot(const double volume, const double pan, const double speed, const MixBus busIndex) const
	{
		playOneShot(busIndex, volume, pan, speed);
	}

	void Audio::playOneShot(const MixBus busIndex, const double volume, const double pan, const double speed) const
	{
		SIV3D_ENGINE(Audio)->playOneShot(m_handle->id(), FromEnum(busIndex), volume, pan, speed);
	}

	void Audio::pauseAllShots() const
	{
		SIV3D_ENGINE(Audio)->pauseAllShots(m_handle->id());
	}

	void Audio::pauseAllShots(const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->pauseAllShots(m_handle->id(), fadeTime);
	}

	void Audio::resumeAllShots() const
	{
		SIV3D_ENGINE(Audio)->resumeAllShots(m_handle->id());
	}

	void Audio::resumeAllShots(const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->resumeAllShots(m_handle->id(), fadeTime);
	}

	void Audio::stopAllShots() const
	{
		SIV3D_ENGINE(Audio)->stopAllShots(m_handle->id());
	}

	void Audio::stopAllShots(const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->stopAllShots(m_handle->id(), fadeTime);
	}

	int64 Audio::posSample() const
	{
		const double posSec = SIV3D_ENGINE(Audio)->posSec(m_handle->id());
		const size_t sampleRate = SIV3D_ENGINE(Audio)->sampleRate(m_handle->id());

		return static_cast<int64>(posSec * sampleRate);
	}

	double Audio::posSec() const
	{
		return SIV3D_ENGINE(Audio)->posSec(m_handle->id());
	}

	void Audio::seekSamples(const size_t posSample) const
	{
		const size_t sampleRate = SIV3D_ENGINE(Audio)->sampleRate(m_handle->id());

		SIV3D_ENGINE(Audio)->seekTo(m_handle->id(), SecondsF{ (static_cast<double>(posSample) / sampleRate) });
	}

	void Audio::seekTime(const double posSec) const
	{
		seekTime(SecondsF{ posSec });
	}

	void Audio::seekTime(const Duration& pos) const
	{
		SIV3D_ENGINE(Audio)->seekTo(m_handle->id(), Max(pos, SecondsF(0.0)));
	}

	size_t Audio::loopCount() const
	{
		return SIV3D_ENGINE(Audio)->getLoopCount(m_handle->id());
	}

	double Audio::getVolume() const
	{
		return SIV3D_ENGINE(Audio)->getVolume(m_handle->id());
	}

	const Audio& Audio::setVolume(const double volume) const
	{
		SIV3D_ENGINE(Audio)->setVolume(m_handle->id(), volume);

		return *this;
	}

	const Audio& Audio::fadeVolume(const double volume, const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->fadeVolume(m_handle->id(), volume, fadeTime);

		return *this;
	}

	double Audio::getPan() const
	{
		return SIV3D_ENGINE(Audio)->getPan(m_handle->id());
	}

	const Audio& Audio::setPan(const double pan) const
	{
		SIV3D_ENGINE(Audio)->setPan(m_handle->id(), Clamp(pan, -1.0, 1.0));

		return *this;
	}

	const Audio& Audio::fadePan(const double pan, const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->fadePan(m_handle->id(), Clamp(pan, -1.0, 1.0), fadeTime);

		return *this;
	}

	double Audio::getSpeed() const
	{
		return SIV3D_ENGINE(Audio)->getSpeed(m_handle->id());
	}

	const Audio& Audio::setSpeed(const double speed) const
	{
		SIV3D_ENGINE(Audio)->setSpeed(m_handle->id(), speed);

		return *this;
	}

	const Audio& Audio::fadeSpeed(const double speed, const Duration& fadeTime) const
	{
		SIV3D_ENGINE(Audio)->fadeSpeed(m_handle->id(), speed, fadeTime);

		return *this;
	}

	const Audio& Audio::setSpeedBySemitone(const int32 semitone) const
	{
		return setSpeed(std::exp2(semitone / 12.0));
	}

	const Audio& Audio::fadeSpeedBySemitone(const int32 semitone, const Duration& fadeTime) const
	{
		return fadeSpeed(std::exp2(semitone / 12.0), fadeTime);
	}

	const float* Audio::getSamples(const size_t channel) const
	{
		if (2 <= channel)
		{
			return nullptr;
		}

		return SIV3D_ENGINE(Audio)->getSamples(m_handle->id(), channel);
	}

	void Audio::swap(Audio& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
