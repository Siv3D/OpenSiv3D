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
# include <Siv3D/Microphone.hpp>
# include <Siv3D/Wave.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
# include <ThirdParty/rtaudio/RtAudio.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	class Microphone::MicrophoneDetail
	{
	public:

		MicrophoneDetail();

		~MicrophoneDetail();

		[[nodiscard]]
		bool open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const Duration& duration, Loop loop);

		[[nodiscard]]
		bool open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, size_t bufferLength, Loop loop);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		bool start();

		void stop();

		[[nodiscard]]
		bool isRecording() const;

		[[nodiscard]]
		uint32 microphoneIndex() const;

		[[nodiscard]]
		uint32 getSampleRate() const;

		[[nodiscard]]
		size_t getBufferLength() const;

		[[nodiscard]]
		bool isLoop() const;

		[[nodiscard]]
		const Wave& getBuffer() const;

		[[nodiscard]]
		size_t posSample() const;

	private:

		RtAudio m_device;

		uint32 m_microphoneIndex = 0;

		Wave m_buffer;

		std::atomic<size_t> m_writePos = 0;

		uint32 m_sampleRate = Wave::DefaultSampleRate;

		bool m_initialized = false;

		bool m_isRecording = false;

		bool m_loop = true;

		bool onRead_S16_1ch(const int16*, size_t samples);

		bool onRead_S16_2ch(const WaveSampleS16*, size_t samples);

		bool onRead_F32_1ch(const float*, size_t samples);

		bool onRead_F32_2ch(const WaveSample*, size_t samples);

		static int InputCallback_S16_1ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data);

		static int InputCallback_S16_2ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data);

		static int InputCallback_F32_1ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data);

		static int InputCallback_F32_2ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data);
	};
}
