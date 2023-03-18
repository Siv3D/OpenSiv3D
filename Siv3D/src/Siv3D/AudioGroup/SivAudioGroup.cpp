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

# include <Siv3D/AudioGroup.hpp>
# include <Siv3D/AudioGroup/AudioGroupDetail.hpp>

namespace s3d
{
	AudioGroup::AudioGroup()
		: pImpl{ std::make_shared<AudioGroupDetail>() } {}

	AudioGroup::AudioGroup(const Array<Audio>& audios)
		: AudioGroup{}
	{
		pImpl->create(audios);
	}

	AudioGroup::AudioGroup(std::initializer_list<Audio> ilist)
		: AudioGroup{ Array<Audio>{ ilist } } {}

	AudioGroup::~AudioGroup()
	{
		// do nothing
	}

	void AudioGroup::create(const Array<Audio>& audios)
	{
		return pImpl->create(audios);
	}

	void AudioGroup::release()
	{
		pImpl->release();
	}

	bool AudioGroup::isEmpty() const
	{
		return pImpl->isEmpty();
	}
	
	AudioGroup::operator bool() const
	{
		return (not isEmpty());
	}

	size_t AudioGroup::size() const
	{
		return pImpl->size();
	}

	void AudioGroup::playAll(const MixBus busIndex) const
	{
		return pImpl->playAll(FromEnum(busIndex));
	}

	void AudioGroup::playAll(const Duration& fadeTime, const MixBus busIndex) const
	{
		playAll(busIndex, fadeTime);
	}

	void AudioGroup::playAll(const MixBus busIndex, const Duration& fadeTime) const
	{
		return pImpl->playAll(FromEnum(busIndex), fadeTime);
	}

	void AudioGroup::pauseAll() const
	{
		return pImpl->pauseAll();
	}

	void AudioGroup::pauseAll(const Duration& fadeTime) const
	{
		return pImpl->pauseAll(fadeTime);
	}

	void AudioGroup::setVolumeAll(const double volume) const
	{
		pImpl->setVolumeAll(volume);
	}

	void AudioGroup::fadeVolumeAll(const double volume, const Duration& fadeTime) const
	{
		pImpl->fadeVolumeAll(volume, fadeTime);
	}

	void AudioGroup::setVolumeOne(const size_t index, const double volume) const
	{
		pImpl->setVolumeOne(index, volume);
	}

	void AudioGroup::fadeVolumeOne(const size_t index, const double volume, const Duration& fadeTime) const
	{
		pImpl->fadeVolumeOne(index, volume, fadeTime);
	}

	bool AudioGroup::isActiveOne(const size_t index) const
	{
		return pImpl->isActiveOne(index);
	}

	size_t AudioGroup::samplesOne(const size_t index) const
	{
		return pImpl->samplesOne(index);
	}

	int64 AudioGroup::samplesPlayedOne(const size_t index) const
	{
		return pImpl->samplesPlayedOne(index);
	}

	int64 AudioGroup::posSampleOne(const size_t index) const
	{
		return pImpl->posSampleOne(index);
	}
}
