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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "AudioGroupDetail.hpp"
# include <Siv3D/Audio/AudioBus.hpp>
# include <ThirdParty/soloud/include/soloud.h>

namespace s3d
{
	AudioGroup::AudioGroupDetail::AudioGroupDetail() {}

	AudioGroup::AudioGroupDetail::~AudioGroupDetail()
	{
		release();
	}

	void AudioGroup::AudioGroupDetail::create(const Array<Audio>& audios)
	{
		release();

		m_audios = audios;

		if (audios)
		{
			m_groupHandle = SIV3D_ENGINE(Audio)->createAudioGroup(audios.map([](const Audio& a)
				{
					return a.id();
				}), m_handles);
		}
	}

	void AudioGroup::AudioGroupDetail::release()
	{
		if (m_groupHandle)
		{
			SIV3D_ENGINE(Audio)->getSoloud().stop(m_groupHandle);

			SIV3D_ENGINE(Audio)->getSoloud().destroyVoiceGroup(m_groupHandle);

			m_groupHandle = 0;
		}

		m_handles.clear();
		m_audios.clear();
	}

	bool AudioGroup::AudioGroupDetail::isEmpty() const
	{
		return (m_groupHandle != 0);
	}

	size_t AudioGroup::AudioGroupDetail::size() const
	{
		return m_audios.size();
	}

	void AudioGroup::AudioGroupDetail::playAll(const size_t busIndex) const
	{
		if (not m_groupHandle)
		{
			return;
		}
		
		SIV3D_ENGINE(Audio)->getBus(busIndex).annexSoundHandle(m_groupHandle);
		auto& soloud = SIV3D_ENGINE(Audio)->getSoloud();
		soloud.setPause(m_groupHandle, false);
	}

	void AudioGroup::AudioGroupDetail::playAll(const size_t busIndex, const Duration& fadeTime) const
	{
		if (not m_groupHandle)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getBus(busIndex).annexSoundHandle(m_groupHandle);
		auto& soloud = SIV3D_ENGINE(Audio)->getSoloud();
		soloud.setVolume(m_groupHandle, 0.0f);
		soloud.fadeVolume(m_groupHandle, 1.0f, fadeTime.count());
		soloud.setPause(m_groupHandle, false);
	}

	void AudioGroup::AudioGroupDetail::pauseAll() const
	{
		if (not m_groupHandle)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getSoloud().setPause(m_groupHandle, true);
	}

	void AudioGroup::AudioGroupDetail::pauseAll(const Duration& fadeTime) const
	{
		if (not m_groupHandle)
		{
			return;
		}

		auto& soloud = SIV3D_ENGINE(Audio)->getSoloud();
		soloud.fadeVolume(m_groupHandle, 0.0f, fadeTime.count());
		soloud.schedulePause(m_groupHandle, fadeTime.count());
	}

	void AudioGroup::AudioGroupDetail::setVolumeAll(const double volume)
	{
		if (not m_groupHandle)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getSoloud()
			.setVolume(m_groupHandle, static_cast<float>(volume));
	}

	void AudioGroup::AudioGroupDetail::fadeVolumeAll(const double volume, const Duration& fadeTime)
	{
		if (not m_groupHandle)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getSoloud()
			.fadeVolume(m_groupHandle, static_cast<float>(volume), fadeTime.count());
	}

	void AudioGroup::AudioGroupDetail::setVolumeOne(const size_t index, const double volume)
	{
		if (m_handles.size() <= index)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getSoloud()
			.setVolume(m_handles[index], static_cast<float>(volume));
	}

	void AudioGroup::AudioGroupDetail::fadeVolumeOne(const size_t index, const double volume, const Duration& fadeTime)
	{
		if (m_handles.size() <= index)
		{
			return;
		}

		SIV3D_ENGINE(Audio)->getSoloud()
			.fadeVolume(m_handles[index], static_cast<float>(volume), fadeTime.count());
	}

	bool AudioGroup::AudioGroupDetail::isActiveOne(const size_t index) const
	{
		if (m_handles.size() <= index)
		{
			return false;
		}

		return SIV3D_ENGINE(Audio)->getSoloud()
			.isValidVoiceHandle(m_handles[index]);
	}

	size_t AudioGroup::AudioGroupDetail::samplesOne(const size_t index) const
	{
		if (m_handles.size() <= index)
		{
			return 0;
		}

		return m_audios[index].samples();
	}

	int64 AudioGroup::AudioGroupDetail::samplesPlayedOne(const size_t index) const
	{
		if (m_handles.size() <= index)
		{
			return 0;
		}

		const double timePlayed = SIV3D_ENGINE(Audio)->getSoloud().getStreamTime(m_handles[index]);

		return static_cast<int64>(timePlayed * m_audios[index].sampleRate());
	}

	int64 AudioGroup::AudioGroupDetail::posSampleOne(const size_t index) const
	{
		if (m_handles.size() <= index)
		{
			return 0;
		}

		const double posSec = SIV3D_ENGINE(Audio)->getSoloud().getStreamPosition(m_handles[index]);

		return static_cast<int64>(posSec * m_audios[index].sampleRate());
	}
}
