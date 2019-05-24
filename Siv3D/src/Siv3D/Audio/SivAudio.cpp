//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include "IAudio.hpp"

namespace s3d
{
	template <>
	AssetHandle<Audio::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Audio` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Audio::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Audio` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Audio::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DAudio>())
		{
			p->release(m_id);
		}
	}

	Audio::Audio()
		: m_handle(std::make_shared<AudioHandle>())
	{

	}

	Audio::Audio(Wave&& wave)
		: m_handle(std::make_shared<AudioHandle>(Siv3DEngine::Get<ISiv3DAudio>()->create(std::move(wave))))
	{
		ReportAssetCreation();
	}

	Audio::Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop)
		: Audio(std::move(wave))
	{
		if (loop)
		{
			if (loop->endPos)
			{
				setLoop(Arg::loopBegin = loop->beginPos, Arg::loopEnd = loop->endPos);
			}
			else
			{
				setLoop(Arg::loopBegin = loop->beginPos);
			}
		}
	}

	Audio::Audio(Wave&& wave, const Arg::loop_<bool> loop)
		: Audio(std::move(wave))
	{
		if (*loop)
		{
			setLoop(true);
		}
	}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin);
	}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin, loopEnd);
	}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin);
	}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin, loopEnd);
	}

	Audio::Audio(const Wave& wave)
		: Audio(Wave(wave))
	{

	}

	Audio::Audio(const Wave& wave, const Optional<AudioLoopTiming>& loop)
		: Audio(Wave(wave), loop)
	{

	}

	Audio::Audio(const Wave& wave, Arg::loop_<bool> loop)
		: Audio(Wave(wave), loop)
	{

	}

	Audio::Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin)
		: Audio(Wave(wave), loopBegin)
	{

	}

	Audio::Audio(const Wave& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd)
		: Audio(Wave(wave), loopBegin, loopEnd)
	{

	}

	Audio::Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin)
		: Audio(Wave(wave), loopBegin)
	{

	}

	Audio::Audio(const Wave& wave, Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd)
		: Audio(Wave(wave), loopBegin, loopEnd)
	{

	}

	Audio::Audio(const FilePath& path)
		: Audio(Wave(path))
	{

	}

	Audio::Audio(const FilePath& path, const Optional<AudioLoopTiming>& loop)
		: Audio(path)
	{
		if (loop)
		{
			if (loop->endPos)
			{
				setLoop(Arg::loopBegin = loop->beginPos, Arg::loopEnd = loop->endPos);
			}
			else
			{
				setLoop(Arg::loopBegin = loop->beginPos);
			}
		}
	}

	Audio::Audio(const FilePath& path, const Arg::loop_<bool> loop)
		: Audio(path)
	{
		if (*loop)
		{
			setLoop(true);
		}
	}

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<uint64> loopBegin)
		: Audio(path)
	{
		setLoop(loopBegin);
	}

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio(path)
	{
		setLoop(loopBegin, loopEnd);
	}

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<Duration> loopBegin)
		: Audio(path)
	{
		setLoop(loopBegin);
	}

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio(path)
	{
		setLoop(loopBegin, loopEnd);
	}

	Audio::Audio(IReader&& reader, const AudioFormat format)
		: Audio(Wave(std::move(reader), format))
	{

	}

	Audio::~Audio()
	{

	}

	void Audio::release()
	{
		m_handle = std::make_shared<AudioHandle>();
	}

	bool Audio::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	AudioID Audio::id() const
	{
		return m_handle->id();
	}

	bool Audio::operator ==(const Audio& audio) const
	{
		return m_handle->id() == audio.m_handle->id();
	}

	bool Audio::operator !=(const Audio& audio) const
	{
		return m_handle->id() != audio.m_handle->id();
	}

	uint32 Audio::samplingRate() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->samplingRate(m_handle->id());
	}

	size_t Audio::samples() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->samples(m_handle->id());
	}

	void Audio::setLoop(const bool loop)
	{
		Siv3DEngine::Get<ISiv3DAudio>()->setLoop(
			m_handle->id(),
			loop,
			0,
			loop ? samples() - 1 : 0);
	}

	void Audio::setLoop(const Arg::loopBegin_<uint64> loopBegin)
	{
		assert(*loopBegin < samples());

		const uint64 loopBeginSample = *loopBegin;
		const uint64 loopEndSample = samples() - 1;

		Siv3DEngine::Get<ISiv3DAudio>()->setLoop(
			m_handle->id(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	void Audio::setLoop(const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
	{
		assert(*loopBegin < samples());
		assert(*loopBegin < *loopEnd);

		const uint64 loopBeginSample = *loopBegin;
		const uint64 loopEndSample = std::min<uint64>(*loopEnd, samples() - 1);

		Siv3DEngine::Get<ISiv3DAudio>()->setLoop(
			m_handle->id(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	void Audio::setLoop(const Arg::loopBegin_<Duration> loopBegin)
	{
		const uint64 loopBeginSample = static_cast<uint64>(samplingRate() * std::max(loopBegin->count(), 0.0));
		const uint64 loopEndSample = samples() - 1;

		assert(loopBeginSample < loopEndSample);

		Siv3DEngine::Get<ISiv3DAudio>()->setLoop(
			m_handle->id(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	void Audio::setLoop(const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
	{
		const uint64 loopBeginSample = static_cast<uint64>(samplingRate() * std::max(loopBegin->count(), 0.0));
		const uint64 loopEndSample = std::min<uint64>(static_cast<uint64>(samplingRate() * std::max(loopEnd->count(), 0.0)), samples() - 1);

		assert(loopBeginSample < loopEndSample);

		Siv3DEngine::Get<ISiv3DAudio>()->setLoop(
			m_handle->id(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	Optional<AudioLoopTiming> Audio::getLoop() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->getLoop(m_handle->id());
	}

	bool Audio::isLoop() const
	{
		return getLoop().has_value();
	}

	bool Audio::play(const Duration& fadeinDuration) const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->play(m_handle->id(), fadeinDuration);
	}

	void Audio::pause(const Duration& fadeoutDuration) const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->pause(m_handle->id(), fadeoutDuration);
	}

	void Audio::stop(const Duration& fadeoutDuration) const
	{
		Siv3DEngine::Get<ISiv3DAudio>()->stop(m_handle->id(), fadeoutDuration);
	}

	void Audio::playOneShot(const double volume, const double pitch) const
	{
		Siv3DEngine::Get<ISiv3DAudio>()->playOneShot(m_handle->id(), volume, pitch);
	}

	void Audio::stopAllShots() const
	{
		Siv3DEngine::Get<ISiv3DAudio>()->stopAllShots(m_handle->id());
	}

	bool Audio::isPlaying() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->isPlaying(m_handle->id());
	}

	bool Audio::isPaused() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->isPaused(m_handle->id());
	}

	int64 Audio::posSample() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->posSample(m_handle->id());
	}

	double Audio::posSec() const
	{
		return static_cast<double>(posSample()) / samplingRate();
	}

	int64 Audio::streamPosSample() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->streamPosSample(m_handle->id());
	}

	int64 Audio::samplesPlayed() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->samplesPlayed(m_handle->id());
	}

	double Audio::lengthSec() const
	{
		return static_cast<double>(samples()) / samplingRate();
	}

	const Wave& Audio::getWave() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->getWave(m_handle->id());
	}

	void Audio::setPosSec(const double posSec) const
	{
		const int64 sample = static_cast<int64>(posSec * samplingRate());

		setPosSample(sample);
	}

	void Audio::setPosSample(const int64 posSample) const
	{
		Siv3DEngine::Get<ISiv3DAudio>()->setPosSample(m_handle->id(), posSample);
	}

	void Audio::setVolume(const double volume) const
	{
		setVolumeLR(volume, volume);
	}

	void Audio::setVolumeLR(const double left, const double right) const
	{
		const std::pair<double, double> volume =
		{
			Clamp(left, 0.0, 1.0),
			Clamp(right, 0.0, 1.0)
		};

		Siv3DEngine::Get<ISiv3DAudio>()->setVolume(m_handle->id(), volume);
	}

	void Audio::setVolume_dB(const double attenuation_dB) const
	{
		setVolumeLR_dB(attenuation_dB, attenuation_dB);
	}

	void Audio::setVolumeLR_dB(const double attenuationLeft_dB, const double attenuationRight_dB) const
	{
		const double left = std::pow(10.0, attenuationLeft_dB / 20.0);
		const double right = std::pow(10.0, attenuationRight_dB / 20.0);
		setVolumeLR(left, right);
	}

	void Audio::setSpeed(const double speed) const
	{
		Siv3DEngine::Get<ISiv3DAudio>()->setSpeed(m_handle->id(), speed);
	}

	void Audio::setSpeedBySemitone(const int32 semitone) const
	{
		setSpeed(std::exp2(semitone / 12.0));
	}

	double Audio::getSpeed() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->getSpeed(m_handle->id());
	}

	double Audio::getMinSpeed() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->getMinMaxSpeed(m_handle->id()).first;
	}

	double Audio::getMaxSpeed() const
	{
		return Siv3DEngine::Get<ISiv3DAudio>()->getMinMaxSpeed(m_handle->id()).second;
	}
}
