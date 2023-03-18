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
# include <Siv3D/AudioGroup.hpp>

namespace s3d
{
	class AudioGroup::AudioGroupDetail
	{
	public:

		AudioGroupDetail();

		~AudioGroupDetail();

		void create(const Array<Audio>& audios);

		void release();

		bool isEmpty() const;

		size_t size() const;

		void playAll(size_t busIndex) const;

		void playAll(size_t busIndex, const Duration& fadeTime) const;

		void pauseAll() const;

		void pauseAll(const Duration& fadeTime) const;

		void setVolumeAll(double volume);

		void fadeVolumeAll(double volume, const Duration& fadeTime);

		void setVolumeOne(size_t index, double volume);

		void fadeVolumeOne(size_t index, double volume, const Duration& fadeTime);

		bool isActiveOne(size_t index) const;

		size_t samplesOne(size_t index) const;

		int64 samplesPlayedOne(size_t index) const;

		int64 posSampleOne(size_t index) const;

	private:

		Array<Audio> m_audios;

		Array<uint32> m_handles;

		uint32 m_groupHandle = 0;
	};
}
