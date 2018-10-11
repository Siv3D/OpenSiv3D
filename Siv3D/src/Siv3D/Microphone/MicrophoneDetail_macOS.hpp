//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/Microphone.hpp>
# include "../../ThirdParty/RtAudio/RtAudio.h"

namespace s3d
{
	class Microphone::MicrophoneDetail
	{
	private:
		
		RtAudio m_device;

		Array<WaveSampleS16> m_buffer;
		
		size_t m_writePos = 0;

		uint32 m_samplingRate = Wave::DefaultSamplingRate;

		bool m_initialized = false;
		
		bool m_isRecording = false;
		
		bool m_loop = true;
		
		static int InputCallback(void*, void *inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data);
		
	public:

		MicrophoneDetail();

		~MicrophoneDetail();

		bool init(const Optional<size_t> deviceID, RecordingFormat format, size_t bufferLength, bool loop);

		bool isAvailable() const;

		void release();

		bool start();

		void stop();

		bool isRecording() const;

		uint32 samplingRate() const;

		const Array<WaveSampleS16>& getBuffer() const;

		size_t posSample() const;
		
		bool onRead(const WaveSampleS16* pSrc, size_t samples);
	};
}

# endif
