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
# include <AL/al.h>
# include <AL/alc.h>
# include <Siv3D/Microphone.hpp>
# include <Siv3D/Wave.hpp>

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

		ALCdevice* m_device;

		uint32 m_microphoneIndex = 0;
		
		Wave m_buffer;

		Array<int16> m_nativeBuffer;
		
		size_t m_writePos = 0;
		
		uint32 m_sampleRate = Wave::DefaultSampleRate;
		
		bool m_initialized = false;
		
		bool m_isRecording = false;
		
		bool m_loop = true;

		bool onRead_S16_1ch();

		static void InputCallback_S16_1ch(void*);
	};
}
