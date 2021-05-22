//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>
# include <ThirdParty/soloud/include/soloud.h>

namespace s3d
{
	class AudioData
	{
	public:

		struct Null {};

		AudioData() = default;

		explicit AudioData(Null);

		AudioData(Wave&& wave, const Optional<AudioLoopTiming>& loop);

		AudioData(FilePathView path);

		AudioData(FilePathView path, uint64 loopBegin);

		~AudioData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		uint32 sampleRate() const noexcept;

		[[nodiscard]]
		uint32 samples() const noexcept;

		[[nodiscard]]
		const AudioLoopTiming& loopTiming() const noexcept;

		[[nodiscard]]
		bool isStreaming() const noexcept;

	private:

		std::unique_ptr<SoLoud::AudioSource> m_audioSource;

		Wave m_wave;

		uint32 m_sampleRate = 0;

		uint32 m_lengthSample = 0;

		AudioLoopTiming m_loopTiming;

		bool m_isStreaming = false;

		bool m_loop = false;

		SoLoud::handle m_handle = 0;

		Array<SoLoud::handle> m_shotHandles;

		bool m_initialized = false;
	};
}
