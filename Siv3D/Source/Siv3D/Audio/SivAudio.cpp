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

# include "../Siv3DEngine.hpp"
# include "IAudio.hpp"
# include "../Profiler/IProfiler.hpp"

namespace s3d
{
	template <>
	AssetHandle<Audio::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetAudio())
		{
			p->release(m_id);
		}
	}

	Audio::Audio()
		: m_handle(std::make_shared<AudioHandle>())
	{

	}

	Audio::Audio(Wave&& wave)
		: m_handle(std::make_shared<AudioHandle>(Siv3DEngine::GetAudio()->create(std::move(wave))))
	{
		ASSET_CREATION();
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

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<SecondsF> loopBegin)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin);
	}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<SecondsF> loopBegin, const Arg::loopEnd_<SecondsF> loopEnd)
		: Audio(std::move(wave))
	{
		setLoop(loopBegin, loopEnd);
	}

	Audio::Audio(const FilePath& path)
		: Audio(Wave(path))
	{

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

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<SecondsF> loopBegin)
		: Audio(path)
	{
		setLoop(loopBegin);
	}

	Audio::Audio(const FilePath& path, const Arg::loopBegin_<SecondsF> loopBegin, const Arg::loopEnd_<SecondsF> loopEnd)
		: Audio(path)
	{
		setLoop(loopBegin, loopEnd);
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
		return m_handle->getID() == AudioHandle::NullID;
	}

	Audio::IDType Audio::id() const
	{
		return m_handle->getID();
	}

	bool Audio::operator ==(const Audio& audio) const
	{
		return m_handle->getID() == audio.m_handle->getID();
	}

	bool Audio::operator !=(const Audio& audio) const
	{
		return m_handle->getID() != audio.m_handle->getID();
	}

	uint32 Audio::samplingRate() const
	{
		return Siv3DEngine::GetAudio()->samplingRate(m_handle->getID());
	}

	size_t Audio::samples() const
	{
		return Siv3DEngine::GetAudio()->samples(m_handle->getID());
	}

	void Audio::setLoop(const bool loop)
	{
		Siv3DEngine::GetAudio()->setLoop(
			m_handle->getID(),
			loop,
			0,
			loop ? samples() - 1 : 0);
	}

	void Audio::setLoop(const Arg::loopBegin_<uint64> loopBegin)
	{
		assert(*loopBegin < samples());

		const uint64 loopBeginSample = *loopBegin;
		const uint64 loopEndSample = samples() - 1;

		Siv3DEngine::GetAudio()->setLoop(
			m_handle->getID(),
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

		Siv3DEngine::GetAudio()->setLoop(
			m_handle->getID(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	void Audio::setLoop(const Arg::loopBegin_<SecondsF> loopBegin)
	{
		const uint64 loopBeginSample = static_cast<uint64>(samplingRate() * std::max(loopBegin->count(), 0.0L));
		const uint64 loopEndSample = samples() - 1;

		assert(loopBeginSample < loopEndSample);

		Siv3DEngine::GetAudio()->setLoop(
			m_handle->getID(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	void Audio::setLoop(const Arg::loopBegin_<SecondsF> loopBegin, const Arg::loopEnd_<SecondsF> loopEnd)
	{
		const uint64 loopBeginSample = static_cast<uint64>(samplingRate() * std::max(loopBegin->count(), 0.0L));
		const uint64 loopEndSample = std::min<uint64>(static_cast<uint64>(samplingRate() * std::max(loopEnd->count(), 0.0L)), samples() - 1);

		assert(loopBeginSample < loopEndSample);

		Siv3DEngine::GetAudio()->setLoop(
			m_handle->getID(),
			true,
			loopBeginSample,
			loopEndSample);
	}

	bool Audio::play(const SecondsF& fadeinDuration) const
	{
		return Siv3DEngine::GetAudio()->play(m_handle->getID(), fadeinDuration);
	}

	void Audio::pause(const SecondsF& fadeoutDuration) const
	{
		return Siv3DEngine::GetAudio()->pause(m_handle->getID(), fadeoutDuration);
	}

	void Audio::stop(const SecondsF& fadeoutDuration) const
	{
		Siv3DEngine::GetAudio()->stop(m_handle->getID(), fadeoutDuration);
	}

	bool Audio::isPlaying() const
	{
		return Siv3DEngine::GetAudio()->isPlaying(m_handle->getID());
	}

	bool Audio::isPaused() const
	{
		return Siv3DEngine::GetAudio()->isPaused(m_handle->getID());
	}

	int64 Audio::posSample() const
	{
		return Siv3DEngine::GetAudio()->posSample(m_handle->getID());
	}

	int64 Audio::streamPosSample() const
	{
		return Siv3DEngine::GetAudio()->streamPosSample(m_handle->getID());
	}

	double Audio::lengthSec() const
	{
		return static_cast<double>(samples()) / samplingRate();
	}

	const Wave& Audio::getWave() const
	{
		return Siv3DEngine::GetAudio()->getWave(m_handle->getID());
	}

	int64 Audio::samplesPlayed() const
	{
		return Siv3DEngine::GetAudio()->samplesPlayed(m_handle->getID());
	}

	void Audio::setVolumeLR(const double left, const double right) const
	{
		const std::pair<double, double> volume =
		{
			Clamp(left, 0.0, 1.0),
			Clamp(right, 0.0, 1.0)
		};

		Siv3DEngine::GetAudio()->setVolume(m_handle->getID(), volume);
	}
}
