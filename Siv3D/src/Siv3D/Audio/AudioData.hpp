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

		explicit AudioData(Null, SoLoud::Soloud* pSoloud);

		AudioData(SoLoud::Soloud* pSoloud, Wave&& wave, const Optional<AudioLoopTiming>& loop);

		AudioData(SoLoud::Soloud* pSoloud, FilePathView path);

		AudioData(SoLoud::Soloud* pSoloud, FilePathView path, uint64 loopBegin);

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

		[[nodiscard]]
		int64 samplesPlayed() const;

		[[nodiscard]]
		bool isActive() const;

		[[nodiscard]]
		bool isPlaying() const;

		[[nodiscard]]
		bool isPaused() const;

		[[nodiscard]]
		bool isLoop() const;

		void setLoop(bool loop);

		void setLoopPoint(const Duration& loopBegin);

		void play(size_t busIndex);

		void play(size_t busIndex, const Duration& duration);

		void pause();

		void pause(const Duration& duration);

		void stop();

		void stop(const Duration& duration);




		[[nodiscard]]
		double posSec() const;

		void seekTo(const Duration& pos);

		[[nodiscard]]
		double getVolume() const;

		void setVolume(double volume);

		void fadeVolume(double volume, const Duration& time);

		[[nodiscard]]
		double getPan() const;

		void setPan(double pan);

		void fadePan(double pan, const Duration& time);

		double getSpeed() const;

		void setSpeed(double speed);

		void fadeSpeed(double speed, const Duration& time);

	private:

		std::unique_ptr<SoLoud::AudioSource> m_audioSource;

		SoLoud::Soloud* m_pSoloud = nullptr;

		Wave m_wave;

		uint32 m_sampleRate = 0;

		uint32 m_lengthSample = 0;

		AudioLoopTiming m_loopTiming;

		bool m_isStreaming = false;

		bool m_loop = false;

		SoLoud::handle m_handle = 0;

		uint32 m_busIndex = 0;

		struct Reserved
		{
			Duration pos = SecondsF{ 0.0 };
			
			double volume = 1.0;

			double pan = 0.0;

			double speed = 1.0;

		} m_reservedSetting = {};

		Array<SoLoud::handle> m_shotHandles;

		bool m_initialized = false;
	};
}
