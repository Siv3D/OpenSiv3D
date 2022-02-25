//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Audio.hpp"

namespace s3d
{
	class AudioGroup
	{
	public:

		AudioGroup();

		explicit AudioGroup(const Array<Audio>& audios);

		explicit AudioGroup(std::initializer_list<Audio> ilist);

		~AudioGroup();

		void create(const Array<Audio>& audios);

		void release();

		bool isEmpty() const;

		explicit operator bool() const;

		size_t size() const;

		void playAll(MixBus busIndex = MixBus0) const;

		void playAll(const Duration& fadeTime, MixBus busIndex) const;

		void playAll(MixBus busIndex, const Duration& fadeTime) const;

		void pauseAll() const;

		void pauseAll(const Duration& fadeTime) const;

		void setVolumeAll(double volume) const;

		void fadeVolumeAll(double volume, const Duration& fadeTime) const;

		void setVolumeOne(size_t index, double volume) const;

		void fadeVolumeOne(size_t index, double volume, const Duration& fadeTime) const;

		bool isActiveOne(size_t index) const;

		[[nodiscard]]
		size_t samplesOne(size_t index) const;

		[[nodiscard]]
		int64 samplesPlayedOne(size_t index) const;

		[[nodiscard]]
		int64 posSampleOne(size_t index) const;

	private:

		class AudioGroupDetail;

		std::shared_ptr<AudioGroupDetail> pImpl;
	};
}
